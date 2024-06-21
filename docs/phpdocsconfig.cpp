/*
    SPDX-FileCopyrightText: 2012 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "phpdocsconfig.h"

#include "phpdocsplugin.h"
#include "phpdocssettings.h"
#include "ui_phpdocsconfig.h"

#include <KLocalizedString>

#include <QIcon>

PhpDocsConfig::PhpDocsConfig(PhpDocsPlugin* plugin, QWidget *parent)
    : KDevelop::ConfigPage(plugin, PhpDocsSettings::self(), parent)
{
    auto * l = new QVBoxLayout( this );

    QWidget* w = new QWidget;
    m_configWidget = new Ui::PhpDocsConfigUI;
    m_configWidget->setupUi( w );

    m_configWidget->kcfg_phpDocLocation->setMode( KFile::Directory | KFile::ExistingOnly );

    l->addWidget( w );

    reset();
}

PhpDocsConfig::~PhpDocsConfig()
{
    delete m_configWidget;
}

KDevelop::ConfigPage::ConfigPageType PhpDocsConfig::configPageType() const
{
    return KDevelop::ConfigPage::DocumentationConfigPage;
}

QString PhpDocsConfig::name() const
{
    return i18nc("@title:tab", "PHP Documentation");
}

QString PhpDocsConfig::fullName() const
{
    return i18nc("@title:tab", "Configure PHP Documentation Settings");
}

QIcon PhpDocsConfig::icon() const
{
    return QIcon::fromTheme(QStringLiteral("application-x-php"));
}

#include "moc_phpdocsconfig.cpp"
