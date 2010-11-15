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
    virtual void usingDeclaration(AstNode* node, const DeclarationPointer& decl) {
        m_builder->newCheckedUse(node, decl);
    }

private:
    UseBuilder* m_builder;
};

UseBuilder::UseBuilder( EditorIntegrator* editor )
{
    m_editor = editor;
}

ReferencedTopDUContext UseBuilder::build ( const IndexedString& url, AstNode* node, ReferencedTopDUContext updateContext )
{
    // just for safety purposes: running the UseBuilder on the internal function file
    // will lead to undefined behavior due to the amount of optimization it has received
    // (esp. in the contextbuilder)
    Q_ASSERT(url != internalFunctionFile());
    return UseBuilderBase::build ( url, node, updateContext );
}

void UseBuilder::visitParameter(ParameterAst *node)
{
    if (node->parameterType) {
        buildNamespaceUses(node->parameterType);
    }
}

void UseBuilder::visitClassImplements(ClassImplementsAst *node)
{
    if (node->implementsSequence) {
        const KDevPG::ListNode<NamespacedIdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
        do {
            buildNamespaceUses(__it->element);
            __it = __it->next;
        } while (__it != __end);
    }
}

void UseBuilder::visitClassExtends(ClassExtendsAst *node)
{
    buildNamespaceUses(node->identifier);
}

void UseBuilder::visitExpr(ExprAst* node)
{
    UseExpressionVisitor v(m_editor, this);
    node->ducontext = currentContext();
    v.visitNode(node);
}

void UseBuilder::visitGlobalVar(GlobalVarAst* node)
{
    if (node->var) {
        DeclarationPointer dec = findDeclarationImport(GlobalVariableDeclarationType, node->var);
        if (dec) {
            newCheckedUse(node->var, dec);
        }
    }
}

void UseBuilder::visitStaticScalar(StaticScalarAst* node)
{
    if (currentContext()->type() == DUContext::Class) {
        UseExpressionVisitor v(m_editor, this);
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
        UseExpressionVisitor v(m_editor, this);
        visitNode->ducontext = currentContext();
        v.visitNode(visitNode);
    }

    UseBuilderBase::visitStatement(node);
}

void UseBuilder::visitCatchItem(CatchItemAst *node)
{
    if (node->catchClass) {
        DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, node->catchClass);
        newCheckedUse(node->catchClass, dec);
    }
    UseBuilderBase::visitCatchItem(node);

}

void UseBuilder::newCheckedUse(AstNode* node, const DeclarationPointer& declaration)
{
    if ( declaration && declaration->comment().contains("@deprecated") ) {
        reportError(i18n("Usage of %1 is deprecated.", declaration->toString()), node, ProblemData::Hint);
    }
    UseBuilderBase::newUse(node, declaration);
}

void UseBuilder::visitUnaryExpression( UnaryExpressionAst* node )
{
    IndexedString includeFile = getIncludeFileForNode(node, m_editor);
    if ( !includeFile.isEmpty() ) {
        ///TODO: is there not a more elegant way to get a QualifiedIdentifier from a IndexedString?
        QualifiedIdentifier identifier(QString::fromUtf8(includeFile.byteArray()));

        DUChainWriteLocker lock(DUChain::lock());
        foreach ( Declaration* dec, currentContext()->topContext()->findDeclarations(identifier) ) {
            if ( dec->kind() == Declaration::Import ) {
                newUse(node->includeExpression, DeclarationPointer(dec));
                return;
            }
        }
    }
}

void UseBuilder::visitUseNamespace(UseNamespaceAst* node)
{
    buildNamespaceUses(node->identifier, NamespaceDeclarationType);
}

void UseBuilder::buildNamespaceUses(NamespacedIdentifierAst* node, DeclarationType lastType)
{
    QualifiedIdentifier identifier = identifierForNamespace(node, m_editor);
    QualifiedIdentifier curId;
    curId.setExplicitlyGlobal(identifier.explicitlyGlobal());
    Q_ASSERT(identifier.count() == node->namespaceNameSequence->count());
    for ( int i = 0; i < identifier.count() - 1; ++i ) {
        curId.push(identifier.at(i));
        AstNode* n = node->namespaceNameSequence->at(i)->element;
        DeclarationPointer dec = findDeclarationImport(NamespaceDeclarationType, curId, n);
        newCheckedUse(n, dec);
    }
    newCheckedUse(node->namespaceNameSequence->back()->element,
                  findDeclarationImport(lastType, identifier, node ));
}

void UseBuilder::openNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node,
                               const IdentifierPair& identifier, const RangeInRevision& range)
{
    if (node != parent->namespaceNameSequence->back()->element) {
        newCheckedUse(node, findDeclarationImport(NamespaceDeclarationType, identifier.second, node));
    }
    UseBuilderBase::openNamespace(parent, node, identifier, range);
}


}
