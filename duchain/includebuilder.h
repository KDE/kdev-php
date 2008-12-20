/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/


#ifndef INCLUDEBUILDER_H
#define INCLUDEBUILDER_H

#include <QList>
#include <language/duchain/indexedstring.h>

#include "phpduchainexport.h"
#include "phpdefaultvisitor.h"

namespace Php {
class EditorIntegrator;

class KDEVPHPDUCHAIN_EXPORT IncludeBuilder : public DefaultVisitor
{
public:
    IncludeBuilder(EditorIntegrator* editor);
    QList<KDevelop::IndexedString> includes();
    void build(const KDevelop::IndexedString &document, AstNode* ast);

protected:
    virtual void visitUnaryExpression(UnaryExpressionAst* node);

private:
    EditorIntegrator* m_editor;
    QList<KDevelop::IndexedString> m_includes;
    KDevelop::IndexedString m_document;
};

}

#endif // INCLUDEBUILDER_H
