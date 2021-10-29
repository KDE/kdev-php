/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef TYPEBUILDER_H
#define TYPEBUILDER_H

#include "contextbuilder.h"

#include <language/duchain/builders/abstracttypebuilder.h>

#include <language/duchain/types/functiontype.h>
#include <language/duchain/declaration.h>
#include <language/duchain/identifier.h>

namespace Php
{

typedef KDevelop::AbstractTypeBuilder<AstNode, IdentifierAst, ContextBuilder> TypeBuilderBase;

/**
 * Create types from an AstNode tree.
 *
 * \note This builder overrides visitDeclarator, in order to support
 * array types; parent classes will not have
 * their visitDeclarator function called.
 */
class KDEVPHPDUCHAIN_EXPORT TypeBuilder: public TypeBuilderBase
{
public:
    TypeBuilder();
    ~TypeBuilder() override;

protected:
    void visitClassDeclarationStatement(ClassDeclarationStatementAst* node) override;
    void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node) override;
    void visitTraitDeclarationStatement(TraitDeclarationStatementAst* node) override;
    void visitClassStatement(ClassStatementAst *node) override;
    void visitClassVariable(ClassVariableAst *node) override;
    void visitConstantDeclaration(ConstantDeclarationAst* node) override;
    void visitClassConstantDeclaration(ClassConstantDeclarationAst* node) override;
    void visitParameter(ParameterAst *node) override;
    void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node) override;
    void visitClosure(ClosureAst* node) override;

    void visitStatement(StatementAst* node) override;
    void visitAssignmentExpression(AssignmentExpressionAst* node) override;
    void visitStaticVar(StaticVarAst *node) override;
    void visitCatchItem(CatchItemAst *node) override;
    void visitVarExpression(VarExpressionAst *node) override;

    /// The declaration builder implements this and updates
    /// the type of the current declaration
    virtual void updateCurrentType();

    KDevelop::AbstractType::Ptr getTypeForNode(AstNode* node);

    /**
     * Opens the given context type, and sets it to be the current context type.
     */
    void openContextType(const KDevelop::AbstractType::Ptr& type)
    {
        m_contextTypes.append(type);
    }

    /**
     * Close the current context type.
     */
    void closeContextType()
    {
        // And the reference will be lost...
        m_contextTypes.pop();
    }

    /**
     * Retrieve the type of the current context.
     *
     * \returns the abstract type of the current context.
     */
    inline KDevelop::AbstractType::Ptr currentContextType()
    {
        if (m_contextTypes.isEmpty()) {
            return KDevelop::AbstractType::Ptr();
        } else {
            return m_contextTypes.top();
        }
    }

  /// Determine if the type builder has a type for the current context. \returns true if there is a current context type, else returns false.
  inline bool hasCurrentContextType() { return !m_contextTypes.isEmpty(); }

private:
    KDevelop::FunctionType::Ptr m_currentFunctionType;
    QList<KDevelop::AbstractType::Ptr> m_currentFunctionParams;
    KDevelop::Stack<KDevelop::AbstractType::Ptr> m_contextTypes;

    bool m_gotTypeFromDocComment;
    bool m_gotReturnTypeFromDocComment;
    bool m_gotTypeFromTypeHint;

    KDevelop::AbstractType::Ptr injectParseType(QString type, AstNode* node);
    KDevelop::AbstractType::Ptr parseType(QString type, AstNode* node);
    KDevelop::AbstractType::Ptr parseSimpleType(QString type, AstNode* node);
    KDevelop::AbstractType::Ptr parseDocComment(AstNode* node, const QString& docCommentName);
    QList<KDevelop::AbstractType::Ptr> parseDocCommentParams(AstNode* node);
};

}

#endif // TYPEBUILDER_H

