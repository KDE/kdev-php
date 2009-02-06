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

PreDeclarationBuilder::PreDeclarationBuilder (ParseSession* session)
{
  setEditor(session);
}

PreDeclarationBuilder::PreDeclarationBuilder (EditorIntegrator* editor)
{
  setEditor(editor);
}

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

    // don't evaluate the body in PreDeclarationBuilder
    {
        const KDevPG::ListNode<ClassStatementAst*>* backup = node->body->classStatementsSequence;
        node->body->classStatementsSequence = 0;
        
        DeclarationBuilderBase::visitClassDeclarationStatement(node);
        
        node->body->classStatementsSequence = backup;
    }
    
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
    
    // don't evaluate the body in PreDeclarationBuilder
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
    
    // don't evaluate the body or parameters in PreDeclarationBuilder
    {
        const KDevPG::ListNode<TopStatementAst*>* bodyBackup = node->functionBody->statementsSequence;
        node->functionBody->statementsSequence = 0;
        const KDevPG::ListNode<ParameterAst*>* parameterBackup = node->parameters->parametersSequence;
        node->parameters->parametersSequence = 0;
        
        DeclarationBuilderBase::visitFunctionDeclarationStatement(node);
        
        node->functionBody->statementsSequence = bodyBackup;
        node->parameters->parametersSequence = parameterBackup;
    }
    
    closeDeclaration();
}

void PreDeclarationBuilder::classContextOpened(KDevelop::DUContext* context)
{
    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setInternalContext(context);
}

//copied from cpp
void PreDeclarationBuilder::classTypeOpened(AbstractType::Ptr type)
{
    //We override this so we can get the class-declaration into a usable state(with filled type) earlier
    DUChainWriteLocker lock(DUChain::lock());

    IdentifiedType* idType = dynamic_cast<IdentifiedType*>(type.unsafeData());

    if( idType && !idType->declarationId().isValid() ) //When the given type has no declaration yet, assume we are declaring it now
        idType->setDeclaration( currentDeclaration() );

    currentDeclaration()->setType(type);
}

}
