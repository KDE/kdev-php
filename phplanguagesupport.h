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

#ifndef KDEVPHPLANGUAGESUPPORT_H
#define KDEVPHPLANGUAGESUPPORT_H

#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>
#include <QtCore/QVariant>
#include <QReadWriteLock>

namespace KDevelop
{
class IDocument;
class IProject;
class CodeHighlighting;
class ReferencedTopDUContext;
class IndexedString;
class ParseJob;
}


namespace Php
{

class Highlighting;

/**
 * \brief Language Support plugin for PHP
 *
 * All internal PHP declarations can be found in the document called InternalFunctions.php.
 * It's real path is not important. To check whether the file was already loaded, use
 * \p internalFunctionsLoaded. If it has not yet loaded, you have two options:
 *
 * 1) Block thread and wait for job to finish:
 * \code
 * if ( phpLangSupport->internalFunctionsLoaded ) {
 *   QReadLocker(phpLangSupport->internalFunctionsLock());
 * }
 * // now you can get the ducontext
 * \endcode
 *
 * 2) Wait for job to finish and get notified via signal:
 * \code
 *  connect(ICore::self()->languageController()->backgroundParser(), SIGNAL(parseJobFinished(KDevelop::ParseJob*)),
 *           this, SLOT(slotParseJobFinished(KDevelop::ParseJob*)));
 *  ...
 *  void slotParseJobFinished(ParseJob* job) {
 *    if ( job->document() == IndexedString("InternalFunctions.php") )
 *      // now you can get the ducontext
 *  }
 * \endcode
 *
 * To access the DUContext, use:
 * \code
 *  DUChainWriteLocker lock(DUChain::lock());
 *  TopDUContext* ctx = DUChain::self()->chainForDocument(IndexedString("InternalFunctions.php"));
 * \endcode
 */
class LanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
    Q_OBJECT
    Q_INTERFACES(KDevelop::ILanguageSupport)

public:
    explicit LanguageSupport(QObject *parent, const QVariantList& args = QVariantList());
    virtual ~LanguageSupport();
    /*Name Of the Language*/
    QString name() const;
    /*Parsejob used by background parser to parse given Url*/
    KDevelop::ParseJob *createParseJob(const KUrl &url);
    /*the actual language object*/
    KDevelop::ILanguage *language();

    static LanguageSupport* self();
    /*the code highlighter*/
    const KDevelop::ICodeHighlighting* codeHighlighting() const;

    virtual QWidget* specialLanguageObjectNavigationWidget(const KUrl& url, const KDevelop::SimpleCursor& position);
    virtual KDevelop::SimpleRange specialLanguageObjectRange(const KUrl& url, const KDevelop::SimpleCursor& position);

    /// returns true, if the internal function file has been loaded
    /// to wait for it to finished, use a QReadLocker on the parse lock.
    /// @see internalFunctionsLock()
    bool internalFunctionsLoaded() const;
    /// returns a pointer to the internal functions lock, lock it for reading to wait for the
    /// internal functions to get loaded.
    /// @see internalFunctionsLoaded()
    QReadWriteLock* internalFunctionsLock();

public slots:
    /**
     * Get notified by background parser when internal function file was loaded.
     *
     * \see loadedInternalFunctions
     */
    void updateReady(KDevelop::IndexedString url, KDevelop::ReferencedTopDUContext topContext);

private slots:
    void slotPluginLoaded(KDevelop::IPlugin* plugin);

private:
    KDevelop::CodeHighlighting* m_highlighting;
    static LanguageSupport* m_self;
    bool m_internalFunctionsLoaded;
    QReadWriteLock m_internalFunctionsLock;

    QPair<QString, KDevelop::SimpleRange>  wordUnderCursor(const KUrl& url, const KDevelop::SimpleCursor& position);

};

}

#endif

