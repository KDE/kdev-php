/*****************************************************************************
 * Copyright (c) 2007 Andreas Pakulat <apaku@gmx.de>                         *
 * Copyright (c) 2007 Piyush verma <piyush.verma@gmail.com>                  *
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

#include <ktexteditor/document.h>
#include <ktexteditor/smartinterface.h>

#include <kdebug.h>
#include <klocale.h>
#include <kstandarddirs.h>

#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/dumpchain.h>

// #include "phphighlighting.h"
#include "editorintegrator.h"
#include "parsesession.h"
#include "phplanguagesupport.h"
#include "phpdebugvisitor.h"
#include "duchain/declarationbuilder.h"
#include "duchain/usebuilder.h"
#include "duchain/helper.h"

using namespace KDevelop;

namespace Php
{


ParseJob::ParseJob( const KUrl &url, LanguageSupport *parent )
        : KDevelop::ParseJob( url, parent )
        , m_session( new ParseSession )
        , m_ast( 0 )
        , m_readFromDisk( false )
        , m_url( url )
{
}

ParseJob::~ParseJob()
{
}

LanguageSupport *ParseJob::php() const
{
    return qobject_cast<LanguageSupport*>( const_cast<QObject*>( parent() ) );
}


StartAst *ParseJob::ast() const
{
    Q_ASSERT( isFinished() && m_ast );
    return m_ast;
}

ReferencedTopDUContext ParseJob::duChain() const
{
    return m_duContext;
}

bool ParseJob::wasReadFromDisk() const
{
    return m_readFromDisk;
}

void ParseJob::setDUChain( ReferencedTopDUContext duChain )
{
    m_duContext = duChain;
}

void ParseJob::run()
{
    kDebug() << "parsing" << document().str();

    for (uint i=0; i < internalFunctionFilesCount; i++) {
        if (document() == internalFunctionFiles[i]) break;
        if (!DUChain::self()->chainForDocument(internalFunctionFiles[i])) {
            ParseJob job(KUrl(internalFunctionFiles[i].str()), php());
            job.run();
        }
    }
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
            p->setSource(KDevelop::Problem::Disk);
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
        Q_ASSERT( m_session->contents().size() > 0 );
        file.close();
    }
    else
    {
        m_session->setContents( contentsFromEditor().toAscii() );
    }


    // 2) parse
    bool matched = m_session->parse( &m_ast );

    if ( abortRequested() )
        return abortJob();

    if ( matched )
    {
        EditorIntegrator editor( m_session );
        editor.setCurrentUrl(document(),true);

        DeclarationBuilder builder(&editor);
        KDevelop::ReferencedTopDUContext chain = builder.build(document(), m_ast);
        setDuChain(chain);

        UseBuilder useBuilder(&editor);
        useBuilder.buildUses(m_ast);
    }
    else
    {
        kDebug() << "===Failed===" << document().str();
        return;
    }
}

ParseSession *ParseJob::parseSession() const
{
    return m_session;
}

}

#include "phpparsejob.moc"
// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
