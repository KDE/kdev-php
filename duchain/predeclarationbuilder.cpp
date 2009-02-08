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

void PreDeclarationBuilder::closeDeclaration()
{
    if (currentDeclaration() && lastType()) {
        DUChainWriteLocker lock(DUChain::lock());
        currentDeclaration()->setType(lastType());
    }

    eventuallyAssignInternalContext();

    DeclarationBuilderBase::closeDeclaration();
}

void PreDeclarationBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst * node)
{
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
    }
    
    DeclarationBuilderBase::visitClassDeclarationStatement(node);
    
    closeDeclaration();
}

void PreDeclarationBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
{
    ClassDeclaration* dec = openDefinition<ClassDeclaration>(node->interfaceName, node);
    {
        DUChainWriteLocker lock(DUChain::lock());
        dec->setKind(KDevelop::Declaration::Type);
        dec->setBaseClass(IndexedType());
        dec->clearInterfaces();
        dec->setClassType(Php::ClassDeclarationData::Interface);
    }
    
    // don't evaluate the body of interfaces in PreDeclarationBuilder
    {
        const KDevPG::ListNode<ClassStatementAst*>* backup = node->body->classStatementsSequence;
        node->body->classStatementsSequence = 0;
        
        DeclarationBuilderBase::visitInterfaceDeclarationStatement(node);
        
        node->body->classStatementsSequence = backup;
    }
    
    closeDeclaration();
}

void PreDeclarationBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    FunctionDeclaration *dec = openDefinition<FunctionDeclaration>(node->functionName, node);
    {
        DUChainWriteLocker lock(DUChain::lock());
        dec->setKind(Declaration::Type);
        dec->clearDefaultParameters();
    }
    
    // don't evaluate the parameters of functions in PreDeclarationBuilder
    {
        const KDevPG::ListNode<ParameterAst*>* parameterBackup = node->parameters->parametersSequence;
        node->parameters->parametersSequence = 0;
        
        DeclarationBuilderBase::visitFunctionDeclarationStatement(node);
        
        node->parameters->parametersSequence = parameterBackup;
    }
    
    closeDeclaration();
}

}
