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

#include "declarationbuilder.h"

#include <QByteArray>

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/duchain/functiondeclaration.h>
#include "phpast.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

DeclarationBuilder::DeclarationBuilder (ParseSession* session)
{
  setEditor(session);
}

DeclarationBuilder::DeclarationBuilder (EditorIntegrator* editor)
{
  setEditor(editor);
}

void DeclarationBuilder::closeDeclaration()
{
  if (currentDeclaration()) {
    DUChainWriteLocker lock(DUChain::lock());

    currentDeclaration()->setType(lastType());
  }

  eventuallyAssignInternalContext();

  //kDebug() << "Mangled declaration:" << currentDeclaration()->mangledIdentifier();

  DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst * node)
{
    openDefinition(node->className, node, false);

    currentDeclaration()->setKind(KDevelop::Declaration::Type);

    DeclarationBuilderBase::visitClassDeclarationStatement(node);

    closeDeclaration();
}

void DeclarationBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration

        openDefinition(node->methodName, node, true);

        currentDeclaration()->setKind(Declaration::Type);

        DeclarationBuilderBase::visitClassStatement(node);

        closeDeclaration();

    } else {
        //member-variable
        DeclarationBuilderBase::visitClassStatement(node);
    }
}


void DeclarationBuilder::classTypeOpened(AbstractType::Ptr type)
{
    //We override this so we can get the class-declaration into a usable state(with filled type) earlier
    DUChainWriteLocker lock(DUChain::lock());

    IdentifiedType* idType = dynamic_cast<IdentifiedType*>(type.data());

    if( idType && idType->declaration() == 0 ) //When the given type has no declaration yet, assume we are declaring it now
        idType->setDeclaration( currentDeclaration() );

    currentDeclaration()->setType(type);
}

void DeclarationBuilder::visitParameter(ParameterAst *node)
{
  //openDefinition(node->variableName, node, false);

  DeclarationBuilderBase::visitParameter(node);

  //closeDeclaration();
}


}
