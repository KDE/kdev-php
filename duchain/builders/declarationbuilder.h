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

#ifndef DECLARATIONBUILDER_H
#define DECLARATIONBUILDER_H

#include "typebuilder.h"
#include "helper.h"
#include <language/duchain/classdeclaration.h>
#include <language/duchain/builders/abstractdeclarationbuilder.h>

namespace KDvelop
{
class Declaration;
}
namespace Php
{
class ParseSession;
class EditorIntegrator;
class ClassDeclaration;
class FunctionDeclaration;
class NamespaceDeclaration;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, TypeBuilder> DeclarationBuilderBase;

/**
 * The DeclarationBuilder builds declarations, types and contexts for everything in a AST.
 *
 * \note Since PHP allows the usage of functions, classes and interfaces before definition,
 *       a \see PreDeclarationBuilder is used to get the declarations _and_ types for those.
 *       Thus type- and declaratoinbuilding for these is skipped in this class.
 */
class KDEVPHPDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase
{
public:
    DeclarationBuilder(EditorIntegrator* editor)
        : m_currentModifers(0)
    {
        m_editor = editor;
        m_findVariable.find = false;
    }
    KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, AstNode* node,
            KDevelop::ReferencedTopDUContext updateContext
            = KDevelop::ReferencedTopDUContext()) override;

    void startVisiting(AstNode* node) override;

protected:
    void visitClassDeclarationStatement(ClassDeclarationStatementAst *node) override;
    void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node) override;
    void visitTraitDeclarationStatement(TraitDeclarationStatementAst *node) override;
    void visitClassStatement(ClassStatementAst *node) override;
    virtual void importTraitMethods(ClassStatementAst *node);
    void visitClassExtends(ClassExtendsAst *node) override;
    void visitClassImplements(ClassImplementsAst *node) override;
    void visitParameterList(ParameterListAst *node) override;
    void visitParameter(ParameterAst *node) override;
    void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node) override;
    void visitReturnType(ReturnTypeAst *node) override;
    void visitClassVariable(ClassVariableAst *node) override;
    void visitConstantDeclaration(ConstantDeclarationAst *node) override;
    void visitClassConstantDeclaration(ClassConstantDeclarationAst *node) override;
    void visitTraitAliasStatement(TraitAliasStatementAst *node) override;
    virtual void createTraitAliasDeclarations(TraitAliasStatementAst *node, KDevelop::DeclarationPointer dec);
    void visitOuterTopStatement(OuterTopStatementAst* node) override;
    void visitAssignmentExpression(AssignmentExpressionAst* node) override;
    void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node) override;
    void visitVariable(VariableAst* node) override;
    void visitFunctionCall(FunctionCallAst* node) override;
    void visitFunctionCallParameterList(FunctionCallParameterListAst* node) override;
    void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst* node) override;
    void visitStatement(StatementAst* node) override;
    void visitStaticVar(StaticVarAst* node) override;
    void visitGlobalVar(GlobalVarAst* node) override;
    void visitCatchItem(CatchItemAst *node) override;
    void visitUnaryExpression( UnaryExpressionAst* node ) override;
    void visitAssignmentListElement(AssignmentListElementAst* node) override;
    void openNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node, const IdentifierPair& identifier, const KDevelop::RangeInRevision& range) override;
    void closeNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node, const IdentifierPair& identifier) override;
    void visitUseNamespace(UseNamespaceAst* node) override;
    void visitClosure(ClosureAst* node) override;
    void visitLexicalVar(LexicalVarAst* node) override;
    void visitVarExpression(VarExpressionAst* node) override;

    /// checks whether the body is empty (i.e. equals ";" instead of "{...}")
    bool isEmptyMethodBody(const MethodBodyAst* body) const {
        return !body || !body->statements;
    }

    void closeDeclaration() override;
    void classContextOpened(KDevelop::DUContext* context) override;

    void supportBuild(AstNode* node, KDevelop::DUContext* context = nullptr) override;
    void closeContext() override;

    /// don't forget to closeDeclaration() afterwards
    /// set m_currentModifers to your likings and reset it afterwards
    void openClassMemberDeclaration(AstNode* node, const KDevelop::QualifiedIdentifier& name);

    void updateCurrentType() override;

