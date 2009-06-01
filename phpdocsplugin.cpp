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

#include <KPluginFactory>
#include <KPluginLoader>
#include <KAboutData>
#include <KMimeType>

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

using namespace KDevelop;

K_PLUGIN_FACTORY(PhpDocsFactory, registerPlugin<PhpDocsPlugin>(); )
K_EXPORT_PLUGIN(PhpDocsFactory(KAboutData("kdevphpdocs","kdevphpdocs", ki18n("PhpDocs"), "0.1", ki18n("Check PHP.net documentation"), KAboutData::License_GPL).addAuthor(ki18n("Milian Wolff"), ki18n("Maintainer"), "mail@milianw.de", "http://milianw.de")))

PhpDocsPlugin::PhpDocsPlugin(QObject* parent, const QVariantList& args)
    : IPlugin(PhpDocsFactory::componentData(), parent)
{
    Q_UNUSED(args);
}

///TODO: possibly return multiple filenames (i.e. fallbacks) when doing local lookups
QString PhpDocsPlugin::getDocumentationFilename( KDevelop::Declaration* dec ) const
{
    QString fname;

    //TODO: most of the SPL stuff is not found for me in the deb package php-doc
    //      => check newer documentation or give a fallback to ref.spl.html
    if ( ClassFunctionDeclaration* fdec = dynamic_cast<ClassFunctionDeclaration*>( dec ) ) {
        // class methods -> php.net/function.CLASS-METHOD
        if ( dec->context() && dec->context()->type() == DUContext::Class && dec->context()->owner() ) {
            QString className = dec->context()->owner()->identifier().toString();

            if ( fdec->isConstructor() ) {
                fname = "construct";
            } else if ( fdec->isDestructor() ) {
                fname = "destruct";
            } else {
                fname = fdec->identifier().toString();
            }

            fname = "function." + className + fname;
        }
    } else if ( dynamic_cast<ClassDeclaration*>(dec) ) {
        ///TODO: check with current documentation
        fname = "ref." + dec->identifier().toString();
    } else if ( dynamic_cast<FunctionDeclaration*>(dec) ) {
        fname = "function." + dec->identifier().toString();
    }
    // check for superglobals
    else if ( dec->identifier() == Identifier("GLOBALS") ||
                dec->identifier() == Identifier("php_errormsg") ||
                dec->identifier() == Identifier("HTTP_RAW_POST_DATA") ||
                dec->identifier() == Identifier("http_response_header") ||
                dec->identifier() == Identifier("argc") ||
                dec->identifier() == Identifier("argv") ) {
        ///TODO: check with current documentation
//         fname = QString("reserved.variables.") + dec->identifier().toString();
        fname = "reserved.variables.html";
    } else if ( dec->identifier() == Identifier("_SERVER") ||
                dec->identifier() == Identifier("_GET") ||
                dec->identifier() == Identifier("_POST") ||
                dec->identifier() == Identifier("_FILES") ||
                dec->identifier() == Identifier("_REQUEST") ||
                dec->identifier() == Identifier("_SESSION") ||
                dec->identifier() == Identifier("_ENV") ||
                dec->identifier() == Identifier("_COOKIE") ) {
//         fname = QString("reserved.variables.") + dec->identifier().toString().mid(1);
        ///TODO: check with current documentation
        fname = "reserved.variables.html";
    }

    if ( !fname.isEmpty() ) {
        fname = fname.toLower();
        fname.replace('_', '-');
        fname.append(".html");
    }

    return fname;
}

KSharedPtr< IDocumentation > PhpDocsPlugin::documentationForDeclaration( Declaration* dec )
{
    if ( dec ) {
        DUChainReadLocker lock( DUChain::lock() );

        // filter non global or non-php declarations
        if ( dec->topContext()->url() != IndexedString("PHPInternalFunctions") ) {
            return KSharedPtr<IDocumentation>();
        }

        QString file = getDocumentationFilename( dec );
        if ( file.isEmpty() ) {
            return KSharedPtr<IDocumentation>();
        }

        KUrl url = PhpDocsSettings::phpDocLocation();
        kDebug() << url;
        kDebug() << PhpDocsSettings::self();
        url.addPath( file );
        if ( url.isLocalFile() && !QFile::exists( url.toLocalFile() ) ) {
            kDebug() << "bad path" << url << "for documentation of" << dec->toString() << "falling back to http://php.net/";
            url.setUrl("http://php.net/" + file);
        }

        kDebug() << "php documentation located at " << url << "for" << dec->toString();
        return KSharedPtr<IDocumentation>(new PhpDocumentation( url, dec->qualifiedIdentifier().toString(), dec->comment() ));
    }

    return KSharedPtr<IDocumentation>();
}

