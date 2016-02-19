/*
   Copyright 2009 Milian Wolff <mail@milianw.de>

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

#include "magicconstantnavigationcontext.h"

#include <QtGui/QTextDocument>
#include <KLocalizedString>
#include <language/duchain/topducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/functiontype.h>

using namespace KDevelop;

namespace Php {

MagicConstantNavigationContext::MagicConstantNavigationContext(TopDUContextPointer topContext,
                                                                const KTextEditor::Cursor& position,
                                                                const QString& constant)
    : AbstractNavigationContext(topContext, 0), m_position(position.line(), position.column()), m_constant(constant)
{
}


QString MagicConstantNavigationContext::name() const
{
    return m_constant;
}

DUContext* findContext(TopDUContextPointer topCtx, const CursorInRevision& pos, DUContext::ContextType type) {
    DUContext* ctx = topCtx->findContextAt(pos);
    while ( ctx && ctx->type() != type ) {
        ctx = ctx->parentContext();
    }
    if ( !ctx || ctx->type() != type ) {
        return 0;
    } else {
        return ctx;
    }
}

QString MagicConstantNavigationContext::html(bool /*shorten*/)
{
    QString html = QStringLiteral("<html><body><p><small><small>");
    html += typeHighlight(i18n("magic constant"));
    html += ' ';
    html += nameHighlight(m_constant.toHtmlEscaped());
    html += QLatin1String("<br/>\n");

    QString value;
    ///TODO: php 5.3: __DIR__, __NAMESPACE__
    if ( m_constant == QLatin1String("__FILE__") ) {
        value = m_topContext->url().str().toHtmlEscaped();
    } else if ( m_constant == QLatin1String("__LINE__") ) {
        value.setNum(m_position.line + 1);
    } else if ( m_constant == QLatin1String("__CLASS__") ) {
        if ( DUContext* ctx = findContext(m_topContext, m_position, DUContext::Class) ) {
            value = codeHighlight(ctx->localScopeIdentifier().toString().toHtmlEscaped());
        } else {
            value = commentHighlight(i18n("empty (not inside a class)"));
        }
    } else if ( m_constant == QLatin1String("__METHOD__") ) {
        CursorInRevision pos = m_position;
        while ( DUContext* ctx = findContext(m_topContext, pos, DUContext::Other) ) {
            if ( !ctx->parentContext() ) {
                break;
            }
            if ( ctx->parentContext()->type() == DUContext::Class ) {
                value = codeHighlight(QString(
                            ctx->parentContext()->localScopeIdentifier().toString() + "::"
                            + ctx->localScopeIdentifier().toString()
                        ).toHtmlEscaped());
                break;
            }
            // might be a "normal" function inside a method...
            pos = ctx->range().start;
        }
        if ( value.isEmpty() ) {
            value = commentHighlight(i18n("empty (not inside a method)"));
        }
    } else if ( m_constant == QLatin1String("__FUNCTION__") ) {
        CursorInRevision pos = m_position;
        if ( DUContext* ctx = findContext(m_topContext, pos, DUContext::Other) ) {
            if ( ctx->owner() && ctx->owner()->type<FunctionType>() ) {
                value = codeHighlight(ctx->localScopeIdentifier().toString().toHtmlEscaped());
            }
        }
        if ( value.isEmpty() ) {
            value = commentHighlight(i18n("empty (not inside a function)"));
        }
    } else if ( m_constant == QLatin1String("__NAMESPACE__") ) {
        if ( DUContext* ctx = findContext(m_topContext, m_position, DUContext::Namespace) ) {
            if ( ctx->owner() && ctx->owner()->kind() == Declaration::Namespace ) {
                value = codeHighlight(ctx->localScopeIdentifier().toString().toHtmlEscaped());
            }
        }
        if ( value.isEmpty() ) {
            value = commentHighlight(i18n("empty (not inside a namespace)"));
        }
    }

    html += i18n("current value: %1", value);

    html += QLatin1String("</small></small></p></body></html>");

    return html;
}


}
