/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Milian Wolff <mail@milianw.de>                         *
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

#include "classmethoddeclaration.h"

using namespace KDevelop;

namespace Php {

bool ClassMethodDeclaration::isConstructor() const {
  Identifier id = identifier();
  return id.nameEquals(Identifier("__construct"))
      || id.nameEquals(context()->indexedLocalScopeIdentifier().identifier().first());
}

bool ClassMethodDeclaration::isDestructor() const {
  //TODO: register_shutdown_function
  return identifier().nameEquals(Identifier("__destruct"));
}

Declaration* ClassMethodDeclaration::clonePrivate() const {
  return new ClassMethodDeclaration(*this);
}


}
