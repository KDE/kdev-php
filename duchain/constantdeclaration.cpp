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

#include "constantdeclaration.h"

#include <language/duchain/ducontext.h>
#include <language/duchain/duchainregister.h>

using namespace KDevelop;
namespace Php {
REGISTER_DUCHAIN_ITEM(ConstantDeclaration);

ConstantDeclaration::ConstantDeclaration(ConstantDeclarationData& data) : KDevelop::Declaration(data) {
}

ConstantDeclaration::ConstantDeclaration(ConstantDeclarationData& data, const KDevelop::SimpleRange& range)
    : KDevelop::Declaration(data, range) {
}

ConstantDeclaration::ConstantDeclaration(const ConstantDeclaration& rhs)
    : KDevelop::Declaration(*new ConstantDeclarationData( *rhs.d_func() )) {
  setSmartRange(rhs.smartRange(), DocumentRangeObject::DontOwn);
}

ConstantDeclaration::ConstantDeclaration(const KDevelop::SimpleRange& range, KDevelop::DUContext* context)
  : KDevelop::Declaration(*new ConstantDeclarationData, range)
{
  d_func_dynamic()->setClassId(this);
  if( context )
    setContext( context );
}
ConstantDeclaration::~ConstantDeclaration()
{
}

uint ConstantDeclaration::additionalIdentity() const
{
    return 1;
}

QString ConstantDeclaration::toString() const
{
    return "const " + KDevelop::Declaration::toString();
}

}
