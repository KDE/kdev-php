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

#ifndef PHPDRIVER_H
#define PHPDRIVER_H

#include <QtCore/QString>
#include "parserexport.h"
namespace KDevPG
{
class MemoryPool;
class TokenStream;
}
namespace Php
{
class StartAst;
}

namespace Php
{
/**
 * Class to parse a Php source file or a string containing php source code
 */
class KDEVPHPPARSER_EXPORT Driver
{
public:
    Driver();
    bool readFile( const QString&, const char* = 0 );
    void setContent( const QString& );
    void setDebug( bool );
    bool parse( Php::StartAst** ast );
    void setTokenStream( KDevPG::TokenStream* );
    void setMemoryPool( KDevPG::MemoryPool* );
    QString content() const;
    KDevPG::TokenStream* tokenStream() const;

private:
    QString m_content;
    bool m_debug;
    KDevPG::MemoryPool* m_pool;
    KDevPG::TokenStream* m_tokenstream;

};

}

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
