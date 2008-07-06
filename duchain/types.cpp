/* This file is part of KDevelop
    Copyright 2002-2005 Roberto Raggi <roberto@kdevelop.org>
    Copyright 2006 Adam Treat <treat@kde.org>
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>
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

#include "types.h"

#include <duchain/classfunctiondeclaration.h>
#include <duchain/abstractfunctiondeclaration.h>
#include <duchain/indexedstring.h>
#include <duchain/typeregister.h>

using namespace KDevelop;
namespace Php {

REGISTER_TYPE(ClassType);
REGISTER_TYPE(FunctionType);
REGISTER_TYPE(IntegralType);

ClassType::ClassType() : ClassTypeBase(createData<ClassTypeData>())
{
    d_func_dynamic()->setTypeClassId<ClassType>();
}

AbstractType* ClassType::clone() const {
  return new ClassType(*this);
}

bool ClassType::equals(const AbstractType* _rhs) const
{
    if( !fastCast<const ClassType*>(_rhs))
        return false;
    const ClassType* rhs = fastCast<const ClassType*>(_rhs);

    return IdentifiedType::equals(rhs) && StructureType::equals(rhs);
}



void ClassType::accept0 (TypeVisitor *v) const
{
    v->visit (this);
    v->endVisit (this);
}


void ClassType::exchangeTypes(TypeExchanger */*e*/)
{
}

void ClassType::setClassType(ClassTypeType type)
{
    d_func_dynamic()->m_classType = type;
}

ClassTypeType ClassType::classType() const
{
    return d_func()->m_classType;
}

uint ClassType::hash() const
{
  return IdentifiedType::hash() + 19*StructureType::hash();
}

void ClassType::clear() {
    //StructureType::clear(); commented out as in c++ (why?)
    IdentifiedType::clear();
    d_func_dynamic()->m_classType = Class;
    d_func_dynamic()->m_closed = false;
}

QString ClassType::toString() const
{
  QualifiedIdentifier id = qualifiedIdentifier();
  if (!id.isEmpty())
    return id.top().toString();

  QString type;
  switch (classType()) {
    case Class:
      type = "class";
      break;
    case Interface:
      type = "interface";
      break;
  }
  return QString("<%1>").arg(type);
}




AbstractType* FunctionType::clone() const {
  return new FunctionType(*this);
}

bool FunctionType::equals(const AbstractType* _rhs) const
{
    if( !fastCast<const FunctionType*>(_rhs))
        return false;
    const FunctionType* rhs = static_cast<const FunctionType*>(_rhs);

    if( this == rhs )
        return true;
    
    //Ignore IdentifiedType here, because we do not want to respect that while comparing function-types.

    return FunctionTypeBase::equals(rhs);
}

QString FunctionType::toString() const
{
  return FunctionTypeBase::toString();
}

uint FunctionType::hash() const
{
    return FunctionTypeBase::hash();
}


IntegralType::IntegralType() : IntegralTypeBase(createData<IntegralTypeData>()) {
    d_func_dynamic()->setTypeClassId<IntegralType>();
    setName(IndexedString("<mixed>"));
}

AbstractType* IntegralType::clone() const {
    return new IntegralType(*this);
}

bool IntegralType::equals(const AbstractType* _rhs) const
{
    return IntegralTypeBase::equals(_rhs);
}

QString IntegralType::toString() const
{
    return IntegralTypeBase::toString();
}

uint IntegralType::hash() const
{
    return IntegralTypeBase::hash();
}

}

