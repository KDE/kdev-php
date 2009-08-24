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

#include <QtGui/QTextDocument>

#include <klocale.h>
#include <klocalizedstring.h>

#include <language/duchain/functiondefinition.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/forwarddeclaration.h>
#include <language/duchain/duchainutils.h>

#include "classdeclaration.h"
#include "helper.h"

namespace Php
{
using namespace KDevelop;

DeclarationNavigationContext::DeclarationNavigationContext(DeclarationPointer decl, KDevelop::TopDUContextPointer topContext, AbstractNavigationContext* previousContext)
        : AbstractDeclarationNavigationContext(decl, topContext, previousContext)
{
}

NavigationContextPointer DeclarationNavigationContext::registerChild(DeclarationPointer declaration)
{
    return AbstractDeclarationNavigationContext::registerChild(new DeclarationNavigationContext(declaration, m_topContext, this));
}

void DeclarationNavigationContext::htmlClass()
{
    StructureType::Ptr klass = m_declaration->abstractType().cast<StructureType>();
    Q_ASSERT(klass);
    ClassDeclaration* classDecl = dynamic_cast<ClassDeclaration*>(klass->declaration(m_topContext.data()));
    if (classDecl) {
        // write class modifier
        switch (classDecl->classModifier()) {
        case ClassDeclarationData::Abstract:
            modifyHtml() += "abstract ";
            break;
        case ClassDeclarationData::Final:
            modifyHtml() += "final ";
            break;
        default:
            //nothing
            break;
        }
        // write class type
        if (classDecl->classType() == ClassDeclarationData::Interface) {
            modifyHtml() += "interface ";
        } else {
            modifyHtml() += "class ";
        }
        // write class identifier
        eventuallyMakeTypeLinks(m_declaration->abstractType());
        // write inheritance
        if (classDecl->baseClassesSize() > 0) {
            AbstractType::Ptr extends;
            QList<AbstractType::Ptr> implements;
            FOREACH_FUNCTION(const BaseClassInstance& base, classDecl->baseClasses) {
                StructureType::Ptr stype = base.baseClass.type<StructureType>();
                if (stype) {
                    ClassDeclaration *classDecl = dynamic_cast<ClassDeclaration*>(stype->declaration(m_topContext.data()));
                    if (classDecl) {
                        if (classDecl->classType() == ClassDeclarationData::Interface) {
                            implements.append(base.baseClass.abstractType());
                        } else {
                            extends = base.baseClass.abstractType();
                        }
                    }
                }
            }
            // write parent class
            if (extends) {
                modifyHtml() += " extends ";
                eventuallyMakeTypeLinks(extends);
            }
            // write implemented interfaces
            if (!implements.isEmpty()) {
                modifyHtml() += " implements ";
                for (QList<AbstractType::Ptr>::iterator i = implements.begin(); ;) {
                    eventuallyMakeTypeLinks(*i);
                    ++i;
                    if (i != implements.end()) {
                        modifyHtml() += ", ";
                    } else {
                        break;
                    }
                }
            }
        }
        modifyHtml() += " ";
    }
}

QualifiedIdentifier DeclarationNavigationContext::prettyQualifiedIdentifier( DeclarationPointer decl ) const
{
    return QualifiedIdentifier(prettyName(decl.data()));
}

}
