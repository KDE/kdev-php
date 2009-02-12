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

#include "predeclarationbuilder.h"

#include <QByteArray>

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/duchain/functiondeclaration.h>
#include <language/duchain/stringhelpers.h>
#include <language/duchain/aliasdeclaration.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/structuretype.h>

#include <klocalizedstring.h>

#include "phpast.h"
#include "parsesession.h"
#include "helper.h"
#include "constantdeclaration.h"
#include "variabledeclaration.h"
#include "classdeclaration.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

PreDeclarationBuilder::~PreDeclarationBuilder()
{
}

/*
void PreDeclarationBuilder::visitNode(Php::AstNode* node) {
    // AstNode is computer generated and the enum is sorted alphabetically
    // filter out some kinds which cannot include class or function declarations
    if ( node->kind >= AstNode::AdditiveExpressionKind && node->kind <= AstNode::BooleanOrExpressionKind ) {
        return;
    }
    if ( node->kind == AstNode::ClassConstantDeclarationKind ) {
        return;
    }
    if ( node->kind == AstNode::ClassExtendsKind || node->kind == AstNode::ClassImplementsKind ) {
        return;
    }
    if ( node->kind >= AstNode::ClassVariableDeclarationKind && node->kind <= AstNode::CtorArgumentsKind ) {
        return;
    }
    if ( node->kind == AstNode::ShiftExpressionKind || node->kind == AstNode::ShiftExpressionRestKind ) {
        return;
    }
    if ( node->kind >= AstNode::UnaryExpressionKind && node->kind <= AstNode::VariableWithoutObjectsKind ) {
        return;
    }
    DefaultVisitor::visitNode(node);
}
*/

void PreDeclarationBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst * node)
{
    setComment(formatComment(node, editor()));
    ClassDeclaration* dec = openDefinition<ClassDeclaration>(node->className, node);
    {
        DUChainWriteLocker lock(DUChain::lock());
        dec->setKind(KDevelop::Declaration::Type);
        dec->setBaseClass(IndexedType());
        dec->clearInterfaces();
        dec->setClassType(Php::ClassDeclarationData::Class);
        if ( node->modifier ) {
          dec->setClassModifier(node->modifier->modifier);
        }
        
        // build the type as well, to make this declaration usable
        StructureType::Ptr type(new StructureType());
        type->setDeclaration(dec);
        dec->setType(type);
    }
    
    // only visit the body to look for other function declarations inside the methods
    visitNode(node->body);
    
    m_types->insert(node->className->string, dec);
    
    closeDeclaration();
}

void PreDeclarationBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
{
    setComment(formatComment(node, editor()));
    ClassDeclaration* dec = openDefinition<ClassDeclaration>(node->interfaceName, node);
    {
        DUChainWriteLocker lock(DUChain::lock());
        dec->setKind(KDevelop::Declaration::Type);
        dec->setBaseClass(IndexedType());
        dec->clearInterfaces();
        dec->setClassType(Php::ClassDeclarationData::Interface);
        
        // build the type as well, to make this declaration usable
        StructureType::Ptr type(new StructureType());
        type->setDeclaration(dec);
        dec->setType(type);
    }
    
    // don't evaluate the body or extends of interfaces in PreDeclarationBuilder
    
    m_types->insert(node->interfaceName->string, dec);
    
    closeDeclaration();
}

void PreDeclarationBuilder::visitClassStatement(ClassStatementAst* node) {
    // we are only looking for function declarations inside methods
    if ( node->methodBody ) {
      visitNode(node->methodBody);
    }
}

void PreDeclarationBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    setComment(formatComment(node, editor()));
    FunctionDeclaration *dec = openDefinition<FunctionDeclaration>(node->functionName, node);
    {
        DUChainWriteLocker lock(DUChain::lock());
        dec->setKind(Declaration::Type);
        dec->clearDefaultParameters();
        
        FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());
        
        dec->setType(type);
    }
    // only visit the body to look for other function declarations
    visitNode(node->functionBody);
    
    m_functions->insert(node->functionName->string, dec);
    
    closeDeclaration();
}

}
