/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Milian Wolff <mail@milianw.de>                         *
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

#include "declarationbuilderbase.h"

#include "typebuilder.h"
#include "helper.h"
#include <language/duchain/builders/abstractdeclarationbuilder.h>

namespace KDvelop {
    class Declaration;
}
namespace Php {
class ParseSession;
class EditorIntegrator;


class KDEVPHPDUCHAIN_EXPORT PreDeclarationBuilder : public DeclarationBuilderBase {
public:
    PreDeclarationBuilder(QHash<qint64, ClassDeclaration*>* types, QHash<qint64,
                          KDevelop::FunctionDeclaration*>* functions,
                          ParseSession* session)
                        : DeclarationBuilderBase(session), m_types(types), m_functions(functions) {}
    PreDeclarationBuilder(QHash<qint64, ClassDeclaration*>* types, QHash<qint64,
                          KDevelop::FunctionDeclaration*>* functions,
                          EditorIntegrator* editor)
                        : DeclarationBuilderBase(editor), m_types(types), m_functions(functions) {}
    
protected:
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

private:
    QHash<qint64, ClassDeclaration*>* m_types;
    QHash<qint64, KDevelop::FunctionDeclaration*>* m_functions;
};

}

#endif // PREDECLARATIONBUILDER_H

