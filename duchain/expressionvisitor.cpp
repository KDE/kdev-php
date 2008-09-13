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
#include "editorintegrator.h"
#include "helper.h"

#include <language/duchain/topducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/structuretype.h>

using namespace KDevelop;

namespace Php {

ExpressionVisitor::ExpressionVisitor(EditorIntegrator* editor, bool useCursor)
    : m_editor(editor), m_useCursor(useCursor)
{
}

void ExpressionVisitor::visitExpr(ExprAst *node)
{
    if (node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);
    DefaultVisitor::visitExpr(node);
}

void ExpressionVisitor::visitAssignmentExpression(AssignmentExpressionAst *node)
{
    DefaultVisitor::visitAssignmentExpression(node);
}

void ExpressionVisitor::visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
{
    DefaultVisitor::visitAssignmentExpressionEqual(node);
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
            m_result.setDeclaration(m_currentContext->parentContext()->owner());
        }
    } else {
        DUChainReadLocker lock(DUChain::lock());
        SimpleCursor position = SimpleCursor::invalid();
        if (m_useCursor) {
            position = m_editor->findPosition(node->variable->variable, EditorIntegrator::FrontEdge);
        }
        m_result.setDeclarations(m_currentContext->findDeclarations(identifier, position));
    }
    if (!m_result.allDeclarations().isEmpty()) {
        usingDeclaration(node->variable, m_result.allDeclarations().last());
    }
    DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
}

void ExpressionVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    DefaultVisitor::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        QualifiedIdentifier id = identifierForNode(node->className->identifier);
        Declaration* dec = findClassDeclaration(m_currentContext, id);
        DUChainReadLocker lock(DUChain::lock());
        m_result.setDeclaration(dec);
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
            if (m_editor->parseSession()->symbol(node->stringFunctionNameOrClass->string) != "self") {
                ident += m_editor->parseSession()->symbol(node->stringFunctionNameOrClass->string);
                ident += "::";
            }
            ident += m_editor->parseSession()->symbol(node->stringFunctionName->string);
            m_result.setDeclarations(m_currentContext->findDeclarations(QualifiedIdentifier(ident)));
            lock.unlock();
            if (!m_result.allDeclarations().isEmpty()) {
                usingDeclaration(node->stringFunctionName, m_result.allDeclarations().last());
                FunctionType::Ptr function = m_result.allDeclarations().last()->type<FunctionType>();
                if (function) {
                    m_result.setType(function->returnType());
                } else {
                    m_result.setType(AbstractType::Ptr());
                }
            }
        } else if (node->varFunctionName) {
            //static function call foo::$bar()
        } else {
            //global function call foo();
            DUChainReadLocker lock(DUChain::lock());
            QualifiedIdentifier functionIdentifier(m_editor->parseSession()->symbol(node->stringFunctionNameOrClass->string));
            m_result.setDeclarations(m_currentContext->findDeclarations(functionIdentifier));
            if (!m_result.allDeclarations().isEmpty()) {
                FunctionType::Ptr function = m_result.allDeclarations().last()->type<FunctionType>();
                if (function) {
                    m_result.setType(function->returnType());
                } else {
                    m_result.setType(AbstractType::Ptr());
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
        QualifiedIdentifier functionIdentifier(m_editor->parseSession()->symbol(node->string));
        QList<Declaration*> declarations = m_currentContext->findDeclarations(functionIdentifier);
        m_result.setDeclarations(declarations);
    } else {
        //TODO: is this correct?
        IntegralType::Ptr integral(new IntegralType());
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    }
}

void ExpressionVisitor::visitVariableProperty(VariablePropertyAst *node)
{
    if (node->objectProperty->objectDimList) {
        //handle $foo->bar() and $foo->baz, $foo is m_result.type()

        if (m_result.type() && StructureType::Ptr::dynamicCast(m_result.type())) {
            DUChainReadLocker lock(DUChain::lock());
            QualifiedIdentifier id = StructureType::Ptr::staticCast(m_result.type())->qualifiedIdentifier();
            QList<Declaration*> declarations = m_currentContext->findDeclarations(id);
            if (!declarations.isEmpty()) {
                DUContext* context = declarations.first()->internalContext();
                if (!context && m_currentContext->parentContext()->localScopeIdentifier() == declarations.first()->qualifiedIdentifier()) {
                    //class is currentClass (internalContext is not yet set)
                    context = m_currentContext->parentContext();
                }
                QualifiedIdentifier propertyId = identifierForNode(node->objectProperty->objectDimList->variableName->name);
                m_result.setDeclarations(context->findDeclarations(propertyId));
                lock.unlock();
                if (!m_result.allDeclarations().isEmpty()) {
                    usingDeclaration(node->objectProperty->objectDimList->variableName, m_result.allDeclarations().last());
                    if (node->isFunctionCall!=-1) {
                        FunctionType::Ptr function = m_result.allDeclarations().last()->type<FunctionType>();
                        if (function) {
                            m_result.setType(function->returnType());
                        } else {
                            m_result.setType(AbstractType::Ptr());
                        }
                    }
                } else {
                    m_result.setType(AbstractType::Ptr());
                }
            } else {
                m_result.setType(AbstractType::Ptr());
            }
        }
    }
    DefaultVisitor::visitVariableProperty(node);
}

void ExpressionVisitor::visitStaticMember(StaticMemberAst* node)
{
    //don't call DefaultVisitor::visitStaticMember(node);
    //because we would end up in visitCompoundVariableWithSimpleIndirectReference
    if (node->variable->variable->variable) {
        DUContext* context = 0;
        if (identifierForNode(node->className) == QualifiedIdentifier("self")) {
            context = m_currentContext->parentContext();
        } else {
            DUChainReadLocker lock(DUChain::lock());
            QList<Declaration*> declarations = m_currentContext->findDeclarations(identifierForNode(node->className));
            if (!declarations.isEmpty()) {
                context = declarations.first()->internalContext();
                lock.unlock();
                if (!context && m_currentContext->parentContext()->localScopeIdentifier() == declarations.first()->qualifiedIdentifier()) {
                    //className is currentClass (internalContext is not yet set)
                    context = m_currentContext->parentContext();
                }
                usingDeclaration(node->className, declarations.last());
            }
        }
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            m_result.setDeclarations(context->findDeclarations(identifierForNode(node->variable->variable->variable)));
            lock.unlock();
            usingDeclaration(node->variable->variable->variable, m_result.allDeclarations().last());
        } else {
            m_result.setType(AbstractType::Ptr());
        }
    }
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(IdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();

    return QualifiedIdentifier(m_editor->parseSession()->symbol(id->string));
}
QualifiedIdentifier ExpressionVisitor::identifierForNode(VariableIdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();
    QString ret(m_editor->parseSession()->symbol(id->variable));
    ret = ret.mid(1); //cut off $
    return QualifiedIdentifier(ret);
}

}
