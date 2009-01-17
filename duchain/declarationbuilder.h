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
namespace KDvelop {
    class Declaration;
}
namespace Php {
class ParseSession;
class EditorIntegrator;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, Php::TypeBuilder> DeclarationBuilderBase;

class KDEVPHPDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase {
public:
    DeclarationBuilder(ParseSession* session);
    DeclarationBuilder(EditorIntegrator* editor);
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, Php::AstNode* node,
                                            KDevelop::ReferencedTopDUContext updateContext
                                                = KDevelop::ReferencedTopDUContext(), bool useSmart = true );

protected:
    virtual void closeDeclaration();
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

    void classTypeOpened(KDevelop::AbstractType::Ptr type);
    void classContextOpened(KDevelop::DUContext* context);

private:
    void preBuild(const KDevelop::IndexedString& url, Php::AstNode* node,
                  KDevelop::ReferencedTopDUContext updateContext = KDevelop::ReferencedTopDUContext(),
                  bool useSmart = true);

    VariableIdentifierAst* m_lastVariableIdentifier;
    unsigned int m_currentModifers;
    QString m_lastTopStatementComment;
};

}

#endif // DECLARATIONBUILDER_H

