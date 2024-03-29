/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "usebuilder.h"

#include <KLocalizedString>

#include "editorintegrator.h"
#include "expressionvisitor.h"
#include "parsesession.h"
#include <duchaindebug.h>

using namespace KDevelop;

namespace Php
{

class UseExpressionVisitor : public ExpressionVisitor
{
public:
    UseExpressionVisitor(EditorIntegrator* editor, UseBuilder* useBuilder)
            : ExpressionVisitor(editor), m_builder(useBuilder) {
    }

protected:
    void usingDeclaration(AstNode* node, const DeclarationPointer& decl) override {
        m_builder->newCheckedUse(node, decl);
    }

private:
    UseBuilder* m_builder;
};

UseBuilder::UseBuilder( EditorIntegrator* editor )
{
    m_editor = editor;
}

ReferencedTopDUContext UseBuilder::build ( const IndexedString& url, AstNode* node, const ReferencedTopDUContext& updateContext )
{
    // just for safety purposes: running the UseBuilder on the internal function file
    // will lead to undefined behavior due to the amount of optimization it has received
    // (esp. in the contextbuilder)
    Q_ASSERT(url != internalFunctionFile());
    return UseBuilderBase::build ( url, node, updateContext );
}

void UseBuilder::visitParameter(ParameterAst *node)
{
    if (node->parameterType) {
        visitParameterType(node->parameterType);
    }
    if (node->defaultValue) {
        visitNodeWithExprVisitor(node->defaultValue);
    }
}

void UseBuilder::visitClassImplements(ClassImplementsAst *node)
{
    if (node->implementsSequence) {
        const KDevPG::ListNode<NamespacedIdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
        do {
            buildNamespaceUses(__it->element);
            __it = __it->next;
        } while (__it != __end);
    }
}

void UseBuilder::visitClassExtends(ClassExtendsAst *node)
{
    buildNamespaceUses(node->identifier);
}

void UseBuilder::visitClassStatement(ClassStatementAst *node)
{
     if (!node->traitsSequence) {
        UseBuilderBase::visitClassStatement(node);
        return;
     }

    const KDevPG::ListNode< NamespacedIdentifierAst* >* it = node->traitsSequence->front();
    forever {
        buildNamespaceUses(it->element, ClassDeclarationType);

        if ( it->hasNext() ) {
            it = it->next;
        } else {
            break;
        }
    }

    if (node->imports) {
        visitTraitAliasDeclaration(node->imports);
    }

    UseBuilderBase::visitClassStatement(node);
}

void UseBuilder::visitTraitAliasStatement(TraitAliasStatementAst *node)
{
    if (node->conflictIdentifierSequence) {
        const KDevPG::ListNode< NamespacedIdentifierAst* >* it = node->conflictIdentifierSequence->front();
        forever {
            buildNamespaceUses(it->element, ClassDeclarationType);

            if ( it->hasNext() ) {
                it = it->next;
            } else {
                break;
            }
        }
    }

    DUChainWriteLocker lock;
    DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, identifierForNamespace(node->importIdentifier->identifier, m_editor));

    if (dec) {
        QualifiedIdentifier original = identifierPairForNode(node->importIdentifier->methodIdentifier).second;
        QList <Declaration*> list = dec.data()->internalContext()->findLocalDeclarations(original.last(), dec.data()->internalContext()->range().start);

        if (!list.isEmpty()) {
            UseBuilderBase::newUse(node->importIdentifier->methodIdentifier, DeclarationPointer(list.first()));
        }
    }

    lock.unlock();

    visitTraitAliasIdentifier(node->importIdentifier);
}

void UseBuilder::visitTraitAliasIdentifier(TraitAliasIdentifierAst *node)
{
    buildNamespaceUses(node->identifier, ClassDeclarationType);
}

void UseBuilder::visitExpr(ExprAst* node)
{
    visitNodeWithExprVisitor(node);
}

void UseBuilder::visitGlobalVar(GlobalVarAst* node)
{
    if (node->var) {
        DeclarationPointer dec = findDeclarationImport(GlobalVariableDeclarationType, node->var);
        if (dec) {
            newCheckedUse(node->var, dec);
        }
    }
}

