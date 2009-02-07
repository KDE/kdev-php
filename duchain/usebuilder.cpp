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

#include "editorintegrator.h"
#include "expressionvisitor.h"
#include "parsesession.h"
using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

class UseExpressionVisitor : public ExpressionVisitor {
public:
    UseExpressionVisitor(EditorIntegrator* editor, bool useCursor, UseBuilder* useBuilder)
        : ExpressionVisitor(editor, useCursor), m_builder(useBuilder) {
    }

protected:
    virtual void usingDeclaration(AstNode* node, KDevelop::Declaration* decl) {
        m_builder->newUse(node, decl);
    }

private:
    UseBuilder* m_builder;
};

UseBuilder::UseBuilder (ParseSession* session)
{
    setEditor(session);
}

UseBuilder::UseBuilder (EditorIntegrator* editor)
{
    setEditor(editor);
}

void UseBuilder::visitParameter(ParameterAst *node)
{
    UseBuilderBase::visitParameter(node);

    if (node->parameterType) {
        newUse(node->parameterType);
    }
}

void UseBuilder::visitClassImplements(ClassImplementsAst *node)
{
    UseBuilderBase::visitClassImplements(node);
    if (node->implementsSequence) {
        const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
        do {
            newUse(__it->element, findDeclarationImport(ClassDeclarationType, __it->element));
            __it = __it->next;
        } while (__it != __end);
    }
}

void UseBuilder::visitClassExtends(ClassExtendsAst *node)
{
    UseBuilderBase::visitClassExtends(node);
    newUse(node->identifier, findDeclarationImport(ClassDeclarationType, node->identifier));
}

void UseBuilder::visitExpr(ExprAst* node)
{
    UseBuilderBase::visitExpr(node);
    UseExpressionVisitor v(editor(), currentContext()->topContext(), this);
    v.visitNode(node);
}

void UseBuilder::visitGlobalVar(GlobalVarAst* node)
{
    if (node->var) {
        Declaration* dec = findDeclarationImport(GlobalVariableDeclarationType, node->var);
        if (dec) {
            newUse(node->var, dec);
        }
    }
    UseBuilderBase::visitGlobalVar(node);
}

Declaration* UseBuilder::findDeclarationImport(DeclarationType declarationType, IdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext(), identifierForNode(node), declarationType, node, editor(), true);
}

Declaration* UseBuilder::findDeclarationImport(DeclarationType declarationType, VariableIdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext(), identifierForNode(node), declarationType, node, editor(), true);
}

}
