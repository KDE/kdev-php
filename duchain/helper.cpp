/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "helper.h"

#include <KParts/MainWindow>
#include <KLocalizedString>

#include <language/duchain/ducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/duchain.h>
#include <language/duchain/stringhelpers.h>
#include <language/duchain/parsingenvironment.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/arraytype.h>
#include <interfaces/icore.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/iproject.h>
#include <project/projectmodel.h>
#include <util/path.h>

#include "editorintegrator.h"
#include "../parser/parsesession.h"
#include "phpast.h"
#include "phpdefaultvisitor.h"
#include "declarations/classdeclaration.h"
#include "declarations/classmethoddeclaration.h"
#include "declarations/functiondeclaration.h"
#include "types/integraltypeextended.h"
#include "expressionparser.h"
#include "expressionvisitor.h"

#include "duchaindebug.h"

#define ifDebug(x)

using namespace KDevelop;

namespace Php
{

bool isMatch(Declaration* declaration, DeclarationType declarationType)
{
    if (declarationType == ClassDeclarationType
            && dynamic_cast<ClassDeclaration*>(declaration)
       ) {
        return true;
    } else if (declarationType == FunctionDeclarationType
               && dynamic_cast<FunctionDeclaration*>(declaration)
              ) {
        return true;
    } else if (declarationType == ConstantDeclarationType
               && declaration->abstractType() && declaration->abstractType()->modifiers() & AbstractType::ConstModifier
               && (!declaration->context() || declaration->context()->type() != DUContext::Class)
              ) {
        return true;
    } else if (declarationType == GlobalVariableDeclarationType
               && declaration->kind() == Declaration::Instance
               && !(declaration->abstractType() && declaration->abstractType()->modifiers() & AbstractType::ConstModifier)
              ) {
        return true;
    } else if (declarationType == NamespaceDeclarationType
               && (declaration->kind() == Declaration::Namespace || declaration->kind() == Declaration::NamespaceAlias || dynamic_cast<ClassDeclaration*>(declaration)) )
    {
        return true;
    }
    return false;
}

bool isGenericClassTypehint(NamespacedIdentifierAst* node, EditorIntegrator *editor)
{
    const KDevPG::ListNode< IdentifierAst* >* it = node->namespaceNameSequence->front();
    QString typehint = editor->parseSession()->symbol(it->element);

    if (typehint.compare(QLatin1String("bool"), Qt::CaseInsensitive) == 0) {
        return false;
    } else if (typehint.compare(QLatin1String("float"), Qt::CaseInsensitive) == 0) {
        return false;
    } else if (typehint.compare(QLatin1String("int"), Qt::CaseInsensitive) == 0) {
        return false;
    } else if (typehint.compare(QLatin1String("string"), Qt::CaseInsensitive) == 0) {
        return false;
    } else if (typehint.compare(QLatin1String("iterable"), Qt::CaseInsensitive) == 0) {
        return false;
    } else if (typehint.compare(QLatin1String("object"), Qt::CaseInsensitive) == 0) {
        return false;
    } else if (typehint.compare(QLatin1String("mixed"), Qt::CaseInsensitive) == 0) {
        return false;
    } else {
        return true;
    }
}

template <class T>
bool isClassTypehint(T* typeHint, EditorIntegrator *editor)
{
    Q_ASSERT(typeHint);

    if (typeHint->callableType != -1) {
        return false;
    } else if (typeHint->voidType != -1) {
        return false;
    } else if (typeHint->genericType) {
        if (typeHint->genericType->arrayType != -1) {
            return false;
        } else {
            return isGenericClassTypehint(typeHint->genericType->genericType, editor);
        }
    } else {
        return false;
    }
}

bool hasClassTypehint(UnionParameterTypeAst* unionType, EditorIntegrator *editor)
{
    Q_ASSERT(unionType);

    const KDevPG::ListNode< ParameterTypeHintAst* >* it = unionType->unionTypeSequence->front();

    do {
        if (isClassTypehint(it->element, editor)) {
            return true;
        }
    } while(it->hasNext() && (it = it->next));

    return false;
}

bool hasClassTypehint(UnionPropertyTypeAst* unionType, EditorIntegrator *editor)
{
    Q_ASSERT(unionType);

    const KDevPG::ListNode< PropertyTypeHintAst* >* it = unionType->unionTypeSequence->front();

    do {
        if (isClassTypehint(it->element, editor)) {
            return true;
        }
    } while(it->hasNext() && (it = it->next));

    return false;
}

bool hasClassTypehint(UnionReturnTypeAst* unionType, EditorIntegrator *editor)
{
    Q_ASSERT(unionType);

    const KDevPG::ListNode< ReturnTypeHintAst* >* it = unionType->unionTypeSequence->front();

    do {
        if (isClassTypehint(it->element, editor)) {
            return true;
        }
    } while(it->hasNext() && (it = it->next));

    return false;
}

bool hasType(AbstractType::Ptr haystack, AbstractType::Ptr needle)
{
    auto unsure = haystack.dynamicCast<UnsureType>();
    if (unsure) {
        FOREACH_FUNCTION(const IndexedType& t, unsure->types) {
            if (needle->equals(t.abstractType().data())) {
                return true;
            }
        }
    } else {
        return needle->equals(haystack.data());
    }

    return false;
}

DeclarationPointer findDeclarationImportHelper(DUContext* currentContext, const QualifiedIdentifier& id,
        DeclarationType declarationType)
{
    /// Qualified identifier for 'self'
    static const QualifiedIdentifier selfQId(QStringLiteral("self"));
    /// Qualified identifier for 'parent'
    static const QualifiedIdentifier parentQId(QStringLiteral("parent"));
    /// Qualified identifier for 'static'
    static const QualifiedIdentifier staticQId(QStringLiteral("static"));

    QualifiedIdentifier lookup;

    if (id.explicitlyGlobal()) {
        ifDebug(qCDebug(DUCHAIN) << id.toString() << declarationType;)

        lookup = id;
        lookup.setExplicitlyGlobal(false);
    } else {
        lookup = identifierWithNamespace(id, currentContext);

        ifDebug(qCDebug(DUCHAIN) << lookup.toString() << declarationType;)
    }

    if (declarationType == ClassDeclarationType && id == selfQId) {
        DUChainReadLocker lock(DUChain::lock());
        if (currentContext->type() == DUContext::Class) {
            return DeclarationPointer(currentContext->owner());
        } else if (currentContext->parentContext() && currentContext->parentContext()->type() == DUContext::Class) {
            return DeclarationPointer(currentContext->parentContext()->owner());
        } else {
            return DeclarationPointer();
        }
    } else if (declarationType == ClassDeclarationType && id == staticQId) {
        DUChainReadLocker lock;
        if (currentContext->type() == DUContext::Class) {
            return DeclarationPointer(currentContext->owner());
        } else if (currentContext->parentContext() && currentContext->parentContext()->type() == DUContext::Class) {
            return DeclarationPointer(currentContext->parentContext()->owner());
        } else {
            return DeclarationPointer();
        }
    } else if (declarationType == ClassDeclarationType && id == parentQId) {
        //there can be just one Class-Context imported
        DUChainReadLocker lock;
        DUContext* classCtx = nullptr;
        if (currentContext->type() == DUContext::Class) {
            classCtx = currentContext;
        } else if (currentContext->parentContext() && currentContext->parentContext()->type() == DUContext::Class) {
            classCtx = currentContext->parentContext();
        }
        if (classCtx) {
            foreach(const DUContext::Import &i, classCtx->importedParentContexts()) {
                DUContext* ctx = i.context(classCtx->topContext());
                if (ctx && ctx->type() == DUContext::Class) {
                    return DeclarationPointer(ctx->owner());
                }
            }
        }
        return DeclarationPointer();
    } else {
        DUChainReadLocker lock;
        QList<Declaration*> foundDeclarations = currentContext->topContext()->findDeclarations(lookup);

        foreach(Declaration *declaration, foundDeclarations) {
            if (isMatch(declaration, declarationType)) {
                return DeclarationPointer(declaration);
            }
        }
        if ( currentContext->url() == internalFunctionFile() ) {
            // when compiling php internal functions, we don't need to ask the persistent symbol table for anything
            return DeclarationPointer();
        }

        lock.unlock();

        if (declarationType != GlobalVariableDeclarationType) {
            ifDebug(qCDebug(DUCHAIN) << "No declarations found with findDeclarations, trying through PersistentSymbolTable";)
            DeclarationPointer decl;

            decl = findDeclarationInPST(currentContext, lookup, declarationType);

            if (decl) {
                ifDebug(qCDebug(DUCHAIN) << "PST declaration exists";)
            } else {
                ifDebug(qCDebug(DUCHAIN) << "PST declaration does not exist";)
            }
            return decl;
        }
    }

    ifDebug(qCDebug(DUCHAIN) << "returning 0";)
    return DeclarationPointer();
}

DeclarationPointer findDeclarationInPST(DUContext* currentContext, QualifiedIdentifier id, DeclarationType declarationType)
{
    DeclarationPointer ret;

    ifDebug(qCDebug(DUCHAIN) << "PST: " << id.toString() << declarationType;)
    DUChainWriteLocker wlock;

    /// Indexed string for 'Php', identifies environment files from this language plugin
    static const IndexedString phpLangString("Php");
    auto visitor = [&](const IndexedDeclaration &indexedDeclaration) {
        ParsingEnvironmentFilePointer env = DUChain::self()->environmentFileForDocument(indexedDeclaration.indexedTopContext());
        if(!env) {
            ifDebug(qCDebug(DUCHAIN) << "skipping declaration, missing meta-data";)
            return PersistentSymbolTable::VisitorState::Continue;
        }
        if(env->language() != phpLangString) {
            ifDebug(qCDebug(DUCHAIN) << "skipping declaration, invalid language" << env->language().str();)
            return PersistentSymbolTable::VisitorState::Continue;
        }

        const auto declaration = indexedDeclaration.declaration();
        if (!declaration) {
            ifDebug(qCDebug(DUCHAIN) << "skipping declaration, doesn't have declaration";)
            return PersistentSymbolTable::VisitorState::Continue;
        } else if (!isMatch(declaration, declarationType)) {
            ifDebug(qCDebug(DUCHAIN) << "skipping declaration, doesn't match with declarationType";)
            return PersistentSymbolTable::VisitorState::Continue;
        }

        TopDUContext* top = declaration->context()->topContext();
        currentContext->topContext()->addImportedParentContext(top);
        currentContext->topContext()->parsingEnvironmentFile()
        ->addModificationRevisions(top->parsingEnvironmentFile()->allModificationRevisions());
        currentContext->topContext()->updateImportsCache();
        ifDebug(qCDebug(DUCHAIN) << "using" << declarations[i].declaration()->toString() << top->url();)
        ret = declaration;
        return PersistentSymbolTable::VisitorState::Break;
    };
    PersistentSymbolTable::self().visitDeclarations(id, visitor);

    return ret;
}

QByteArray formatComment(AstNode* node, EditorIntegrator* editor)
{
    return KDevelop::formatComment(editor->parseSession()->docComment(node->startToken).toUtf8());
}

//Helper visitor to extract a commonScalar node
//used to get the value of an function call argument
class ScalarExpressionVisitor : public DefaultVisitor
{
public:
    ScalarExpressionVisitor() : m_node(nullptr) {}
    CommonScalarAst* node() const {
        return m_node;
    }
private:
    void visitCommonScalar(CommonScalarAst* node) override {
        m_node = node;
    }
    CommonScalarAst* m_node;
};

CommonScalarAst* findCommonScalar(AstNode* node)
{
    ScalarExpressionVisitor visitor;
    visitor.visitNode(node);
    return visitor.node();
}

static bool includeExists(const Path &include)
{
    const QString path = include.pathOrUrl();
    {
        DUChainReadLocker lock;
        if (DUChain::self()->chainForDocument(IndexedString(path))) {
            return true;
        }
    }
    if ( include.isLocalFile() ) {
        return QFile::exists(path);
    } else {
        return false;
    }
}

static IndexedString findIncludeFile(const QString &includePath, const IndexedString &currentDocument)
{
    if ( includePath.isEmpty() ) {
        return IndexedString();
    }

    // check remote files
    if ( includePath.startsWith(QLatin1String("http://"), Qt::CaseInsensitive)
            || includePath.startsWith(QLatin1String("ftp://"), Qt::CaseInsensitive) ) {
        // always expect remote includes to exist
        return IndexedString(includePath);
    }

    const Path currentPath(currentDocument.str());

    // look for file relative to current url
    Path include = Path(currentPath.parent(), includePath);
    if ( includeExists(include) ) {
        return IndexedString(include.pathOrUrl());
    }

    // in the first round look for a project that is a parent of the current document
    // in the next round look for any project
    for (int i = 0; i < 2; ++i) {
        foreach(IProject* project, ICore::self()->projectController()->projects()) {
            if ( !i && !project->path().isParentOf(currentPath)) {
                continue;
            }
            include = Path(project->path(), includePath);
            if ( includeExists(include) ) {
                return IndexedString(include.pathOrUrl());
            }
        }
    }

    //TODO configurable include paths

    return IndexedString();
}

IndexedString getIncludeFileForNode(UnaryExpressionAst* node, EditorIntegrator* editor) {
    if ( node->includeExpression ) {
        //find name of the constant (first argument of the function call)
        CommonScalarAst* scalar = findCommonScalar(node->includeExpression);
        if (scalar && scalar->string != -1) {
            QString str = editor->parseSession()->symbol(scalar->string);
            str = str.mid(1, str.length() - 2);
            if ( str == QLatin1String(".") || str == QLatin1String("..") || str.endsWith('/') ) {
                return IndexedString();
            }
            return findIncludeFile(str, editor->parseSession()->currentDocument());
        }
    }

    return IndexedString();
}

QString prettyName(Declaration* dec) {
    if (!dec) {
        return {};
    } else if ( dec->context() && dec->context()->type() == DUContext::Class && dec->isFunctionDeclaration() ) {
        ClassMethodDeclaration* classMember = dynamic_cast<ClassMethodDeclaration*>(dec);
        Q_ASSERT(classMember);
        return classMember->prettyName().str();
    } else if ( dec->isFunctionDeclaration() ) {
        FunctionDeclaration* func = dynamic_cast<FunctionDeclaration*>(dec);
        Q_ASSERT(func);
        return func->prettyName().str();
    } else if ( dec->internalContext() && dec->internalContext()->type() == DUContext::Class ) {
        ClassDeclaration* classDec = dynamic_cast<ClassDeclaration*>(dec);
        Q_ASSERT(classDec);
        return classDec->prettyName().str();
    } else {
        return dec->identifier().toString();
    }
}

const KDevelop::IndexedString& internalFunctionFile()
{
    static const KDevelop::IndexedString internalFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kdevphpsupport/phpfunctions.php")));
    return internalFile;
}

const KDevelop::IndexedString& phpLanguageString()
{
    static const KDevelop::IndexedString phpLangString("Php");
    return phpLangString;
}

const IndexedString& internalTestFile()
{
    static const KDevelop::IndexedString phpUnitFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kdevphpsupport/phpunitdeclarations.php")));
    return phpUnitFile;
}

QualifiedIdentifier identifierForNamespace(NamespacedIdentifierAst* node, EditorIntegrator* editor, bool lastIsConstIdentifier)
{
    QualifiedIdentifier id;
    if (node->isGlobal != -1) {
        id.setExplicitlyGlobal(true);
    }
    const KDevPG::ListNode< IdentifierAst* >* it = node->namespaceNameSequence->front();
    do {
        if (lastIsConstIdentifier && !it->hasNext()) {
            id.push(Identifier(editor->parseSession()->symbol(it->element)));
        } else {
            id.push(Identifier(editor->parseSession()->symbol(it->element).toLower()));
        }
    } while (it->hasNext() && (it = it->next));
    return id;
}

QualifiedIdentifier identifierForNamespace(NamespacedIdentifierBeforeGroupedNamespaceAst* node, EditorIntegrator* editor, bool lastIsConstIdentifier)
{
    QualifiedIdentifier id;
    if (node->isGlobal != -1) {
        id.setExplicitlyGlobal(true);
    }
    const KDevPG::ListNode< IdentifierAst* >* it = node->namespaceNameSequence->front();
    do {
        if (lastIsConstIdentifier && !it->hasNext()) {
            id.push(Identifier(editor->parseSession()->symbol(it->element)));
        } else {
            id.push(Identifier(editor->parseSession()->symbol(it->element).toLower()));
        }
    } while (it->hasNext() && (it = it->next));
    return id;
}

QualifiedIdentifier identifierForNamespace(
    NamespacedIdentifierBeforeGroupedNamespaceAst* prefixNode,
    InnerUseNamespaceAst* node,
    EditorIntegrator* editor,
    bool lastIsConstIdentifier)
{
    QualifiedIdentifier id;
    if (prefixNode->isGlobal != -1) {
        id.setExplicitlyGlobal(true);
    }
    const KDevPG::ListNode< IdentifierAst* >* it;
    
    it = prefixNode->namespaceNameSequence->front();
    do {
        id.push(Identifier(editor->parseSession()->symbol(it->element).toLower()));
    }
    while (it->hasNext() && (it = it->next));
    it = node->namespaceNameSequence->front();
    do {
        if (lastIsConstIdentifier && !it->hasNext()) {
            id.push(Identifier(editor->parseSession()->symbol(it->element)));
        } else {
            id.push(Identifier(editor->parseSession()->symbol(it->element).toLower()));
        }
    } while (it->hasNext() && (it = it->next));
    return id;
}

QualifiedIdentifier identifierWithNamespace(const QualifiedIdentifier& base, DUContext* context)
{
    DUChainReadLocker lock;
    auto scope = context;
    while (scope && scope->type() != DUContext::Namespace) {
        scope = scope->parentContext();
    }

    if (scope) {
        return scope->scopeIdentifier() + base;
    } else {
        return base;
    }
}

AbstractType::Ptr determineGenericTypeHint(const GenericTypeHintAst* genericType, EditorIntegrator *editor, DUContext* currentContext)
{
    Q_ASSERT(genericType);
    AbstractType::Ptr type;

    if (genericType->arrayType != -1) {
        type = AbstractType::Ptr(new IntegralType(IntegralType::TypeArray));
    } else if (genericType->genericType) {
        NamespacedIdentifierAst* node = genericType->genericType;
        const KDevPG::ListNode< IdentifierAst* >* it = node->namespaceNameSequence->front();
        QString typehint = editor->parseSession()->symbol(it->element);

        if (typehint.compare(QLatin1String("bool"), Qt::CaseInsensitive) == 0) {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeBoolean));
        } else if (typehint.compare(QLatin1String("float"), Qt::CaseInsensitive) == 0) {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeFloat));
        } else if (typehint.compare(QLatin1String("int"), Qt::CaseInsensitive) == 0) {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeInt));
        } else if (typehint.compare(QLatin1String("string"), Qt::CaseInsensitive) == 0) {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeString));
        } else if (typehint.compare(QLatin1String("object"), Qt::CaseInsensitive) == 0) {
            type = AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeObject));
        } else if (typehint.compare(QLatin1String("mixed"), Qt::CaseInsensitive) == 0) {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
        } else if (typehint.compare(QLatin1String("iterable"), Qt::CaseInsensitive) == 0) {
            DeclarationPointer traversableDecl = findDeclarationImportHelper(currentContext, QualifiedIdentifier(u"traversable"), ClassDeclarationType);

            if (traversableDecl) {
                UnsureType::Ptr unsure(new UnsureType());
                AbstractType::Ptr arrayType = AbstractType::Ptr(new IntegralType(IntegralType::TypeArray));
                unsure->addType(arrayType->indexed());
                unsure->addType(traversableDecl->abstractType()->indexed());

                type = AbstractType::Ptr(unsure);
            }
        } else {
            //don't use openTypeFromName as it uses cursor for findDeclarations
            DeclarationPointer decl = findDeclarationImportHelper(currentContext,
                                                        identifierForNamespace(genericType->genericType, editor), ClassDeclarationType);
            if (decl) {
                type = decl->abstractType();
            }
        }
    }

    return type;
}

