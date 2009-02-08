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


#include "includebuilder.h"
#include "helper.h"
#include "editorintegrator.h"
#include "parsesession.h"

namespace Php {
using namespace KDevelop;

IncludeBuilder::IncludeBuilder(EditorIntegrator* editor)
    : m_editor(editor)
{}

QMap< Php::AstNode*, KDevelop::IndexedString > IncludeBuilder::includes()
{
    return m_includes;
}

QMap< Php::AstNode*, QString > IncludeBuilder::badIncludes()
{
    return m_badIncludes;
}

void IncludeBuilder::build(const IndexedString &document, AstNode *ast)
{
    m_document = document;
    visitNode(ast);
}

void IncludeBuilder::visitUnaryExpression(UnaryExpressionAst* node)
{
    DefaultVisitor::visitUnaryExpression(node);
    if (node->includeExpression) {
        //find name of the constant (first argument of the function call)
        CommonScalarAst* scalar = findCommonScalar(node->includeExpression);
        if (scalar && scalar->string != -1) {
            QString str = m_editor->parseSession()->symbol(scalar->string);
            str = str.mid(1, str.length()-2);
            IndexedString includeFile = findIncludeFileUrl(str, KUrl(m_document.str()));
            if (!includeFile.isEmpty()) {
                m_includes[node] = includeFile;
            } else {
                m_badIncludes[node] = str;
            }
        }
    }
}

}
