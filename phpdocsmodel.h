/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PHPDOCSMODULE_H
#define PHPDOCSMODULE_H

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

#endif // PHPDOCSMODULE_H
