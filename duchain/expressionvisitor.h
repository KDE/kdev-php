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
    void visitUnaryExpression(UnaryExpressionAst* node) override;
    void visitAdditiveExpressionRest(AdditiveExpressionRestAst* node) override;
    void visitVariable(VariableAst* node) override;
    void visitFunctionCallParameterList( FunctionCallParameterListAst* node ) override;
    void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst* node) override;
    void visitRelationalExpression(RelationalExpressionAst* node) override;

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

private:
    KDevelop::DUContext* findClassContext(NamespacedIdentifierAst* className);
    KDevelop::DUContext* findClassContext(IdentifierAst* className);
    void buildNamespaceUses(NamespacedIdentifierAst* namespaces, const KDevelop::QualifiedIdentifier& identifier);

    bool m_createProblems;
    KDevelop::CursorInRevision m_offset;
    KDevelop::DUContext* m_currentContext;

    ExpressionEvaluationResult m_result;

    bool m_isAssignmentExpressionEqual;
    bool m_inDefine;
};

}
#endif
