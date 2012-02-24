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

#include "phpdocsplugin.h"
#include "phpdocsmodel.h"

#include <KPluginFactory>
#include <KPluginLoader>
#include <KAboutData>
#include <KMimeType>
#include <KSettings/Dispatcher>
#include <KUrl>
#include <KIcon>

#include <interfaces/idocumentation.h>

#include <language/duchain/duchain.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/indexedstring.h>

#include <language/duchain/classdeclaration.h>
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/classmemberdeclaration.h>
#include <language/duchain/classfunctiondeclaration.h>

#include <QtCore/QFile>

#include "phpdocumentation.h"
#include "phpdocssettings.h"
#include <interfaces/icore.h>
#include <interfaces/idocumentationcontroller.h>

using namespace KDevelop;

K_PLUGIN_FACTORY(PhpDocsFactory, registerPlugin<PhpDocsPlugin>(); )
K_EXPORT_PLUGIN(PhpDocsFactory(KAboutData("kdevphpdocs","kdevphpdocs", ki18n("PhpDocs"),
                                          "1.2.90", ki18n("Check PHP.net documentation"),
                               KAboutData::License_GPL).addAuthor(ki18n("Milian Wolff"),
                               ki18n("Maintainer"), "mail@milianw.de", "http://milianw.de")))

PhpDocsPlugin::PhpDocsPlugin(QObject* parent, const QVariantList& args)
    : IPlugin(PhpDocsFactory::componentData(), parent), m_model(new PhpDocsModel(this))
{
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::IDocumentationProvider )
    Q_UNUSED(args);

    readConfig();

    KSettings::Dispatcher::registerComponent( KComponentData("kdevphpdocs_config"),
                                              this, "readConfig" );
}

PhpDocsPlugin::~PhpDocsPlugin()
{
}

QString PhpDocsPlugin::name() const
{
    return QString("PHP");
}

QIcon PhpDocsPlugin::icon() const
{
    static KIcon icon("application-x-php");;
    return icon;
}

void PhpDocsPlugin::readConfig()
{
    // since PhpDocsSettings pointer in this plugin is distinct from the one in the KCM
    // we have to trigger reading manually
    PhpDocsSettings::self()->readConfig();
}

///TODO: possibly return multiple filenames (i.e. fallbacks) when doing local lookups
QString PhpDocsPlugin::getDocumentationFilename( KDevelop::Declaration* dec, const bool& isLocal ) const
{
    QString fname;

    //TODO: most of the SPL stuff is not found for me in the deb package php-doc
    //      => check newer documentation or give a fallback to ref.spl.html
    if ( ClassFunctionDeclaration* fdec = dynamic_cast<ClassFunctionDeclaration*>( dec ) ) {
        // class methods -> php.net/CLASS.METHOD
        // local: either CLASS.METHOD.html or function.CLASS-METHOD.html... really sucks :-/
        //        for now, use the latter...
        if ( dec->context() && dec->context()->type() == DUContext::Class && dec->context()->owner() ) {
            QString className = dec->context()->owner()->identifier().toString();

            if ( !isLocal ) {
                fname = className + '.' + fdec->identifier().toString();
            } else {
                if ( fdec->isConstructor() ) {
                    fname = "construct";
                } else if ( fdec->isDestructor() ) {
                    fname = "destruct";
                } else {
                    fname = fdec->identifier().toString();
                }
                //TODO: CLASS.METHOD.html e.g. for xmlreader etc. pp.
                fname = "function." + className + '-' + fname;
            }
        }
    } else if ( dynamic_cast<ClassDeclaration*>(dec) ) {
        fname = "class." + dec->identifier().toString();
    } else if ( dynamic_cast<FunctionDeclaration*>(dec) ) {
        fname = "function." + dec->identifier().toString();
    }
    // check for superglobals / reserved variables
    else if ( dec->identifier() == Identifier("GLOBALS") ||
                dec->identifier() == Identifier("php_errormsg") ||
                dec->identifier() == Identifier("HTTP_RAW_POST_DATA") ||
                dec->identifier() == Identifier("http_response_header") ||
                dec->identifier() == Identifier("argc") ||
                dec->identifier() == Identifier("argv") ||
                dec->identifier() == Identifier("_GET") ||
                dec->identifier() == Identifier("_POST") ||
                dec->identifier() == Identifier("_FILES") ||
                dec->identifier() == Identifier("_REQUEST") ||
                dec->identifier() == Identifier("_SESSION") ||
                dec->identifier() == Identifier("_ENV") ||
                dec->identifier() == Identifier("_COOKIE") ) {
        if ( isLocal ) {
            fname = QString("reserved.variables.") + dec->identifier().toString().remove('_');
        } else {
            fname = dec->identifier().toString();
        }
    }

    kDebug() << fname;

    if ( !fname.isEmpty() && isLocal ) {
        fname = fname.toLower();
        fname.replace('_', '-');
        fname.append(".html");
    }

    return fname;
}

KSharedPtr< IDocumentation > PhpDocsPlugin::documentationForDeclaration( Declaration* dec ) const
{
    if ( dec ) {
        DUChainReadLocker lock( DUChain::lock() );

        // filter non global or non-php declarations
        if ( dec->topContext()->url() != m_model->internalFunctionFile() ) {
            return KSharedPtr<IDocumentation>();
        }

        KUrl url = PhpDocsSettings::phpDocLocation();
        kDebug() << url;

        QString file = getDocumentationFilename( dec, url.isLocalFile() );
        if ( file.isEmpty() ) {
            kDebug() << "no documentation pattern found for" << dec->toString();
            return KSharedPtr<IDocumentation>();
        }

        url.addPath( file );
        if ( url.isLocalFile() && !QFile::exists( url.toLocalFile() ) ) {
            kDebug() << "bad path" << url << "for documentation of" << dec->toString() << " - aborting";
            return KSharedPtr<IDocumentation>();
        }

        kDebug() << "php documentation located at " << url << "for" << dec->toString();
        return documentationForUrl(url, dec->qualifiedIdentifier().toString(), dec->comment());
    }

    return KSharedPtr<IDocumentation>();
}

QAbstractListModel* PhpDocsPlugin::indexModel() const
{
    return m_model;
}

KSharedPtr< IDocumentation > PhpDocsPlugin::documentationForIndex(const QModelIndex& index) const
{
    return documentationForDeclaration(static_cast<Declaration*>(
        index.data(PhpDocsModel::DeclarationRole).value<DeclarationPointer>().data()
    ));
}

void PhpDocsPlugin::loadUrl(const QUrl& url) const
{
    kDebug() << "loading URL" << url;
    KSharedPtr<IDocumentation> doc = documentationForUrl(url, QString());
    ICore::self()->documentationController()->showDocumentation(doc);
}

KSharedPtr< IDocumentation > PhpDocsPlugin::documentationForUrl(const KUrl& url, const QString& name, const QByteArray& description) const
{
    return KSharedPtr<IDocumentation>(new PhpDocumentation( url, name, description, const_cast<PhpDocsPlugin*>(this)));
}

KSharedPtr< IDocumentation > PhpDocsPlugin::homePage() const
{
    KUrl url = PhpDocsSettings::phpDocLocation();
    if ( url.isLocalFile() ) {
        url.addPath("index.html");
    } else {
        url.addPath("manual");
    }
    return documentationForUrl(url, i18n("PHP Documentation"));
}

#include "phpdocsplugin.h"