void UseBuilder::visitStaticScalar(StaticScalarAst* node)
{
    if (currentContext()->type() == DUContext::Class) {
        visitNodeWithExprVisitor(node);
    }
}

void UseBuilder::visitStatement(StatementAst *node)
{
    if (node->foreachVar) {
        visitNodeWithExprVisitor(node->foreachVar);
    } else if (node->unsetVariablesSequence) {
        visitNodeWithExprVisitor(node);
    }

    if (node->foreachExprAsVar) {
        visitNodeWithExprVisitor(node->foreachExprAsVar);
    }
    if (node->foreachVarAsVar) {
        visitNodeWithExprVisitor(node->foreachVarAsVar);
    }
    if (node->foreachVariable) {
        visitNodeWithExprVisitor(node->foreachVariable);
    }

    UseBuilderBase::visitStatement(node);
}

void UseBuilder::visitCatchItem(CatchItemAst *node)
{
    if (node->catchClassSequence) {
        const KDevPG::ListNode< NamespacedIdentifierAst* >* it = node->catchClassSequence->front();
        forever {
            buildNamespaceUses(it->element, ClassDeclarationType);

            if ( it->hasNext() ) {
                it = it->next;
            } else {
                break;
            }
        }
    }
    UseBuilderBase::visitCatchItem(node);
}

void UseBuilder::newCheckedUse(AstNode* node, const DeclarationPointer& declaration, bool reportNotFound)
{
    if ( declaration && declaration->comment().contains("@deprecated") ) {
        reportError(i18n("Usage of %1 is deprecated.", declaration->toString()), node, IProblem::Hint);
    } else if ( !declaration && reportNotFound ) {
        reportError(i18n("Declaration not found: %1", m_editor->parseSession()->symbol(node)), node, IProblem::Hint);
    }
    UseBuilderBase::newUse(node, declaration);
}

void UseBuilder::visitUnaryExpression( UnaryExpressionAst* node )
{
    IndexedString includeFile = getIncludeFileForNode(node, m_editor);
    if ( !includeFile.isEmpty() ) {
        QualifiedIdentifier identifier(includeFile.str());

        DUChainWriteLocker lock(DUChain::lock());
        foreach ( Declaration* dec, currentContext()->topContext()->findDeclarations(identifier) ) {
            if ( dec->kind() == Declaration::Import ) {
                newUse(node->includeExpression, DeclarationPointer(dec));
                return;
            }
        }
    }
}

void UseBuilder::visitUseNamespaceOrUseGroupedNamespace(UseNamespaceOrUseGroupedNamespaceAst* node)
{
    if (node->compoundNamespace) {
        QualifiedIdentifier identifier = identifierForNamespace(node->identifier, m_editor, false);
        buildNamespaceUses(
            identifier,
            nullptr,
            node->identifier->namespaceNameSequence,
            NamespaceDeclarationType);
        m_compoundNamespacePrefix = node->identifier;
        visitCompoundNamespace(node->compoundNamespace);
    } else {
        buildNamespaceUses(node->identifier, node->useImportType);
    }
}

void UseBuilder::visitInnerUseNamespace(InnerUseNamespaceAst* node)
{
    Php::DeclarationType lastType;
    if (node->useImportType == ConstantImport) {
        lastType = ConstantDeclarationType;
    } else if (node->useImportType == FunctionImport) {
        lastType = FunctionDeclarationType;
    } else {
        lastType = NamespaceDeclarationType;
    }

    QualifiedIdentifier identifier = identifierForNamespace(
        m_compoundNamespacePrefix,
        node,
        m_editor,
        node->useImportType == ConstantImport);
    buildNamespaceUses(
        identifier,
        m_compoundNamespacePrefix->namespaceNameSequence,
        node->namespaceNameSequence,
        lastType);
}

void UseBuilder::visitGenericTypeHint(GenericTypeHintAst* node) {
    if (node->genericType && isGenericClassTypehint(node->genericType, m_editor)) {
        buildNamespaceUses(node->genericType);
    }
}

