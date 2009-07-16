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
#ifndef PHP_PARSEJOB_H
#define PHP_PARSEJOB_H

#include <language/backgroundparser/parsejob.h>

// from the parser subdirectory
#include "phpast.h"

#include <QStringList>

#include <ksharedptr.h>
#include <ktexteditor/range.h>

#include <language/duchain/duchainpointer.h>
#include <language/duchain/topducontext.h>


namespace Php
{

class LanguageSupport;

class ParseSession;

class EditorIntegrator;

class ParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    explicit ParseJob(const KUrl &url, QObject* parent = 0);
    virtual ~ParseJob();

    void setAST(StartAst* ast);
    virtual StartAst *ast() const;

    const KTextEditor::Range& textRangeToParse() const;

    LanguageSupport* php() const;
    ParseSession* parseSession() const;
    bool wasReadFromDisk() const;

    void setParentJob(ParseJob *job);

protected:
    virtual void run();

private:
    ParseSession *m_session;
    StartAst *m_ast;
    bool m_readFromDisk;
    KDevelop::ReferencedTopDUContext m_duContext;
    KUrl m_url;
    KTextEditor::Range m_textRangeToParse;
    ParseJob *m_parentJob; ///< parent job if this one is an include

    /**
     * Checks if a parent job parses already \p document. Used to prevent
     * endless recursions in include statements
     */
    bool hasParentDocument(const KDevelop::IndexedString &document);

    /// create a problem pointer for the current document
    KDevelop::ProblemPointer createProblem(const QString &description, AstNode* node,
                                           EditorIntegrator * editor, KDevelop::ProblemData::Source source,
                                           KDevelop::ProblemData::Severity severity = KDevelop::ProblemData::Error);
};

}

#endif
// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
