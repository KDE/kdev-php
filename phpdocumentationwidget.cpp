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

#include "phpdocumentationwidget.h"

#include <KHTMLPart>
#include <QProgressBar>

#include <QVBoxLayout>

#include "phpdocsplugin.h"
#include <QLabel>

PhpDocumentationWidget::PhpDocumentationWidget(const KUrl &url, PhpDocsPlugin* provider, QWidget* parent)
    : QStackedWidget(parent), m_part(new KHTMLPart(this)), m_loading(new QWidget(this))
{
    addWidget(m_part->widget());
    addWidget(m_loading);

    connect( m_part, SIGNAL(docCreated()),
             this, SLOT(documentLoaded()) );

    QProgressBar* progressbar = new QProgressBar;
    progressbar->setValue(0);
    progressbar->setMinimum(0);
    progressbar->setMaximum(100);
    progressbar->setAlignment(Qt::AlignCenter);

    connect( m_part->browserExtension(), SIGNAL(loadingProgress(int)),
             progressbar, SLOT(setValue(int)) );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addStretch();
    QLabel* label = new QLabel(i18n("...loading documentation..."));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    layout->addWidget(progressbar);
    layout->addStretch();
    m_loading->setLayout(layout);
    setCurrentWidget(m_loading);

    connect( m_part->browserExtension(), SIGNAL(openUrlRequest(KUrl,KParts::OpenUrlArguments, KParts::BrowserArguments)),
             provider, SLOT(loadUrl(KUrl)) );

    m_part->openUrl( url );
}

void PhpDocumentationWidget::documentLoaded()
{
    m_part->setUserStyleSheet( QString( "#headnav,#headsearch,#footnav,#leftbar{display:none !important;}"
                                        "body{font-size:80% !important;}"
                                        "option,select{font-size:80% !important;}"
                                        "#layout_2,#layout_3{background: none !important;}"
                                        "#content{margin:0 !important}") );

    setCurrentWidget(m_part->widget());
    removeWidget(m_loading);
    delete m_loading;
    m_loading = 0;
}

#include "phpdocumentationwidget.moc"
