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

#ifndef CLASSDECLARATION_H
#define CLASSDECLARATION_H
namespace Php {

class ClassDeclarationData : public KDevelop::DeclarationData
{
public:
  enum ClassType {
    Class,
    Interface
  };
  
  ClassDeclarationData() : m_classType(Class) {
  }

  ~ClassDeclarationData() {
  }

  ClassDeclarationData(const ClassDeclarationData& rhs) : KDevelop::DeclarationData(rhs) {
    m_classType = rhs.m_classType;
  }
  
  /// Type of the class (class, interface)
  ClassType m_classType;
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
  
  enum {
    Identity = 81
  };

private:
  virtual KDevelop::Declaration* clonePrivate() const;
  DUCHAIN_DECLARE_DATA(ClassDeclaration)
};

}
#endif // CLASSDECLARATION_H
