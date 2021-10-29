/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "magicconstantnavigationcontext.h"

#include <QTextDocument>
#include <KLocalizedString>
#include <language/duchain/topducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/functiontype.h>
#include <serialization/indexedstring.h>

using namespace KDevelop;

namespace Php {

MagicConstantNavigationContext::MagicConstantNavigationContext(TopDUContextPointer topContext,
                                                                const KTextEditor::Cursor& position,
                                                                const QString& constant)
    : AbstractNavigationContext(topContext, nullptr), m_position(position.line(), position.column()), m_constant(constant)
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
        return nullptr;
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

    if ( m_constant == QLatin1String("__FILE__") ) {
        value = topContext()->url().str().toHtmlEscaped();
    } else if ( m_constant == QLatin1String("__DIR__") ) {
        value = QFileInfo(topContext()->url().str()).absoluteDir().path().toHtmlEscaped();
    } else if ( m_constant == QLatin1String("__LINE__") ) {
        value.setNum(m_position.line + 1);
    } else if ( m_constant == QLatin1String("__CLASS__") ) {
        if ( DUContext* ctx = findContext(topContext(), m_position, DUContext::Class) ) {
            value = codeHighlight(ctx->localScopeIdentifier().toString().toHtmlEscaped());
        } else {
            value = commentHighlight(i18n("empty (not inside a class)"));
        }
    } else if ( m_constant == QLatin1String("__TRAIT__") ) {
        if ( DUContext* ctx = findContext(topContext(), m_position, DUContext::Class) ) {
            value = codeHighlight(ctx->localScopeIdentifier().toString().toHtmlEscaped());
        } else {
            value = commentHighlight(i18n("empty (not inside a trait)"));
        }
    } else if ( m_constant == QLatin1String("__METHOD__") ) {
        CursorInRevision pos = m_position;
        while ( DUContext* ctx = findContext(topContext(), pos, DUContext::Other) ) {
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
        if ( DUContext* ctx = findContext(topContext(), pos, DUContext::Other) ) {
            if ( ctx->owner() && ctx->owner()->type<FunctionType>() ) {
                value = codeHighlight(ctx->localScopeIdentifier().toString().toHtmlEscaped());
            }
        }
        if ( value.isEmpty() ) {
            value = commentHighlight(i18n("empty (not inside a function)"));
        }
    } else if ( m_constant == QLatin1String("__NAMESPACE__") ) {
        if ( DUContext* ctx = findContext(topContext(), m_position, DUContext::Namespace) ) {
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
