/* This file is part of KDevelop
    Copyright 2006 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "editorintegrator.h"

#include <ktexteditor/document.h>
#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/editor/documentrange.h>
#include <language/editor/documentrangeobject.h>

#include "phpast.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace Php;

EditorIntegrator::EditorIntegrator(ParseSession* session)
        : m_session(session)
{
}

KDevelop::SimpleCursor EditorIntegrator::findPosition(qint64 token, Edge edge) const
{
    const KDevPG::TokenStream::Token& t = m_session->tokenStream()->token(token);
    return findPosition(t, edge);
}

KDevelop::SimpleCursor EditorIntegrator::findPosition(const KDevPG::TokenStream::Token & token, Edge edge) const
{
    if (edge == BackEdge) {
        // Apparently KTE expects a range to go until _after_ the last character that should be included
        // however the parser calculates endCol as the index _before_ the last included character, so adjust here
        return m_session->positionAt(token.end + 1);
    } else {
        return m_session->positionAt(token.begin);
    }
}

KDevelop::SimpleRange EditorIntegrator::findRange(AstNode * node, RangeEdge edge)
{
    Q_UNUSED(edge);
    return KDevelop::SimpleRange(findPosition(node->startToken, FrontEdge), findPosition(node->endToken, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange(qint64 startToken, qint64 endToken)
{
    return KDevelop::SimpleRange(findPosition(startToken, FrontEdge), findPosition(endToken, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange(AstNode* from, AstNode* to)
{
    return KDevelop::SimpleRange(findPosition(from->startToken, FrontEdge), findPosition(to->endToken, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange(const KDevPG::TokenStream::Token & token)
{
    return KDevelop::SimpleRange(findPosition(token, FrontEdge), findPosition(token, BackEdge));
}

QString EditorIntegrator::tokenToString(qint64 token) const
{
    return m_session->symbol(token);
}

ParseSession * EditorIntegrator::parseSession() const
{
    return m_session;
}

