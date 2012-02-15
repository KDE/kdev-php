/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Miha ?an?ula <miha.cancula@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "phpunitprovider.h"
#include <interfaces/icore.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iproject.h>
#include <interfaces/ilanguage.h>
#include <interfaces/ilanguagecontroller.h>
#include <project/projectmodel.h>
#include <language/duchain/declaration.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>


#include <KPluginFactory>
#include <KAboutData>
#include <KLocalizedString>
#include <KStandardDirs>
#include <QVariant>
#include <QTimer>

K_PLUGIN_FACTORY(PhpUnitProviderFactory, registerPlugin<PhpUnitProvider>(); )
K_EXPORT_PLUGIN(PhpUnitProviderFactory(KAboutData("kdevphpunitprovider","kdevphpunitprovider", ki18n("PHPUnit Integration"), "0.1", ki18n("Finds and run PHPUnit tests"), KAboutData::License_GPL)))


using namespace KDevelop;

PhpUnitProvider::PhpUnitProvider(QObject* parent, const QList< QVariant >& args): IPlugin(PhpUnitProviderFactory::componentData(), parent)
{
    Q_UNUSED(args);
    findTestSuites();
    connect(core()->projectController(), SIGNAL(projectOpened(KDevelop::IProject*)), SLOT(findTestSuites()));

    QTimer::singleShot(10000, this, SLOT(findTestSuites()));
}

void PhpUnitProvider::unload()
{
}

void PhpUnitProvider::createTestSuite(const QString& name, const KUrl& url, IProject* project)
{

}

void PhpUnitProvider::findTestSuites()
{
    QString file = KStandardDirs::locate("data", "kdevphpsupport/phpunitdeclarations.php");
    DUChainReadLocker lock(DUChain::lock());
    DUChain::self()->updateContextForUrl(IndexedString(file), KDevelop::TopDUContext::AllDeclarationsAndContexts, this, -10);

    PersistentSymbolTable::Declarations declarations = PersistentSymbolTable::self().getDeclarations( QualifiedIdentifier("PHPUnit_Framework_TestCase") );
    kDebug() << "Found" << declarations.dataSize() << "declaration of PHPUnit_Framework_TestCase";
    for (PersistentSymbolTable::Declarations::Iterator it = declarations.iterator(); it; ++it) {
        uint steps = 2;
        foreach (Declaration* testDeclaration, DUChainUtils::getInheriters(it->declaration(), steps) )
        {
            QString name = testDeclaration->identifier().toString();
            KUrl url = testDeclaration->url().toUrl();
            IProject* project = core()->projectController()->findProjectForUrl(url);
            kDebug() << name << url << (project ? project->name() : "No project");
            if (!project)
            {
                continue;
            }
            createTestSuite(name, url, project);
        }
    }

    DUContext* context = DUChainUtils::standardContextForUrl(file);
    QVector<Declaration*> decl = context->localDeclarations();
    kDebug() << "Found" << decl.size() << "declarations using the direct method";
    foreach (Declaration* p, decl)
    {
        kDebug() << "Found PHP Unit declaration" << p->identifier().toString();
        uint depth = 3;
        foreach (Declaration* d, DUChainUtils::getInheriters(p, depth))
        {
            QString name = d->identifier().toString();
            KUrl url = d->url().toUrl();
            IProject* project = core()->projectController()->findProjectForUrl(url);
            kDebug() << name << url << (project ? project->name() : "No project");
            if (!project)
            {
                continue;
            }
            createTestSuite(name, url, project);
        }
    }

    QTimer::singleShot(10000, this, SLOT(findTestSuites()));
}

