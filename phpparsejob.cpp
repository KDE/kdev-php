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
#include <KZip>

#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/dumpchain.h>
#include <interfaces/ilanguage.h>
#include <language/highlighting/codehighlighting.h>
#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>

// #include "phphighlighting.h"
#include "editorintegrator.h"
#include "parsesession.h"
#include "phplanguagesupport.h"
#include "phpdebugvisitor.h"
#include "duchain/declarationbuilder.h"
#include "duchain/usebuilder.h"
#include "duchain/helper.h"
#include "includebuilder.h"
#include "phpducontext.h"

#include <QtCore/QReadLocker>
#include <QtCore/QThread>

using namespace KDevelop;

namespace Php
{

///TODO: push this into kdevplatform - copied from cpp for now

///Facilities to prevent multiple parse-jobs from processing the same url.
QMutex urlParseMutex;
QMap<IndexedString, QPair<Qt::HANDLE, uint> > parsingUrls;

struct UrlParseLock {
    UrlParseLock(IndexedString url) : m_url(url) {
        QMutexLocker lock(&urlParseMutex);
        while (parsingUrls.contains(m_url) && parsingUrls[m_url].first != QThread::currentThreadId()) {
            //Wait here until no other thread is updating parsing the url
            lock.unlock();
            sleep(1);
            lock.relock();
        }
        if (parsingUrls.contains(m_url)) {
            ++parsingUrls[m_url].second;
        } else {
            parsingUrls.insert(m_url, qMakePair(QThread::currentThreadId(), 1u));
        }
    }

    ~UrlParseLock() {
        QMutexLocker lock(&urlParseMutex);
        Q_ASSERT(parsingUrls.contains(m_url));
        Q_ASSERT(parsingUrls[m_url].first == QThread::currentThreadId());
        --parsingUrls[m_url].second;
        if (parsingUrls[m_url].second == 0) {
            parsingUrls.remove(m_url);
        }
    }

    IndexedString m_url;
};

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
    // make sure we loaded the internal file already
    if ( !php()->internalFunctionsLoaded() && !m_parentJob && document() != internalFunctionFile() ) {
        kDebug() << "waiting for internal function file to finish parsing";
        QReadLocker(php()->internalFunctionsLock());
    }

    UrlParseLock urlLock(document());

    {
        DUChainReadLocker lock(DUChain::lock());
        bool needsUpdate = true;
        foreach(const ParsingEnvironmentFilePointer &file, DUChain::self()->allEnvironmentFiles(document())) {
            if (file->needsUpdate()) {
                needsUpdate = true;
                break;
            } else {
                needsUpdate = false;
            }
        }
        if (!(minimumFeatures() & TopDUContext::ForceUpdate) && !needsUpdate) {
            kDebug() << "Already up to date" << document().str();
            return;
        }
    }

    kDebug() << "parsing" << document().str();

    bool readFromDisk = !contentsAvailableFromEditor();

    ParseSession session;

    QString fileName = document().str();

    if (readFromDisk) {
        if ( fileName.endsWith(".php.zip", Qt::CaseInsensitive) ) {
            KZip file(fileName);
            if ( !file.open(QIODevice::ReadOnly) || !file.directory() ) {
                kDebug() << "Could not open file" << document().str();
                return abortJob();
            } else if ( file.directory()->entries().count() != 1 ) {
                kDebug() << "invalid zip file, too many entries:" << file.directory()->entries();
                return abortJob();
            }
            //NOTE: we only support archives with exactly one file in them
            const KZipFileEntry* entry = static_cast<const KZipFileEntry*>(file.directory()->entry(file.directory()->entries().first()));
            if ( !entry ) {
                kDebug() << "invalid zip file, entry is not a file" << file.directory()->entries().first();
                return abortJob();
            }
            session.setContents(entry->data());
            file.close();
        } else {
            QFile file(fileName);
            //TODO: Read the first lines to determine encoding using Php encoding and use that for the text stream

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                /*
                KDevelop::ProblemPointer p(new KDevelop::Problem());
                p->setSource(KDevelop::ProblemData::Disk);
                p->setDescription(i18n("Could not open file '%1'", document().str()));
                switch (file.error()) {
                case QFile::ReadError:
                    p->setExplanation(i18n("File could not be read from."));
                    break;
                case QFile::OpenError:
                    p->setExplanation(i18n("File could not be opened."));
                    break;
                case QFile::PermissionsError:
                    p->setExplanation(i18n("File permissions prevent opening for read."));
                    break;
                default:
                    break;
                }
                p->setFinalLocation(KDevelop::DocumentRange(document().str(), KTextEditor::Cursor(0, 0), KTextEditor::Cursor(0, 0)));
                // TODO addProblem(p);
                */
                kWarning() << "Could not open file" << document().str();
                return abortJob();
            }

            QTextStream s(&file);

//         if( codec )
//             s.setCodec( QTextCodec::codecForName(codec) );
            session.setContents(s.readAll());
            file.close();
        }
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

    if (matched) {
        EditorIntegrator editor(&session);

        IncludeBuilder includeBuilder(&editor);
        includeBuilder.build(document(), ast);

        QList<ProblemPointer> includeProblems;
        {
            QMapIterator<Php::AstNode*, QString> i(includeBuilder.badIncludes());
            while (i.hasNext()) {
                i.next();
                if (abortRequested()) {
                    return abortJob();
                }
                includeProblems << createProblem(i18n("Included file %1 could not be found.", i.value()), i.key(),
                                                 &editor, ProblemData::Preprocessor);
                continue;
            }
        }
        {
            QMapIterator<Php::AstNode*, IndexedString> i(includeBuilder.includes());
            while (i.hasNext()) {
                i.next();
                if (abortRequested()) {
                    return abortJob();
                }
                if (hasParentDocument(i.value())) {
                    includeProblems << createProblem(i18n("File %1 includes itself.", i.value().str()), i.key(),
                                                     &editor, ProblemData::Preprocessor);
                    continue;
                }
                kDebug() << "parse included file" << i.value().str();
                ParseJob job(i.value().toUrl());
                job.setMinimumFeatures(minimumFeatures());
                job.setParentJob(this);
                job.run();
            }
        }

        QReadLocker parseLock(php()->language()->parseLock());

        DeclarationBuilder builder(&editor);
        KDevelop::ReferencedTopDUContext chain = builder.build(document(), ast);

        if (abortRequested()) {
            return abortJob();
        }

        setDuChain(chain);

        if ( minimumFeatures() & TopDUContext::AllDeclarationsContextsAndUses
                && document() != internalFunctionFile() )
        {
            UseBuilder useBuilder(&editor);
            useBuilder.buildUses(ast);
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

        foreach(const ProblemPointer &p, includeProblems) {
            chain->addProblem(p);
        }

        chain->setFeatures(minimumFeatures());
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
            file->setLanguage(IndexedString("Php"));
            top = new TopDUContext(document(), SimpleRange(SimpleCursor(0, 0), SimpleCursor(INT_MAX, INT_MAX)), file);
            DUChain::self()->addDocumentChain(top);
        }
        setDuChain(top);
        foreach(const ProblemPointer &p, session.problems()) {
            DUChainWriteLocker lock(DUChain::lock());
            top->addProblem(p);
        }
        kDebug() << "===Failed===" << document().str();
        {
            DUChainReadLocker lock(DUChain::lock());
            kDebug() << DUChain::self()->chainForDocument(document());
        }
        return;
    }
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
