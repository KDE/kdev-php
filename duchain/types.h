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

#ifndef PHP_TYPES_H
#define PHP_TYPES_H

#include <duchain/identifier.h>
#include <duchain/typesystem.h>
#include <duchain/declaration.h>
#include <duchain/identifiedtype.h>

namespace Php {

enum TypeModifiers {
    NoModifier           = 0,
    PrivateModifier      = 1,
    PublicModifier       = 1 << 1,
    ProtectedModifier    = 1 << 2,
    StaticModifier       = 1 << 3,
    FinalModifier        = 1 << 4,
    AbstractModifier     = 1 << 5,
};

class ModifierType
{
    friend class TypeRepository;
    friend class TypeBuilder;

public:
    ModifierType(TypeModifiers modifiers = NoModifier);

    TypeModifiers modifiers() const;

    void clear();

    bool equals(const ModifierType* rhs) const;

    QString toString() const;
//     QString modMangled() const;
    uint modHash(uint input) const { return input; }

private:
    TypeModifiers m_mod;
};

class ClassType : public KDevelop::StructureType, public KDevelop::IdentifiedType/*, public JavaType*/
{
public:
  typedef KSharedPtr<ClassType> Ptr;

  ClassType();

  const QList<ClassType::Ptr>& extendsClasses() const;
  void addExtendsClass(const ClassType::Ptr& baseClass);
  void clearExtendsClasses();

  const QList<ClassType::Ptr>& implementsInterfaces() const;
  void addImplementsInterface(const ClassType::Ptr& baseClass);
  void clearImplementsInterfaces();

  enum Type
  {
    Class,
    Interface
  };

  void setClassType(Type type);
  Type classType() const;

  /// Java classes are closed types, once they are defined, they can't be changed.
  bool isClosed() const { return m_closed; }
  void close() { m_closed = true; }

  ///After clearing, a class-type is open again.
  void clear();

  /// Error if the type is closed.
  virtual void addElement(KDevelop::AbstractType::Ptr element);

  virtual uint hash() const;

  virtual QString toString() const;

  virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual void accept0 (KDevelop::TypeVisitor *v) const;

  virtual void exchangeTypes(KDevelop::TypeExchanger*);

private:
  QList<ClassType::Ptr> m_extendsClasses, m_implementsInterfaces;
  Type m_classType;
  bool m_closed;
};

class FunctionType : public KDevelop::FunctionType, public KDevelop::IdentifiedType, public ModifierType
{
public:
  typedef KSharedPtr<FunctionType> Ptr;

  FunctionType(TypeModifiers modifiers = NoModifier);

  ///Declarations of this class(@see KDevelop::IdentifiedType::declaration()) are guaranteed to be based on AbstractFunctionDeclaration

  virtual QString toString() const;

  virtual uint hash() const;

//   virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;
};

}

#endif
