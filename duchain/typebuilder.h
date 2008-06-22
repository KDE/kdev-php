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

#ifndef TYPEBUILDER_H
#define TYPEBUILDER_H

#include "contextbuilder.h"

#include <language/duchain/abstracttypebuilder.h>

#include <language/duchain/typesystem.h>
#include <language/duchain/declaration.h>
#include <language/duchain/identifier.h>
#include "types.h"
#include "typerepository.h"

namespace Php {

class ClassType;
class FunctionType;

typedef KDevelop::AbstractTypeBuilder<AstNode, IdentifierAst, ContextBuilder> TypeBuilderBase;

/**
 * Create types from an AstNode tree.
 *
 * \note This builder overrides visitDeclarator, in order to support
 * array types; parent classes will not have
 * their visitDeclarator function called.
 */
class KDEVPHPDUCHAIN_EXPORT TypeBuilder: public TypeBuilderBase
{
protected:
  virtual TypeRepository* typeRepository() const;

  void visitClassDeclarationStatement( ClassDeclarationStatementAst* node );
  void visitClassStatement(ClassStatementAst *node);

private:
  bool nodeValid(AstNode* node) const;

  ClassType* openClass(bool interface);

  TypeModifiers parseModifiers(OptionalModifiersAst* node) const;
};

}

#endif // TYPEBUILDER_H

