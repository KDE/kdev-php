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
#include "constantdeclaration.h"

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
    : m_editor(editor), m_useCursor(useCursor), m_currentContext(0), m_isAssignmentExpressionEqual(false), m_createProblems(false)
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
        //DontSearchInParent-flag because (1) in Php global variables aren't avaliable in function
        //context and (2) a function body consists of a single context (so this is no problem)
        QList<Declaration*> decls = m_currentContext->findDeclarations(identifier, position,
                            AbstractType::Ptr(), 0, DUContext::DontSearchInParent);
        for (int i=decls.count()-1; i >= 0; i--) {
            kDebug() << i;
            Declaration *dec = decls.at(i);
            if (dec->kind() == Declaration::Instance && !dynamic_cast<ConstantDeclaration*>(dec)) {
                ret = dec;
                break;
            }
        }
    }
    if (ret && !m_isAssignmentExpressionEqual) {
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
    if (node->assignmentExpressionEqual) {
        m_isAssignmentExpressionEqual = true;
    }
    DefaultVisitor::visitAssignmentExpression(node);
    m_isAssignmentExpressionEqual = false;

    if (node->operation == OperationPlus || node->operation == OperationMinus || node->operation == OperationMul || node->operation == OperationDiv) {
        IntegralType::Ptr integral(new IntegralType(IntegralType::TypeInt));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    } else if (node->operation == OperationConcat) {
        IntegralType::Ptr integral(new IntegralType(IntegralType::TypeString));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    }
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
        Declaration* dec = findDeclarationImport(m_currentContext, ClassDeclarationType, node->className->identifier);
        usingDeclaration(node->className->identifier, dec);
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
            Declaration* dec = findDeclarationImport(m_currentContext, FunctionDeclarationType, node->stringFunctionNameOrClass);
            m_result.setDeclaration(dec);
            if (dec) {
                usingDeclaration(node->stringFunctionNameOrClass, dec);
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
    Declaration* declaration = findDeclarationImport(m_currentContext, ClassDeclarationType, className);
    if (declaration) {
        {
            DUChainReadLocker lock(DUChain::lock());
            context = declaration->internalContext();
            if (!context && m_currentContext->parentContext() && m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
                //className is currentClass (internalContext is not yet set)
                context = m_currentContext->parentContext();
            }
        }
        usingDeclaration(className, declaration);
    }
    return context;
}

void ExpressionVisitor::visitConstantOrClassConst(ConstantOrClassConstAst *node)
{
    DefaultVisitor::visitConstantOrClassConst(node);

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
        QString str(stringForNode(node->constant).toLower());
        if (str == "true" || str == "false") {
            IntegralType::Ptr integral(new IntegralType(IntegralType::TypeBoolean));
            m_result.setType(AbstractType::Ptr::staticCast(integral));
        } else if (str == "null") {
            IntegralType::Ptr integral(new IntegralType(IntegralType::TypeNull));
            m_result.setType(AbstractType::Ptr::staticCast(integral));
        } else {
            //constant (created with declare('foo', 'bar'))
            Declaration* declaration = findDeclarationImport(m_currentContext, ConstantDeclarationType, node->constant);
            if (!declaration) {
                //it could also be a global function call, without ()
                declaration = findDeclarationImport(m_currentContext, FunctionDeclarationType, node->constant);
            }
            m_result.setDeclaration(declaration);
            if (declaration) {
                usingDeclaration(node->constant, declaration);
            }
        }
    }
}

void ExpressionVisitor::visitScalar(ScalarAst *node)
{
    DefaultVisitor::visitScalar(node);

    if (node->commonScalar) {
        uint type = IntegralType::TypeVoid;
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

void ExpressionVisitor::visitStaticScalar(StaticScalarAst *node)
{
    if (node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);

    DefaultVisitor::visitStaticScalar(node);

    uint type = IntegralType::TypeVoid;
    if (node->value) {
        switch (node->value->scalarType) {
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
    } else if (node->plusValue || node->minusValue) {
        type = IntegralType::TypeInt;
    } else if (node->array != -1) {
        type = IntegralType::TypeArray;
    }
    if (type != IntegralType::TypeVoid) {
        IntegralType::Ptr integral(new IntegralType(type));
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
            Declaration* declaration = StructureType::Ptr::staticCast(m_result.type())->declaration(m_currentContext->topContext());
            if (declaration) {
                DUContext* context = declaration->internalContext();
                if (!context && m_currentContext->parentContext()) {
                    if (m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = m_currentContext->parentContext();
                    }
                }
                if (context) {
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

void ExpressionVisitor::visitUnaryExpression(UnaryExpressionAst* node)
{
    DefaultVisitor::visitUnaryExpression(node);
    if (node->castType) {
        uint type = 0;
        switch (node->castType) {
            case CastInt:
                type = IntegralType::TypeInt;
                break;
            case CastDouble:
                type = IntegralType::TypeFloat;
                break;
            case CastString:
                type = IntegralType::TypeString;
                break;
            case CastArray:
                type = IntegralType::TypeArray;
                break;
            case CastObject:
                {
                    DUChainReadLocker lock(DUChain::lock());
                    m_result.setDeclarations(m_currentContext->findDeclarations(QualifiedIdentifier("stdClass")));
                    break;
                }
            case CastBool:
                type = IntegralType::TypeBoolean;
                break;
            case CastUnset:
                //TODO
                break;
        }
        if (type) {
            IntegralType::Ptr integral(new IntegralType(type));
            m_result.setType(AbstractType::Ptr::staticCast(integral));
        }
    }
}

void ExpressionVisitor::visitAdditiveExpressionRest(AdditiveExpressionRestAst* node)
{
    DefaultVisitor::visitAdditiveExpressionRest(node);
    if (node->operation == OperationPlus || node->operation == OperationMinus) {
        IntegralType::Ptr integral(new IntegralType(IntegralType::TypeInt));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    } else if (node->operation == OperationConcat) {
        IntegralType::Ptr integral(new IntegralType(IntegralType::TypeString));
        m_result.setType(AbstractType::Ptr::staticCast(integral));
    }
}


QString ExpressionVisitor::stringForNode(IdentifierAst* id)
{
    if( !id )
        return QString();

    return m_editor->parseSession()->symbol(id->string);
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(IdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}

QString ExpressionVisitor::stringForNode(VariableIdentifierAst* id)
{
    if( !id )
        return QString();
    QString ret(m_editor->parseSession()->symbol(id->variable));
    ret = ret.mid(1); //cut off $
    return ret;
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(VariableIdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}

void ExpressionVisitor::setCreateProblems(bool v)
{
    m_createProblems = v;
}

Declaration* ExpressionVisitor::findDeclarationImport(DUContext* currentContext,
                            DeclarationType declarationType, IdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext, identifierForNode(node), declarationType, node, m_editor, m_createProblems);
}

Declaration* ExpressionVisitor::findDeclarationImport(DUContext* currentContext,
                            DeclarationType declarationType, VariableIdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext, identifierForNode(node), declarationType, node, m_editor, m_createProblems);
}

}
