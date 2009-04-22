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

#include "phpdocumentation.h"

using namespace KDevelop;

K_PLUGIN_FACTORY(PhpDocsFactory, registerPlugin<PhpDocsPlugin>(); )
K_EXPORT_PLUGIN(PhpDocsFactory(KAboutData("kdevphpdocs","kdevphpdocs", ki18n("PhpDocs"), "0.1", ki18n("Check PHP.net documentation"), KAboutData::License_GPL).addAuthor(ki18n("Milian Wolff"), ki18n("Maintainer"), "mail@milianw.de", "http://milianw.de")))

PhpDocsPlugin::PhpDocsPlugin(QObject* parent, const QVariantList& args)
    : IPlugin(PhpDocsFactory::componentData(), parent)
{
    Q_UNUSED(args);
}

KSharedPtr< IDocumentation > PhpDocsPlugin::documentationForDeclaration( Declaration* dec )
{
    if ( dec ) {
        DUChainReadLocker lock( DUChain::lock() );

        // filter non global or non-php declarations
        if ( dec->topContext()->url() != IndexedString("PHPInternalFunctions") ) {
            kDebug() << "topcontext is not internal functions:" << dec->topContext()->url().str();
            return KSharedPtr<IDocumentation>();
        }

        KUrl url("http://php.net/");

        if ( ClassMemberDeclaration* cdec = dynamic_cast<ClassMemberDeclaration*>( dec ) ) {
            // classmember (methods and properties) -> php.net/CLASS.CLASSMEMBER
            url.addPath( cdec->identifier().toString() + "." +
                         dec->identifier().toString() );
        } else if ( dynamic_cast<ClassDeclaration*>(dec) ||
                    dynamic_cast<FunctionDeclaration*>(dec) ) {
            // class -> php.net/CLASS
            // function -> php.net/FUNCTION {
            url.addPath( dec->identifier().toString() );
        }
        // check for superglobals
        else if ( dec->identifier() == Identifier("GLOBALS") ||
                  dec->identifier() == Identifier("php_errormsg") ||
                  dec->identifier() == Identifier("HTTP_RAW_POST_DATA") ||
                  dec->identifier() == Identifier("http_response_header") ||
                  dec->identifier() == Identifier("argc") ||
                  dec->identifier() == Identifier("argv") ) {
            url.addPath( QString("reserved.variables.") + dec->identifier().toString() );
        } else if ( dec->identifier() == Identifier("_SERVER") ||
                    dec->identifier() == Identifier("_GET") ||
                    dec->identifier() == Identifier("_POST") ||
                    dec->identifier() == Identifier("_FILES") ||
                    dec->identifier() == Identifier("_REQUEST") ||
                    dec->identifier() == Identifier("_SESSION") ||
                    dec->identifier() == Identifier("_ENV") ||
                    dec->identifier() == Identifier("_COOKIE") ) {
            url.addPath( QString("reserved.variables.") + dec->identifier().toString().mid(1) );
        } else {
            kDebug() << "looks like nothing we can provide documentation for:" << dec->toString();
            ///TODO: constants
            return KSharedPtr<IDocumentation>();
        }

        kDebug() << "php documentation located at " << url << "for" << dec->toString();
        return KSharedPtr<IDocumentation>(new PhpDocumentation( url, dec->qualifiedIdentifier().toString(), dec->comment() ));
    }

    return KSharedPtr<IDocumentation>();
}

