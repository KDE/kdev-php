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

K_PLUGIN_FACTORY(PhpDocsConfigFactory, registerPlugin<PhpDocsConfig>();)
K_EXPORT_PLUGIN(PhpDocsConfigFactory("kdevphpdocs_config"))

PhpDocsConfig::PhpDocsConfig(QWidget *parent, const QVariantList &args)
    : KCModule(PhpDocsConfigFactory::componentData(), parent, args)
{
    setupUi(this);

    ///TODO: how to use this?
    addConfig( PhpDocsSettings::self(), this );

    kcfg_phpDocLocation->setMode( KFile::Directory | KFile::ExistingOnly );

    connect( kcfg_phpDocLocation, SIGNAL(textChanged(QString)),
             this, SLOT(changed()) );
    connect( kcfg_phpDocLocation, SIGNAL(urlSelected(KUrl)),
             this, SLOT(changed()) );

    load();
}

PhpDocsConfig::~PhpDocsConfig()
{
}

void PhpDocsConfig::save()
{
    ///TODO: can't this be done automatically with KConfigXT? i.e. the mapping .ui <-> .kcfg
    PhpDocsSettings::self()->phpDocLocationItem()->setValue( kcfg_phpDocLocation->url() );
    PhpDocsSettings::self()->writeConfig();
    KCModule::save();
    kDebug() << PhpDocsSettings::phpDocLocation() << PhpDocsSettings::self();
}

void PhpDocsConfig::load()
{
    PhpDocsSettings::self()->readConfig();
    kcfg_phpDocLocation->setUrl( PhpDocsSettings::phpDocLocation() );
    KCModule::load();
}

void PhpDocsConfig::defaults()
{
    PhpDocsSettings::self()->setDefaults();
    kcfg_phpDocLocation->setUrl( PhpDocsSettings::phpDocLocation() );
    KCModule::defaults();
}

#include "phpdocsconfig.moc"
