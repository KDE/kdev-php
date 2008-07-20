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
#include "parsesession.h"

#include "phpparser.h"

#include "kdev-pg-memory-pool.h"
#include "kdev-pg-token-stream.h"

#include <QFile>
#include <QTextCodec>

namespace Php
{

ParseSession::ParseSession()
    :   m_debug(false),
        m_pool(new KDevPG::MemoryPool()),
        m_tokenStream(new TokenStream())
{
}
ParseSession::~ParseSession()
{
    delete m_pool;
    delete m_tokenStream;
}

QString ParseSession::contents() const
{
    return m_contents;
}

void ParseSession::setContents( const QString& contents )
{
    m_contents = contents;
}

bool ParseSession::readFile( const QString& filename, const char* codec )
{
    QFile f(filename);
    if( !f.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        kDebug() << "Couldn't open project file:" << filename;
        return false;
    }
    QTextStream s(&f);
    if( codec )
        s.setCodec( QTextCodec::codecForName(codec) );
    m_contents = s.readAll();
    return true;
}
void ParseSession::setDebug( bool debug )
{
    m_debug = debug;
}

TokenStream* ParseSession::tokenStream() const
{
    return m_tokenStream;
}

bool ParseSession::parse( Php::StartAst** ast )
{
    Parser parser;
    parser.setTokenStream( m_tokenStream );
    parser.setMemoryPool( m_pool );
    parser.setDebug( m_debug );

    parser.tokenize(m_contents);
    StartAst* phpAst;
    bool matched = parser.parseStart(&phpAst);
    if( matched )
    {
        kDebug() << "Successfully parsed";
        *ast = phpAst;
    }else
    {
        *ast = 0;
        parser.expectedSymbol(AstNode::StartKind, "start");
        kDebug() << "Couldn't parse content";
    }
    return matched;
}

KDevelop::SimpleCursor ParseSession::positionAt( qint64 offset ) const
{
    qint64 line, column;
    m_tokenStream->locationTable()->positionAt( offset, &line, &column );
    return KDevelop::SimpleCursor(line, column);
}

QString ParseSession::symbol( qint64 token ) const
{
    const TokenStream::Token& tok = m_tokenStream->token( token );
    return m_contents.mid(tok.begin, tok.end - tok.begin + 1);
}

QString ParseSession::docComment( qint64 token ) const
{
    const TokenStream::Token& tok = m_tokenStream->token( token );
    if (!tok.docCommentEnd) return QString();
    return m_contents.mid(tok.docCommentBegin, tok.docCommentEnd - tok.docCommentBegin + 1);
}

}
