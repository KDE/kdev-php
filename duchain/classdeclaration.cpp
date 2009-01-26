/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/


#include "classdeclaration.h"

#include <language/duchain/ducontext.h>
#include <language/duchain/duchainregister.h>

using namespace KDevelop;
namespace Php {
REGISTER_DUCHAIN_ITEM(ClassDeclaration);

DEFINE_LIST_MEMBER_HASH(ClassDeclarationData, baseClasses, BaseClassInstance)
DEFINE_LIST_MEMBER_HASH(ClassDeclarationData, interfaces, BaseClassInstance)

ClassDeclaration::ClassDeclaration(ClassDeclarationData& data) : KDevelop::Declaration(data) {
}

ClassDeclaration::ClassDeclaration(const ClassDeclaration& rhs)
    : KDevelop::Declaration(*new ClassDeclarationData( *rhs.d_func() )) {
  setSmartRange(rhs.smartRange(), DocumentRangeObject::DontOwn);
}

ClassDeclaration::ClassDeclaration(const KDevelop::SimpleRange& range, KDevelop::DUContext* context)
  : KDevelop::Declaration(*new ClassDeclarationData, range)
{
  d_func_dynamic()->setClassId(this);
  if( context )
    setContext( context );
}

KDevelop::Declaration* ClassDeclaration::clonePrivate() const
{
  return new ClassDeclaration(*this);
}

ClassDeclaration::~ClassDeclaration()
{
}

QString ClassDeclaration::toString() const 
{
    QString ret;
    switch (d_func()->m_classType) {
        case ClassDeclarationData::Class:
            ret = "class";
            break;
        case ClassDeclarationData::Interface:
            ret = "interface";
            break;
    }
    ret += " " + identifier().toString();
    return ret;
}

ClassDeclarationData::ClassType ClassDeclaration::classType() const
{
    return d_func()->m_classType;
}

void ClassDeclaration::setClassType(ClassDeclarationData::ClassType type) 
{
    d_func_dynamic()->m_classType = type;
}

void ClassDeclaration::clearBaseClasses() {
  d_func_dynamic()->baseClassesList().clear();
}

uint ClassDeclaration::baseClassesSize() const {
  return d_func()->baseClassesSize();
}

const BaseClassInstance* ClassDeclaration::baseClasses() const {
  return d_func()->baseClasses();
}

void ClassDeclaration::setBaseClass(BaseClassInstance base) {
  ///TODO: make sure only one base class is set per ClassDeclaration
  ///      inheritance makes a list of baseClasses possible though.
  ///TODO: prevent recursion
  d_func_dynamic()->baseClassesList().append(base);
}

bool ClassDeclaration::inherits(const IndexedType& type) const {
  if ( baseClassesSize() > 0 ) {
    FOREACH_FUNCTION( const Php::BaseClassInstance& base, baseClasses ) {
      if ( base.baseClass == type ) {
        return true;
      }
    }
  }
  return false;
}


void ClassDeclaration::clearInterfaces() {
  d_func_dynamic()->interfacesList().clear();
}

uint ClassDeclaration::interfacesSize() const {
  return d_func()->interfacesSize();
}

const BaseClassInstance* ClassDeclaration::interfaces() const {
  return d_func()->interfaces();
}

void ClassDeclaration::addInterface(BaseClassInstance interface) {
  ///TODO: prevent recursion
  d_func_dynamic()->interfacesList().append(interface);
}

bool ClassDeclaration::implements(const IndexedType& type) const {
  kDebug() << type.type()->toString();
  if ( interfacesSize() > 0 ) {
    FOREACH_FUNCTION( const Php::BaseClassInstance& base, interfaces ) {
      kDebug() << base.baseClass.type()->toString();
      if ( base.baseClass == type ) {
        return true;
      }
    }
  }
  return false;
}
}
