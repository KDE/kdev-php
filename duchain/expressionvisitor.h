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
#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

#include "phpdefaultvisitor.h"
#include "phpduchainexport.h"
#include "expressionevaluationresult.h"

#include <language/duchain/types/abstracttype.h>
#include <language/duchain/identifier.h>

namespace KDevelop {
    class TopDUContext;
    class Declaration;
}

namespace Php {
class ParseSession;

class KDEVPHPDUCHAIN_EXPORT ExpressionVisitor : public DefaultVisitor
{
public:
    ExpressionVisitor(ParseSession* session, const KDevelop::TopDUContext* source, bool strict);
    ExpressionEvaluationResult result() { return m_result; }

protected:
    void visitExpr(ExprAst *node);
    void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node);
    void visitVarExpressionNewObject(VarExpressionNewObjectAst *node);
    void visitFunctionCall(FunctionCallAst* node);
    void visitScalar(ScalarAst *node);
    void visitVariableProperty(VariablePropertyAst *node);
    void visitStaticMember(StaticMemberAst* node);

    KDevelop::QualifiedIdentifier identifierForNode(IdentifierAst* id);
    KDevelop::QualifiedIdentifier identifierForNode(VariableIdentifierAst* id);

    virtual void usingDeclaration(AstNode* node, KDevelop::Declaration* decl) {
        Q_UNUSED(node) Q_UNUSED(decl)
    }

protected:
    ParseSession* m_session;

private:
    const KDevelop::TopDUContext* m_source;
    bool m_strict;
    KDevelop::DUContext* m_currentContext;
    
    ExpressionEvaluationResult m_result;
};

}
#endif
