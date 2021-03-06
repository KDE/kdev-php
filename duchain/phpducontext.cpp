/*
   Copyright 2008 Niko Sams <niko.sams@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "phpducontext.h"

#include <language/duchain/topducontext.h>
#include <language/duchain/duchainregister.h>
#include <language/duchain/topducontextdata.h>

#include <language/util/includeitem.h>

#include <KIO/Global>

#include "navigation/navigationwidget.h"

namespace Php
{
using namespace KDevelop;

typedef PhpDUContext<TopDUContext> PhpTopDUContext;
REGISTER_DUCHAIN_ITEM_WITH_DATA(PhpTopDUContext, TopDUContextData);

typedef PhpDUContext<DUContext> PhpNormalDUContext;
REGISTER_DUCHAIN_ITEM_WITH_DATA(PhpNormalDUContext, DUContextData);

template<>
KDevelop::AbstractNavigationWidget* PhpDUContext<TopDUContext>::createNavigationWidget(Declaration* decl, TopDUContext* topContext, KDevelop::AbstractNavigationWidget::DisplayHints hints) const
{
    if (decl == nullptr) {
        return nullptr;
    } else if ( decl->kind() == Declaration::Import ) {
        QUrl u( decl->identifier().toString() );
        IncludeItem i;
        i.pathNumber = -1;
        i.name = u.fileName();
        i.isDirectory = false;
        i.basePath = KIO::upUrl(u);

        return new NavigationWidget( i, TopDUContextPointer(topContext), hints );
    } else {
        return new NavigationWidget(DeclarationPointer(decl), TopDUContextPointer(topContext ? topContext : this->topContext()), hints);
    }
}

template<>
KDevelop::AbstractNavigationWidget* PhpDUContext<DUContext>::createNavigationWidget(Declaration* decl, TopDUContext* topContext, KDevelop::AbstractNavigationWidget::DisplayHints hints) const
{
    if (decl == nullptr) {
        if (owner())
            return new NavigationWidget(DeclarationPointer(owner()), TopDUContextPointer(topContext ? topContext : this->topContext()), hints);
        else
            return nullptr;
    } else {
        return new NavigationWidget(DeclarationPointer(decl), TopDUContextPointer(topContext ? topContext : this->topContext()), hints);
    }
}


}

