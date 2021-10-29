/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

#include "phpdefaultvisitor.h"
#include "phpduchainexport.h"
#include "expressionevaluationresult.h"
#include "helper.h"

#include <language/duchain/types/abstracttype.h>
#include <language/duchain/identifier.h>

namespace KDevelop
{
class TopDUContext;
class Declaration;
}

namespace Php
{
class EditorIntegrator;

class KDEVPHPDUCHAIN_EXPORT ExpressionVisitor : public DefaultVisitor
{
public:
    ExpressionVisitor(EditorIntegrator* editor);
    ExpressionEvaluationResult result() {
        return m_result;
    }
    void setCreateProblems(bool v);
    void setOffset(const KDevelop::CursorInRevision& offset);

    void visitNode(AstNode *node) override;

protected:
    KDevelop::DeclarationPointer processVariable( VariableIdentifierAst* variable);

    void visitAssignmentExpression(AssignmentExpressionAst *node) override;
    void visitArrayIndexSpecifier(ArrayIndexSpecifierAst* node) override;
    void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node) override;
    void visitVarExpression(VarExpressionAst *node) override;
    void visitVarExpressionNewObject(VarExpressionNewObjectAst *node) override;
    void visitVarExpressionArray(VarExpressionArrayAst *node) override;
    void visitClosure(ClosureAst* node) override;
    void visitFunctionCall(FunctionCallAst* node) override;
    void visitConstantOrClassConst(ConstantOrClassConstAst *node) override;
    void visitScalar(ScalarAst *node) override;
    void visitStaticScalar(StaticScalarAst *node) override;
    void visitEncapsVar(EncapsVarAst *node) override;
    void visitVariableProperty(VariablePropertyAst *node) override;
    void visitStaticMember(StaticMemberAst* node) override;
    void visitClassNameReference(ClassNameReferenceAst* node) override;
    void visitClassNameReferenceDimListItems(ClassPropertyAst* node);
    void visitUnaryExpression(UnaryExpressionAst* node) override;
    void visitAdditiveExpressionRest(AdditiveExpressionRestAst* node) override;
    void visitVariable(VariableAst* node) override;
    void visitFunctionCallParameterList( FunctionCallParameterListAst* node ) override;
    void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst* node) override;
    void visitRelationalExpression(RelationalExpressionAst* node) override;
    void visitRelationalExpressionRest(RelationalExpressionRestAst* node) override;
    void visitEqualityExpressionRest(EqualityExpressionRestAst* node) override;
    void visitStatement(StatementAst* node) override;

    QString stringForNode(AstNode* id);
    KDevelop::QualifiedIdentifier identifierForNode(IdentifierAst* id);
    QString stringForNode(VariableIdentifierAst* id);
    KDevelop::QualifiedIdentifier identifierForNode(VariableIdentifierAst* id);


    virtual void usingDeclaration(AstNode* node, const KDevelop::DeclarationPointer& decl) {
        Q_UNUSED(node) Q_UNUSED(decl)
    }

    KDevelop::DeclarationPointer findDeclarationImport(DeclarationType declarationType, IdentifierAst* node);
    KDevelop::DeclarationPointer findDeclarationImport(DeclarationType declarationType, VariableIdentifierAst* node);
    KDevelop::DeclarationPointer findDeclarationImport(DeclarationType declarationType,
                                                       const KDevelop::QualifiedIdentifier& identifier);
    KDevelop::Declaration* findVariableDeclaration(KDevelop::DUContext* context, KDevelop::Identifier identifier,
                                                   KDevelop::CursorInRevision position, KDevelop::DUContext::SearchFlag flag);
protected:
    EditorIntegrator* m_editor;

    /**
     * Opens the given closure return type, and sets it to be the current closure return type.
     */
    void openClosureReturnType(const KDevelop::AbstractType::Ptr& type)
    {
        m_closureReturnTypes.append(type);
    }

    /**
     * Close the current closure return type.
     */
    void closeClosureReturnType()
    {
        // And the reference will be lost...
        m_closureReturnTypes.pop();
    }

    /**
     * Retrieve the return type of the current closure.
     *
     * \returns the abstract type of the current context.
     */
    inline KDevelop::AbstractType::Ptr currentClosureReturnType()
    {
        if (m_closureReturnTypes.isEmpty()) {
            return KDevelop::AbstractType::Ptr();
        } else {
            return m_closureReturnTypes.top();
        }
    }

  /// Determine if the expression visitor has a return type for the current closure. \returns true if there is a current closure return type, else returns false.
  inline bool hasCurrentClosureReturnType() { return !m_closureReturnTypes.isEmpty(); }

private:
    KDevelop::DUContext* findClassContext(NamespacedIdentifierAst* className);
    KDevelop::DUContext* findClassContext(IdentifierAst* className);
    void buildNamespaceUses(NamespacedIdentifierAst* namespaces, const KDevelop::QualifiedIdentifier& identifier);
    void useDeclaration(VariableIdentifierAst* node, KDevelop::DUContext* context);
    void useDeclaration(IdentifierAst* node, KDevelop::DUContext* context);

    bool m_createProblems;
    KDevelop::CursorInRevision m_offset;
    KDevelop::DUContext* m_currentContext;

    ExpressionEvaluationResult m_result;
    KDevelop::Stack<KDevelop::AbstractType::Ptr> m_closureReturnTypes;

    bool m_isAssignmentExpressionEqual;
    bool m_inDefine;
};

}
#endif
