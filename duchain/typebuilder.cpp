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

#include "typebuilder.h"

#include <ktexteditor/smartrange.h>

#include <language/duchain/identifier.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include "editorintegrator.h"
#include "parsesession.h"
#include "phpdebugvisitor.h"

using namespace KDevelop;
namespace Php {

bool TypeBuilder::nodeValid(AstNode* node) const
{
  return node && node->startToken <= node->endToken;
}

void TypeBuilder::visitClassDeclarationStatement( ClassDeclarationStatementAst* node )
{
    ClassType::Ptr classType = ClassType::Ptr(new ClassType());
    classType->setClassType(Class);

    openType(classType);

    classTypeOpened(currentAbstractType()); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

    TypeBuilderBase::visitClassDeclarationStatement(node);

    // Prevent additional elements being added if this becomes the current type again
    classType->close();

    closeType();
}

void TypeBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node)
{
    ClassType::Ptr classType = ClassType::Ptr(new ClassType());
    classType->setClassType(Interface);

    openType(classType);

    classTypeOpened(currentAbstractType()); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

    TypeBuilderBase::visitInterfaceDeclarationStatement(node);

    // Prevent additional elements being added if this becomes the current type again
    classType->close();

    closeType();

}

void TypeBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration
        FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());

        openType(functionType);

        TypeBuilderBase::visitClassStatement(node);

        closeType();

    } else {
        //member-variable
        TypeBuilderBase::visitClassStatement(node);
    }
}


void TypeBuilder::visitParameter(ParameterAst *node)
{
    TypeBuilderBase::visitParameter(node);
    if (hasCurrentType()) {
        if (FunctionType::Ptr function = currentType<FunctionType>()) {
            if (node->parameterType && openTypeFromName(node->parameterType, true)) {
                closeType();
                function->addArgument(lastType());
            }
        }
    }
}

void TypeBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{

    FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());

    openType(functionType);

    m_currentFunctionType = functionType;

    TypeBuilderBase::visitFunctionDeclarationStatement(node);

    m_currentFunctionType = 0;

    closeType();

}

void TypeBuilder::visitExpr(ExprAst *node)
{
    m_expressionType = 0;
    TypeBuilderBase::visitExpr(node);
}

void TypeBuilder::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    if(openTypeFromName(identifierForNode(node->variable), node, true)) {
        closeType();
        m_expressionType = lastType();
    }
    TypeBuilderBase::visitCompoundVariableWithSimpleIndirectReference(node);
}

void TypeBuilder::visitFunctionCall(FunctionCallAst* node)
{
    TypeBuilderBase::visitFunctionCall(node);
    {
        //TODO: stringFunctionNameOrClass::stringFunctionName (static calls)
        DUChainReadLocker lock(DUChain::lock());
        QList<Declaration*> declarations = currentContext()->findDeclarations(identifierForNode(node->stringFunctionNameOrClass));
        if (!declarations.isEmpty()) {
            FunctionType::Ptr function = declarations.last()->type<FunctionType>();
            if (function) {
                m_expressionType = function->returnType();
            }
        }
    }
}

void TypeBuilder::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    TypeBuilderBase::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        if(openTypeFromName(node->className->identifier, true)) {
            closeType();
            m_expressionType = lastType();
        }
    }
}
void TypeBuilder::visitScalar(ScalarAst *node)
{
    TypeBuilderBase::visitScalar(node);

    //TODO: is this correct?
    IntegralType::Ptr integral(new IntegralType());
    m_expressionType = AbstractType::Ptr::staticCast(integral);
}
void TypeBuilder::visitStatement(StatementAst* node)
{
    TypeBuilderBase::visitStatement(node);
    if (node->returnExpr && m_expressionType && m_currentFunctionType) {
        m_currentFunctionType->setReturnType(m_expressionType);
    }
}

}

