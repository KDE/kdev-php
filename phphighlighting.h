/*
    SPDX-FileCopyrightText: 2010 Milian Wolff

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PHP_PHPHIGHLIGHTING_H
#define PHP_PHPHIGHLIGHTING_H

#include <language/highlighting/codehighlighting.h>


namespace Php {

class Highlighting : public KDevelop::CodeHighlighting
{
public:
    Highlighting(QObject* parent);
    KDevelop::CodeHighlightingInstance* createInstance() const override;
};

}

#endif // PHP_PHPHIGHLIGHTING_H
