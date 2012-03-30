/*  This file is part of the KDevelop PHP Documentation Plugin

    Copyright 2012 Milian Wolff <mail@milianw.de>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PHPDOCSPLUGIN_H
#define PHPDOCSPLUGIN_H

#include <interfaces/iplugin.h>
#include <interfaces/idocumentationprovider.h>
#include <QVariantList>

class PhpDocsModel;

class KUrl;

class PhpDocsPlugin : public KDevelop::IPlugin, public KDevelop::IDocumentationProvider
{
  Q_OBJECT

  Q_INTERFACES( KDevelop::IDocumentationProvider )

  public:
    explicit PhpDocsPlugin(QObject *parent, const QVariantList & args= QVariantList());
    ~PhpDocsPlugin();

    virtual KSharedPtr< KDevelop::IDocumentation > documentationForDeclaration (KDevelop::Declaration* dec) const;
    virtual QAbstractListModel* indexModel() const;
    virtual KSharedPtr< KDevelop::IDocumentation > documentationForIndex(const QModelIndex& index) const;
    virtual QIcon icon() const;
    virtual QString name() const;
    virtual KSharedPtr< KDevelop::IDocumentation > homePage() const;

    void addToHistory(const QUrl& url);

  signals:
    void addHistory( const KSharedPtr< KDevelop::IDocumentation >& doc ) const;

  public slots:
    void loadUrl(const QUrl &url) const;

  private:
    KSharedPtr< KDevelop::IDocumentation > documentationForUrl(
        const KUrl& url, const QString& name, const QByteArray& description = QByteArray()
    ) const;

    QString getDocumentationFilename(KDevelop::Declaration* dec, const bool& isLocal) const;
    PhpDocsModel* m_model;

  private slots:
    void readConfig();
};

#endif // PHPDOCSPLUGIN_H
