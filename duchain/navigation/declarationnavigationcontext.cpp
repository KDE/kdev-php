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

#include "declarationnavigationcontext.h"
#include "classdeclaration.h"

#include <QtGui/QTextDocument>

#include <klocale.h>
#include <klocalizedstring.h>

#include <language/duchain/functiondefinition.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/forwarddeclaration.h>
#include <language/duchain/duchainutils.h>

namespace Php {
using namespace KDevelop;

DeclarationNavigationContext::DeclarationNavigationContext( DeclarationPointer decl, KDevelop::TopDUContextPointer topContext, AbstractNavigationContext* previousContext)
  : AbstractDeclarationNavigationContext( decl, topContext, previousContext )
{
}

NavigationContextPointer DeclarationNavigationContext::registerChild(DeclarationPointer declaration)
{
  return AbstractDeclarationNavigationContext::registerChild(new DeclarationNavigationContext(declaration, m_topContext, this));
}

void DeclarationNavigationContext::htmlClass()
{
  AbstractDeclarationNavigationContext::htmlClass();

  StructureType::Ptr klass = m_declaration->abstractType().cast<StructureType>();
  Q_ASSERT(klass);
  ClassDeclaration* classDecl = dynamic_cast<ClassDeclaration*>(klass->declaration(m_topContext.data()));
  if(classDecl) {
    if ( classDecl->baseClassesSize() > 0 ) {
      modifyHtml() += i18n(" inherits ");
      FOREACH_FUNCTION( const Php::BaseClassInstance& base, classDecl->baseClasses ) {
        eventuallyMakeTypeLinks(base.baseClass.type());
        if ( a < containerSize - 1 ) {
          modifyHtml() += ", ";
        }
      }
    }
    modifyHtml() += " ";
    if ( classDecl->interfacesSize() > 0 ) {
      modifyHtml() += i18n(" interfaces ");
      FOREACH_FUNCTION( const Php::BaseClassInstance& interface, classDecl->interfaces ) {
        eventuallyMakeTypeLinks(interface.baseClass.type());
        if ( a < containerSize - 1 ) {
          modifyHtml() += ", ";
        }
      }
    }
    modifyHtml() += " ";
  }
}

}