private:
    /// because the predeclarationbuilder runs before us,
    /// we always "think" that we are recompiling, while this is not necessarily true
    bool m_actuallyRecompiling;

    struct FindVariableResults {
        /// Set this to true if you want to catch any variable in the lower AST tree
        bool find;
        /// If the found variable is accessed as an array ($var[...]) this is set to true.
        /// @see m_findVariable
        bool isArray;
        /// The identifier for the found variable.
        /// @see m_findVariable
        KDevelop::QualifiedIdentifier identifier;
        /// The identifier for the parent of the found variable. Empty if
        /// the found variable is not a class member.
        /// @see m_findVariable
        KDevelop::QualifiedIdentifier parentIdentifier;
        /// The AstNode of the found variable. Use this for declarations.
        /// @see m_findVariable
        AstNode* node;

        FindVariableResults();
    };
    FindVariableResults m_findVariable;

    /// The position of the current argument, will only be set inside function calls.
    int m_functionCallParameterPos;
    /// Type of the current function, will only be set inside function calls.
    KDevelop::FunctionType::Ptr m_currentFunctionType;
    /// The AstNode of the previous function declaration argument
    ParameterAst *m_functionDeclarationPreviousArgument = nullptr;
    /// The AstNode of the previous function call argument
    FunctionCallParameterListElementAst *m_functionCallPreviousArgument = nullptr;

    unsigned int m_currentModifers;
    QString m_lastTopStatementComment;

    QHash<qint64, ClassDeclaration*> m_types;
    QHash<qint64, FunctionDeclaration*> m_functions;
    QHash<qint64, NamespaceDeclaration*> m_namespaces;
    QVector<KDevelop::QualifiedIdentifier> m_upcomingClassVariables;

    /// handles common stuff for both interfaces and classes
    ClassDeclaration* openTypeDeclaration(IdentifierAst *name, KDevelop::ClassDeclarationData::ClassType type);

    /// check if this declaration is already declared
    bool isGlobalRedeclaration(const KDevelop::QualifiedIdentifier &identifier, AstNode *node,
                               DeclarationType type);
    /// check if a non-abstract method declaration tries to overwrite a final base method
    /// or whether a abstract method is redeclared
    /// @param ids      The identifier for the current method
    /// @param curClass the current class we are in
    /// @param node     the node we are processing, used to access modifiers and for error reporting
    bool isBaseMethodRedeclaration(const IdentifierPair &ids, ClassDeclaration *curClass,
                                   ClassStatementAst *node);
    /// reports a redeclaration error for the given node
    /// @param declaration the old declaration
    /// @param node        the AstNode which resembles the redeclaration
    void reportRedeclarationError(KDevelop::Declaration* declaration, AstNode *node);

    /**
     * Get the interesting identifiers out of a VariableAst node:
     * $var yields @p id = 'var', @p parent = ''
     * $var->asdf yields @p id = 'asdf', @p parent = 'asdf'
     * $var->...->foo->bar yields @p id = 'bar', @p parent => 'foo'
     *
     * @note If the parent or the identifier itself end on an array access, e.g. $var[0] or
     *       $var->...->parent[0]->bar, @p arrayAccess will be set to true.
     *
     * @param id the last identifier
     * @param parent the parent of the last identifier
     * @param targetNode the node of the last identifier
     * @param arrayAccess the node actually ends on an array access, like $node->var->..->asdf[0]
     */
    void getVariableIdentifier(VariableAst *node,
                                    KDevelop::QualifiedIdentifier &id,
                                    KDevelop::QualifiedIdentifier &parent,
                                    AstNode* &targetNode,
                                    bool &arrayAccess);

    /**
     * Declare a class member in @p parentCtx. Validates whether the current context allowes
     * redeclaration of private/protected members.
     *
     * @param parentCtx  The class context you want to add the member to.
     * @param type       The type of the member.
     * @param identifier The identifier of the member.
     * @param node       The node of the member.
     */
    void declareClassMember(KDevelop::DUContext *parentCtx, KDevelop::AbstractType::Ptr type,
                            const KDevelop::QualifiedIdentifier& identifier, AstNode* node );

    /**
     * Declare a variable in @p parentCtx. If the variable is already defined in the
     * context and it's last type equals @p type, don't do anything.
     *
     * @param parentCtx  The context you want to declare the variable in.
     * @param type       The type of the variable
     * @param identifier The identifier for the variable.
     * @param node       The node for the variable.
     */
    void declareVariable(KDevelop::DUContext *parentCtx, KDevelop::AbstractType::Ptr type,
                            const KDevelop::QualifiedIdentifier& identifier, AstNode* node );

    /**
     * Wrapper that operates declares the found variable. It will declare it
     * either as a class member or as a variable, depending whether a parent was found.
     *
     * It will also check whether that var also exists and if so, won't do anything.
     *
     * @param type When the var gets declared, this will be it's type.
     *
     * @see m_findVariable
     * @see declareClassMeember
     * @see declareVariable
     */
    void declareFoundVariable(KDevelop::AbstractType::Ptr type);

    /**
     * Sets encountered and updates the comment when we are recompiling.
     */
    void encounter(KDevelop::Declaration* dec);

    bool isReservedClassName(QString className);
};

}

#endif // DECLARATIONBUILDER_H

