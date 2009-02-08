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

#ifndef DECLARATIONBUILDERBASE_H
#define DECLARATIONBUILDERBASE_H

#include "typebuilder.h"
#include <language/duchain/builders/abstractdeclarationbuilder.h>
namespace KDvelop {
    class Declaration;
}
namespace Php {
class ParseSession;
class EditorIntegrator;

class KDEVPHPDUCHAIN_EXPORT DeclarationBuilderBase
    : public KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, Php::TypeBuilder> {
public:
    DeclarationBuilderBase(ParseSession* session);
    DeclarationBuilderBase(EditorIntegrator* editor);

protected:
    void classTypeOpened(KDevelop::AbstractType::Ptr type);
    void classContextOpened(KDevelop::DUContext* context);
};

}

#endif // DECLARATIONBUILDERBASE_H

