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
#include "constantdeclaration.h"

using namespace KDevelop;

namespace Php {

bool isMatch(Declaration* declaration, DeclarationType declarationType)
{
    if (declarationType == ClassDeclarationType && declaration->internalContext()
        && declaration->internalContext()->type() == DUContext::Class
    ) {
        return true;
    } else if(declarationType == FunctionDeclarationType
        && dynamic_cast<FunctionDeclaration*>(declaration)
    ) {
        return true;
    } else if(declarationType == ConstantDeclarationType
        && dynamic_cast<ConstantDeclaration*>(declaration)
    ) {
        return true;
    }
    return false;
}

Declaration* findDeclarationImport(DUContext* currentContext, QualifiedIdentifier id, DeclarationType declarationType)
{
    kDebug() << id.toString() << declarationType;
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
                if (i.context(currentContext->topContext())->type() == DUContext::Class) {
                    return i.context(currentContext->topContext())->owner();
                }
            }
        }
    } else {
        QList<Declaration*> foundDeclarations;
        DUChainReadLocker lock(DUChain::lock());
        foundDeclarations = currentContext->findDeclarations(id);
        foreach (Declaration *declaration, foundDeclarations) {
            if (isMatch(declaration, declarationType)) {
                return declaration;
            }
        }
        kDebug() << "No declarations found with findDeclarations, trying through PersistentSymbolTable" << id.toString();
        uint nr;
        const IndexedDeclaration* declarations = 0;
        PersistentSymbolTable::self().declarations(id, nr, declarations);
        kDebug() << "found declarations:" << nr;
        lock.unlock();

        DUChainWriteLocker wlock(DUChain::lock());
        for (uint i=0; i<nr; ++i) {
            //TODO check if context is in any loaded project
            if (!declarations[i].declaration()) {
                kDebug() << "skipping declaration, doesn't have declaration";
                continue;
            } else if (!isMatch(declarations[i].declaration(), declarationType)) {
                kDebug() << "skipping declaration, doesn't match with declarationType";
                continue;
            }
            TopDUContext* top = declarations[i].declaration()->context()->topContext();
            if (top->language() != IndexedString("Php")) {
                kDebug() << "skipping declaration, invalid language" << top->language().str();
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
