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

#ifndef PHPDOCUMENTATIONWIDGET_H
#define PHPDOCUMENTATIONWIDGET_H

#include <QtGui/QStackedWidget>

class QTemporaryFile;
class KUrl;
class QUrl;

namespace KDevelop {
    class StandardDocumentationView;
    class DocumentationFindWidget;
}

class PhpDocsPlugin;

class PhpDocumentationWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit PhpDocumentationWidget(KDevelop::DocumentationFindWidget* find, const KUrl &url,
                                    PhpDocsPlugin* provider, QWidget* parent = 0);

private slots:
    /// used to inject some custom CSS to alter the remote php.net site
    void documentLoaded();
    void linkClicked(const QUrl& url);

private:
    KDevelop::StandardDocumentationView* m_part;
    QWidget* m_loading;
    QTemporaryFile* m_styleSheet;
    PhpDocsPlugin* m_provider;
};

#endif // PHPDOCUMENTATIONWIDGET_H
