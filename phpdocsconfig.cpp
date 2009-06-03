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

#include "phpdocsconfig.h"

#include <KLocalizedString>
#include <KPluginFactory>
#include <KPluginLoader>
#include <KConfigGroup>
#include <KUrlRequester>
#include <KUrl>
#include <KAboutData>
#include <KDebug>
#include <KFile>

#include <QtGui/QBoxLayout>
#include <QtGui/QLabel>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include "phpdocssettings.h"
#include "ui_phpdocsconfig.h"

K_PLUGIN_FACTORY(PhpDocsConfigFactory, registerPlugin<PhpDocsConfig>();)
K_EXPORT_PLUGIN(PhpDocsConfigFactory("kdevphpdocs_config"))

PhpDocsConfig::PhpDocsConfig(QWidget *parent, const QVariantList &args)
    : KCModule(PhpDocsConfigFactory::componentData(), parent, args)
{
    QVBoxLayout * l = new QVBoxLayout( this );

    QWidget* w = new QWidget;
    m_configWidget = new Ui::PhpDocsConfigUI;
    m_configWidget->setupUi( w );

    m_configWidget->kcfg_phpDocLocation->setMode( KFile::Directory | KFile::ExistingOnly );

    l->addWidget( w );

    addConfig( PhpDocsSettings::self(), w );

    load();
}

PhpDocsConfig::~PhpDocsConfig()
{
    delete m_configWidget;
}

#include "phpdocsconfig.moc"