void UseBuilder::buildNamespaceUses(NamespacedIdentifierBeforeGroupedNamespaceAst* node, UseImportType useImportType)
{
    Php::DeclarationType lastType;
    if (useImportType == ConstantImport) {
        lastType = ConstantDeclarationType;
    } else if (useImportType == FunctionImport) {
        lastType = FunctionDeclarationType;
    } else {
        lastType = NamespaceDeclarationType;
    }

    QualifiedIdentifier identifier = identifierForNamespace(node, m_editor, useImportType == ConstantImport);
    buildNamespaceUses(identifier, nullptr, node->namespaceNameSequence, lastType);
}

void UseBuilder::buildNamespaceUses(NamespacedIdentifierAst* node, DeclarationType lastType)
{
    QualifiedIdentifier identifier = identifierForNamespace(node, m_editor, lastType == ConstantDeclarationType);
    buildNamespaceUses(identifier, nullptr, node->namespaceNameSequence, lastType);
}

void UseBuilder::buildNamespaceUses(
    KDevelop::QualifiedIdentifier identifier,
    const KDevPG::ListNode<IdentifierAst *>* prefixNamespaceNameSequence,
    const KDevPG::ListNode<IdentifierAst *>* namespaceNameSequence,
    Php::DeclarationType lastType)
{
    QualifiedIdentifier curId;

    // check if we need to resolve the namespaced identifier globally or locally
    DeclarationPointer tempDec = findDeclarationImport(lastType, identifier);

    // if we couldn't find a class declaration, it might be a partial namespace identifier
    if (!tempDec) {
        tempDec = findDeclarationImport(NamespaceDeclarationType, identifier);
    }

    if (!tempDec && !identifier.explicitlyGlobal()) {
        identifier.setExplicitlyGlobal(true);
        tempDec = findDeclarationImport(lastType, identifier);

        if (!tempDec) {
            tempDec = findDeclarationImport(NamespaceDeclarationType, identifier);
        }

        // Can't resolve either globally or locally, so revert back to original
        if (!tempDec) {
            identifier.setExplicitlyGlobal(false);
        }
    }

    curId.setExplicitlyGlobal(identifier.explicitlyGlobal());
    int prefixCount = prefixNamespaceNameSequence == nullptr ? 0 : prefixNamespaceNameSequence->count();
    Q_ASSERT(identifier.count() == prefixCount + namespaceNameSequence->count());
    for ( int i = 0; i < identifier.count() - 1; ++i ) {
        curId.push(identifier.at(i));
        if (i>=prefixCount) {
            AstNode* n = namespaceNameSequence->at(i)->element;
            DeclarationPointer dec = findDeclarationImport(NamespaceDeclarationType, curId);
            if (!dec || dec->range() != editorFindRange(n, n)) {
                newCheckedUse(n, dec, true);
            }
        }
    }
    bool reportNotFound = lastType == ClassDeclarationType
        || lastType == ConstantDeclarationType
        || lastType == FunctionDeclarationType
        || lastType == NamespaceDeclarationType;
    newCheckedUse(namespaceNameSequence->back()->element, findDeclarationImport(lastType, identifier), reportNotFound);
}

void UseBuilder::openNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node,
                               const IdentifierPair& identifier, const RangeInRevision& range)
{
    if (node != parent->namespaceNameSequence->back()->element) {
        DeclarationPointer dec = findDeclarationImport(NamespaceDeclarationType, identifier.second);
        if (!dec || dec->range() != editorFindRange(node, node)) {
            newCheckedUse(node, dec);
        }
    }
    UseBuilderBase::openNamespace(parent, node, identifier, range);
}

void UseBuilder::visitNodeWithExprVisitor(AstNode* node)
{
    UseExpressionVisitor v(m_editor, this);
    node->ducontext = currentContext();
    v.visitNode(node);

    if (v.result().hadUnresolvedIdentifiers()) {
        m_hadUnresolvedIdentifiers = true;
    }
}

}
