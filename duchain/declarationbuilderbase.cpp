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

#include "declarationbuilderbase.h"

#include "phpast.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

DeclarationBuilderBase::DeclarationBuilderBase (ParseSession* session)
{
  setEditor(session);
}

DeclarationBuilderBase::DeclarationBuilderBase (EditorIntegrator* editor)
{
  setEditor(editor);
}

void DeclarationBuilderBase::classContextOpened(KDevelop::DUContext* context)
{
    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setInternalContext(context);
}

//copied from cpp
void DeclarationBuilderBase::classTypeOpened(AbstractType::Ptr type)
{
    // We override this so we can get the class-declaration into a usable state(with filled type) earlier
    DUChainWriteLocker lock(DUChain::lock());

    IdentifiedType* idType = dynamic_cast<IdentifiedType*>(type.unsafeData());

    // When the given type has no declaration yet, assume we are declaring it now
    if( idType && !idType->declarationId().isValid() )
        idType->setDeclaration( currentDeclaration() );

    currentDeclaration()->setType(type);
}

}
