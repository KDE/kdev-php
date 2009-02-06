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

#ifndef PREDECLARATIONBUILDER_H
#define PREDECLARATIONBUILDER_H

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

class KDEVPHPDUCHAIN_EXPORT PreDeclarationBuilder : public DeclarationBuilderBase {
public:
    PreDeclarationBuilder(ParseSession* session);
    PreDeclarationBuilder(EditorIntegrator* editor);

protected:
    virtual void closeDeclaration();
    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node);
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node);
    virtual void visitClassStatement(ClassStatementAst *node){Q_UNUSED(node);}
    virtual void visitClassExtends(ClassExtendsAst *node){Q_UNUSED(node);}
    virtual void visitClassImplements(ClassImplementsAst *node){Q_UNUSED(node);}
    virtual void visitParameter(ParameterAst *node){Q_UNUSED(node);}
    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node);
    virtual void visitClassVariable(ClassVariableAst *node){Q_UNUSED(node);}
    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *node){Q_UNUSED(node);}
    virtual void visitExpr(ExprAst *node){Q_UNUSED(node);}
    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node){Q_UNUSED(node);}
    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node){Q_UNUSED(node);}
    virtual void visitFunctionCall(FunctionCallAst* node){Q_UNUSED(node);}
    virtual void visitStatement(StatementAst* node){Q_UNUSED(node);}
    virtual void visitStaticVar(StaticVarAst* node){Q_UNUSED(node);}
    virtual void visitGlobalVar(GlobalVarAst* node){Q_UNUSED(node);}

    void classTypeOpened(KDevelop::AbstractType::Ptr type);
    void classContextOpened(KDevelop::DUContext* context);

private:
    QString m_lastTopStatementComment;
};

}

#endif // PREDECLARATIONBUILDER_H

