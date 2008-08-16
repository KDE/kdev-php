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
#include "helper.h"
#include <language/duchain/ducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/duchain.h>

using namespace KDevelop;

namespace Php {

Declaration* findClassDeclaration(DUContext* currentContext, QualifiedIdentifier id)
{
    QList<Declaration*> foundDeclarations;
    DUChainReadLocker lock(DUChain::lock());
    foundDeclarations = currentContext->findDeclarations(id);
    if (!foundDeclarations.isEmpty()) {
        return foundDeclarations.first();
    }
    kDebug() << "findDeclarations was empty, trying through PersistentSymbolTable";
    uint nr;
    const IndexedDeclaration* declarations = 0;
    PersistentSymbolTable::self().declarations(id, nr, declarations);
    kDebug() << "found declarations: " << nr;
    lock.unlock();
    DUChainWriteLocker wlock(DUChain::lock());
    for (uint i=0; i<nr; ++i) {
        if (declarations[i].declaration()->internalContext()
            && declarations[i].declaration()->internalContext()->type() == DUContext::Class) {
            //check if context is in any loaded project
            currentContext->topContext()->addImportedParentContext(declarations[i].declaration()->context()->topContext());
            return declarations[i].declaration();
        } else {
            kDebug() << "skipping declaration, no class-type context";
        }
    }
    return 0;
}

}
