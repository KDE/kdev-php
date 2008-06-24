/*****************************************************************************
 * Copyright (c) 2007 Andreas Pakulat <apaku@gmx.de>                         *
 * Copyright (c) 2007 Piyush verma <piyush.verma@gmail.com>                  *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/


#include "phplanguagesupport.h"

#include <QMutexLocker>

#include <kdebug.h>
#include <kcomponentdata.h>
#include <kstandarddirs.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <ktexteditor/smartinterface.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/ilanguage.h>
#include <interfaces/idocument.h>
#include <editor/editorintegrator.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/duchain/duchain.h>
#include <interfaces/idocumentcontroller.h>

#include "phpparsejob.h"
//#include "phphighlighting.h"

using namespace KDevelop;

K_PLUGIN_FACTORY( KDevPhpSupportFactory, registerPlugin<Php::LanguageSupport>(); )
K_EXPORT_PLUGIN( KDevPhpSupportFactory( "kdevphpsupport" ) )

namespace Php
{

LanguageSupport::LanguageSupport( QObject* parent, const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevPhpSupportFactory::componentData(), parent ),
        KDevelop::ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::ILanguageSupport )
//     core()->pluginController()->loadPlugin( "kdevduchainview" );
//    m_highlighting = new Highlighting( this );
}

LanguageSupport::~LanguageSupport()
{
    core()->languageController()->backgroundParser()->clear( this );
    //delete m_highlighting;
    //m_highlighting = 0;
}

KDevelop::ParseJob *LanguageSupport::createParseJob( const KUrl &url )
{
    return new ParseJob( url, this );
}

QString LanguageSupport::name() const
{
    return "Php";
}

KDevelop::ILanguage *LanguageSupport::language()
{
    return core()->languageController()->language( name() );
}

// KDevelop::ICodeHighlighting* LanguageSupport::codeHighlighting() const
// {
//     return 0;
// }

}

#include "phplanguagesupport.moc"
