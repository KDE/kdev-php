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
    m_integral = new IntegralType();
}

TypeRepository* TypeRepository::self()
{
  K_GLOBAL_STATIC(TypeRepository, s_instance)
  return s_instance;
}

IntegralType::Ptr TypeRepository::integral() const
{
    return m_integral;
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
      return registerFunction(FunctionType::Ptr::dynamicCast(input));

    case AbstractType::TypeStructure:
      return input;

    case AbstractType::TypeArray:
//       return registerArray(ArrayType::Ptr::dynamicCast(input));
      return input;

    default:
      return input;
  }
}

int hashFromFunction(FunctionType* function) {
  int ret = 1;
  const int numElements = function->arguments().count();
  for (int i = 0; i < numElements; ++i)
    ret = (int)((size_t)function->arguments()[i].data()) + ret*13;
  ret = (int)((size_t)function) + ret * 37;
  ret = (int)((size_t)function->modifiers()) + ret * 17;
  return ret;
}

AbstractType::Ptr TypeRepository::registerFunction(FunctionType::Ptr input)
{
  QMutexLocker lock(&m_mutex);

  Q_ASSERT(input);

  AbstractType* returnType = input->returnType().data();
  const int numElements = input->arguments().count();
  if (!returnType)
    // Invalid
    return AbstractType::Ptr::staticCast(input);

  foreach (const AbstractType::Ptr& argument, input->arguments())
    if (!argument)
      // Invalid
      return AbstractType::Ptr::staticCast(input);

  int hash = hashFromFunction(input.data());

  TypeModifiers mod = input->modifiers();

  QMultiHash<int, FunctionType::Ptr>::ConstIterator it = m_functions.constFind(hash);
  if (it != m_functions.constEnd()) {
    for (; it.key() == hash; ++it) {
      if(numElements != (*it)->arguments().count())
        continue;
      if (it.value()->modifiers() == mod) {
        if (it.value()->returnType() != returnType)
          goto nomatch;

        for (int i = 0; i < numElements; ++i)
          if (it.value()->arguments()[i] != input->arguments()[i])
            goto nomatch;

        // Match
        return AbstractType::Ptr::staticCast(it.value());
      }
      nomatch:
      continue;
    }
  }

  // No match
  m_functions.insert(hash, input);
  return AbstractType::Ptr::staticCast(input);
}
}
