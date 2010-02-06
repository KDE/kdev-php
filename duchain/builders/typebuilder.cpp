/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "typebuilder.h"

#include <ktexteditor/smartrange.h>

#include <language/duchain/identifier.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/integraltype.h>
#include "../declarations/classdeclaration.h"
#include "../types/integraltypeextended.h"
#include "../types/structuretype.h"

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
    , m_gotReturnTypeFromDocComment(false)
{
}

TypeBuilder::~TypeBuilder()
{
}

AbstractType::Ptr TypeBuilder::parseType(QString type, AstNode* node)
{
    uint iType = 0;
    type = type.trimmed();
    QString lType = type.toLower();
    if (lType == "int" || lType == "integer") {
        iType = IntegralType::TypeInt;
    } else if (lType == "float" || lType == "double") {
        iType = IntegralType::TypeFloat;
    } else if (lType == "bool" || lType == "boolean" || lType == "false" || lType == "true") {
        iType = IntegralType::TypeBoolean;
    } else if (lType == "string") {
        iType = IntegralType::TypeString;
    } else if (lType == "mixed") {
        iType = IntegralType::TypeMixed;
    } else if (lType == "array") {
        iType = IntegralType::TypeArray;
    } else if (lType == "resource") {
        return AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeResource));
    } else if (lType == "object") {
        //TODO
        iType = IntegralType::TypeMixed;
    } else if (lType == "null") {
        iType = IntegralType::TypeNull;
    } else if (lType == "void") {
        iType = IntegralType::TypeVoid;
    } else if (lType == "self" || lType == "this") {
        DUChainReadLocker lock(DUChain::lock());
        if ( currentContext()->type() == DUContext::Class && currentContext()->owner() ) {
            return currentContext()->owner()->abstractType();
        }
    } else {
        //don't use openTypeFromName as it uses cursor for findDeclarations
        Declaration* decl = findDeclarationImport(ClassDeclarationType, QualifiedIdentifier(type.toLower()), node);
        if (decl && decl->abstractType()) {
            return decl->abstractType();
        }
        if (type.contains('|')) {
            QList<AbstractType::Ptr> types;
            foreach (const QString& t, type.split('|')) {
                AbstractType::Ptr subType = parseType(t, node);
                if (!(IntegralType::Ptr::dynamicCast(subType) && IntegralType::Ptr::staticCast(subType)->dataType() == IntegralType::TypeMixed)) {
                    types << parseType(t, node);
                }
            }
            if (!type.isEmpty()) {
                UnsureType::Ptr ret(new UnsureType());
                foreach (const AbstractType::Ptr& t, types) {
                    ret->addType(t->indexed());
                }
                //kDebug() << type << ret->toString();
                return AbstractType::Ptr::staticCast(ret);
            }
        }
        iType = IntegralType::TypeMixed;
    }
    AbstractType::Ptr ret(new IntegralType(iType));
    //kDebug() << type << ret->toString();
    return ret;
}

AbstractType::Ptr TypeBuilder::injectParseType(QString type, AstNode* node)
{
    AbstractType::Ptr ret = parseType(type, node);
    injectType(ret);
    //kDebug() << type << ret->toString();
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
            if (matches.first() == "$this") {
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
        const QStringList& matches = findInDocComment(docComment, "param", false);
        if ( !matches.isEmpty() ) {
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
        node->ducontext = currentContext();
        ExpressionParser ep;
        ep.setCreateProblems(true);
        ExpressionEvaluationResult res = ep.evaluateType(node, editor());
        type = res.type();
    }
    if (!type) {
        type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
    }
    return type;
}

FunctionType::Ptr TypeBuilder::openFunctionType(AstNode* node)
{
    FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());

    openType(functionType);

    functionType->setReturnType(parseDocComment(node, "return"));
    m_gotReturnTypeFromDocComment = functionType->returnType();
    updateCurrentType();

    return functionType;
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

void TypeBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration
        m_currentFunctionParams = parseDocCommentParams(node);
        openFunctionType(node);
        TypeBuilderBase::visitClassStatement(node);
        if (currentType<FunctionType>() && !currentType<FunctionType>()->returnType()) {
            currentType<FunctionType>()->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
        }
        closeType();
    } else {
        //member-variable
        parseDocComment(node, "var");
        TypeBuilderBase::visitClassStatement(node);
        if (m_gotTypeFromDocComment) {
            clearLastType();
            m_gotTypeFromDocComment = false;
        }
    }
}

void TypeBuilder::visitClassVariable(ClassVariableAst *node)
{
    if (!m_gotTypeFromDocComment) {
        openAbstractType(getTypeForNode(node->value));

        TypeBuilderBase::visitClassVariable(node);

        closeType();
    } else {
        TypeBuilderBase::visitClassVariable(node);
    }
}

