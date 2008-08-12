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

#include "contextbuilder.h"

#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainlock.h>

#include "parsesession.h"
#include "editorintegrator.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

ContextBuilder::ContextBuilder()
{
}

void ContextBuilder::setEditor(EditorIntegrator* editor)
{
    ContextBuilderBase::setEditor(editor, false);
}

void ContextBuilder::setEditor(ParseSession* session)
{
    EditorIntegrator* e = new EditorIntegrator(session);
    ContextBuilderBase::setEditor(e, false);
}

ContextBuilder::~ContextBuilder()
{
}

void ContextBuilder::startVisiting(AstNode* node)
{
    visitNode(node);
}

void ContextBuilder::setContextOnNode(AstNode* node, KDevelop::DUContext* ctx)
{
    node->ducontext = ctx;
}

KDevelop::DUContext* ContextBuilder::contextFromNode(AstNode* node)
{
    return node->ducontext;
}

EditorIntegrator* ContextBuilder::editor() const
{
    return static_cast<EditorIntegrator*>(ContextBuilderBase::editor());
}

KTextEditor::Range ContextBuilder::editorFindRange(AstNode* fromRange, AstNode* toRange)
{
    return editor()->findRange(fromRange, toRange).textRange();
}

QualifiedIdentifier ContextBuilder::identifierForNode(IdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();

    return QualifiedIdentifier(editor()->parseSession()->symbol(id->string));
}
QualifiedIdentifier ContextBuilder::identifierForNode(VariableIdentifierAst* id)
{
    if( !id )
        return QualifiedIdentifier();
    QString ret(editor()->parseSession()->symbol(id->variable));
    ret = ret.mid(1); //cut off $
    return QualifiedIdentifier(ret);
}

void ContextBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst* node)
{
    openContext(node, DUContext::Class, node->className);
    classContextOpened(currentContext()); //This callback is needed, so we can set the internal context and so find the declaration for the context (before closeDeclaration())
    DefaultVisitor::visitClassDeclarationStatement(node);
    closeContext();
}

void ContextBuilder::classContextOpened(KDevelop::DUContext* context)
{
}

void ContextBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node)
{
    visitNode(node->extends);
    openContext(node, DUContext::Class, node->interfaceName);
    visitNode(node->body);
    closeContext();
}

void ContextBuilder::visitClassStatement(ClassStatementAst *node)
{
    visitNode(node->modifiers);
    if (node->methodName) {
        //method declaration

        QualifiedIdentifier id;

        DUContext* parameters = 0;
        if (node->parameters) {
            parameters = openContext(node->parameters, DUContext::Function, node->methodName);
            id = currentContext()->localScopeIdentifier();
            visitNode(node->parameters);
            closeContext();
        }

        DUContext* body = openContext(node->methodBody, DUContext::Other, id);

        if (parameters) {
            DUChainWriteLocker lock(DUChain::lock());
            body->addImportedParentContext(parameters);
        }
        visitNode(node->methodBody);
        closeContext();
    } else {
        //member-variable or const
        DefaultVisitor::visitClassStatement(node);
    }
}

void ContextBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    QualifiedIdentifier id;
    DUContext* parameters = 0;
    if (node->parameters) {
        parameters = openContext(node->parameters, DUContext::Function, node->functionName);
        id = currentContext()->localScopeIdentifier();
        visitNode(node->parameters);
        closeContext();
    }

    DUContext* body = openContext(node->functionBody, DUContext::Other, id);
    if (parameters) {
        DUChainWriteLocker lock(DUChain::lock());
        body->addImportedParentContext(parameters);
    }
    visitNode(node->functionBody);
    closeContext();
}

void ContextBuilder::addBaseType(const ClassType::Ptr& base, bool implementsInterface)
{
    DUChainWriteLocker lock(DUChain::lock());

    Q_ASSERT(currentContext()->type() == DUContext::Class);
    if (base->declaration(currentContext()->topContext())
        && base->declaration(currentContext()->topContext())->logicalInternalContext(0)) {
        currentContext()->addImportedParentContext( base->declaration(currentContext()->topContext())->logicalInternalContext(0) );
    }
}

}
