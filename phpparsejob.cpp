/*****************************************************************************
 * Copyright (c) 2007 Piyush verma <piyush.verma@gmail.com>                  *
 * Copyright (c) 2008 Niko Sams <niko.sams@gmail.com>                        *
 * Copyright (c) 2010 Milian Wolff <mail@milianw.de>                         *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/

#include "phpparsejob.h"
#include <QFile>
#include <QReadWriteLock>

#include <ktexteditor/document.h>
#include <ktexteditor/smartinterface.h>

#include <kdebug.h>
#include <klocale.h>

#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/dumpchain.h>
#include <interfaces/ilanguage.h>
#include <language/highlighting/codehighlighting.h>
#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/backgroundparser/urlparselock.h>

#include "editorintegrator.h"
#include "parsesession.h"
#include "phplanguagesupport.h"
#include "phpdebugvisitor.h"
#include "duchain/builders/declarationbuilder.h"
#include "duchain/builders/usebuilder.h"
#include "duchain/helper.h"
#include "phpducontext.h"

#include <QtCore/QReadLocker>
#include <QtCore/QThread>
#include <language/duchain/duchainutils.h>

using namespace KDevelop;

namespace Php
{

ParseJob::ParseJob(const KUrl &url)
        : KDevelop::ParseJob(url)
        , m_parentJob(0)
{
}

ParseJob::~ParseJob()
{
}

LanguageSupport *ParseJob::php() const
{
    return LanguageSupport::self();
}

void ParseJob::run()
{
    if ( !php() ) {
        return abortJob();
    }
    // make sure we loaded the internal file already
    if ( !php()->internalFunctionsLoaded() && !m_parentJob && document() != internalFunctionFile() ) {
        kDebug() << "waiting for internal function file to finish parsing";
        QReadLocker(php()->internalFunctionsLock());
    }

    UrlParseLock urlLock(document());

    if ( !(minimumFeatures() & TopDUContext::ForceUpdate || minimumFeatures() & Resheduled) ) {
        DUChainReadLocker lock(DUChain::lock());
        static const IndexedString langString("Php");
        foreach(const ParsingEnvironmentFilePointer &file, DUChain::self()->allEnvironmentFiles(document())) {
            if (file->language() != langString) {
                continue;
            }
            if (!file->needsUpdate() && file->featuresSatisfied(minimumFeatures())) {
                kDebug() << "Already up to date" << document().str();
                setDuChain(file->topContext());
                return;
            }
            break;
        }
    }

    kDebug() << "parsing" << document().str();

    bool readFromDisk = !contentsAvailableFromEditor();

    ParseSession session;

    QString fileName = document().str();

    if (readFromDisk) {
        session.readFile(fileName);
    } else {
        session.setContents(contentsFromEditor());
        session.setCurrentDocument(document().str());
    }

    // 2) parse
    StartAst* ast = 0;
    bool matched = session.parse(&ast);

    if (abortRequested()) {
        return abortJob();
    }

    KDevelop::ReferencedTopDUContext toUpdate;
    {
        KDevelop::DUChainReadLocker duchainlock(KDevelop::DUChain::lock());
        toUpdate = KDevelop::DUChainUtils::standardContextForUrl(document().toUrl());
    }

    KDevelop::TopDUContext::Features newFeatures = minimumFeatures();
    if (toUpdate)
        newFeatures = (KDevelop::TopDUContext::Features)(newFeatures | toUpdate->features());

    //Remove update-flags like 'Recursive' or 'ForceUpdate'
    newFeatures = static_cast<KDevelop::TopDUContext::Features>(newFeatures & KDevelop::TopDUContext::AllDeclarationsContextsUsesAndAST);

    if (matched) {
        if (abortRequested() || !php() || !php()->language()) {
            return abortJob();
        }

        EditorIntegrator editor(&session);

        QReadLocker parseLock(php()->language()->parseLock());

        DeclarationBuilder builder(&editor);
        KDevelop::ReferencedTopDUContext chain = builder.build(document(), ast);

        if (abortRequested()) {
            return abortJob();
        }

        setDuChain(chain);

        if ( newFeatures & TopDUContext::AllDeclarationsContextsAndUses
                && document() != internalFunctionFile() )
        {
            UseBuilder useBuilder(&editor);
            useBuilder.buildUses(ast);
        }

        if (builder.hadUnresolvedIdentifiers()) {
            if (!(minimumFeatures() & Resheduled) && KDevelop::ICore::self()->languageController()->backgroundParser()->queuedCount()) {
                // Need to create new parse job with lower priority
                kDebug() << "Reschedule file " << document().str() << "for parsing";
                KDevelop::TopDUContext::Features feat = static_cast<KDevelop::TopDUContext::Features>(
                        minimumFeatures() | KDevelop::TopDUContext::VisibleDeclarationsAndContexts | Resheduled
                    );
                KDevelop::ICore::self()->languageController()->backgroundParser()
                    ->addDocument(document().toUrl(), feat, 50000);

            } else {
                // We haven't resolved all identifiers, but by now, we don't expect to
                kDebug() << "Builder found unresolved identifiers when they should have been resolved! (if there was no coding error)";
            }
        }

        if (abortRequested()) {
            return abortJob();
        }

        if (editor.smart() && KDevelop::EditorIntegrator::documentForUrl(document())) {
            if (php() && php()->codeHighlighting()) {
                php()->codeHighlighting()->highlightDUChain(chain);
            }
        }

        if (abortRequested()) {
            return abortJob();
        }

        DUChainWriteLocker lock(DUChain::lock());

        foreach(const ProblemPointer &p, session.problems()) {
            chain->addProblem(p);
        }

        chain->setFeatures(newFeatures);
        ParsingEnvironmentFilePointer file = chain->parsingEnvironmentFile();

        QFileInfo fileInfo(fileName);
        QDateTime lastModified = fileInfo.lastModified();
        if (readFromDisk) {
            file->setModificationRevision(KDevelop::ModificationRevision(lastModified));
        } else {
            file->setModificationRevision(KDevelop::ModificationRevision(lastModified, revisionToken()));
        }

        DUChain::self()->updateContextEnvironment( chain->topContext(), file.data() );
    } else {
        ReferencedTopDUContext top;
        {
            DUChainReadLocker lock(DUChain::lock());
            top = DUChain::self()->chainForDocument(document());
        }
        if (top) {
            DUChainWriteLocker lock(DUChain::lock());
            ///NOTE: if we clear the imported parent contexts, autocompletion of built-in PHP stuff won't work!
            //top->clearImportedParentContexts();
            top->parsingEnvironmentFile()->clearModificationRevisions();
            top->clearProblems();
        } else {
            DUChainWriteLocker lock(DUChain::lock());
            ParsingEnvironmentFile *file = new ParsingEnvironmentFile(document());
            /// Indexed string for 'Php', identifies environment files from this language plugin
            static const IndexedString phpLangString("Php");
            file->setLanguage(phpLangString);
            top = new TopDUContext(document(), SimpleRange(SimpleCursor(0, 0), SimpleCursor(INT_MAX, INT_MAX)), file);
            DUChain::self()->addDocumentChain(top);
        }
        setDuChain(top);
        foreach(const ProblemPointer &p, session.problems()) {
            DUChainWriteLocker lock(DUChain::lock());
            top->addProblem(p);
        }
        kDebug() << "===Failed===" << document().str();
    }

    cleanupSmartRevision();
}

void ParseJob::setParentJob(ParseJob *job)
{
    m_parentJob = job;
}


bool ParseJob::hasParentDocument(const IndexedString &doc)
{
    if (document() == doc) return true;
    if (!m_parentJob) return false;
    if (m_parentJob->document() == doc) return true;
    return m_parentJob->hasParentDocument(doc);
}

ProblemPointer ParseJob::createProblem(const QString &description, AstNode* node,
                                       EditorIntegrator * editor, ProblemData::Source source,
                                       ProblemData::Severity severity)
{
    ProblemPointer p(new Problem());
    p->setSource(source);
    p->setSeverity(severity);
    p->setDescription(description);
    p->setFinalLocation(DocumentRange(document().str(), editor->findRange(node).textRange()));
    kDebug() << p->description();
    return p;
}

}

#include "phpparsejob.moc"
// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
