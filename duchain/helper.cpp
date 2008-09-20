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
#include <language/duchain/functiondeclaration.h>

using namespace KDevelop;

namespace Php {

Declaration* findDeclarationImport(DUContext* currentContext, QualifiedIdentifier id, DUContext::ContextType contextType)
{
    if (contextType == DUContext::Class && id == QualifiedIdentifier("self")) {
        DUChainReadLocker lock(DUChain::lock());
        if (currentContext->parentContext()) {
            Declaration* declaration = currentContext->parentContext()->owner();
            return declaration;
        }
    } else if (contextType == DUContext::Class && id == QualifiedIdentifier("parent")) {
        //there can be just one Class-Context imported
        DUChainReadLocker lock(DUChain::lock());
        if (currentContext->parentContext()) {
            foreach (DUContext::Import i, currentContext->parentContext()->importedParentContexts()) {
                if (i.context()->type() == DUContext::Class) {
                    return i.context()->owner();
                }
            }
        }
    } else {
        QList<Declaration*> foundDeclarations;
        DUChainReadLocker lock(DUChain::lock());
        foundDeclarations = currentContext->findDeclarations(id);

        if (!foundDeclarations.isEmpty()) {
            return foundDeclarations.first();
        }
        kDebug() << "findDeclarations was empty, trying through PersistentSymbolTable" << id.toString();
        uint nr;
        const IndexedDeclaration* declarations = 0;
        PersistentSymbolTable::self().declarations(id, nr, declarations);
        kDebug() << "found declarations: " << nr;
        lock.unlock();
        DUChainWriteLocker wlock(DUChain::lock());
        for (uint i=0; i<nr; ++i) {
            if (contextType == DUContext::Class && declarations[i].declaration()->internalContext()
                && declarations[i].declaration()->internalContext()->type() == DUContext::Class) {
                //TODO check if context is in any loaded project
                currentContext->topContext()->addImportedParentContext(declarations[i].declaration()->context()->topContext());
                return declarations[i].declaration();
            } else if(contextType == DUContext::Function
                && dynamic_cast<FunctionDeclaration*>(declarations[i].declaration())) {
                currentContext->topContext()->addImportedParentContext(declarations[i].declaration()->context()->topContext());
                return declarations[i].declaration();
            } else {
                kDebug() << "skipping declaration, invalid contextType";
            }
        }
    }
    return 0;
}

}
