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

#include "phpdocumentation.h"
#include "phpdocsplugin.h"

#include <KHTMLPart>

PhpDocumentation::PhpDocumentation(const KUrl& url, const QString& name, const QByteArray& description, PhpDocsPlugin* parent)
    : m_url(url), m_name(name), m_description(description), m_parent(parent)
{
}

PhpDocumentation::~PhpDocumentation()
{
}

KDevelop::IDocumentationProvider* PhpDocumentation::provider()
{
    return m_parent;
}

QString PhpDocumentation::description() const
{
    return QString::fromUtf8( m_description );
}

QWidget* PhpDocumentation::documentationWidget( QWidget* parent )
{
    m_part = new KHTMLPart( parent );
    connect( m_part, SIGNAL(docCreated()),
             this, SLOT(documentLoaded()) );

    m_part->openUrl( m_url );
    return m_part->widget();
}

void PhpDocumentation::documentLoaded() const
{
    if ( !m_part ) {
        return;
    }
    m_part->setUserStyleSheet( QString( "#headnav,#headsearch,#footnav,#leftbar{display:none !important;}"
                                        "body{font-size:90% !important;}"
                                        "#layout_2,#layout_3{background: none !important;}"
                                        "#content{margin:0 !important}") );
}

QString PhpDocumentation::name() const
{
    return m_name;
}

bool PhpDocumentation::providesWidget() const
{
    return true;
}

#include "phpdocumentation.moc"
