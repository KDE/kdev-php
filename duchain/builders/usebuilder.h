/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef USEBUILDER_H
#define USEBUILDER_H

#include <language/duchain/builders/abstractusebuilder.h>

#include "helper.h"
#include "contextbuilder.h"
#include "phpduchainexport.h"

namespace Php
{

class ParseSession;

typedef KDevelop::AbstractUseBuilder<AstNode, IdentifierAst, ContextBuilder> UseBuilderBase;

/**
 * A class which iterates the AST to extract uses of definitions.
 */
class KDEVPHPDUCHAIN_EXPORT UseBuilder: public UseBuilderBase
{
public:
    UseBuilder(EditorIntegrator* editor);

    /**
     * Reports a problem if the use'd declaration is deprecated.
     * Also reports an error if @p reportNotFound is true and @p declaration is null.
     */
    void newCheckedUse(Php::AstNode* node, const KDevelop::DeclarationPointer& declaration, bool reportNotFound = false);

    KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, AstNode* node,
        const KDevelop::ReferencedTopDUContext& updateContext
        = KDevelop::ReferencedTopDUContext()) override;

protected:
    void visitParameter(ParameterAst *node) override;
    void visitClassImplements(ClassImplementsAst *node) override;
    void visitClassExtends(ClassExtendsAst *node) override;
    void visitClassStatement(ClassStatementAst *node) override;
    void visitTraitAliasStatement(TraitAliasStatementAst *node) override;
    void visitTraitAliasIdentifier(TraitAliasIdentifierAst *node) override;
    void visitExpr(ExprAst* node) override;
    void visitGlobalVar(GlobalVarAst* node) override;
    void visitStaticScalar(StaticScalarAst* node) override;
    void visitStatement(StatementAst* node) override;
    void visitCatchItem(CatchItemAst* node) override;
    void visitUnaryExpression( UnaryExpressionAst* node ) override;
    void visitUseNamespaceOrUseGroupedNamespace(UseNamespaceOrUseGroupedNamespaceAst* node) override;
    void visitInnerUseNamespace(InnerUseNamespaceAst* node) override;
    void openNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node, const IdentifierPair& identifier, const KDevelop::RangeInRevision& range) override;
    void visitGenericTypeHint(GenericTypeHintAst* node) override;

private:
    void buildNamespaceUses(
        Php::NamespacedIdentifierAst* node,
        Php::DeclarationType lastType = Php::ClassDeclarationType);
    void buildNamespaceUses(
        Php::NamespacedIdentifierBeforeGroupedNamespaceAst* node,
        Php::UseImportType useImportType);
    void buildNamespaceUses(
        KDevelop::QualifiedIdentifier identifier,
        const KDevPG::ListNode<IdentifierAst *>* prefixNamespaceNameSequence,
        const KDevPG::ListNode<IdentifierAst *>* namespaceNameSequence,
        Php::DeclarationType lastType);

    void visitNodeWithExprVisitor(AstNode* node);

    /// Prefix in front of grouped namespace
    NamespacedIdentifierBeforeGroupedNamespaceAst *m_compoundNamespacePrefix;
};

}

#endif // USEBUILDER_H

