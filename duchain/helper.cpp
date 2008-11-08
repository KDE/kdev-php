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
#include <language/duchain/stringhelpers.h>

#include "editorintegrator.h"
#include "../parser/parsesession.h"
#include "phpast.h"

using namespace KDevelop;

namespace Php {

Declaration* findDeclarationImport(DUContext* currentContext, QualifiedIdentifier id, DeclarationType declarationType)
{
    if (declarationType == ClassDeclarationType && id == QualifiedIdentifier("self")) {
        DUChainReadLocker lock(DUChain::lock());
        if (currentContext->parentContext()) {
            Declaration* declaration = currentContext->parentContext()->owner();
            return declaration;
        }
    } else if (declarationType == ClassDeclarationType && id == QualifiedIdentifier("parent")) {
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
            if (!declarations[i].declaration()) {
                kDebug() << "skipping declaration, doesn't ahve declaration";
                continue;
            } else if (declarationType == ClassDeclarationType && declarations[i].declaration()->internalContext()
                && declarations[i].declaration()->internalContext()->type() == DUContext::Class) {
                //TODO check if context is in any loaded project
            } else if(declarationType == FunctionDeclarationType
                && dynamic_cast<FunctionDeclaration*>(declarations[i].declaration())) {
            } else if(declarationType == ConstantDeclarationType
                && declarations[i].declaration()->kind() == Declaration::Instance) {
            } else {
                kDebug() << "skipping declaration, invalid contextType";
                continue;
            }
            TopDUContext* top = declarations[i].declaration()->context()->topContext();
            if (top->language() != IndexedString("Php")) {
                kDebug() << "skipping declaration, invalid langauge" << top->language().str();
                continue;
            }
            currentContext->topContext()->addImportedParentContext(top);
            return declarations[i].declaration();
        }
    }
    return 0;
}

QString formatComment(AstNode* node, EditorIntegrator* editor)
{
    return KDevelop::formatComment(editor->parseSession()->docComment(node->startToken));
}

}
