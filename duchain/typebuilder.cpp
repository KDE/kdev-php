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
#include <language/duchain/types/integraltype.h>

#include "editorintegrator.h"
#include "parsesession.h"
#include "phpdebugvisitor.h"
#include "expressionparser.h"

using namespace KDevelop;
namespace Php {

AbstractType::Ptr TypeBuilder::parseType(QString type, AstNode* node)
{
    uint iType = 0;
    type = type.trimmed();
    if (type == "int" || type == "integer") {
        iType = IntegralType::TypeInt;
    } else if (type == "float") {
        iType = IntegralType::TypeFloat;
    } else if (type == "bool") {
        iType = IntegralType::TypeBoolean;
    } else if (type == "string") {
        iType = IntegralType::TypeString;
    } else if (type == "mixed") {
        iType = IntegralType::TypeMixed;
    } else if (type == "array") {
        iType = IntegralType::TypeArray;
    } else {
        if(openTypeFromName(QualifiedIdentifier(type), node, true)) {
            closeType();
            return lastType();
        } else {
            return AbstractType::Ptr();
        }
    }
    AbstractType::Ptr ret(new IntegralType(iType));
    setLastType(ret);
    return ret;
}

AbstractType::Ptr TypeBuilder::parseDocComment(AstNode* node, const QString& docCommentName)
{
    QString docComment = editor()->parseSession()->docComment(node->startToken);
    if (!docComment.isEmpty()) {
        QRegExp rx("\\* +@"+QRegExp::escape(docCommentName)+" ([^ ]*)");
        if (rx.indexIn(docComment) != -1) {
            return parseType(rx.cap(1), node);
        }
    }
    return AbstractType::Ptr();
}


QList<AbstractType::Ptr> TypeBuilder::parseDocCommentParams(AstNode* node)
{
    QList<AbstractType::Ptr> ret;
    QString docComment = editor()->parseSession()->docComment(node->startToken);
    if (!docComment.isEmpty()) {
        QRegExp rx("\\* +@param ([^ ]*)");
        int pos = 0;
        while ((pos = rx.indexIn(docComment, pos)) != -1) {
            ret << parseType(rx.cap(1), node);
            pos += rx.matchedLength();
        }
    }
    return ret;
}

FunctionType::Ptr TypeBuilder::openFunctionType(AstNode* node)
{
    FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());

    openType(functionType);

    m_currentFunctionType = functionType;
    functionType->setReturnType(parseDocComment(node, "return"));

    return functionType;
}

void TypeBuilder::visitClassDeclarationStatement( ClassDeclarationStatementAst* node )
{
    StructureType::Ptr classType = StructureType::Ptr(new StructureType());
    classType->setClassType(StructureType::Class);

    openType(classType);

    classTypeOpened(currentAbstractType()); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

    TypeBuilderBase::visitClassDeclarationStatement(node);

    // Prevent additional elements being added if this becomes the current type again
    classType->close();

    closeType();
}

void TypeBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node)
{
    StructureType::Ptr classType = StructureType::Ptr(new StructureType());
    classType->setClassType(StructureType::Interface);

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
        m_currentFunctionParams = parseDocCommentParams(node);
        openFunctionType(node);
        TypeBuilderBase::visitClassStatement(node);
        if (m_currentFunctionType && !m_currentFunctionType->returnType()) {
            m_currentFunctionType->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed)));
        }
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
    if (node->parameterType && openTypeFromName(node->parameterType, true)) {
    } else if (node->arrayType != -1) {
        openAbstractType(AbstractType::Ptr(new IntegralType(IntegralType::TypeArray)));
    } else {
        if (m_currentFunctionParams.count() > m_currentFunctionType->arguments().count()) {
            openAbstractType(m_currentFunctionParams.at(m_currentFunctionType->arguments().count()));
        } else {
            openAbstractType(AbstractType::Ptr());
        }
    }
    TypeBuilderBase::visitParameter(node);
    closeType();
    m_currentFunctionType->addArgument(lastType());
}

void TypeBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    m_currentFunctionParams = parseDocCommentParams(node);
    openFunctionType(node);
    TypeBuilderBase::visitFunctionDeclarationStatement(node);
    if (!m_currentFunctionType->returnType()) {
        m_currentFunctionType->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed)));
    }
    m_currentFunctionType = 0;
    closeType();
}

void TypeBuilder::visitExpr(ExprAst *node)
{
    node->ducontext = currentContext();
    ExpressionParser ep(true);
    ExpressionEvaluationResult res = ep.evaluateType(node, editor());
    openAbstractType(res.type());

    TypeBuilderBase::visitExpr(node);

    closeType();
}

void TypeBuilder::visitStatement(StatementAst* node)
{
    TypeBuilderBase::visitStatement(node);
    if (node->returnExpr && lastType() && m_currentFunctionType
            && (!m_currentFunctionType->returnType()
                || IntegralType::Ptr::dynamicCast(m_currentFunctionType->returnType())))
    {
        m_currentFunctionType->setReturnType(lastType());
    }
}


}

