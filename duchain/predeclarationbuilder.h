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

#ifndef PREDECLARATIONBUILDER_H
#define PREDECLARATIONBUILDER_H

#include "contextbuilder.h"
#include "helper.h"
#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include <language/duchain/classdeclaration.h>

namespace KDvelop
{
class Declaration;
}
namespace Php
{
class ParseSession;
class EditorIntegrator;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, ContextBuilder> PreDeclarationBuilderBase;

/**
 * The PreDeclarationBuilder builds usable declarations for classes, interfaces and functions.
 *
 * \todo constants should probably be handled here as well
 */
class KDEVPHPDUCHAIN_EXPORT PreDeclarationBuilder : public PreDeclarationBuilderBase
{
public:
    PreDeclarationBuilder(QHash<qint64, KDevelop::ClassDeclaration*>* types, QHash < qint64,
                          KDevelop::FunctionDeclaration* > * functions,
                          ParseSession* session)
            : m_types(types), m_functions(functions) {
        setEditor(session);
    }
    PreDeclarationBuilder(QHash<qint64, KDevelop::ClassDeclaration*>* types, QHash < qint64,
                          KDevelop::FunctionDeclaration* > * functions,
                          EditorIntegrator* editor)
            : m_types(types), m_functions(functions) {
        setEditor(editor);
    }

    virtual ~PreDeclarationBuilder();

protected:
//     virtual void visitNode(Php::AstNode* node);
    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node);
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node);
    virtual void visitClassStatement(ClassStatementAst *node);
    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node);

private:
    QHash<qint64, KDevelop::ClassDeclaration*>* m_types;
    QHash<qint64, KDevelop::FunctionDeclaration*>* m_functions;
};

}

#endif // PREDECLARATIONBUILDER_H

