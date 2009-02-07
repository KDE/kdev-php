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
#include <language/duchain/types/structuretype.h>

using namespace KDevelop;
namespace Php {
REGISTER_DUCHAIN_ITEM(ClassDeclaration);

DEFINE_LIST_MEMBER_HASH(ClassDeclarationData, interfaces, KDevelop::IndexedType)

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
    
    switch (d_func()->m_classModifier) {
      case Php::AbstractClass:
          ret += "abstract ";
          break;
      case Php::FinalClass:
          ret += "final ";
          break;
      default:
          break;
    }
    
    switch (d_func()->m_classType) {
        case ClassDeclarationData::Class:
            ret += "class";
            break;
        case ClassDeclarationData::Interface:
            ret += "interface";
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

ClassModifier ClassDeclaration::classModifier() const
{
    return d_func()->m_classModifier;
}

void ClassDeclaration::setClassModifier(ClassModifier modifier) 
{
    d_func_dynamic()->m_classModifier = modifier;
}

const KDevelop::IndexedType ClassDeclaration::baseClass() const
{
   return d_func()->m_baseClass;
}

void ClassDeclaration::setBaseClass(const KDevelop::IndexedType& base)
{
    d_func_dynamic()->m_baseClass = base;
}

bool ClassDeclaration::inherits(const IndexedType& type) const {
  if( indexedType() == type )
    return true;

  if ( baseClass() == type ) {
    return true;
  }
  if( StructureType::Ptr c = baseClass().type().cast<StructureType>() ) {
    ClassDeclaration* decl = dynamic_cast<ClassDeclaration*>(c->declaration(topContext()));
    if( decl && decl->inherits( type ) ) {
      return true;
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

const KDevelop::IndexedType* ClassDeclaration::interfaces() const {
  return d_func()->interfaces();
}

void ClassDeclaration::addInterface(const KDevelop::IndexedType& interface) {
  ///TODO: prevent recursion
  d_func_dynamic()->interfacesList().append(interface);
}

bool ClassDeclaration::implements(const IndexedType& type) const {
  FOREACH_FUNCTION(const KDevelop::IndexedType& b, interfaces)
  {
    if ( b == type ) {
      return true;
    }
    if( StructureType::Ptr c = b.type().cast<StructureType>() ) {
      ClassDeclaration* decl = dynamic_cast<ClassDeclaration*>(c->declaration(topContext()));
      if( decl && decl->implements( type ) ) {
        return true;
      }
    }
  }
  return false;
}
}
