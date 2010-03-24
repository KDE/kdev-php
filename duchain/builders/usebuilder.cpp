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

#include "usebuilder.h"

#include <KLocalizedString>

#include "editorintegrator.h"
#include "expressionvisitor.h"
#include "parsesession.h"
using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

class UseExpressionVisitor : public ExpressionVisitor
{
public:
    UseExpressionVisitor(EditorIntegrator* editor, UseBuilder* useBuilder)
            : ExpressionVisitor(editor), m_builder(useBuilder) {
    }

protected:
    virtual void usingDeclaration(AstNode* node, KDevelop::Declaration* decl) {
        m_builder->newCheckedUse(node, decl);
    }

private:
    UseBuilder* m_builder;
};

UseBuilder::UseBuilder(ParseSession* session)
{
    setEditor(session);
}

UseBuilder::UseBuilder(EditorIntegrator* editor)
{
    setEditor(editor);
}

ReferencedTopDUContext UseBuilder::build ( const KDevelop::IndexedString& url, AstNode* node, ReferencedTopDUContext updateContext, bool useSmart )
{
    // just for safety purposes: running the UseBuilder on the internal function file
    // will lead to undefined behavior due to the amount of optimization it has received
    // (esp. in the contextbuilder)
    Q_ASSERT(url != internalFunctionFile());
    return UseBuilderBase::build ( url, node, updateContext, useSmart );
}

void UseBuilder::visitParameter(ParameterAst *node)
{
    if (node->parameterType) {
        newCheckedUse(node->parameterType, findDeclarationImport(ClassDeclarationType, node->parameterType));
    }
}

void UseBuilder::visitClassImplements(ClassImplementsAst *node)
{
    if (node->implementsSequence) {
        const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
        do {
            newCheckedUse(__it->element, findDeclarationImport(ClassDeclarationType, __it->element));
            __it = __it->next;
        } while (__it != __end);
    }
}

void UseBuilder::visitClassExtends(ClassExtendsAst *node)
{
    newCheckedUse(node->identifier, findDeclarationImport(ClassDeclarationType, node->identifier));
}

void UseBuilder::visitExpr(ExprAst* node)
{
    UseExpressionVisitor v(editor(), this);
    node->ducontext = currentContext();
    v.visitNode(node);
}

void UseBuilder::visitGlobalVar(GlobalVarAst* node)
{
    if (node->var) {
        Declaration* dec = findDeclarationImport(GlobalVariableDeclarationType, node->var);
        if (dec) {
            newCheckedUse(node->var, dec);
        }
    }
}

void UseBuilder::visitStaticScalar(StaticScalarAst* node)
{
    if (currentContext()->type() == DUContext::Class) {
        UseExpressionVisitor v(editor(), this);
        node->ducontext = currentContext();
        v.visitNode(node);
    }
}

void UseBuilder::visitStatement(StatementAst *node)
{
    AstNode* visitNode = 0;
    if (node->foreachVar) {
        visitNode = node->foreachVar;
    } else if (node->unsetVariablesSequence) {
        visitNode = node;
    }

    if (visitNode) {
        UseExpressionVisitor v(editor(), this);
        visitNode->ducontext = currentContext();
        v.visitNode(visitNode);
    }

    UseBuilderBase::visitStatement(node);
}

void UseBuilder::visitCatchItem(CatchItemAst *node)
{
    if (node->catchClass) {
        Declaration* dec = findDeclarationImport(ClassDeclarationType, node->catchClass);
        newCheckedUse(node->catchClass, dec);
    }
    UseBuilderBase::visitCatchItem(node);

}

void UseBuilder::newCheckedUse(AstNode* node, Declaration* declaration)
{
    if ( declaration && declaration->comment().contains("@deprecated") ) {
        reportError(i18n("Usage of %1 is deprecated.", declaration->toString()), node, ProblemData::Hint);
    }
    UseBuilderBase::newUse(node, declaration);
}

void UseBuilder::visitUnaryExpression( UnaryExpressionAst* node )
{
    UseBuilderBase::visitUnaryExpression(node);
    IndexedString includeFile = getIncludeFileForNode(node, editor());
    if ( !includeFile.isEmpty() ) {
        ///TODO: is there not a more elegant way to get a QualifiedIdentifier from a IndexedString?
        QualifiedIdentifier identifier(QString::fromUtf8(includeFile.byteArray()));

        DUChainWriteLocker lock(DUChain::lock());
        foreach ( Declaration* dec, currentContext()->topContext()->findDeclarations(identifier) ) {
            if ( dec->kind() == Declaration::Import ) {
                newUse(node->includeExpression, dec);
                return;
            }
        }
    }

}

}
