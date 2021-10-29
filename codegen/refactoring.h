/*
    SPDX-FileCopyrightText: 2014 Miquel Sabaté <mikisabate@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/


#ifndef REFACTORING_H
#define REFACTORING_H


#include <interfaces/context.h>
#include <language/codegen/basicrefactoring.h>


namespace Php
{

class Refactoring : public KDevelop::BasicRefactoring
{
public:
    explicit Refactoring(QObject *parent = nullptr);

    KDevelop::DocumentChangeSet::ChangeResult applyChangesToDeclarations(
        const QString& oldName,
        const QString& newName,
        KDevelop::DocumentChangeSet& changes,
        const QList<KDevelop::IndexedDeclaration>& declarations) override;

    KDevelop::DocumentChangeSet::ChangeResult applyChanges(
        const QString& oldName,
        const QString& newName,
        KDevelop::DocumentChangeSet& changes,
        KDevelop::DUContext* context,
        int usedDeclarationIndex) override;

private:
    bool shouldRemoveDollar(const KDevelop::RangeInRevision &range, QString name);
    bool shouldRemoveDollar(const KTextEditor::Range &range, QString name);
};

} // End of namespace Php


#endif /* REFACTORING_H */