template <class T>
AbstractType::Ptr determineTypehintFromList(const T* list, EditorIntegrator *editor, DUContext* currentContext)
{
    Q_ASSERT(list);
    AbstractType::Ptr type;

    if (list->element->callableType != -1) {
        type = AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeCallable));
    } else if (list->element->voidType != -1) {
        type = AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid));
    } else if (list->element->genericType) {
        type = determineGenericTypeHint(list->element->genericType, editor, currentContext);
    }

    if (list->count() > 1) {
        auto unsure = type.dynamicCast<UnsureType>();
        if (!unsure) {
            unsure = UnsureType::Ptr(new UnsureType());
            unsure->addType(type->indexed());
        }

        while(list->hasNext() && (list = list->next)) {
            if (list->element->callableType != -1) {
                unsure->addType(AbstractType::Ptr(new IntegralTypeExtended(IntegralTypeExtended::TypeCallable))->indexed());
            } else if (list->element->voidType != -1) {
                unsure->addType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid))->indexed());
            } else if (list->element->genericType) {
                unsure->addType(determineGenericTypeHint(list->element->genericType, editor, currentContext)->indexed());
            }

            if (list->element->isNullable != -1) {
                AbstractType::Ptr nullType = AbstractType::Ptr(new IntegralType(IntegralType::TypeNull));
                unsure->addType(nullType->indexed());
            }
        }

        type = unsure;
    } else if (type && list->element->isNullable != -1) {
        AbstractType::Ptr nullType = AbstractType::Ptr(new IntegralType(IntegralType::TypeNull));
        auto unsure = type.dynamicCast<UnsureType>();
        if (unsure) {
            unsure->addType(nullType->indexed());
        } else {
            unsure = UnsureType::Ptr(new UnsureType());
            unsure->addType(type->indexed());
            unsure->addType(nullType->indexed());

            type = unsure;
        }
    }

    return type;
}

