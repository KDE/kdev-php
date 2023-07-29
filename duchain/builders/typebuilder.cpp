/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "typebuilder.h"

#include <language/duchain/identifier.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/arraytype.h>
#include "../declarations/classdeclaration.h"
#include "../types/integraltypeextended.h"
#include "../types/structuretype.h"
#include <duchaindebug.h>

#include "editorintegrator.h"
#include "parsesession.h"
#include "phpdebugvisitor.h"
#include "expressionparser.h"
#include "expressionvisitor.h"
#include "../declarations/classmethoddeclaration.h"
#include <language/duchain/types/unsuretype.h>

using namespace KDevelop;
namespace Php
{

TypeBuilder::TypeBuilder()
    : TypeBuilderBase()
    , m_gotTypeFromDocComment(false)
    , m_gotTypeFromTypeHint(false)
    , m_gotReturnTypeFromDocComment(false)
{
}

TypeBuilder::~TypeBuilder()
{
}

AbstractType::Ptr TypeBuilder::parseType(QString type, AstNode* node)
{
    type = type.trimmed();

    if (type.contains('|')) {
        QList<AbstractType::Ptr> types;
        foreach (const QString& t, type.split('|')) {
            AbstractType::Ptr subType = parseType(t, node);
            if (!(subType.dynamicCast<IntegralType>() && subType.staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed)) {
                types << parseType(t, node);
            }
        }
        UnsureType::Ptr ret(new UnsureType());
        foreach (const AbstractType::Ptr& t, types) {
            ret->addType(t->indexed());
        }
        return ret;
    }

    if (type.endsWith(QLatin1String("[]"))) {
        KDevelop::ArrayType* a_type = new KDevelop::ArrayType();
        a_type->setElementType(parseSimpleType(type.left(type.length() - 2), node));
        return AbstractType::Ptr(a_type);
    } else {
        return parseSimpleType(type, node);
    }
}

AbstractType::Ptr TypeBuilder::parseSimpleType(QString type, AstNode* node)
{
    Q_UNUSED(node)
    uint iType = 0;
    if (!type.compare(QLatin1String("int"), Qt::CaseInsensitive) || !type.compare(QLatin1String("integer"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeInt;
    } else if (!type.compare(QLatin1String("float"), Qt::CaseInsensitive) || !type.compare(QLatin1String("double"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeFloat;
    } else if (!type.compare(QLatin1String("bool"), Qt::CaseInsensitive) || !type.compare(QLatin1String("boolean"), Qt::CaseInsensitive)
            || !type.compare(QLatin1String("false"), Qt::CaseInsensitive) || !type.compare(QLatin1String("true"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeBoolean;
    } else if (!type.compare(QLatin1String("string"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeString;
    } else if (!type.compare(QLatin1String("mixed"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeMixed;
    } else if (!type.compare(QLatin1String("array"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeArray;
    } else if (!type.compare(QLatin1String("resource"), Qt::CaseInsensitive)) {
        return AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeResource));
    } else if (!type.compare(QLatin1String("null"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeNull;
    } else if (!type.compare(QLatin1String("void"), Qt::CaseInsensitive)) {
        iType = IntegralType::TypeVoid;
    } else if (!type.compare(QLatin1String("self"), Qt::CaseInsensitive)
            || !type.compare(QLatin1String("this"), Qt::CaseInsensitive) || !type.compare(QLatin1String("static"), Qt::CaseInsensitive)) {
        DUChainReadLocker lock(DUChain::lock());
        if ( currentContext()->type() == DUContext::Class && currentContext()->owner() ) {
            return currentContext()->owner()->abstractType();
        }
    } else {
        if (!type.compare(QLatin1String("object"), Qt::CaseInsensitive)) {
            return AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeObject));
        }

        QualifiedIdentifier typehint = QualifiedIdentifier(type.toLower().replace(QLatin1Literal("\\"), QLatin1Literal("::")));

        if (typehint.toString().startsWith(QLatin1Literal("::"))) {
            typehint.setExplicitlyGlobal(true);
        }

        //don't use openTypeFromName as it uses cursor for findDeclarations
        DeclarationPointer decl = findDeclarationImport(ClassDeclarationType, typehint);

        if (decl && decl->abstractType()) {
            return decl->abstractType();
        }
        iType = IntegralType::TypeMixed;
    }
    AbstractType::Ptr ret(new IntegralType(iType));
    //qCDebug(DUCHAIN) << type << ret->toString();
    return ret;
}

AbstractType::Ptr TypeBuilder::injectParseType(QString type, AstNode* node)
{
    AbstractType::Ptr ret = parseType(type, node);
    injectType(ret);
    //qCDebug(DUCHAIN) << type << ret->toString();
    return ret;
}

/**
 * Find all (or only one - see @p docCommentName) values for a given needle
 * in a doc-comment. Needle has to start a line in the doccomment,
 * i.e.:
 *
 *  * @docCommentName value
 *
 * or
 *
 *  /// @docCommentName value
 */
QStringList findInDocComment(const QString &docComment, const QString &docCommentName, const bool onlyOne)
{
    QStringList matches;
    // optimization that does not require potentially slow regexps
    // old code was something like this:
    /*
    if (!docComment.isEmpty()) {
        QRegExp rx("\\*\\s+@param\\s([^\\s]*)");
        int pos = 0;
        while ((pos = rx.indexIn(docComment, pos)) != -1) {
            ret << parseType(rx.cap(1), node);
            pos += rx.matchedLength();
        }
    }
    */

    for ( int i = 0, size = docComment.size(); i < size; ++i ) {
        if ( docComment[i].isSpace() || docComment[i] == '*' || docComment[i] == '/' ) {
            // skip whitespace and comment-marker at beginning of line
            continue;
        } else if ( docComment[i] == '@' && docComment.midRef(i + 1, docCommentName.size()) == docCommentName ) {
            // find @return or similar
            i += docCommentName.size() + 1;
            // skip whitespace (at least one is required)
            if ( i >= size || !docComment[i].isSpace() ) {
                // skip to next line
                i = docComment.indexOf('\n', i);
                if ( i == -1 ) {
                    break;
                }
                continue;
            } else if ( docComment[i] == '\n' ) {
                continue;
            }
            ++i; // at least one whitespace
            while ( i < size && docComment[i].isSpace() ) {
                ++i;
            }
            // finally get the typename
            int pos = i;
            while ( pos < size && !docComment[pos].isSpace() ) {
                ++pos;
            }
            if ( pos > i ) {
                matches << docComment.mid(i, pos - i);
                if ( onlyOne ) {
                    break;
                } else {
                    i = pos;
                }
            }
        }
        // skip to next line
        i = docComment.indexOf('\n', i);
        if ( i == -1 ) {
            break;
        }
    }

    return matches;
}

AbstractType::Ptr TypeBuilder::parseDocComment(AstNode* node, const QString& docCommentName)
{
    m_gotTypeFromDocComment = false;
    const QString& docComment = editor()->parseSession()->docComment(node->startToken);

    if ( !docComment.isEmpty() ) {
        const QStringList& matches = findInDocComment(docComment, docCommentName, true);
        if ( !matches.isEmpty() ) {
            AbstractType::Ptr type;
            if (matches.first() == QLatin1String("$this")) {
                DUChainReadLocker lock(DUChain::lock());
                if (currentContext()->owner()) {
                    type = currentContext()->owner()->abstractType();
                }
            } else {
                type = injectParseType(matches.first(), node);
            }
            if (type) {
                m_gotTypeFromDocComment = true;
            }
            return type;
        }
    }
    return AbstractType::Ptr();
}

QList<AbstractType::Ptr> TypeBuilder::parseDocCommentParams(AstNode* node)
{
    QList<AbstractType::Ptr> ret;
    QString docComment = editor()->parseSession()->docComment(node->startToken);
    if ( !docComment.isEmpty() ) {
        const QStringList& matches = findInDocComment(docComment, QStringLiteral("param"), false);
        if ( !matches.isEmpty() ) {
            ret.reserve(matches.size());
            foreach ( const QString& type, matches ) {
                ret << parseType(type, node);
            }
        }
    }
    return ret;
}

AbstractType::Ptr TypeBuilder::getTypeForNode(AstNode* node)
{

    AbstractType::Ptr type;
    if (node) {
        type = parseDocComment(node, QStringLiteral("var")); //we fully trust in @var typehint and don't try to evaluate ourself
        if (!type) {
            node->ducontext = currentContext();
            ExpressionParser ep;
            ep.setCreateProblems(true);
            ExpressionEvaluationResult res = ep.evaluateType(node, editor());
            if (res.hadUnresolvedIdentifiers()) {
                m_hadUnresolvedIdentifiers = true;
            }
            type = res.type();
        }
    }
    if (!type) {
        type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
    }
    return type;
}

void TypeBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst* node)
{
    // the predeclaration builder should have set up a type already
    // and the declarationbuilder should have set that as current type
    Q_ASSERT(hasCurrentType() && currentType<StructureType>());

    TypeBuilderBase::visitClassDeclarationStatement(node);
}

void TypeBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node)
{
    // the predeclaration builder should have set up a type already
    // and the declarationbuilder should have set that as current type
    Q_ASSERT(hasCurrentType() && currentType<StructureType>());

    TypeBuilderBase::visitInterfaceDeclarationStatement(node);
}

void TypeBuilder::visitTraitDeclarationStatement(TraitDeclarationStatementAst* node)
{
    // the predeclaration builder should have set up a type already
    // and the declarationbuilder should have set that as current type
    Q_ASSERT(hasCurrentType() && currentType<StructureType>());

    TypeBuilderBase::visitTraitDeclarationStatement(node);
}

void TypeBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration
        m_currentFunctionParams = parseDocCommentParams(node);

        FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());
        openType(functionType);
        openContextType(functionType);

        AbstractType::Ptr phpdocReturnType = parseDocComment(node, QStringLiteral("return"));
        functionType->setReturnType(returnType(node->returnType, phpdocReturnType, editor(), currentContext()));
        m_gotReturnTypeFromDocComment = functionType->returnType();
        updateCurrentType();

        TypeBuilderBase::visitClassStatement(node);
        if (currentType<FunctionType>() && !currentType<FunctionType>()->returnType()) {
            currentType<FunctionType>()->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
        }
        closeContextType();
        closeType();
    } else if (node->constsSequence) {
        //class constant
        TypeBuilderBase::visitClassStatement(node);
    } else if (node->propertyType) {
        m_gotTypeFromTypeHint = true;
        AbstractType::Ptr phpDocTypehint = parseDocComment(node, QStringLiteral("var"));
        AbstractType::Ptr type = propertyType(node, phpDocTypehint, editor(), currentContext());

        injectType(type);
        TypeBuilderBase::visitClassStatement(node);
        clearLastType();
        m_gotTypeFromTypeHint = false;

        if (m_gotTypeFromDocComment) {
            clearLastType();
            m_gotTypeFromDocComment = false;
        }
    } else {
        //member-variable
        parseDocComment(node, QStringLiteral("var"));
        TypeBuilderBase::visitClassStatement(node);
        if (m_gotTypeFromDocComment) {
            clearLastType();
            m_gotTypeFromDocComment = false;
        }
    }
}

void TypeBuilder::visitClassVariable(ClassVariableAst *node)
{
    if (!m_gotTypeFromDocComment && !m_gotTypeFromTypeHint) {
        if (node->value) {
            openAbstractType(getTypeForNode(node->value));
        } else {
            openAbstractType(AbstractType::Ptr(new IntegralType(IntegralType::TypeNull)));
        }

        TypeBuilderBase::visitClassVariable(node);

        closeType();
    } else {
        TypeBuilderBase::visitClassVariable(node);
    }
}

void TypeBuilder::visitConstantDeclaration(ConstantDeclarationAst* node)
{
    if (!m_gotTypeFromDocComment || !currentAbstractType()) {
        AbstractType::Ptr type = getTypeForNode(node->scalar);
        type->setModifiers(type->modifiers() | AbstractType::ConstModifier);
        openAbstractType(type);

        TypeBuilderBase::visitConstantDeclaration(node);

        closeType();
    } else {
        currentAbstractType()->setModifiers(currentAbstractType()->modifiers() & AbstractType::ConstModifier);
        TypeBuilderBase::visitConstantDeclaration(node);
    }
}

void TypeBuilder::visitClassConstantDeclaration(ClassConstantDeclarationAst* node)
{
    if (!m_gotTypeFromDocComment || !currentAbstractType()) {
        AbstractType::Ptr type = getTypeForNode(node->scalar);
        type->setModifiers(type->modifiers() | AbstractType::ConstModifier);
        openAbstractType(type);

        TypeBuilderBase::visitClassConstantDeclaration(node);

        closeType();
    } else {
        currentAbstractType()->setModifiers(currentAbstractType()->modifiers() & AbstractType::ConstModifier);
        TypeBuilderBase::visitClassConstantDeclaration(node);
    }
}

void TypeBuilder::visitParameter(ParameterAst *node)
{
    AbstractType::Ptr phpDocTypehint;
    if (m_currentFunctionParams.count() > currentType<FunctionType>()->arguments().count()) {
        phpDocTypehint = m_currentFunctionParams.at(currentType<FunctionType>()->arguments().count());
    }

    AbstractType::Ptr type = parameterType(node, phpDocTypehint, editor(), currentContext());

    if (node->defaultValue) {
        QString symbol = m_editor->parseSession()->symbol(node->defaultValue);

        if (node->parameterType && node->parameterType->typehint &&
                symbol.compare(QLatin1String("null"), Qt::CaseInsensitive) != 0 &&
                type->contains(new IntegralTypeExtended(IntegralTypeExtended::TypeObject))) {
            reportError(i18n("Default value for parameters with an object type can only be NULL."), node->defaultValue);
        }
    }

    openAbstractType(type);
    TypeBuilderBase::visitParameter(node);
    closeType();
    DUChainWriteLocker lock(DUChain::lock());
    currentType<FunctionType>()->addArgument(type);
}

void TypeBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    m_currentFunctionParams = parseDocCommentParams(node);
    // the predeclarationbuilder should have already built the type
    // and the declarationbuilder should have set it to open
    Q_ASSERT(hasCurrentType());
    FunctionType::Ptr type = currentType<FunctionType>();
    Q_ASSERT(type);

    openContextType(type);

    AbstractType::Ptr phpdocReturnType = parseDocComment(node, QStringLiteral("return"));
    type->setReturnType(returnType(node->returnType, phpdocReturnType, editor(), currentContext()));
    m_gotReturnTypeFromDocComment = type->returnType();

    updateCurrentType();

    TypeBuilderBase::visitFunctionDeclarationStatement(node);

    if (!type->returnType()) {
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    }

    closeContextType();
}

void TypeBuilder::visitClosure(ClosureAst* node)
{
    m_currentFunctionParams = parseDocCommentParams(node);
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());
    openType(type);
    openContextType(type);

    AbstractType::Ptr phpdocReturnType = parseDocComment(node, QStringLiteral("return"));
    type->setReturnType(returnType(node->returnType, phpdocReturnType, editor(), currentContext()));
    m_gotReturnTypeFromDocComment = type->returnType();

    updateCurrentType();

    TypeBuilderBase::visitClosure(node);

    if (!type->returnType()) {
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    }
    closeContextType();
    closeType();
}

void TypeBuilder::visitAssignmentExpression(AssignmentExpressionAst* node)
{
    // performance: only try to find type when we are actually in an assignment expr
    if (node->assignmentExpression || node->assignmentExpressionEqual) {
        openAbstractType(getTypeForNode(node));
    }

    TypeBuilderBase::visitAssignmentExpression(node);

    if (node->assignmentExpression || node->assignmentExpressionEqual) {
        closeType();
    }
}

void TypeBuilder::visitStaticVar(StaticVarAst *node)
{
    openAbstractType(getTypeForNode(node->value));

    TypeBuilderBase::visitStaticVar(node);

    closeType();
}

void TypeBuilder::visitStatement(StatementAst* node)
{
    TypeBuilderBase::visitStatement(node);
    if ( !m_gotReturnTypeFromDocComment && node->returnExpr && hasCurrentType() && currentType<FunctionType>())
    {
        FunctionType::Ptr ft = currentType<FunctionType>();
        // qCDebug(DUCHAIN) << "return" << (ft->returnType() ? ft->returnType()->toString() : "none") << lastType()->toString();
        AbstractType::Ptr type = getTypeForNode(node->returnExpr);
        if (type) {
            // ignore references for return values, PHP does so as well
            if ( auto rType = type.dynamicCast<ReferenceType>() ) {
                type = rType->baseType();
            }
            if (ft->returnType() && !ft->returnType()->equals(type.data())) {
                bool existingTypeIsCallable = ft->returnType().dynamicCast<IntegralTypeExtended>() &&
                    ft->returnType().staticCast<IntegralTypeExtended>()->dataType() == IntegralTypeExtended::TypeCallable;
                bool newTypeIsCallable = type.dynamicCast<IntegralTypeExtended>() &&
                    type.staticCast<IntegralTypeExtended>()->dataType() == IntegralTypeExtended::TypeCallable;
                if (ft->returnType().dynamicCast<IntegralType>()
                    && ft->returnType().staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed)
                {
                    //don't add TypeMixed to the list, just ignore
                    ft->setReturnType(type);
                } else if ((existingTypeIsCallable && type.dynamicCast<FunctionType>()) || (newTypeIsCallable && ft->returnType().dynamicCast<FunctionType>())) {
                    //If one type is "callable" and the other a real function, the result is just a "callable".
                    ft->setReturnType(AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeCallable)));
                } else {
                    UnsureType::Ptr retT;
                    if (ft->returnType().dynamicCast<UnsureType>()) {
                        //qCDebug(DUCHAIN) << "we already have an unsure type";
                        retT = ft->returnType().staticCast<UnsureType>();
                        if (type.dynamicCast<UnsureType>()) {
                            //qCDebug(DUCHAIN) << "add multiple to returnType";
                            FOREACH_FUNCTION(const IndexedType& t, type.staticCast<UnsureType>()->types) {
                                retT->addType(t);
                            }
                        } else {
                            //qCDebug(DUCHAIN) << "add to returnType";
                            retT->addType(type->indexed());
                        }
                    } else {
                        if (type.dynamicCast<UnsureType>()) {
                            retT = type.staticCast<UnsureType>();
                        } else {
                            retT = new UnsureType();
                            retT->addType(type->indexed());
                        }
                        retT->addType(ft->returnType()->indexed());
                    }
                    ft->setReturnType(retT);
                }
            } else {
                ft->setReturnType(type);
            }
            updateCurrentType();
        }
    }

    AstNode *foreachNode = nullptr;
    if (node->foreachVar) {
        foreachNode = node->foreachVar;
    } else if (node->foreachExpr) {
        foreachNode = node->foreachExpr;
    } else if (node->foreachExprAsVar) {
        foreachNode = node->foreachExprAsVar;
    }
    if (foreachNode) {
        ExpressionVisitor v(editor());
        foreachNode->ducontext = currentContext();
        v.visitNode(foreachNode);
        DUChainReadLocker lock(DUChain::lock());
        bool foundType = false;
        if (auto type = v.result().type().dynamicCast<StructureType>()) {
            ClassDeclaration *classDec = dynamic_cast<ClassDeclaration*>(type->declaration(currentContext()->topContext()));
            if (!classDec) {
                ///FIXME: this is just a hack for https://bugs.kde.org/show_bug.cgi?id=269369
                ///       a proper fix needs full fledged two-pass, i.e. get rid of PreDeclarationBuilder
                // 0 == global lookup and the declaration is found again...
                classDec = dynamic_cast<ClassDeclaration*>(type->declaration(nullptr));
            }
            if (classDec) {
                /// Qualified identifier for 'iterator'
                static QualifiedIdentifier iteratorQId(QStringLiteral("iterator"));
                iteratorQId.setExplicitlyGlobal(true);
                ClassDeclaration* iteratorDecl = dynamic_cast<ClassDeclaration*>(
                    findDeclarationImport(ClassDeclarationType, iteratorQId).data()
                );
                Q_ASSERT(iteratorDecl);
                if (classDec->isPublicBaseClass(iteratorDecl, currentContext()->topContext())) {
                    /// Qualified identifier for 'current'
                    static const QualifiedIdentifier currentQId(QStringLiteral("current"));
                    auto classContext = classDec->internalContext();
                    if (classContext) {
                        foreach (Declaration *d, classContext->findDeclarations(currentQId)) {
                            if (!dynamic_cast<ClassMethodDeclaration*>(d)) continue;
                            Q_ASSERT(d->type<FunctionType>());
                            injectType(d->type<FunctionType>()->returnType());
                            foundType = true;
                            // qCDebug(DUCHAIN) << "that's it: " << d->type<FunctionType>()->returnType()->toString();
                        }
                    }
                }
            }
        } else if ( auto a_type = v.result().type().dynamicCast<ArrayType>() ) {
            injectType(a_type->elementType());
            foundType = true;
        }

        if (!foundType) {
            injectType(AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed)));
        }
    }
}

