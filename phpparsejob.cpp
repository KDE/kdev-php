/*****************************************************************************
 * Copyright (c) 2007 Andreas Pakulat <apaku@gmx.de>                         *
 * Copyright (c) 2007 Piyush verma <piyush.verma@gmail.com>                  *
 * Copyright (c) 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/
#include "phpparsejob.h"
#include <QFile>
#include <QReadWriteLock>

#include <ktexteditor/document.h>
#include <ktexteditor/smartinterface.h>

#include <kdebug.h>
#include <klocale.h>
#include <kstandarddirs.h>

#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/dumpchain.h>
#include <interfaces/ilanguage.h>

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

using namespace KDevelop;

namespace Php
{


ParseJob::ParseJob( const KUrl &url, QObject *parent )
        : KDevelop::ParseJob( url, parent )
        , m_session( new ParseSession )
        , m_ast( 0 )
        , m_readFromDisk( false )
        , m_url( url )
        , m_parentJob( 0 )
{
}

ParseJob::~ParseJob()
{
}

LanguageSupport *ParseJob::php() const
{
    return LanguageSupport::self();
}

StartAst *ParseJob::ast() const
{
    Q_ASSERT( isFinished() && m_ast );
    return m_ast;
}

bool ParseJob::wasReadFromDisk() const
{
    return m_readFromDisk;
}

void ParseJob::run()
{
    for (uint i=0; i < internalFunctionFilesCount; i++) {
        if (document() == internalFunctionFiles[i]) break;
        TopDUContext *top = 0;
        {
            DUChainReadLocker lock(DUChain::lock());
            top = DUChain::self()->chainForDocument(internalFunctionFiles[i]);
        }
        if (!top) {
            ParseJob job(KUrl(internalFunctionFiles[i].str()));
            job.run();
        }
    }

    {
        DUChainReadLocker lock(DUChain::lock());
        bool needsUpdate = true;
        foreach (ParsingEnvironmentFilePointer file, DUChain::self()->allEnvironmentFiles(document())) {
            if (file->needsUpdate()) {
                needsUpdate = true;
                break;
            } else {
                needsUpdate = false;
            }
        }
        if (!(minimumFeatures() | TopDUContext::ForceUpdate) && !needsUpdate) {
            kDebug() << "Already up to date" << document().str();
            return;
        }
    }

    kDebug() << "parsing" << document().str();

    m_readFromDisk = !contentsAvailableFromEditor();

    if ( m_readFromDisk )
    {
        QString fileName = document().str();
        if (fileName == "internalfunctions") {
            fileName = KStandardDirs::locate("data", "kdevphpsupport/phpfunctions.php");
        }
        QFile file(fileName);
        //TODO: Read the first lines to determine encoding using Php encoding and use that for the text stream

        if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            KDevelop::ProblemPointer p(new KDevelop::Problem());
            p->setSource(KDevelop::ProblemData::Disk);
            p->setDescription(i18n( "Could not open file '%1'", document().str() ));
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
            p->setFinalLocation(KDevelop::DocumentRange(document().str(), KTextEditor::Cursor(0,0), KTextEditor::Cursor(0,0)));
            // TODO addProblem(p);
            kWarning() << "Could not open file" << document().str()
            << "(path" << document().str() << ")";
            return ;
        }

        QTextStream s( &file );

//         if( codec )
//             s.setCodec( QTextCodec::codecForName(codec) );
        m_session->setContents( s.readAll() );
        file.close();
    }
    else
    {
        m_session->setContents(contentsFromEditor());
        m_session->setCurrentDocument(document().str());
    }


    // 2) parse
    bool matched = m_session->parse( &m_ast );

    if ( abortRequested() )
        return abortJob();

    if ( matched )
    {
        EditorIntegrator editor( m_session );

        IncludeBuilder includeBuilder(&editor);
        includeBuilder.build(document(), m_ast);
        foreach (IndexedString file, includeBuilder.includes()) {
            if ( abortRequested() )
                return abortJob();
            if (hasParentDocument(file)) {
                kDebug() << "file includes itself" << file.str();
                continue;
            }
            kDebug() << "parse included file" << file.str();
            ParseJob job(file.toUrl(), 0);
            job.setParentJob(this);
            job.run();
        }

        QReadLocker parseLock(php()->language()->parseLock());

        DeclarationBuilder builder(&editor);
        KDevelop::ReferencedTopDUContext chain = builder.build(document(), m_ast);
        setDuChain(chain);

        UseBuilder useBuilder(&editor);
        useBuilder.buildUses(m_ast);

        DUChainWriteLocker lock(DUChain::lock());

        chain->setFeatures(TopDUContext::AllDeclarationsContextsAndUses);
        ParsingEnvironmentFilePointer file = chain->parsingEnvironmentFile();

        QFileInfo fileInfo(document().str());
        QDateTime lastModified = fileInfo.lastModified();
        if (m_readFromDisk) {
            file->setModificationRevision( KDevelop::ModificationRevision( lastModified ) );
        } else {
            file->setModificationRevision( KDevelop::ModificationRevision( lastModified, revisionToken() ) );
        }
    }
    else
    {
        ReferencedTopDUContext top;
        {
            DUChainReadLocker lock(DUChain::lock());
            top = DUChain::self()->chainForDocument(document());
        }
        if (top) {
            DUChainWriteLocker lock(DUChain::lock());
            top->clearImportedParentContexts();
            top->parsingEnvironmentFile()->clearModificationRevisions();
            top->clearProblems();
        } else {
            DUChainWriteLocker lock(DUChain::lock());
            ParsingEnvironmentFile *file = new ParsingEnvironmentFile(document());
            top = new TopDUContext(document(), SimpleRange( SimpleCursor( 0, 0 ), SimpleCursor( INT_MAX, INT_MAX ) ), file);
            file->setTopContext(top.data());
            top->setLanguage(IndexedString("Php"));
            DUChain::self()->addDocumentChain( top );
        }
        setDuChain(top);
        foreach (ProblemPointer p, m_session->problems()) {
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

ParseSession *ParseJob::parseSession() const
{
    return m_session;
}

void ParseJob::setParentJob(ParseJob *job)
{
    m_parentJob = job;
}


bool ParseJob::hasParentDocument(const IndexedString &document)
{
    if (!m_parentJob) return false;
    if (m_parentJob->document() == document) return true;
    return m_parentJob->hasParentDocument(document);
}

}

#include "phpparsejob.moc"
// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