void TypeBuilder::visitClassConstantDeclaration(ClassConstantDeclarationAst* node)
{
    if (!m_gotTypeFromDocComment) {
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
    AbstractType::Ptr type;
    if (node->parameterType) {
        //don't use openTypeFromName as it uses cursor for findDeclarations
        Declaration* decl = findDeclarationImport(ClassDeclarationType, node->parameterType);
        if (decl) type = decl->abstractType();
    } else if (node->arrayType != -1) {
        type = AbstractType::Ptr(new IntegralType(IntegralType::TypeArray));
    }
    if (!type) {
        if (m_currentFunctionParams.count() > currentType<FunctionType>()->arguments().count()) {
            type = m_currentFunctionParams.at(currentType<FunctionType>()->arguments().count());
        } else {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
        }
    }

    if ( node->isRef != -1 ) {
      ReferenceType::Ptr p( new ReferenceType() );
      p->setBaseType( type );

      type = p.cast<AbstractType>();
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

    type->setReturnType(parseDocComment(node, "return"));
    m_gotReturnTypeFromDocComment = type->returnType();

    updateCurrentType();

    TypeBuilderBase::visitFunctionDeclarationStatement(node);

    if (!type->returnType()) {
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    }
}

void TypeBuilder::visitExpr(ExprAst *node)
{
    openAbstractType(getTypeForNode(node));

    TypeBuilderBase::visitExpr(node);

    closeType();
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
    if ( !m_gotReturnTypeFromDocComment && node->returnExpr && lastType() && hasCurrentType() && currentType<FunctionType>())
    {
        FunctionType::Ptr ft = currentType<FunctionType>();
        // kDebug() << "return" << (ft->returnType() ? ft->returnType()->toString() : "none") << lastType()->toString();
        if (ft->returnType()) {
            if (ft->returnType().cast<IntegralType>()
                && ft->returnType().cast<IntegralType>()->dataType() == IntegralType::TypeMixed)
            {
                //don't add TypeMixed to the list, just ignore
                ft->setReturnType(lastType());
            } else {
                UnsureType::Ptr retT;
                if (ft->returnType().cast<UnsureType>()) {
                    //kDebug() << "we already have an unsure type";
                    retT = ft->returnType().cast<UnsureType>();
                    if (lastType().cast<UnsureType>()) {
                        //kDebug() << "add multiple to returnType";
                        FOREACH_FUNCTION(const IndexedType& t, lastType().cast<UnsureType>()->types) {
                            retT->addType(t);
                        }
                    } else {
                        //kDebug() << "add to returnType";
                        retT->addType(lastType()->indexed());
                    }
                } else {
                    if (lastType().cast<UnsureType>()) {
                        retT = lastType().cast<UnsureType>();
                    } else {
                        retT = new UnsureType();
                        retT->addType(lastType()->indexed());
                    }
                    retT->addType(ft->returnType()->indexed());
                }
                ft->setReturnType(AbstractType::Ptr::staticCast(retT));
            }
        } else {
            ft->setReturnType(lastType());
        }
        updateCurrentType();
    }

    AstNode *foreachNode = 0;
    if (node->foreachVar) {
        foreachNode = node->foreachVar;
    } else if (node->foreachExpr) {
        foreachNode = node->foreachExpr;
    }
    if (foreachNode) {
        ExpressionVisitor v(editor());
        foreachNode->ducontext = currentContext();
        v.visitNode(foreachNode);
        DUChainReadLocker lock(DUChain::lock());
        if (StructureType::Ptr type = StructureType::Ptr::dynamicCast(v.result().type())) {
            ClassDeclaration *classDec = dynamic_cast<ClassDeclaration*>(type->declaration(currentContext()->topContext()));
            Q_ASSERT(classDec);
            lock.unlock();
            ClassDeclaration* iteratorDecl = dynamic_cast<ClassDeclaration*>(
                findDeclarationImport(ClassDeclarationType, QualifiedIdentifier("iterator"), 0)
            );
            lock.lock();
            Q_ASSERT(iteratorDecl);
            if (classDec->isPublicBaseClass(iteratorDecl, currentContext()->topContext())) {
                foreach (Declaration *d, classDec->internalContext()->findDeclarations(QualifiedIdentifier("current"))) {
                    if (!dynamic_cast<ClassMethodDeclaration*>(d)) continue;
                    Q_ASSERT(d->type<FunctionType>());
                    injectType(d->type<FunctionType>()->returnType());
                    // kDebug() << "that's it: " << d->type<FunctionType>()->returnType()->toString();
                }
            }
        }
    }
}

void TypeBuilder::visitCatchItem(Php::CatchItemAst *node)
{
    TypeBuilderBase::visitCatchItem(node);
    KDevelop::Declaration *dec = findDeclarationImport(ClassDeclarationType, node->catchClass);
    if (dec && dec->abstractType()) {
        openAbstractType(dec->abstractType());
        closeType();
    }

}

void TypeBuilder::updateCurrentType()
{
    // do nothing
}

}
