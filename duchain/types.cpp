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

using namespace KDevelop;
namespace Php {


bool ModifierType::equals(const ModifierType* rhs) const {
  return m_mod == rhs->m_mod;
}
void ModifierType::clear() {
  m_mod = NoModifier;
}

ModifierType::ModifierType(TypeModifiers modifiers)
  : m_mod(modifiers)
{
}
QString ModifierType::toString() const
{
    QStringList mods;
    if (m_mod & PrivateModifier)   mods << "private";
    if (m_mod & PublicModifier)    mods << "public";
    if (m_mod & ProtectedModifier) mods << "protected";
    if (m_mod & StaticModifier)    mods << "static";
    if (m_mod & FinalModifier)     mods << "final";
    if (m_mod & AbstractModifier)  mods << "abstract";
    return mods.join(" ");
}

TypeModifiers ModifierType::modifiers() const
{
  return m_mod;
}




ClassType::ClassType()
  : m_classType(Class)
  , m_closed(false)
{
}

AbstractType* ClassType::clone() const {
  return new ClassType(*this);
}

bool ClassType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const ClassType*>(_rhs))
    return false;
  const IdentifiedType* rhs = fastCast<const IdentifiedType*>(_rhs);

  Declaration* decl = declaration();
  Declaration* rhsDecl = rhs->declaration();

  if(!decl || !rhsDecl)
    return false;

  ///We cannot use here IdentifiedType::equals, because else we get problems with forward declarations
  return decl->equalQualifiedIdentifier(rhsDecl);
}


void ClassType::accept0 (TypeVisitor *v) const
{
  if (v->visit (this))
    {
      foreach(const ClassType::Ptr& base, m_extendsClasses)
        acceptType (AbstractType::Ptr::staticCast(base), v);
      foreach(const ClassType::Ptr& base, m_implementsInterfaces)
        acceptType (AbstractType::Ptr::staticCast(base), v);
    }

  v->endVisit (this);
}


void ClassType::exchangeTypes(TypeExchanger *e)
{
  // TODO understand better...
  foreach (ClassType::Ptr base, m_extendsClasses)
    base = ClassType::Ptr::dynamicCast(AbstractType::Ptr(e->exchange(base.data())));
  foreach (ClassType::Ptr base, m_implementsInterfaces)
    base = ClassType::Ptr::dynamicCast(AbstractType::Ptr(e->exchange(base.data())));
}

// ---------------------------------------------------------------------------
const QList<ClassType::Ptr>& ClassType::extendsClasses() const
{
  return m_extendsClasses;
}

void ClassType::addExtendsClass(const ClassType::Ptr& extendsClass)
{
  m_extendsClasses.append(extendsClass);
}

void ClassType::clearExtendsClasses()
{
  m_extendsClasses.clear();
}

const QList< ClassType::Ptr > & ClassType::implementsInterfaces() const
{
  return m_implementsInterfaces;
}

void ClassType::addImplementsInterface(const ClassType::Ptr & interface)
{
  Q_ASSERT(interface->classType() == Interface);
  m_implementsInterfaces.append(interface);
}

void ClassType::clearImplementsInterfaces()
{
  m_implementsInterfaces.clear();
}


void ClassType::setClassType(ClassType::Type type)
{
  m_classType = type;
}

ClassType::Type ClassType::classType() const
{
  return m_classType;
}

uint ClassType::hash() const
{
  return identifier().hash();
}

void ClassType::clear() {
  StructureType::clear();
  IdentifiedType::clear();
  m_extendsClasses.clear();
  m_implementsInterfaces.clear();
  m_classType = Class;
  m_closed = false;
}

QString ClassType::toString() const
{
  QualifiedIdentifier id = identifier();
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



FunctionType::FunctionType(TypeModifiers modifiers)
  : ModifierType(modifiers)
{
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

  return ModifierType::equals(rhs) && FunctionType::equals(rhs);
}

QString FunctionType::toString() const
{
  return QString("%1 %2").arg(KDevelop::FunctionType::toString()).arg(ModifierType::toString());
}

uint FunctionType::hash() const
{
    return modHash(KDevelop::FunctionType::hash()) + 31 * identifier().hash();
}


IntegralType::IntegralType()
{
  setName(IndexedString("<mixed>"));
}

AbstractType* IntegralType::clone() const {
  return new IntegralType(*this);
}

bool IntegralType::equals(const AbstractType* _rhs) const
{
  return KDevelop::IntegralType::equals(_rhs);
}

QString IntegralType::toString() const
{
  return KDevelop::IntegralType::toString();
}

uint IntegralType::hash() const
{
  return KDevelop::IntegralType::hash();
}

}

