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
#include "variabledeclaration.h"
#include "classdeclaration.h"

#include <language/duchain/topducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>

#define ifDebug(x)

using namespace KDevelop;

namespace Php
{

ExpressionVisitor::ExpressionVisitor(EditorIntegrator* editor)
        : m_editor(editor), m_createProblems(false),
          m_offset(SimpleCursor::invalid()), m_currentContext(0),
          m_isAssignmentExpressionEqual(false)
{
}

Declaration* ExpressionVisitor::processVariable(Php::VariableIdentifierAst* variable)
{
    Q_ASSERT(m_currentContext);

    SimpleCursor position = m_editor->findPosition(variable->variable, EditorIntegrator::BackEdge);

    if ( m_offset.isValid() ) {
        position.line += m_offset.line;
        position.column += m_offset.column;
    }

    Declaration* ret = 0;
    Identifier identifier = identifierForNode(variable).last();

    ifDebug(kDebug() << "processing variable" << identifier.toString() << position.textCursor();)

    if (identifier.nameEquals(Identifier("this"))) {
        DUChainReadLocker lock(DUChain::lock());
        if (m_currentContext->parentContext()
                && m_currentContext->parentContext()->type() == DUContext::Class
                && m_currentContext->parentContext()->owner()) {
            ret = m_currentContext->parentContext()->owner();
        }
    } else {
        DUChainReadLocker lock(DUChain::lock());
        //DontSearchInParent-flag because (1) in Php global variables aren't available in function
        //context and (2) a function body consists of a single context (so this is no problem)
        QList<Declaration*> decls = m_currentContext->findDeclarations(identifier, position,
                                                            0, DUContext::DontSearchInParent);
        for (int i = decls.count() - 1; i >= 0; i--) {
            Declaration *dec = decls.at(i);
            if (dec->kind() == Declaration::Instance && dynamic_cast<VariableDeclaration*>(dec)) {
                ret = dec;
                break;
            }
        }
    }
    if (!ret) {
        //look for a function argument
        DUChainReadLocker lock(DUChain::lock());
        ///TODO: why doesn't m_currentContext->findDeclarations() work?
        ///      evaluate if the stuff below is fast enough (faster?) than findDeclarations()
        ///see r1028306
        foreach(const DUContext::Import &import, m_currentContext->importedParentContexts() ) {
            if ( !import.isDirect() || import.position > position ) {
                continue;
            }
            DUContext* ctx = import.context(m_currentContext->topContext());
            if ( ctx->type() == DUContext::Function ) {
                QList<Declaration*> args = ctx->findLocalDeclarations(identifier);
                if ( !args.isEmpty() ) {
                    ret = args.first();
                    break;
                }
            }
        }
    }
    if (!ret) {
        //look for a superglobal variable
        DUChainReadLocker lock(DUChain::lock());
        foreach(Declaration* dec, m_currentContext->topContext()->findDeclarations(identifier, position)) {
            VariableDeclaration* varDec = dynamic_cast<VariableDeclaration*>(dec);
            if (varDec && varDec->isSuperglobal()) {
                ret = dec;
                break;
            }
        }
    }
    if ( !m_isAssignmentExpressionEqual || identifier.nameEquals( Identifier("this") )
         // might be something like $s = $s . $s; in which case we have to add a use for the first $s
         || (ret && ret->range().end < position) ) {
        usingDeclaration(variable, ret);
    }
    ifDebug(kDebug() << "found declaration:" << (ret ? ret->toString() : QString("no declaration found"));)
    return ret;
}

void ExpressionVisitor::visitNode(AstNode *node)
{
    if (node && node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);
    DefaultVisitor::visitNode(node);
}

void ExpressionVisitor::visitAssignmentExpression(AssignmentExpressionAst *node)
{
    if (node->assignmentExpressionEqual) {
        m_isAssignmentExpressionEqual = true;
    }
    visitNode(node->expression);
    m_isAssignmentExpressionEqual = false;

    visitNode(node->assignmentExpressionEqual);
    visitNode(node->assignmentExpression);

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
void ExpressionVisitor::visitVariable(VariableAst* node)
{
    if ( node->variablePropertiesSequence &&
         node->variablePropertiesSequence->front() &&
         node->variablePropertiesSequence->front()->element &&
         node->variablePropertiesSequence->front()->element->objectProperty ) {
        // make sure we mark $foo as a use in $foo->...
        bool isAssignmentExpressionEqual = m_isAssignmentExpressionEqual;
        m_isAssignmentExpressionEqual = false;
        DefaultVisitor::visitVariable(node);
        m_isAssignmentExpressionEqual = isAssignmentExpressionEqual;
    } else {
        DefaultVisitor::visitVariable(node);
    }
}

void ExpressionVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    DefaultVisitor::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        Declaration* dec = findDeclarationImport(ClassDeclarationType, node->className->identifier);
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

void ExpressionVisitor::visitFunctionCallParameterList( FunctionCallParameterListAst* node )
{
    QList<Declaration*> decs = m_result.allDeclarations();
    AbstractType::Ptr type = m_result.type();

    DefaultVisitor::visitFunctionCallParameterList( node );

    m_result.setDeclarations(decs);
    m_result.setType(type);
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
                QualifiedIdentifier methodName(stringForNode(node->stringFunctionName).toLower());
                m_result.setDeclarations(context->findDeclarations(methodName));
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
                usingDeclaration(node->stringFunctionName, 0);
                m_result.setType(AbstractType::Ptr());
            }
        } else if (node->varFunctionName) {
            //static function call foo::$bar()
        } else {
            //global function call foo();
            Declaration* dec = findDeclarationImport(FunctionDeclarationType, node->stringFunctionNameOrClass);
            ifDebug(kDebug() << "function call of" << (dec ? dec->toString() : QString("function not found"));)
            m_result.setDeclaration(dec);
            usingDeclaration(node->stringFunctionNameOrClass, dec);
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
    Declaration* declaration = findDeclarationImport(ClassDeclarationType, className);
    usingDeclaration(className, declaration);
    if (declaration) {
        DUChainReadLocker lock(DUChain::lock());
        context = declaration->internalContext();
        if (!context && m_currentContext->parentContext() && m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
            //className is currentClass (internalContext is not yet set)
            context = m_currentContext->parentContext();
        }
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
            } else {
                usingDeclaration(node->constant, 0);
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
            Declaration* declaration = findDeclarationImport(ConstantDeclarationType, node->constant);
            if (!declaration) {
                //it could also be a global function call, without ()
                declaration = findDeclarationImport(FunctionDeclarationType, node->constant);
            }
            m_result.setDeclaration(declaration);
            usingDeclaration(node->constant, declaration);
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
        // handle $foo
        Declaration* dec = processVariable(node->variable);
        if (dec && node->propertyIdentifier) {
            // handle property in $foo->bar
            Declaration* foundDec = 0;
            DUChainReadLocker lock(DUChain::lock());
            if ( StructureType::Ptr structType = dec->type<StructureType>() ) {
                if ( ClassDeclaration* cdec = dynamic_cast<ClassDeclaration*>(structType->declaration(m_currentContext->topContext())) ) {
                    foreach( Declaration* pdec, cdec->internalContext()->findDeclarations(identifierForNode(node->propertyIdentifier)) ) {
                        if ( !pdec->isFunctionDeclaration() ) {
                            foundDec = pdec;
                            break;
                        }
                    }
                }
            }
            lock.unlock();
            usingDeclaration(node->propertyIdentifier, foundDec);
        }
    }
}

void ExpressionVisitor::visitVariableProperty(VariablePropertyAst *node)
{
    ifDebug(kDebug() << "node:" << m_editor->parseSession()->symbol(node)
        << (node->isFunctionCall != -1 ? QString("is function call") : QString("is no function call"));)
    if (node->objectProperty->objectDimList) {
        //handle $foo->bar() and $foo->baz, $foo is m_result.type()

        if (m_result.type() && StructureType::Ptr::dynamicCast(m_result.type())) {
            DUChainReadLocker lock(DUChain::lock());
            Declaration* declaration = StructureType::Ptr::staticCast(m_result.type())->declaration(m_currentContext->topContext());
            if (declaration) {
                ifDebug(kDebug() << "parent:" << declaration->toString();)
                DUContext* context = declaration->internalContext();
                if (!context && m_currentContext->parentContext()) {
                    if (m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = m_currentContext->parentContext();
                    }
                }
                if (context) {
                    QualifiedIdentifier propertyId;
                    if ( node->isFunctionCall != -1 ) {
                        propertyId = QualifiedIdentifier(stringForNode(node->objectProperty->objectDimList->variableName->name).toLower());
                    } else {
                        propertyId = identifierForNode(node->objectProperty->objectDimList->variableName->name);
                    }
                    ifDebug(kDebug() << "property id:" << propertyId.toString();)

                    QList<Declaration*> decs;
                    foreach ( Declaration* dec, context->findDeclarations(propertyId) ) {
                        if ( node->isFunctionCall != -1 ) {
                            if ( dec->isFunctionDeclaration() ) {
                                decs << dec;
                                ifDebug(kDebug() << "found:" << dec->toString();)
                            }
                        } else {
                            if ( !dec->isFunctionDeclaration() ) {
                                decs << dec;
                                ifDebug(kDebug() << "found:" << dec->toString();)
                            }
                        }
                    }
                    lock.unlock();
                    m_result.setDeclarations(decs);
                    if (!m_result.allDeclarations().isEmpty()) {
                        if ( !m_isAssignmentExpressionEqual ) {
                            usingDeclaration(node->objectProperty->objectDimList->variableName, m_result.allDeclarations().last());
                        }
                        if (node->isFunctionCall != -1) {
                            FunctionType::Ptr function = m_result.allDeclarations().last()->type<FunctionType>();
                            if (function) {
                                m_result.setType(function->returnType());
                            } else {
                                m_result.setType(AbstractType::Ptr());
                            }
                        }
                    } else {
                        if ( !m_isAssignmentExpressionEqual ) {
                            usingDeclaration(node->objectProperty->objectDimList->variableName, 0);
                        }
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
            } else {
                usingDeclaration(node->variable->variable->variable, 0);
            }
        } else {
            usingDeclaration(node->className, 0);
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
        case CastObject: {
            DUChainReadLocker lock(DUChain::lock());
            m_result.setDeclarations(m_currentContext->findDeclarations(QualifiedIdentifier("stdclass")));
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
    if (!id)
        return QString();

    return m_editor->parseSession()->symbol(id->string);
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(IdentifierAst* id)
{
    if (!id)
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}

QString ExpressionVisitor::stringForNode(VariableIdentifierAst* id)
{
    if (!id)
        return QString();
    QString ret(m_editor->parseSession()->symbol(id->variable));
    ret = ret.mid(1); //cut off $
    return ret;
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(VariableIdentifierAst* id)
{
    if (!id)
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}

void ExpressionVisitor::setCreateProblems(bool v)
{
    m_createProblems = v;
}

void ExpressionVisitor::setOffset(SimpleCursor offset)
{
    m_offset = offset;
}

Declaration* ExpressionVisitor::findDeclarationImport(DeclarationType declarationType, IdentifierAst* node)
{
    // methods and class names are case insensitive
    QualifiedIdentifier id;
    if ( declarationType == ClassDeclarationType || declarationType == FunctionDeclarationType ) {
        id = QualifiedIdentifier(stringForNode(node).toLower());
    } else {
        id = identifierForNode(node);
    }
    return findDeclarationImportHelper(m_currentContext, id, declarationType, node, m_editor);
}

Declaration* ExpressionVisitor::findDeclarationImport(DeclarationType declarationType, VariableIdentifierAst* node)
{
    return findDeclarationImportHelper(m_currentContext, identifierForNode(node), declarationType, node, m_editor);
}

}
