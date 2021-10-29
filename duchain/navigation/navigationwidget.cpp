/*
    SPDX-FileCopyrightText: 2007 David Nolden <david.nolden.kdevelop@art-master.de>
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
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

