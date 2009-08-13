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

#include <KParts/MainWindow>
#include <KLocalizedString>

#include <language/duchain/ducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/duchain.h>
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/stringhelpers.h>
#include <language/duchain/parsingenvironment.h>
#include <language/duchain/classdeclaration.h>
#include <interfaces/icore.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/iproject.h>
#include <project/projectmodel.h>

#include "editorintegrator.h"
#include "../parser/parsesession.h"
#include "phpast.h"
#include "phpdefaultvisitor.h"
#include "constantdeclaration.h"


#define ifDebug(x)

using namespace KDevelop;

namespace Php
{

bool isMatch(Declaration* declaration, DeclarationType declarationType)
{
    if (declarationType == ClassDeclarationType
            && dynamic_cast<ClassDeclaration*>(declaration)
       ) {
        return true;
    } else if (declarationType == FunctionDeclarationType
               && dynamic_cast<FunctionDeclaration*>(declaration)
              ) {
        return true;
    } else if (declarationType == ConstantDeclarationType
               && dynamic_cast<ConstantDeclaration*>(declaration)
              ) {
        return true;
    } else if (declarationType == GlobalVariableDeclarationType
               && declaration->kind() == Declaration::Instance
               && !dynamic_cast<ConstantDeclaration*>(declaration)
              ) {
        return true;
    }
    return false;
}

Declaration* findDeclarationImportHelper(DUContext* currentContext, QualifiedIdentifier id,
        DeclarationType declarationType, AstNode* node, EditorIntegrator* editor)
{
    ifDebug(kDebug() << id.toString() << declarationType;)
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
            foreach(const DUContext::Import &i, currentContext->parentContext()->importedParentContexts()) {
                if (i.context(currentContext->topContext())->type() == DUContext::Class) {
                    return i.context(currentContext->topContext())->owner();
                }
            }
        }
    } else {
        QList<Declaration*> foundDeclarations;
        DUContext *searchContext = currentContext;
        if (declarationType == GlobalVariableDeclarationType) {
            searchContext = currentContext->topContext();
        }
        DUChainReadLocker lock(DUChain::lock());
        foundDeclarations = currentContext->findDeclarations(id);
        foreach(Declaration *declaration, foundDeclarations) {
            if (isMatch(declaration, declarationType)) {
                return declaration;
            }
        }
        if (declarationType != GlobalVariableDeclarationType) {
            ifDebug(kDebug() << "No declarations found with findDeclarations, trying through PersistentSymbolTable" << id.toString();)
            uint nr;
            const IndexedDeclaration* declarations = 0;
            PersistentSymbolTable::self().declarations(id, nr, declarations);
            ifDebug(kDebug() << "found declarations:" << nr;)
            lock.unlock();

            DUChainWriteLocker wlock(DUChain::lock());
            for (uint i = 0; i < nr; ++i) {
                ParsingEnvironmentFilePointer env = DUChain::self()->environmentFileForDocument(declarations[i].indexedTopContext());
                if(!env) {
                    ifDebug(kDebug() << "skipping declaration, missing meta-data";)
                    continue;
                }
                if(env->language() != IndexedString("Php")) {
                    ifDebug(kDebug() << "skipping declaration, invalid language" << env->language().str();)
                    continue;
                }

                if (!declarations[i].declaration()) {
                    ifDebug(kDebug() << "skipping declaration, doesn't have declaration";)
                    continue;
                } else if (!isMatch(declarations[i].declaration(), declarationType)) {
                    ifDebug(kDebug() << "skipping declaration, doesn't match with declarationType";)
                    continue;
                }
                TopDUContext* top = declarations[i].declaration()->context()->topContext();

                if (ICore::self()) {
                    bool loadedProjectContainsUrl = false;
                    foreach(IProject *project, ICore::self()->projectController()->projects()) {
                        if (project->fileSet().contains(top->url())) {
                            loadedProjectContainsUrl = true;
                            break;
                        }
                    }
                    if (!loadedProjectContainsUrl) {
                        ifDebug(kDebug() << "skipping declaration, not in loaded project";)
                        continue;
                    }
                }
                currentContext->topContext()->addImportedParentContext(top);
                currentContext->topContext()->parsingEnvironmentFile()
                ->addModificationRevisions(top->parsingEnvironmentFile()->allModificationRevisions());
                ifDebug(kDebug() << "using" << declarations[i].declaration()->toString() << top->url().str();)
                return declarations[i].declaration();
            }
        }
    }

    return 0;
}

