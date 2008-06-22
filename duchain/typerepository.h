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

#ifndef TYPEREPOSITORY_H
#define TYPEREPOSITORY_H

#include <QtCore/QSet>
#include <QtCore/QMultiHash>
#include <QtCore/QMutex>

#include <language/duchain/repositories/ityperepository.h>
#include "types.h"

namespace KDevelop {
  class QualifiedIdentifier;
}

namespace Php {

class TypeRepository : public KDevelop::ITypeRepository
{
public:
  static TypeRepository* self();

  ///@todo The type-repository holds shared-pointers to types, and may keep AbstractType's alive that come from already deleted du-chains. AbstractType's with no declarations should be cleaned away on a regular basis.

  /**
   * Registers the given \a input type, and returns a pointer to the
   * type, or the previously registered type if it has been encountered
   * before.
   */
  KDevelop::AbstractType::Ptr registerType(KDevelop::AbstractType::Ptr input);

private:
  TypeRepository();

  mutable QMutex m_mutex;
};

}

#endif // TYPEREPOSITORY_H