void TypeBuilder::visitCatchItem(Php::CatchItemAst *node)
{
    TypeBuilderBase::visitCatchItem(node);

    const KDevPG::ListNode< NamespacedIdentifierAst* >* it = node->catchClassSequence->front();

    if (node->catchClassSequence->count() == 1) {
        DeclarationPointer dec = findDeclarationImport(ClassDeclarationType,
                                                       identifierForNamespace(it->element, m_editor));

        if (dec && dec->abstractType()) {
            openAbstractType(dec->abstractType());
            closeType();
        }
    } else {
        UnsureType::Ptr decs(new UnsureType());

        forever {
            DeclarationPointer dec = findDeclarationImport(ClassDeclarationType,
                                                           identifierForNamespace(it->element, m_editor));

            if (dec && dec->abstractType()) {
                decs->addType(dec->abstractType()->indexed());
            }

            if ( it->hasNext() ) {
                it = it->next;
            } else {
                break;
            }
        }

        if (decs) {
            openAbstractType(decs);
            closeType();
        }
    }
}

void TypeBuilder::visitVarExpression(Php::VarExpressionAst *node)
{
    if (hasCurrentContextType() && node->isGenerator != -1 && !m_gotReturnTypeFromDocComment) {
        auto ft = currentContextType().dynamicCast<FunctionType>();
        static QualifiedIdentifier generatorQId(QStringLiteral("generator"));
        generatorQId.setExplicitlyGlobal(true);
        DeclarationPointer generatorDecl = findDeclarationImport(ClassDeclarationType, generatorQId);

        if (ft && generatorDecl) {
            AbstractType::Ptr generatorType = generatorDecl->abstractType();

            if (generatorType) {
                ft->setReturnType(generatorType);
            }
        }

        updateCurrentType();
    }

    TypeBuilderBase::visitVarExpression(node);
}

void TypeBuilder::updateCurrentType()
{
    // do nothing
}

}

