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


#include "phplanguagesupport.h"

#include <QMutexLocker>
#include <QReadWriteLock>

#include <kdebug.h>
#include <kcomponentdata.h>
#include <kstandarddirs.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <ktexteditor/smartinterface.h>
#include <KTextEditor/Document>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/ilanguage.h>
#include <interfaces/idocument.h>
#include <interfaces/iproject.h>
#include <language/editor/editorintegrator.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <interfaces/idocumentcontroller.h>

#include "phpparsejob.h"
//#include "phphighlighting.h"

#include <language/codecompletion/codecompletion.h>
#include <language/codecompletion/codecompletionmodel.h>
#include <language/highlighting/codehighlighting.h>
#include "completion/model.h"
#include "completion/worker.h"

#include "navigation/navigationwidget.h"

using namespace KDevelop;

K_PLUGIN_FACTORY(KDevPhpSupportFactory, registerPlugin<Php::LanguageSupport>();)
K_EXPORT_PLUGIN(KDevPhpSupportFactory("kdevphpsupport"))

namespace Php
{

LanguageSupport* LanguageSupport::m_self = 0;

LanguageSupport::LanguageSupport(QObject* parent, const QVariantList& /*args*/)
        : KDevelop::IPlugin(KDevPhpSupportFactory::componentData(), parent),
        KDevelop::ILanguageSupport(), m_internalFunctionsLoaded(false)
{
    KDEV_USE_EXTENSION_INTERFACE(KDevelop::ILanguageSupport)

    m_self = this;

    m_highlighting = new KDevelop::CodeHighlighting(this);

    CodeCompletionModel* ccModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion(this, ccModel, name());

    connect(core()->pluginController(), SIGNAL(pluginLoaded(KDevelop::IPlugin*)),
            this, SLOT(slotPluginLoaded(KDevelop::IPlugin*)));
}

LanguageSupport::~LanguageSupport()
{
    // Remove any documents waiting to be parsed from the background paser.
    core()->languageController()->backgroundParser()->clear(this);

    ILanguage* lang = language();
    if ( lang ) {
        lang->parseLock()->lockForWrite();
        m_self = 0; //By locking the parse-mutexes, we make sure that parse- and preprocess-jobs get a chance to finish in a good state
        lang->parseLock()->unlock();
    }
}

void LanguageSupport::slotPluginLoaded( IPlugin* plugin )
{
    if ( plugin == this ) {
        {
            DUChainReadLocker lock(DUChain::lock());
            if ( DUChain::self()->chainForDocument(IndexedString("InternalFunctions.php")) ) {
                m_internalFunctionsLoaded = true;
                return;
            }
        }
        kDebug() << "adding job for internal function file";
        m_internalFunctionsLock.lockForWrite();
        core()->languageController()->backgroundParser()->addDocument(
            KUrl("InternalFunctions.php"), KDevelop::TopDUContext::AllDeclarationsAndContexts, -10, this
        );
        disconnect(core()->pluginController(), SIGNAL(pluginLoaded(KDevelop::IPlugin*)),
                   this, SLOT(slotPluginLoaded(KDevelop::IPlugin*)));
    }
}

void LanguageSupport::updateReady( IndexedString url, ReferencedTopDUContext topContext )
{
    Q_ASSERT(url == IndexedString("InternalFunctions.php"));
    Q_UNUSED(topContext);
    kDebug() << "finished parsing internal function file";
    m_internalFunctionsLoaded = true;
    m_internalFunctionsLock.unlock();
}

bool LanguageSupport::internalFunctionsLoaded() const
{
    return m_internalFunctionsLoaded;
}

QReadWriteLock* LanguageSupport::internalFunctionsLock()
{
    return &m_internalFunctionsLock;
}

KDevelop::ParseJob *LanguageSupport::createParseJob(const KUrl &url)
{
    return new ParseJob(url, this);
}

QString LanguageSupport::name() const
{
    return "Php";
}

KDevelop::ILanguage *LanguageSupport::language()
{
    return core()->languageController()->language(name());
}

const KDevelop::ICodeHighlighting* LanguageSupport::codeHighlighting() const
{
    return m_highlighting;
}

LanguageSupport *LanguageSupport::self()
{
    return m_self;
}

QPair<QString, SimpleRange> LanguageSupport::wordUnderCursor(const KUrl& url, const SimpleCursor& position)
{
    KDevelop::IDocument* doc = core()->documentController()->documentForUrl(url);
    if(!doc || !doc->textDocument() || !doc->textDocument()->activeView())
        return qMakePair(QString(), SimpleRange::invalid());

    int lineNumber = position.line;
    int lineLength = doc->textDocument()->lineLength(lineNumber);

    QString line = doc->textDocument()->text(KTextEditor::Range(lineNumber, 0, lineNumber, lineLength));

    int startCol = position.column;
    for ( ; startCol >= 0; --startCol ) {
        if ( !line[startCol].isLetter() && line[startCol] != '_' ) {
            // don't include the wrong char
            if ( startCol != position.column ) {
                ++startCol;
            }
            break;
        }
    }
    int endCol = position.column;
    for ( ; endCol <= lineLength; ++endCol ) {
        if ( !line[endCol].isLetter() && line[endCol] != '_' ) {
            break;
        }
    }
    QString word = line.mid(startCol, endCol - startCol);
    SimpleRange range(lineNumber, startCol, lineNumber, endCol);
    return qMakePair(word, range);
}

bool isMagicConstant(QPair<QString, SimpleRange> word) {
    if ( word.second.isValid() && !word.second.isEmpty() ) {
        if ( word.first == "__FILE__" || word.first == "__LINE__" ||
             word.first == "__METHOD__" || word.first == "__CLASS__" ||
             word.first == "__FUNCTION__"
             ///TODO: php 5.3: __DIR__, __NAMESPACE__
           )
        {
            ///TODO: maybe we should use the tokenizer to really make sure this is such a token
            ///      and we are not inside a string, comment or similar
            ///      otoh, it doesn't hurt imo
            return true;
        }
    }
    return false;
}

QWidget* LanguageSupport::specialLanguageObjectNavigationWidget(const KUrl& url, const SimpleCursor& position)
{
    QPair<QString, SimpleRange> word = wordUnderCursor(url, position);
    if ( isMagicConstant(word) ) {
        return new NavigationWidget(TopDUContextPointer(standardContext(url)), position, word.first);
    }
    return ILanguageSupport::specialLanguageObjectNavigationWidget(url, position);
}

SimpleRange LanguageSupport::specialLanguageObjectRange(const KUrl& url, const SimpleCursor& position)
{
    QPair<QString, SimpleRange> word = wordUnderCursor(url, position);
    if ( isMagicConstant(word) ) {
        return word.second;
    }
    return ILanguageSupport::specialLanguageObjectRange(url, position);
}

}

#include "phplanguagesupport.moc"
