/*
   Copyright 2007 David Nolden <david.nolden.kdevelop@art-master.de>
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
#include "navigationwidget.h"
#include "declarationnavigationcontext.h"
#include "includenavigationcontext.h"
#include "magicconstantnavigationcontext.h"

namespace Php
{
using namespace KDevelop;

NavigationWidget::NavigationWidget(KDevelop::DeclarationPointer declaration, KDevelop::TopDUContextPointer topContext,
                                   KDevelop::AbstractNavigationWidget::DisplayHints hints)
    : AbstractNavigationWidget()
{
    setDisplayHints(hints);

    initBrowser(400);

    //The first context is registered so it is kept alive by the shared-pointer mechanism
    auto context = NavigationContextPointer(new DeclarationNavigationContext(declaration, topContext));
    setContext(context);
}

NavigationWidget::NavigationWidget(const IncludeItem& includeItem, KDevelop::TopDUContextPointer topContext,
                                   KDevelop::AbstractNavigationWidget::DisplayHints hints)
    : AbstractNavigationWidget()
{
  setDisplayHints(hints);

  initBrowser(200);

  //The first context is registered so it is kept alive by the shared-pointer mechanism
  auto context = NavigationContextPointer(new IncludeNavigationContext(includeItem, topContext));
  setContext(context);
}

NavigationWidget::NavigationWidget(TopDUContextPointer topContext, KTextEditor::Cursor position, const QString& constant,
                                   KDevelop::AbstractNavigationWidget::DisplayHints hints)
    : AbstractNavigationWidget()
{
  setDisplayHints(hints);

  initBrowser(200);

  //The first context is registered so it is kept alive by the shared-pointer mechanism
  auto context = NavigationContextPointer(new MagicConstantNavigationContext(topContext, position, constant));
  setContext(context);
}

QString NavigationWidget::shortDescription(KDevelop::Declaration* declaration)
{
    NavigationContextPointer ctx(new DeclarationNavigationContext(DeclarationPointer(declaration), TopDUContextPointer())); ///@todo give correct top-context
    return ctx->html(true);
}

QString NavigationWidget::shortDescription(const IncludeItem& includeItem) {
  NavigationContextPointer ctx(new IncludeNavigationContext(includeItem, TopDUContextPointer())); ///@todo give correct top-context
  return ctx->html(true);
}

}

