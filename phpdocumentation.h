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

#ifndef PHPDOCUMENTATION_H
#define PHPDOCUMENTATION_H

#include <interfaces/idocumentation.h>

#include <KUrl>

#include <QtCore/QObject>
#include <QtCore/QString>

class QWidget;
class QStackedWidget;
class KHTMLPart;

class PhpDocsPlugin;

class PhpDocumentation : public KDevelop::IDocumentation
{
  public:
    explicit PhpDocumentation(const KUrl& url, const QString& name, const QByteArray& description, PhpDocsPlugin* parent);
    ~PhpDocumentation();

    virtual QString name() const;
    virtual QString description() const;
    virtual bool providesWidget() const;
    virtual QWidget* documentationWidget(QWidget* parent = 0);
    virtual KDevelop::IDocumentationProvider* provider() const;

  private:
    const KUrl m_url;
    const QString m_name;
    const QByteArray m_description;
    PhpDocsPlugin* m_parent;
};

#endif // PHPDOCUMENTATION_H
