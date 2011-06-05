/*
    This file is part of KDevelop PHP
    Copyright (C) 2010 Milian Wolff

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PHP_PHPHIGHLIGHTING_H
#define PHP_PHPHIGHLIGHTING_H

#include <language/highlighting/codehighlighting.h>


namespace Php {

class Highlighting : public KDevelop::CodeHighlighting
{
public:
    Highlighting(QObject* parent);
    virtual KDevelop::CodeHighlightingInstance* createInstance() const;
};

}

#endif // PHP_PHPHIGHLIGHTING_H
