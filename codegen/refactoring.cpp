/* This file is part of KDevelop
 *
 * Copyright 2014 Miquel Sabaté <mikisabate@gmail.com>
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


#include <QObject>
#include <codegen/refactoring.h>
#include <language/duchain/declaration.h>
#include <language/duchain/use.h>

namespace Php
{

using KDevelop::DocumentChange;
using KDevelop::DocumentChangeSet;
using KDevelop::DUContext;
using KDevelop::TopDUContext;
using KDevelop::IndexedDeclaration;
using KDevelop::Declaration;
using KDevelop::Use;

Refactoring::Refactoring(QObject *parent)
    : BasicRefactoring(parent)
{
    /* There's nothing to do here. */
}

DocumentChangeSet::ChangeResult Refactoring::applyChanges(
    const QString& oldName,
    const QString& newName,
    DocumentChangeSet& changes,
    DUContext* context,
    int usedDeclarationIndex
)
{
    if (usedDeclarationIndex == std::numeric_limits<int>::max())
        return DocumentChangeSet::ChangeResult::successfulResult();

    for (int a = 0; a < context->usesCount(); ++a) {
        Use use = context->uses()[a];
        if (use.m_declarationIndex != usedDeclarationIndex)
        {
            continue;
        }
        if (use.m_range.isEmpty()) {
            continue;
        }

        if ( shouldRemoveDollar(use.m_range, oldName) )
        {
            use.m_range.start.column++;
        }
        DocumentChangeSet::ChangeResult result =
            changes.addChange(DocumentChange(context->url(), context->transformFromLocalRevision(use.m_range), oldName,
                                             newName));
        if (!result)
            return result;
    }

    const auto childContexts = context->childContexts();
    for (DUContext* child : childContexts) {
       DocumentChangeSet::ChangeResult result = applyChanges(oldName, newName, changes, child, usedDeclarationIndex);
        if (!result)
            return result;
    }

    return DocumentChangeSet::ChangeResult::successfulResult();
}

DocumentChangeSet::ChangeResult Refactoring::applyChangesToDeclarations(const QString& oldName,
                                                        const QString& newName,
                                                        DocumentChangeSet& changes,
                                                        const QList<IndexedDeclaration>& declarations)
{
    KTextEditor::Range range_to_modify;

    for (const IndexedDeclaration decl : declarations) {
        Declaration *declaration = decl.data();
        if (!declaration)
            continue;
        TopDUContext *top = declaration->topContext();
        range_to_modify = declaration->rangeInCurrentRevision();
        if ( shouldRemoveDollar(range_to_modify, oldName) )
        {
            range_to_modify = KTextEditor::Range(
                range_to_modify.start().line(),
                range_to_modify.start().column()+1,
                range_to_modify.end().line(),
                range_to_modify.end().column());
        }
        DocumentChangeSet::ChangeResult result = changes.addChange(DocumentChange(top->url(), range_to_modify, oldName, newName));
        if (!result)
            return result;
    }
    return DocumentChangeSet::ChangeResult::successfulResult();
}

bool Refactoring::shouldRemoveDollar(const KDevelop::RangeInRevision &range, QString name)
{
    if ( range.start.line != range.end.line )
    {
        return false;
    }
    return ( range.end.column - range.start.column == name.length() + 1 );
}

bool Refactoring::shouldRemoveDollar(const KTextEditor::Range &range, QString name)
{
    if ( range.start().line() != range.end().line() )
    {
        return false;
    }
    return ( range.columnWidth() == name.length() + 1 );
}

} // End of namespace Php
