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

ClassType::Ptr TypeBuilder::parseDocComment(AstNode* node, const QString& docCommentName)
{
    QString docComment = editor()->parseSession()->docComment(node->startToken);
    if (!docComment.isEmpty()) {
        QRegExp rx("\\* +@"+QRegExp::escape(docCommentName)+" ([^ ]*)");
        if (rx.indexIn(docComment) != -1) {
            if(openTypeFromName(QualifiedIdentifier(rx.cap(1)), node, true)) {
                closeType();
                return ClassType::Ptr::dynamicCast(lastType());
            }
        }
    }
    return ClassType::Ptr();
}

FunctionType::Ptr TypeBuilder::openFunctionType(AstNode* node)
{
    FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());

    openType(functionType);

    m_currentFunctionType = functionType;

    ClassType::Ptr returnType = parseDocComment(node, "return");
    if (returnType) {
        functionType->setReturnType(AbstractType::Ptr::staticCast(returnType));
    }

    return functionType;
}

void TypeBuilder::visitClassDeclarationStatement( ClassDeclarationStatementAst* node )
{
    ClassType::Ptr classType = ClassType::Ptr(new ClassType());
    classType->setClassType(Class);
    m_currentClass = classType;


    openType(classType);

    classTypeOpened(currentAbstractType()); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

    TypeBuilderBase::visitClassDeclarationStatement(node);

    // Prevent additional elements being added if this becomes the current type again
    classType->close();

    closeType();

    m_currentClass = 0;
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
        openFunctionType(node);
        TypeBuilderBase::visitClassStatement(node);
        m_currentFunctionType = 0;
        closeType();
    } else {
        //member-variable
        parseDocComment(node, "var"); //sets lastType(), used openDefinition
        TypeBuilderBase::visitClassStatement(node);
        clearLastType();
    }
}

void TypeBuilder::visitClassVariable(ClassVariableAst *node)
{
    TypeBuilderBase::visitClassVariable(node);
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
    openFunctionType(node);
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
    QualifiedIdentifier identifier = identifierForNode(node->variable);
    if (identifier == QualifiedIdentifier("$this")) {
        if (m_currentClass) {
            m_expressionType = AbstractType::Ptr::staticCast(m_currentClass);
        }
    } else if(openTypeFromName(identifier, node, true)) {
        closeType();
        m_expressionType = lastType();
    }
    TypeBuilderBase::visitCompoundVariableWithSimpleIndirectReference(node);
}

void TypeBuilder::visitFunctionCall(FunctionCallAst* node)
{
    TypeBuilderBase::visitFunctionCall(node);
    if (node->stringFunctionNameOrClass) {
        if (node->stringFunctionName) {
            //static function call foo::bar()
            DUChainReadLocker lock(DUChain::lock());
            QString ident;
            ident = editor()->parseSession()->symbol(node->stringFunctionNameOrClass->string);
            ident += "::";
            ident += editor()->parseSession()->symbol(node->stringFunctionName->string);
            QList<Declaration*> declarations = currentContext()->findDeclarations(QualifiedIdentifier(ident));
            if (!declarations.isEmpty()) {
                FunctionType::Ptr function = declarations.last()->type<FunctionType>();
                if (function) {
                    m_expressionType = function->returnType();
                }
            }
        } else if (node->varFunctionName) {
            //static function call foo::$bar()
        } else {
            //global function call foo();
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
    if (node->returnExpr && m_expressionType && m_currentFunctionType
            && (!m_currentFunctionType->returnType()
                || IntegralType::Ptr::dynamicCast(m_currentFunctionType->returnType())))
    {
        m_currentFunctionType->setReturnType(m_expressionType);
    }
}

void TypeBuilder::visitVariableProperty(VariablePropertyAst *node)
{
    if (node->objectProperty->objectDimList) {
        //handle $foo->bar() and $foo->baz, $foo is m_expressionType
        if (m_expressionType) {
            if (ClassType::Ptr::dynamicCast(m_expressionType)) {
                DUChainReadLocker lock(DUChain::lock());
                QualifiedIdentifier id = ClassType::Ptr::staticCast(m_expressionType)->qualifiedIdentifier();
                QList<Declaration*> variableDecs = currentContext()->findDeclarations(id);
                if (!variableDecs.isEmpty()) {
                    DUContext* context = variableDecs.first()->internalContext();
                    if (!context && currentContext()->parentContext()->localScopeIdentifier() == variableDecs.first()->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = currentContext()->parentContext();
                    }
                    QualifiedIdentifier propertyId = identifierForNode(node->objectProperty->objectDimList->variableName->name);
                    if (node->isFunctionCall != -1) {
                        //function call $foo->bar()
                        QList<Declaration*> propertyDeclarations = context->findDeclarations(propertyId);
                        FunctionType::Ptr functionType;
                        if (!propertyDeclarations.isEmpty()) {
                            functionType = propertyDeclarations.first()->type<FunctionType>();
                        }
                        if (functionType) {
                            m_expressionType = functionType->returnType();
                        } else {
                            m_expressionType = 0;
                        }
                    } else {
                        //member variable $foo->bar
                        //TODO: better solution for adding the $
                        QualifiedIdentifier varId = QualifiedIdentifier(QString("$") + propertyId.toString());
                        QList<Declaration*> propertyDeclarations = context->findDeclarations(varId);
                        if (!propertyDeclarations.isEmpty()) {
                            m_expressionType = propertyDeclarations.first()->abstractType();
                        } else {
                            m_expressionType = 0;
                        }
                    }
                } else {
                    m_expressionType = 0;
                }
            }
        }
    }
    TypeBuilderBase::visitVariableProperty(node);
}

void TypeBuilder::visitStaticMember(StaticMemberAst* node)
{
    TypeBuilderBase::visitStaticMember(node);
    if (node->variable->variable->variable) {
        DUContext* context = 0;
        if (identifierForNode(node->className) == QualifiedIdentifier("self")) {
            context = currentContext()->parentContext();
        } else {
            DUChainReadLocker lock(DUChain::lock());
            QList<Declaration*> decs = currentContext()->findDeclarations(identifierForNode(node->className));
            if (!decs.isEmpty()) {
                context = decs.first()->internalContext();
                if (!context && currentContext()->parentContext()->localScopeIdentifier() == decs.first()->qualifiedIdentifier()) {
                    //className is currentClass (internalContext is not yet set)
                    context = currentContext()->parentContext();
                }
            }
        }
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            QList<Declaration*> decs = context->findDeclarations(identifierForNode(node->variable->variable->variable));
            if (!decs.isEmpty()) {
                m_expressionType = decs.first()->abstractType();
            } else {
                m_expressionType = 0;
            }
        } else {
            m_expressionType = 0;
        }
    }
}

}

