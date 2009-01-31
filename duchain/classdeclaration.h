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

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>

#include "phpduchainexport.h"
#include "phpast.h"

#ifndef CLASSDECLARATION_H
#define CLASSDECLARATION_H
namespace Php {

class ClassDeclaration;

DECLARE_LIST_MEMBER_HASH(ClassDeclarationData, interfaces, KDevelop::IndexedType)

class ClassDeclarationData : public KDevelop::DeclarationData
{
public:
  enum ClassType {
    Class,
    Interface
  };
  
  ClassDeclarationData() : m_classType(Class), m_classModifier(NormalClass) {
    initializeAppendedLists();
  }

  ~ClassDeclarationData() {
    freeAppendedLists();
  }

  ClassDeclarationData(const ClassDeclarationData& rhs) : KDevelop::DeclarationData(rhs) {
    initializeAppendedLists();
    copyListsFrom(rhs);
    m_classType = rhs.m_classType;
    m_classModifier = rhs.m_classModifier;
  }
  
  /// Type of the class (class, interface)
  ClassType m_classType;
  KDevelop::IndexedType m_baseClass;

  /// Wether this class is declared final or abstract or non of all
  ClassModifier m_classModifier;
  
  START_APPENDED_LISTS_BASE(ClassDeclarationData, KDevelop::DeclarationData);
  APPENDED_LIST_FIRST(ClassDeclarationData, KDevelop::IndexedType, interfaces);
  END_APPENDED_LISTS(ClassDeclarationData, interfaces);
};

class KDEVPHPDUCHAIN_EXPORT ClassDeclaration : public KDevelop::Declaration
{
public:
  
  ClassDeclaration(const ClassDeclaration& rhs);
  ClassDeclaration(ClassDeclarationData& data);
  ClassDeclaration(const KDevelop::SimpleRange& range, KDevelop::DUContext* context);
  ~ClassDeclaration();

  QString toString() const;

  void setClassType(ClassDeclarationData::ClassType type);
  ClassDeclarationData::ClassType classType() const;
  
  void setClassModifier(ClassModifier modifier);
  ClassModifier classModifier() const;
  
  ///The types this class is based on
  const KDevelop::IndexedType baseClass() const;
  void setBaseClass(const KDevelop::IndexedType& base);
  
  /**
   * Returns true if the class extends the class given in \p type.
   * Does not work like Php instanceof operator that works with interfaces too.
   * \TODO probably merge with implements
   */
  bool inherits(const KDevelop::IndexedType& type) const;
  
  void clearInterfaces();
  ///Count of base-classes
  uint interfacesSize() const;
  ///The types this class is based on
  const KDevelop::IndexedType* interfaces() const;
  void addInterface(const KDevelop::IndexedType& interface);
  
  /**
   * Returns true if the class implements the interface given in \p type.
   * Does not work like Php instanceof operator that works with base classes too.
   * \TODO probably merge with inherits
   */
  bool implements(const KDevelop::IndexedType& type) const;
  
  enum {
    Identity = 81
  };

private:
  virtual KDevelop::Declaration* clonePrivate() const;
  DUCHAIN_DECLARE_DATA(ClassDeclaration)
};

}
#endif // CLASSDECLARATION_H
