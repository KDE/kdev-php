/*
 * KDevelop Php Code Completion Support
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "codemodelitem.h"

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/codemodel.h>
#include <language/codecompletion/codecompletionmodel.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainutils.h>


using namespace KDevelop;

namespace Php
{

CodeModelCompletionItem::CodeModelCompletionItem(const ParsingEnvironmentFilePointer &env, const CodeModelItem &item)
    : CompletionTreeItem(), m_env(env), m_item(item)
{
}

QVariant CodeModelCompletionItem::data(const QModelIndex& index, int role, const KDevelop::CodeCompletionModel* model) const
{

    DUChainReadLocker lock(DUChain::lock(), 500);
    if (!lock.locked()) {
        kDebug() << "Failed to lock the du-chain in time";
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case KDevelop::CodeCompletionModel::Name:
            //if (!m_decl) {
            //    m_decl = m_env->topContext()->findDeclarations(m_item.id).first();
            //}
            //return m_decl->toString();
            return QVariant(m_item.id.identifier().toString());
        }
        break;
    case Qt::DecorationRole:
        if( index.column() == CodeCompletionModel::Icon ) {
            CodeCompletionModel::CompletionProperties p = completionProperties();
            lock.unlock();
            return DUChainUtils::iconForProperties(p);
        }
        break;
    }
    return QVariant();
}

CodeCompletionModel::CompletionProperties CodeModelCompletionItem::completionProperties() const
{
    CodeCompletionModel::CompletionProperties ret = CodeCompletionModel::NoProperty;

    switch (m_item.kind) {
        case CodeModelItem::Unknown:
            break;
        case CodeModelItem::Function:
            ret |= CodeCompletionModel::Function;
            break;
        case CodeModelItem::Variable:
            ret |= CodeCompletionModel::Variable;
            break;
        case CodeModelItem::Class:
            ret |= CodeCompletionModel::Class;
            break;
        case CodeModelItem::ForwardDeclaration:
            break;
        case CodeModelItem::Namespace:
            ret |= CodeCompletionModel::Namespace;
            break;
    }
    return ret;
}


}

