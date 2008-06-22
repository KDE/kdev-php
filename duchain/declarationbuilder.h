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

#ifndef DECLARATIONBUILDER_H
#define DECLARATIONBUILDER_H

#include "typebuilder.h"
#include <language/duchain/abstractdeclarationbuilder.h>

namespace Php {
class ParseSession;
class EditorIntegrator;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, Php::TypeBuilder> DeclarationBuilderBase;

class KDEVPHPDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase {
public:
    DeclarationBuilder(ParseSession* session);
    DeclarationBuilder(EditorIntegrator* editor);
protected:
    virtual void closeDeclaration();
    void visitClassDeclarationStatement(ClassDeclarationStatementAst * node);
    void visitClassStatement(ClassStatementAst *node);
    void visitParameter(ParameterAst *node);


    void classTypeOpened(KDevelop::AbstractType::Ptr type);
};

}

#endif // DECLARATIONBUILDER_H

