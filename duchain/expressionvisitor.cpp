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
#include "expressionvisitor.h"
#include "parsesession.h"

#include <duchain/topducontext.h>
#include <duchain/duchain.h>
#include <duchain/duchainlock.h>
#include "types.h"

using namespace KDevelop;

namespace Php {

ExpressionVisitor::ExpressionVisitor(ParseSession* session, const TopDUContext* source, bool strict)
    : m_session(session), m_source(source), m_strict(strict)
{
}

AbstractType::Ptr ExpressionVisitor::lastType()
{
    return m_lastType;
}

void ExpressionVisitor::visitExpr(ExprAst *node)
{
    if (node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);
    DefaultVisitor::visitExpr(node);
}
void ExpressionVisitor::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    //QualifiedIdentifier identifier = identifierForNode(node->variable);
    QualifiedIdentifier identifier(m_session->symbol(node->variable->variable));
    if (identifier == QualifiedIdentifier("$this")) {
        DUChainReadLocker lock(DUChain::lock());
        if (m_currentContext->parentContext()
            && m_currentContext->parentContext()->type() == DUContext::Class
            && m_currentContext->parentContext()->owner())
        {
            m_lastType = m_currentContext->parentContext()->owner()->abstractType();
        }
    } else {
        DUChainReadLocker lock(DUChain::lock());
        QList<Declaration*> declarations = m_currentContext->findDeclarations(identifier);
        if (!declarations.isEmpty()) {
            m_lastType = declarations.first()->abstractType();
        }
    }
    DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
}

void ExpressionVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    DefaultVisitor::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        DUChainReadLocker lock(DUChain::lock());
        //TODO: add identifierForNode method somewhere
        QualifiedIdentifier id(m_session->symbol(node->className->identifier->string));
        QList<Declaration*> declarations = m_currentContext->findDeclarations(id);
        if (!declarations.isEmpty()) {
            m_lastType = declarations.first()->abstractType();
        }
    }
}

void ExpressionVisitor::visitFunctionCall(FunctionCallAst* node)
{
    DefaultVisitor::visitFunctionCall(node);
    if (node->stringFunctionNameOrClass) {
        if (node->stringFunctionName) {
            //static function call foo::bar()
            DUChainReadLocker lock(DUChain::lock());
            QString ident;
            if (m_session->symbol(node->stringFunctionNameOrClass->string) != "self") {
                ident += m_session->symbol(node->stringFunctionNameOrClass->string);
                ident += "::";
            }
            ident += m_session->symbol(node->stringFunctionName->string);
            QList<Declaration*> declarations = m_currentContext->findDeclarations(QualifiedIdentifier(ident));
            if (!declarations.isEmpty()) {
                FunctionType::Ptr function = declarations.last()->type<FunctionType>();
                if (function) {
                    m_lastType = function->returnType();
                }
            }
        } else if (node->varFunctionName) {
            //static function call foo::$bar()
        } else {
            //global function call foo();
            DUChainReadLocker lock(DUChain::lock());
            QualifiedIdentifier functionIdentifier(m_session->symbol(node->stringFunctionNameOrClass->string));
            QList<Declaration*> declarations = m_currentContext->findDeclarations(functionIdentifier);
            if (!declarations.isEmpty()) {
                FunctionType::Ptr function = declarations.last()->type<FunctionType>();
                if (function) {
                    m_lastType = function->returnType();
                }
            }
        }
    }
}


void ExpressionVisitor::visitScalar(ScalarAst *node)
{
    DefaultVisitor::visitScalar(node);

    //TODO: is this correct?
    IntegralType::Ptr integral(new IntegralType());
    m_lastType = AbstractType::Ptr::staticCast(integral);
}

void ExpressionVisitor::visitVariableProperty(VariablePropertyAst *node)
{
    if (node->objectProperty->objectDimList) {
        //handle $foo->bar() and $foo->baz, $foo is m_lastType
        if (m_lastType) {
            if (ClassType::Ptr::dynamicCast(m_lastType)) {
                DUChainReadLocker lock(DUChain::lock());
                QualifiedIdentifier id = ClassType::Ptr::staticCast(m_lastType)->qualifiedIdentifier();
                QList<Declaration*> variableDecs = m_currentContext->findDeclarations(id);
                if (!variableDecs.isEmpty()) {
                    DUContext* context = variableDecs.first()->internalContext();
                    if (!context && m_currentContext->parentContext()->localScopeIdentifier() == variableDecs.first()->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = m_currentContext->parentContext();
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
                            m_lastType = functionType->returnType();
                        } else {
                            m_lastType = 0;
                        }
                    } else {
                        //member variable $foo->bar
                        //TODO: better solution for adding the $
                        QualifiedIdentifier varId = QualifiedIdentifier(QString("$") + propertyId.toString());
                        QList<Declaration*> propertyDeclarations = context->findDeclarations(varId);
                        if (!propertyDeclarations.isEmpty()) {
                            m_lastType = propertyDeclarations.first()->abstractType();
                        } else {
                            m_lastType = 0;
                        }
                    }
                } else {
                    m_lastType = 0;
                }
            }
        }
    }
    DefaultVisitor::visitVariableProperty(node);
}

void ExpressionVisitor::visitStaticMember(StaticMemberAst* node)
{
    DefaultVisitor::visitStaticMember(node);
    if (node->variable->variable->variable) {
        DUContext* context = 0;
        if (identifierForNode(node->className) == QualifiedIdentifier("self")) {
            context = m_currentContext->parentContext();
        } else {
            DUChainReadLocker lock(DUChain::lock());
            QList<Declaration*> decs = m_currentContext->findDeclarations(identifierForNode(node->className));
            if (!decs.isEmpty()) {
                context = decs.first()->internalContext();
                if (!context && m_currentContext->parentContext()->localScopeIdentifier() == decs.first()->qualifiedIdentifier()) {
                    //className is currentClass (internalContext is not yet set)
                    context = m_currentContext->parentContext();
                }
            }
        }
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            QList<Declaration*> decs = context->findDeclarations(identifierForNode(node->variable->variable->variable));
            if (!decs.isEmpty()) {
                m_lastType = decs.first()->abstractType();
            } else {
                m_lastType = 0;
            }
        } else {
            m_lastType = 0;
        }
    }
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(IdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();

    return QualifiedIdentifier(m_session->symbol(id->string));
}
QualifiedIdentifier ExpressionVisitor::identifierForNode(VariableIdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();

    return QualifiedIdentifier(m_session->symbol(id->variable));
}

}
