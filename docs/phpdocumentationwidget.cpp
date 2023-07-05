/*
    SPDX-FileCopyrightText: 2012 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "phpdocumentationwidget.h"

#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QUrl>

#include <KLocalizedString>

#include "phpdocsplugin.h"
#include <documentation/standarddocumentationview.h>

PhpDocumentationWidget::PhpDocumentationWidget(KDevelop::DocumentationFindWidget* find, const QUrl &url,
                                               PhpDocsPlugin* provider, QWidget* parent)
: QStackedWidget(parent)
, m_loading(new QWidget(this))
, m_provider(provider)
{
    m_part = new KDevelop::StandardDocumentationView(find, this);
    m_part->setDelegateLinks(true);
    addWidget(m_part);
    addWidget(m_loading);

    auto* progressbar = new QProgressBar;
    progressbar->setValue(0);
    progressbar->setMinimum(0);
    progressbar->setMaximum(100);
    progressbar->setAlignment(Qt::AlignCenter);

// temporary disabled for initial porting to QWidget-only StandardDocumentationView
#if 0
    connect( m_part, &KDevelop::StandardDocumentationView::loadProgress,
             progressbar, &QProgressBar::setValue );
#endif

    auto* layout = new QVBoxLayout;
    layout->addStretch();
    QLabel* label = new QLabel(i18n("...loading documentation..."));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    layout->addWidget(progressbar);
    layout->addStretch();
    m_loading->setLayout(layout);
// temporary disabled for initial porting to QWidget-only StandardDocumentationView
#if 0
    setCurrentWidget(m_loading);
#endif
// instead directly show part
    setCurrentWidget(m_part);


    connect(m_part, &KDevelop::StandardDocumentationView::linkClicked, this, &PhpDocumentationWidget::linkClicked);
// temporary disabled for initial porting to QWidget-only StandardDocumentationView
#if 0
    connect(m_part, &KDevelop::StandardDocumentationView::loadFinished, this, &PhpDocumentationWidget::documentLoaded);
#endif
    m_part->load( url );
}

PhpDocumentationWidget::~PhpDocumentationWidget()
{
    // make sure we don't get called by any of the m_part signals on shutdown, see also:
    // https://codereview.qt-project.org/#/c/83800/
    disconnect(m_part, nullptr, this, nullptr);
}

void PhpDocumentationWidget::linkClicked(const QUrl& url)
{
    m_provider->showDocumentation(url);
}

void PhpDocumentationWidget::documentLoaded()
{
    setCurrentWidget(m_part);
    removeWidget(m_loading);
    delete m_loading;
    m_loading = nullptr;
}

#include "moc_phpdocumentationwidget.cpp"