template <class T>
AbstractType::Ptr determineTypehint(const T* unionType, EditorIntegrator *editor, DUContext* currentContext)
{
    Q_ASSERT(unionType);
    AbstractType::Ptr type;

    type = determineTypehintFromList(unionType->unionTypeSequence->front(), editor, currentContext);

    return type;
}

AbstractType::Ptr parameterType(const ParameterAst* node, AbstractType::Ptr phpDocTypehint, EditorIntegrator* editor, DUContext* currentContext)
{
    AbstractType::Ptr type;
    if (node->parameterType && node->parameterType->typehint) {
        type = determineTypehint(node->parameterType->typehint, editor, currentContext);
    }
    if (node->defaultValue) {
        ExpressionVisitor v(editor);
        node->defaultValue->ducontext = currentContext;
        v.visitNode(node->defaultValue);
        AbstractType::Ptr defaultValueType = v.result().type();

        /*
         * If a typehint is already set, default values can only be the same type or `null` in PHP
         * If it's the same type, the type is already correctly set,
         *    so we can ignore this case.
         * If it's null (which cannot be a typehint), add it as UnsureType
         */
        if (type && defaultValueType.dynamicCast<IntegralType>() && defaultValueType.staticCast<IntegralType>()->dataType() == IntegralType::TypeNull) {
            auto unsure = type.dynamicCast<UnsureType>();
            if (unsure) {
                AbstractType::Ptr nullType = AbstractType::Ptr(new IntegralType(IntegralType::TypeNull));
                unsure->addType(defaultValueType->indexed());
            } else {
                unsure = UnsureType::Ptr(new UnsureType());
                unsure->addType(type->indexed());
                unsure->addType(defaultValueType->indexed());

                type = unsure;
            }
        } else if (!type) {
            //Otherwise, let the default value dictate the parameter type
            type = defaultValueType;
        }
    }
    if (!type) {
        if (phpDocTypehint) {
            type = phpDocTypehint;
        } else {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
        }
    }

    if ( node->isRef != -1 ) {
      ReferenceType::Ptr p( new ReferenceType() );
      p->setBaseType( type );

      type = p;
    }

    if (node->isVariadic != -1) {
        auto *container = new KDevelop::ArrayType();
        container->setElementType(type);
        type = AbstractType::Ptr(container);
    }

    Q_ASSERT(type);
    return type;
}

AbstractType::Ptr propertyType(const ClassStatementAst* node, AbstractType::Ptr phpDocTypehint, EditorIntegrator* editor, DUContext* currentContext)
{
    AbstractType::Ptr type;
    if (node->propertyType && node->propertyType->typehint) {
        type = determineTypehint(node->propertyType->typehint, editor, currentContext);
    }

    if (!type) {
        if (phpDocTypehint) {
            type = phpDocTypehint;
        } else {
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
        }
    }

    Q_ASSERT(type);
    return type;
}

AbstractType::Ptr returnType(const ReturnTypeAst* node, AbstractType::Ptr phpDocTypehint, EditorIntegrator* editor, DUContext* currentContext) {
    AbstractType::Ptr type;
    if (node && node->typehint) {
        type = determineTypehint(node->typehint, editor, currentContext);
    }
    if (!type) {
        type = phpDocTypehint;
    }
    return type;
}

}
