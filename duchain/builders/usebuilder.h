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


#ifndef USEBUILDER_H
#define USEBUILDER_H

#include <language/duchain/builders/abstractusebuilder.h>

#include "helper.h"
#include "contextbuilder.h"
#include "phpduchainexport.h"

namespace Php
{

class ParseSession;

typedef KDevelop::AbstractUseBuilder<AstNode, IdentifierAst, ContextBuilder> UseBuilderBase;

/**
 * A class which iterates the AST to extract uses of definitions.
 */
class KDEVPHPDUCHAIN_EXPORT UseBuilder: public UseBuilderBase
{
public:
    UseBuilder(EditorIntegrator* editor);

    /**
     * Reports a problem if the use'd declaration is deprecated.
     * Also reports an error if @p reportNotFound is true and @p declaration is null.
     */
    void newCheckedUse(Php::AstNode* node, const KDevelop::DeclarationPointer& declaration, bool reportNotFound = false);

    KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, AstNode* node,
        const KDevelop::ReferencedTopDUContext& updateContext
        = KDevelop::ReferencedTopDUContext()) override;

protected:
    void visitParameter(ParameterAst *node) override;
    void visitClassImplements(ClassImplementsAst *node) override;
    void visitClassExtends(ClassExtendsAst *node) override;
    void visitClassStatement(ClassStatementAst *node) override;
    void visitTraitAliasStatement(TraitAliasStatementAst *node) override;
    void visitTraitAliasIdentifier(TraitAliasIdentifierAst *node) override;
    void visitExpr(ExprAst* node) override;
    void visitGlobalVar(GlobalVarAst* node) override;
    void visitStaticScalar(StaticScalarAst* node) override;
    void visitStatement(StatementAst* node) override;
    void visitCatchItem(CatchItemAst* node) override;
    void visitUnaryExpression( UnaryExpressionAst* node ) override;
    void visitUseStatement(UseStatementAst* node) override;
    void visitUseNamespace(UseNamespaceAst* node) override;
    void openNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node, const IdentifierPair& identifier, const KDevelop::RangeInRevision& range) override;
    void visitPropertyType(PropertyTypeAst* node) override;
    void visitReturnType(ReturnTypeAst* node) override;

private:
    void buildNamespaceUses(Php::NamespacedIdentifierAst* node, Php::DeclarationType lastType = Php::ClassDeclarationType);

    void visitNodeWithExprVisitor(AstNode* node);

    /// Type of use
    DeclarationType m_useNamespaceType;
};

}

#endif // USEBUILDER_H

