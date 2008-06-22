/* This file is part of KDevelop
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>

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

#include "typerepository.h"

#include <QMutexLocker>

#include <kglobal.h>
#include <duchain/identifier.h>

using namespace KDevelop;
namespace Php {

TypeRepository::TypeRepository()
{
}

TypeRepository* TypeRepository::self()
{
  K_GLOBAL_STATIC(TypeRepository, s_instance)
  return s_instance;
}

AbstractType::Ptr TypeRepository::registerType(AbstractType::Ptr input)
{
  if (!input) {
    kWarning() << "Asked to register a null type." ;
    return input;
  }

  switch (input->whichType()) {
    case AbstractType::TypeAbstract:
      return input;

    case AbstractType::TypeIntegral:
      return input;

    case AbstractType::TypeFunction:
//       return registerFunction(FunctionType::Ptr::dynamicCast(input));
      return input;

    case AbstractType::TypeStructure:
      return input;

    case AbstractType::TypeArray:
//       return registerArray(ArrayType::Ptr::dynamicCast(input));
      return input;

    default:
      return input;
  }
}

}
