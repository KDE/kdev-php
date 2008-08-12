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
QList<Declaration*> ExpressionVisitor::lastDeclarations()
{
    return m_lastDeclarations;
}
void ExpressionVisitor::visitExpr(ExprAst *node)
{
    if (node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);
    DefaultVisitor::visitExpr(node);
    DUChainReadLocker lock(DUChain::lock());
}
void ExpressionVisitor::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    QualifiedIdentifier identifier = identifierForNode(node->variable);
    if (identifier == QualifiedIdentifier("this")) {
        DUChainReadLocker lock(DUChain::lock());
        if (m_currentContext->parentContext()
            && m_currentContext->parentContext()->type() == DUContext::Class
            && m_currentContext->parentContext()->owner())
        {
            m_lastType = m_currentContext->parentContext()->owner()->abstractType();
        }
    } else {
        DUChainReadLocker lock(DUChain::lock());
        m_lastDeclarations = m_currentContext->findDeclarations(identifier);
        if (!m_lastDeclarations.isEmpty()) {
            m_lastType = m_lastDeclarations.first()->abstractType();
        }
    }
    DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
}

void ExpressionVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    DefaultVisitor::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        DUChainReadLocker lock(DUChain::lock());
        QualifiedIdentifier id = identifierForNode(node->className->identifier);
        m_lastDeclarations = m_currentContext->findDeclarations(id);
        if (!m_lastDeclarations.isEmpty()) {
            m_lastType = m_lastDeclarations.first()->abstractType();
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
            m_lastDeclarations = m_currentContext->findDeclarations(QualifiedIdentifier(ident));
            if (!m_lastDeclarations.isEmpty()) {
                FunctionType::Ptr function = m_lastDeclarations.last()->type<FunctionType>();
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
            m_lastDeclarations = m_currentContext->findDeclarations(functionIdentifier);
            if (!m_lastDeclarations.isEmpty()) {
                FunctionType::Ptr function = m_lastDeclarations.last()->type<FunctionType>();
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
    if (node->string != -1 && node->constname == -1) {
        //it could be a global function call, without ()
        DUChainReadLocker lock(DUChain::lock());
        QualifiedIdentifier functionIdentifier(m_session->symbol(node->string));
        m_lastDeclarations = m_currentContext->findDeclarations(functionIdentifier);
        if (!m_lastDeclarations.isEmpty()) {
            if (m_lastDeclarations.last()->type<FunctionType>()) {
                m_lastType = m_lastDeclarations.last()->abstractType();
                return;
            }
        }
    }
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
                m_lastDeclarations = m_currentContext->findDeclarations(id);
                if (!m_lastDeclarations.isEmpty()) {
                    DUContext* context = m_lastDeclarations.first()->internalContext();
                    if (!context && m_currentContext->parentContext()->localScopeIdentifier() == m_lastDeclarations.first()->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = m_currentContext->parentContext();
                    }
                    QualifiedIdentifier propertyId = identifierForNode(node->objectProperty->objectDimList->variableName->name);
                    m_lastDeclarations = context->findDeclarations(propertyId);
                    m_lastType = 0;
                    if (!m_lastDeclarations.isEmpty()) {
                        if (node->isFunctionCall!=-1 && m_lastDeclarations.first()->type<FunctionType>()) {
                            m_lastType = m_lastDeclarations.first()->type<FunctionType>()->returnType();
                        } else {
                            m_lastType = m_lastDeclarations.first()->abstractType();
                        }
                    } else {
                        m_lastType = 0;
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
            m_lastDeclarations = m_currentContext->findDeclarations(identifierForNode(node->className));
            if (!m_lastDeclarations.isEmpty()) {
                context = m_lastDeclarations.first()->internalContext();
                if (!context && m_currentContext->parentContext()->localScopeIdentifier() == m_lastDeclarations.first()->qualifiedIdentifier()) {
                    //className is currentClass (internalContext is not yet set)
                    context = m_currentContext->parentContext();
                }
            }
        }
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            m_lastDeclarations = context->findDeclarations(identifierForNode(node->variable->variable->variable));
            if (!m_lastDeclarations.isEmpty()) {
                m_lastType = m_lastDeclarations.first()->abstractType();
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
    QString ret(m_session->symbol(id->variable));
    ret = ret.mid(1); //cut off $
    return QualifiedIdentifier(ret);
}

}
