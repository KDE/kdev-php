/*  This file is part of KDevelop

    Copyright 2009 Milian Wolff <mail@milianw.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef PHPDOCSMODEL_H
#define PHPDOCSMODEL_H

#include <QtGui/QStringListModel>

namespace KDevelop
{
    class Declaration;
    class ParseJob;
}

class PhpDocsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PhpDocsModel(QObject* parent = 0);
    ~PhpDocsModel();

    enum CustomDataRoles {
        /// returns the Declaration that a given index in the model represents
        DeclarationRole = Qt::UserRole
    };

    /**
     * You can use @p DeclarationRole to get the Declaration for a given index.
     * NOTE: If you use that, don't forget to lock the DUChain if you access the declaration!
     */
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual bool hasChildren(const QModelIndex& parent) const;
    virtual bool canFetchMore(const QModelIndex& parent) const;

    /// Returns the Declaration for a given index
    /// NOTE: Don't forget to lock the DUChain if you access the declaration!
    KDevelop::Declaration* declarationForIndex(const QModelIndex& index) const;
private:
    /// fills model with all declarations from the internal PHP functions file
    void fillModel();

    /// List of pointers to _all_ PHP internal declarations
    QList<KDevelop::Declaration*> m_declarations;
public slots:
    void slotParseJobFinished( KDevelop::ParseJob* job );
};

#endif // PHPDOCSMODEL_H
