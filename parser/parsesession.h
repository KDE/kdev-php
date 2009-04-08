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
#ifndef PHP_PARSESESSION_H
#define PHP_PARSESESSION_H

#include <QtCore/QString>
#include <language/editor/simplecursor.h>
#include "phpparser.h"
#include "parserexport.h"

namespace KDevPG
{
class MemoryPool;
}
namespace KDevelop
{
class SimpleCursor;
}
namespace Php
{
class TokenStream;
class StartAst;

class KDEVPHPPARSER_EXPORT ParseSession
{
public:
    ParseSession();
    ~ParseSession();

    void setContents(const QString& contents);
    void setCurrentDocument(const QString& filename);
    bool readFile(const QString& filename, const char* charset = 0);
    void setDebug(bool);
    TokenStream* tokenStream() const;
    QString contents() const;

    bool parse(Php::StartAst**);
    Parser* createParser(int initialState = Parser::HtmlState);

    QString symbol(qint64 token) const;
    QString symbol(AstNode* node) const;

    /**
     * Return the DocBlock before this token, if any
     */
    QString docComment(qint64 token) const;

    /**
     * Return the position (\a line%, \a column%) of the \a offset in the file.
     *
     * \note the line starts from 0.
     */
    KDevelop::SimpleCursor positionAt(qint64 offset) const;

    QList<KDevelop::ProblemPointer> problems();

private:
    QString m_contents;
    bool m_debug;
    QString m_currentDocument;
    KDevPG::MemoryPool* m_pool;
    TokenStream* m_tokenStream;
    QList<KDevelop::ProblemPointer> m_problems;
};

}

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