QByteArray formatComment(AstNode* node, EditorIntegrator* editor)
{
    return KDevelop::formatComment(editor->parseSession()->docComment(node->startToken).toUtf8());
}

//Helper visitor to extract a commonScalar node
//used to get the value of an function call argument
class ScalarExpressionVisitor : public DefaultVisitor
{
public:
    ScalarExpressionVisitor() : m_node(0) {}
    CommonScalarAst* node() const {
        return m_node;
    }
private:
    virtual void visitCommonScalar(CommonScalarAst* node) {
        m_node = node;
    }
    CommonScalarAst* m_node;
};

CommonScalarAst* findCommonScalar(AstNode* node)
{
    ScalarExpressionVisitor visitor;
    visitor.visitNode(node);
    return visitor.node();
}

bool includeExists(const KUrl &url)
{
    {
        DUChainReadLocker lock(DUChain::lock());
        ///TODO: this may load the chain into memory, do we really want that here?
        if (DUChain::self()->chainForDocument(url)) {
            return true;
        }
    }
    if ( url.isLocalFile() ) {
        return QFile::exists(url.toLocalFile());
    } else {
        return false;
    }
}

KUrl getUrlForBase(const QString &includeFile, const KUrl &baseUrl) {
    if ( includeFile.isEmpty() ) {
        return baseUrl;
    }
    KUrl url = baseUrl;
    if ( includeFile[0] == '/' ) {
        url.setPath(includeFile);
    } else {
        url.addPath(includeFile);
    }
    return url;
}

IndexedString findIncludeFileUrl(const QString &includeFile, const KUrl &currentUrl)
{
    if ( includeFile.isEmpty() ) {
        return IndexedString();
    }

    // check remote files
    if ( includeFile.startsWith("http://", Qt::CaseInsensitive) || includeFile.startsWith("ftp://", Qt::CaseInsensitive) ) {
        // always expect remote includes to exist
        return IndexedString(includeFile);
    }

    KUrl url;

    // look for file relative to current url
    url = getUrlForBase(includeFile, currentUrl.upUrl());
    if ( ICore::self()->projectController()->findProjectForUrl(url) || includeExists(url) ) {
        return IndexedString(url);
    }

    // look for file relative to current project base
    IProject* ownProject = ICore::self()->projectController()->findProjectForUrl(currentUrl);
    if ( ownProject ) {
        url = getUrlForBase(includeFile, ownProject->folder());
        if ( ownProject->inProject(url) || includeExists(url) ) {
            return IndexedString(url);
        }
    }

    // now look in all other projects
    foreach(IProject* project, ICore::self()->projectController()->projects()) {
        if ( project == ownProject ) {
            continue;
        }
        url = getUrlForBase(includeFile, project->folder());
        if ( project->inProject(url) || includeExists(url) ) {
            return IndexedString(url);
        }
    }

    //TODO configurable include paths

    return IndexedString();
}

IndexedString getIncludeFileForNode(UnaryExpressionAst* node, EditorIntegrator* editor) {
    if ( node->includeExpression ) {
        //find name of the constant (first argument of the function call)
        CommonScalarAst* scalar = findCommonScalar(node->includeExpression);
        if (scalar && scalar->string != -1) {
            QString str = editor->parseSession()->symbol(scalar->string);
            str = str.mid(1, str.length() - 2);
            return findIncludeFileUrl(str, editor->currentUrl().toUrl());
        }
    }

    return IndexedString();
}

}
