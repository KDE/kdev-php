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

#ifndef CONSTANTDECLARATION_H
#define CONSTANTDECLARATION_H

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>

#include "phpduchainexport.h"

namespace Php
{

class KDEVPHPDUCHAIN_EXPORT ConstantDeclarationData : public KDevelop::DeclarationData
{
public:
    ConstantDeclarationData()
        : KDevelop::DeclarationData()
    {
    }

    ConstantDeclarationData( const ConstantDeclarationData& rhs )
        : KDevelop::DeclarationData( rhs )
    {
    }

    ~ConstantDeclarationData()
    {
    }

};

/**
 * Declaration used for Php constants eg. define('foo', 0)
 */
class KDEVPHPDUCHAIN_EXPORT ConstantDeclaration : public KDevelop::Declaration
{
public:
    ConstantDeclaration(const ConstantDeclaration& rhs);
    ConstantDeclaration(const KDevelop::SimpleRange& range, KDevelop::DUContext* context);
    ConstantDeclaration(ConstantDeclarationData& data);
    ConstantDeclaration(ConstantDeclarationData& data, const KDevelop::SimpleRange&);
    virtual ~ConstantDeclaration();

    virtual uint additionalIdentity() const;
    virtual QString toString() const;

  enum {
    Identity = 80
  };
  typedef KDevelop::Declaration Base;

private:
  DUCHAIN_DECLARE_DATA(ConstantDeclaration)
};

}

#endif // CONSTANTDECLARATION_H
