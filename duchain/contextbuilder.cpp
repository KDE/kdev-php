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
#include <language/duchain/duchain.h>

#include "parsesession.h"
#include "editorintegrator.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

ContextBuilder::ContextBuilder()
{
}
ReferencedTopDUContext ContextBuilder::build( const IndexedString& url, AstNode* node)
{
    ReferencedTopDUContext updateContext;
    {
        DUChainReadLocker lock(DUChain::lock());
        updateContext = DUChain::self()->chainForDocument(url);
    }
    if (updateContext) {
        DUChainWriteLocker lock(DUChain::lock());
        updateContext->clearImportedParentContexts();
    }
    return ContextBuilderBase::build(url, node, updateContext);
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
    TopDUContext* top = dynamic_cast<TopDUContext*>(currentContext());
    Q_ASSERT(top);
    bool hasImports;
    {
        DUChainReadLocker lock(DUChain::lock());
        hasImports = top->importedParentContexts().isEmpty();
    }
    if (hasImports &&  top->url() != IndexedString("internalfunctions")) {
        DUChainWriteLocker lock(DUChain::lock());
        top->addImportedParentContext(DUChain::self()->chainForDocument(IndexedString("internalfunctions")));
    }
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
    Q_UNUSED(context);
}

void ContextBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node)
{
    openContext(node, DUContext::Class, node->interfaceName);
    classContextOpened(currentContext()); //This callback is needed, so we can set the internal context and so find the declaration for the context (before closeDeclaration())
    DefaultVisitor::visitInterfaceDeclarationStatement(node);
    closeContext();
}

void ContextBuilder::visitClassStatement(ClassStatementAst *node)
{
    visitNode(node->modifiers);
    if (node->methodName) {
        //method declaration
        DUContext* parameters = openContext(node->parameters, DUContext::Function, node->methodName);
        visitNode(node->parameters);
        closeContext();

        DUContext* body = openContext(node->methodBody, DUContext::Other, node->methodName);
        {
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


void ContextBuilder::visitTopStatement(TopStatementAst* node)
{
    DefaultVisitor::visitTopStatement(node);
}

void ContextBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    visitNode(node->functionName);

    DUContext* parameters = openContext(node->parameters, DUContext::Function, node->functionName);
    visitNode(node->parameters);
    closeContext();

    DUContext* body = openContext(node->functionBody, DUContext::Other, node->functionName);
    {
        DUChainWriteLocker lock(DUChain::lock());
        body->addImportedParentContext(parameters);
    }
    visitNode(node->functionBody);
    closeContext();
}

void ContextBuilder::addBaseType(const StructureType::Ptr& base, bool implementsInterface)
{
    DUChainWriteLocker lock(DUChain::lock());

    Q_ASSERT(currentContext()->type() == DUContext::Class);
    if (base->declaration(currentContext()->topContext())
        && base->declaration(currentContext()->topContext())->logicalInternalContext(0)) {
        currentContext()->addImportedParentContext( base->declaration(currentContext()->topContext())->logicalInternalContext(0) );
    }
}

}
