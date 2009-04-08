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
#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include <language/duchain/classdeclaration.h>

namespace KDvelop
{
class Declaration;
}
namespace Php
{
class ParseSession;
class EditorIntegrator;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, Php::TypeBuilder> DeclarationBuilderBase;

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
    DeclarationBuilder(ParseSession* session) : m_lastVariableIdentifier(0) {
        setEditor(session);
    }
    DeclarationBuilder(EditorIntegrator* editor) : m_lastVariableIdentifier(0) {
        setEditor(editor);
    }
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, Php::AstNode* node,
            KDevelop::ReferencedTopDUContext updateContext
            = KDevelop::ReferencedTopDUContext(), bool useSmart = true);

protected:
    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node);
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node);
    virtual void visitClassStatement(ClassStatementAst *node);
    virtual void visitClassExtends(ClassExtendsAst *node);
    virtual void visitClassImplements(ClassImplementsAst *node);
    virtual void visitParameter(ParameterAst *node);
    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node);
    virtual void visitClassVariable(ClassVariableAst *node);
    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *node);
    virtual void visitExpr(ExprAst *node);
    virtual void visitTopStatement(TopStatementAst* node);
    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node);
    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node);
    virtual void visitFunctionCall(FunctionCallAst* node);
    virtual void visitStatement(StatementAst* node);
    virtual void visitStaticVar(StaticVarAst* node);
    virtual void visitGlobalVar(GlobalVarAst* node);

    /// checks whether the body is empty (i.e. equals ";" instead of "{...}")
    bool isEmptyMethodBody(const Php::MethodBodyAst* body) const {
        return !body || !body->statements;
    }

    virtual void closeDeclaration();
    void classContextOpened(KDevelop::DUContext* context);

private:
    VariableIdentifierAst* m_lastVariableIdentifier;
    unsigned int m_currentModifers;
    QString m_lastTopStatementComment;

    QHash<qint64, KDevelop::ClassDeclaration*> m_types;
    QHash<qint64, KDevelop::FunctionDeclaration*> m_functions;

    /// handles common stuff for both interfaces and classes
    KDevelop::ClassDeclaration* openTypeDeclaration(IdentifierAst *name, KDevelop::ClassDeclarationData::ClassType type);

    /// check if this declaration is already declared
    bool isGlobalRedeclaration(const KDevelop::QualifiedIdentifier &identifier, AstNode *node,
                               DeclarationType type);
    /// check if a non-abstract method declaration tries to overwrite a final base method
    /// or whether a abstract method is redeclared
    /// @param identifier   The identifier for the current method
    /// @param curClass     the current class we are in
    /// @param node         the node we are processing, used to access modifiers and for error reporting
    bool isBaseMethodRedeclaration(const KDevelop::Identifier &identifier, KDevelop::ClassDeclaration *curClass,
                                   ClassStatementAst *node);
    /// reports a redeclaration error for the given node
    /// @param declaration the old declaration
    /// @param node        the AstNode which resembles the redeclaration
    void reportRedeclarationError(KDevelop::Declaration* declaration, AstNode *node);
};

}

#endif // DECLARATIONBUILDER_H

