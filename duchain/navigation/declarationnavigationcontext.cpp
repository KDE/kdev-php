/*
    SPDX-FileCopyrightText: 2007 David Nolden <david.nolden.kdevelop@art-master.de>
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "declarationnavigationcontext.h"

#include <QTextDocument>

#include <klocalizedstring.h>

#include <language/duchain/functiondefinition.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/forwarddeclaration.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/arraytype.h>

#include "../declarations/classdeclaration.h"
#include <declarations/classmethoddeclaration.h>
#include <declarations/traitmethodaliasdeclaration.h>
#include <declarations/traitmemberaliasdeclaration.h>
#include <declarations/variabledeclaration.h>
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
    return AbstractDeclarationNavigationContext::registerChild(new DeclarationNavigationContext(declaration, topContext(), this));
}

void DeclarationNavigationContext::htmlClass()
{
    StructureType::Ptr klass = declaration()->abstractType().cast<StructureType>();
    Q_ASSERT(klass);
    ClassDeclaration* classDecl = dynamic_cast<ClassDeclaration*>(klass->declaration(topContext().data()));
    if (classDecl) {
        // write class modifier
        switch (classDecl->classModifier()) {
        case ClassDeclarationData::Abstract:
            modifyHtml() += QStringLiteral("abstract ");
            break;
        case ClassDeclarationData::Final:
            modifyHtml() += QStringLiteral("final ");
            break;
        default:
            //nothing
            break;
        }
        // write class type
        if (classDecl->classType() == ClassDeclarationData::Interface) {
            modifyHtml() += QStringLiteral("interface ");
        } else if (classDecl->classType() == ClassDeclarationData::Trait) {
            modifyHtml() += QStringLiteral("trait ");
        } else {
            modifyHtml() += QStringLiteral("class ");
        }
        // write class identifier
        eventuallyMakeTypeLinks(declaration()->abstractType());
        // write inheritance
        if (classDecl->baseClassesSize() > 0) {
            AbstractType::Ptr extends;
            QList<AbstractType::Ptr> implements;
            FOREACH_FUNCTION(const BaseClassInstance& base, classDecl->baseClasses) {
                StructureType::Ptr stype = base.baseClass.type<StructureType>();
                if (stype) {
                    ClassDeclaration *classDecl = dynamic_cast<ClassDeclaration*>(stype->declaration(topContext().data()));
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
                modifyHtml() += QStringLiteral(" extends ");
                eventuallyMakeTypeLinks(extends);
            }
            // write implemented interfaces
            if (!implements.isEmpty()) {
                modifyHtml() += QStringLiteral(" implements ");
                for (QList<AbstractType::Ptr>::iterator i = implements.begin(); ;) {
                    eventuallyMakeTypeLinks(*i);
                    ++i;
                    if (i != implements.end()) {
                        modifyHtml() += QStringLiteral(", ");
                    } else {
                        break;
                    }
                }
            }
        }
        modifyHtml() += QStringLiteral(" ");
    }
}

void DeclarationNavigationContext::htmlAdditionalNavigation()
{
    if (auto member = dynamic_cast<TraitMethodAliasDeclaration*>(declaration().data())) {
        Declaration *dec = member->aliasedDeclaration().data();
        if (dec && dec->context() && dec->context()->owner()) {
            modifyHtml() += i18n("Use of %1 from %2<br />")
                            .arg(createLink(prettyQualifiedIdentifier(DeclarationPointer(dec)).toString(),
                                            QStringLiteral("jump_to_used"),
                                            NavigationAction(DeclarationPointer(dec),
                                                             KDevelop::NavigationAction::NavigateDeclaration)))
                            .arg(createLink(prettyQualifiedIdentifier(DeclarationPointer(dec->context()->owner())).toString(),
                                            QStringLiteral("jump_to_used_container"),
                                            NavigationAction(DeclarationPointer(dec->context()->owner()),
                                                             KDevelop::NavigationAction::NavigateDeclaration)));
        }
    } else if (auto member = dynamic_cast<TraitMemberAliasDeclaration*>(declaration().data())) {
        Declaration *dec = member->aliasedDeclaration().data();
        if (dec && dec->context() && dec->context()->owner()) {
            modifyHtml() += i18n("Use of %1 from %2<br />")
                            .arg(createLink(prettyQualifiedIdentifier(DeclarationPointer(dec)).toString(),
                                            QStringLiteral("jump_to_used"),
                                            NavigationAction(DeclarationPointer(dec),
                                                             KDevelop::NavigationAction::NavigateDeclaration)))
                            .arg(createLink(prettyQualifiedIdentifier(DeclarationPointer(dec->context()->owner())).toString(),
                                            QStringLiteral("jump_to_used_container"),
                                            NavigationAction(DeclarationPointer(dec->context()->owner()),
                                                             KDevelop::NavigationAction::NavigateDeclaration)));
        } else {
            modifyHtml() += i18n("Broken member alias trait.");
        }
    }

    KDevelop::AbstractDeclarationNavigationContext::htmlAdditionalNavigation();
}

void DeclarationNavigationContext::htmlFunction()
{
  const AbstractFunctionDeclaration* function = dynamic_cast<const AbstractFunctionDeclaration*>(declaration().data());
  Q_ASSERT(function);

  const ClassFunctionDeclaration* classFunDecl = dynamic_cast<const ClassFunctionDeclaration*>(declaration().data());
  const FunctionType::Ptr type = declaration()->abstractType().cast<FunctionType>();
  if( !type ) {
    modifyHtml() += errorHighlight(QStringLiteral("Invalid type<br />"));
    return;
  }

  if( !classFunDecl || (!classFunDecl->isConstructor() && !classFunDecl->isDestructor()) ) {
    // only print return type for global functions and non-ctor/dtor methods
    eventuallyMakeTypeLinks( type->returnType() );
  }

  modifyHtml() += ' ' + identifierHighlight(prettyIdentifier(declaration()).toString().toHtmlEscaped(), declaration());

  if( type->indexedArgumentsSize() == 0 )
  {
    modifyHtml() += QStringLiteral("()");
  } else {
    modifyHtml() += QStringLiteral("( ");

    bool first = true;
    int firstDefaultParam = type->indexedArgumentsSize() - function->defaultParametersSize();
    int currentArgNum = 0;

    QVector<Declaration*> decls;
    if (DUContext* argumentContext = DUChainUtils::argumentContext(declaration().data())) {
      decls = argumentContext->localDeclarations(topContext().data());
    }
    foreach(const AbstractType::Ptr& argType, type->arguments()) {
      if( !first )
        modifyHtml() += QStringLiteral(", ");
      first = false;

      VariableDeclaration *argDec = nullptr;

      if (!decls.isEmpty()) {
        argDec = dynamic_cast<VariableDeclaration*>(decls[currentArgNum]);
      }

      if (argDec && argDec->isVariadic()) {
        AbstractType::Ptr variadicType;
        const auto a_type = argType.cast<KDevelop::ArrayType>();
        if (a_type) {
            variadicType = a_type->elementType();
        } else {
            variadicType = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
        }
        modifyHtml() += QStringLiteral("[");
        eventuallyMakeTypeLinks( variadicType );
        if (currentArgNum < decls.size()) {
          modifyHtml() += QStringLiteral(" ...") + identifierHighlight(decls[currentArgNum]->identifier().toString().toHtmlEscaped(), declaration());
        }
        modifyHtml() += QStringLiteral("]");
      } else {
        eventuallyMakeTypeLinks( argType );
        if (currentArgNum < decls.size()) {
          modifyHtml() += ' ' + identifierHighlight(decls[currentArgNum]->identifier().toString().toHtmlEscaped(), declaration());
        }

        if (currentArgNum >= firstDefaultParam) {
          IndexedString defaultStr = function->defaultParameters()[currentArgNum - firstDefaultParam];
          if (!defaultStr.isEmpty()) {
            modifyHtml() += " = " + defaultStr.str().toHtmlEscaped();
          }
        }
      }

      ++currentArgNum;
    }

    modifyHtml() += QStringLiteral(" )");
  }
  modifyHtml() += QStringLiteral("<br />");
}

QualifiedIdentifier DeclarationNavigationContext::prettyQualifiedIdentifier(const DeclarationPointer& decl) const
{
    return QualifiedIdentifier(prettyName(decl.data()));
}

void DeclarationNavigationContext::makeLink(const QString& name, const DeclarationPointer& declaration, NavigationAction::Type actionType)
{
    if ( actionType == NavigationAction::JumpToSource && declaration->url() == internalFunctionFile() ) {
        modifyHtml() += i18n("PHP internal");
        return;
    }
    AbstractDeclarationNavigationContext::makeLink(name, declaration, actionType);
}

QString DeclarationNavigationContext::declarationKind(const DeclarationPointer& decl)
{
    if ( decl->kind() == Declaration::Instance && decl->abstractType()
         && decl->abstractType()->modifiers() & AbstractType::ConstModifier ) {
        return i18nc("kind of a php-constant, as shown in the declaration tooltip", "Constant");
    }
    return AbstractDeclarationNavigationContext::declarationKind(decl);
}

}
