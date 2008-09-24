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

Declaration* ExpressionVisitor::processVariable(VariableIdentifierAst *variable)
{
    Declaration* ret = 0;
    QualifiedIdentifier identifier = identifierForNode(variable);
    if (identifier == QualifiedIdentifier("this")) {
        DUChainReadLocker lock(DUChain::lock());
        if (m_currentContext->parentContext()
            && m_currentContext->parentContext()->type() == DUContext::Class
            && m_currentContext->parentContext()->owner())
        {
            ret = m_currentContext->parentContext()->owner();
        }
    } else {
        DUChainReadLocker lock(DUChain::lock());
        SimpleCursor position = SimpleCursor::invalid();
        if (m_useCursor) {
            position = m_editor->findPosition(variable->variable, EditorIntegrator::FrontEdge);
        }
        QList<Declaration*> decs = m_currentContext->findDeclarations(identifier, position);
        if (!decs.isEmpty()) ret = decs.last();
    }
    if (ret) {
        usingDeclaration(variable, ret);
    }
    return ret;
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
    if (node->variable) {
        m_result.setDeclaration(processVariable(node->variable));
    }
    DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
}

void ExpressionVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    DefaultVisitor::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        QualifiedIdentifier id = identifierForNode(node->className->identifier);
        Declaration* dec = findDeclarationImport(m_currentContext, id, ClassDeclarationType);
        DUChainReadLocker lock(DUChain::lock());
        m_result.setDeclaration(dec);
    }
}

void ExpressionVisitor::visitVarExpressionNormal(VarExpressionNormalAst *node)
{
    DefaultVisitor::visitVarExpressionNormal(node);
    if (node->array != -1) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeArray)));
    }
}

void ExpressionVisitor::visitFunctionCall(FunctionCallAst* node)
{
    DefaultVisitor::visitFunctionCall(node);
    if (node->stringFunctionNameOrClass) {
        if (node->stringFunctionName) {
            //static function call foo::bar()
            DUContext* context = findClassContext(node->stringFunctionNameOrClass);
            if (context) {
                DUChainReadLocker lock(DUChain::lock());
                m_result.setDeclarations(context->findDeclarations(identifierForNode(node->stringFunctionName)));
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
            } else {
                m_result.setType(AbstractType::Ptr());
            }
        } else if (node->varFunctionName) {
            //static function call foo::$bar()
        } else {
            //global function call foo();
            QualifiedIdentifier functionIdentifier(m_editor->parseSession()->symbol(node->stringFunctionNameOrClass->string));
            Declaration* dec = findDeclarationImport(m_currentContext, functionIdentifier, FunctionDeclarationType);
            m_result.setDeclaration(dec);
            if (dec) {
                FunctionType::Ptr function = dec->type<FunctionType>();
                if (function) {
                    m_result.setType(function->returnType());
                } else {
                    m_result.setType(AbstractType::Ptr());
                }
            }
        }
    }
}
DUContext* ExpressionVisitor::findClassContext(IdentifierAst* className)
{
    DUContext* context = 0;
    Declaration* declaration = findDeclarationImport(m_currentContext, identifierForNode(className), ClassDeclarationType);
    if (declaration) {
        {
            DUChainReadLocker lock(DUChain::lock());
            context = declaration->internalContext();
        }
        if (!context && m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
            //className is currentClass (internalContext is not yet set)
            context = m_currentContext->parentContext();
        }
        usingDeclaration(className, declaration);
    }
    return context;
}
void ExpressionVisitor::visitScalar(ScalarAst *node)
{
    DefaultVisitor::visitScalar(node);

    if (node->className) {
        //class constant Foo::BAR
        DUContext* context = findClassContext(node->className);
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            m_result.setDeclarations(context->findDeclarations(identifierForNode(node->constant)));
            lock.unlock();
            if (!m_result.allDeclarations().isEmpty()) {
                usingDeclaration(node->constant, m_result.allDeclarations().last());
            }
        } else {
            m_result.setType(AbstractType::Ptr());
        }
    } else if (node->constant) {
        QualifiedIdentifier id(identifierForNode(node->constant));
        if (id == QualifiedIdentifier("true") || id == QualifiedIdentifier("false")) {
            IntegralType::Ptr integral(new IntegralType(IntegralType::TypeBoolean));
            m_result.setType(AbstractType::Ptr::staticCast(integral));
        } else if (id == QualifiedIdentifier("null")) {
            IntegralType::Ptr integral(new IntegralType(IntegralType::TypeNull));
            m_result.setType(AbstractType::Ptr::staticCast(integral));
        } else {
            //constant (created with declare('foo', 'bar'))
            //it could also be a global function call, without ()
            //TODO: prefer constant over function
            Declaration* declaration = findDeclarationImport(m_currentContext, id, ConstantDeclarationType);
            m_result.setDeclaration(declaration);
            if (declaration) {
                usingDeclaration(node->constant, declaration);
            }
        }
    } else if (node->commonScalar) {
        uint type;
        switch (node->commonScalar->scalarType) {
            case ScalarTypeInt:
                type = IntegralType::TypeInt;
                break;
            case ScalarTypeFloat:
                type = IntegralType::TypeFloat;
                break;
            case ScalarTypeString:
                type = IntegralType::TypeString;
                break;
        }
        IntegralType::Ptr integral(new IntegralType(type));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    } else if (node->varname != -1) {
        //STRING_VARNAME-Token, probably the type of varname should be used
        IntegralType::Ptr integral(new IntegralType(IntegralType::TypeString));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    } else if (node->encapsList) {
        IntegralType::Ptr integral(new IntegralType(IntegralType::TypeString));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    }
}

void ExpressionVisitor::visitEncaps(EncapsAst *node)
{
    DefaultVisitor::visitEncaps(node);
}

void ExpressionVisitor::visitEncapsVar(EncapsVarAst *node)
{
    DefaultVisitor::visitEncapsVar(node);
    if (node->variable) {
        Declaration* dec = processVariable(node->variable);
        if (dec && node->propertyIdentifier) {
            //$foo->bar inside a string
            DUChainReadLocker lock(DUChain::lock());
            StructureType::Ptr structType = dec->type<StructureType>();
            if (structType) {
                QualifiedIdentifier id = structType->qualifiedIdentifier();
                QList<Declaration*> declarations = m_currentContext->findDeclarations(id);
                if (!declarations.isEmpty()) {
                    DUContext* context = declarations.first()->internalContext();
                    if (!context && m_currentContext->parentContext()->localScopeIdentifier() == declarations.first()->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = m_currentContext->parentContext();
                    }
                    QualifiedIdentifier propertyId = identifierForNode(node->propertyIdentifier);
                    QList<Declaration*> found = context->findDeclarations(propertyId);
                    lock.unlock();
                    if (!found.isEmpty()) {
                        usingDeclaration(node->propertyIdentifier, found.last());
                    }
                }
            }
        }
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
        DUContext* context = findClassContext(node->className);
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            m_result.setDeclarations(context->findDeclarations(identifierForNode(node->variable->variable->variable)));
            lock.unlock();
            if (!m_result.allDeclarations().isEmpty()) {
                usingDeclaration(node->variable->variable->variable, m_result.allDeclarations().last());
            }
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
