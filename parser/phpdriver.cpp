/* Php Parser Driver
 *
 * Copyright 2007 Andreas Pakulat <apaku@gmx.de>
 * Copyright 2008 Niko Sams <niko.sams@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#include "phpdriver.h"
#include "phpparser.h"

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>

namespace Php
{

Driver::Driver()
    : m_debug(false), m_pool(0), m_tokenstream(0)
{
}

bool Driver::readFile( const QString& filename, const char* codec )
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
    m_content = s.readAll();
    return true;
}
void Driver::setContent( const QString& content )
{
    m_content = content;
}
void Driver::setDebug( bool debug )
{
    m_debug = debug;
}


bool Driver::parse( Php::StartAst** ast )
{
    if(!m_tokenstream)
        m_tokenstream = new KDevPG::TokenStream();
    if(!m_pool)
        m_pool = new KDevPG::MemoryPool();

    Parser phpparser;
    phpparser.setTokenStream( m_tokenstream );
    phpparser.setMemoryPool( m_pool );
    phpparser.setDebug( m_debug );

    phpparser.tokenize(m_content);
    StartAst* phpAst;
    bool matched = phpparser.parseStart(&phpAst);
    if( matched )
    {
        kDebug() << "Sucessfully parsed";
        *ast = phpAst;
    }else
    {
        *ast = 0;
        phpparser.expectedSymbol(AstNode::StartKind, "start");
        kDebug() << "Couldn't parse content";
    }
    return matched;
}


void Driver::setTokenStream( KDevPG::TokenStream* ts )
{
    m_tokenstream = ts;
}

void Driver::setMemoryPool( KDevPG::MemoryPool* pool )
{
    m_pool = pool;
}

QString Driver::content() const
{
    return m_content;
}

KDevPG::TokenStream* Driver::tokenStream() const
{
    return m_tokenstream;
}

}

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
