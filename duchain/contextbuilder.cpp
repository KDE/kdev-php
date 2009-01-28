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
#include <language/duchain/declaration.h>

#include <klocalizedstring.h>

#include "parsesession.h"
#include "editorintegrator.h"
#include "helper.h"
#include "phpducontext.h"
#include "phpast.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

ContextBuilder::ContextBuilder()
{
}
ReferencedTopDUContext ContextBuilder::build( const KDevelop::IndexedString& url, AstNode* node,
                                            KDevelop::ReferencedTopDUContext updateContext, bool useSmart )
{
    if (!updateContext) {
        DUChainReadLocker lock(DUChain::lock());
        updateContext = DUChain::self()->chainForDocument(url);
    }
    if (updateContext) {
        kDebug() << "re-compiling" << url.str();
        DUChainWriteLocker lock(DUChain::lock());
        updateContext->clearImportedParentContexts();
        updateContext->parsingEnvironmentFile()->clearModificationRevisions();
        updateContext->clearProblems();
    } else {
        kDebug() << "compiling" << url.str();
    }
    ReferencedTopDUContext top = ContextBuilderBase::build(url, node, updateContext, useSmart);
    if (!updateContext) {
        DUChainWriteLocker lock(DUChain::lock());
        top->setLanguage(IndexedString("Php"));
    }
    return top;
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
        hasImports = !top->importedParentContexts().isEmpty();
    }
    if (!hasImports && !isInternalFunctionFile(top->url())) {
        DUChainWriteLocker lock(DUChain::lock());
        for (uint i=0; i < internalFunctionFilesCount; i++) {
            TopDUContext* import = DUChain::self()->chainForDocument(internalFunctionFiles[i]);
            if (!import) {
                kWarning() << "importing internalFunctions failed" << currentContext()->url().str() << internalFunctionFiles[i].str();
            } else {
                top->addImportedParentContext(import);
            }
        }
    }
    visitNode(node);
}

DUContext* ContextBuilder::newContext(const SimpleRange& range)
{
    return new PhpDUContext<DUContext>(range, currentContext());
}

TopDUContext* ContextBuilder::newTopContext(const SimpleRange& range, ParsingEnvironmentFile* file)
{
    if (!file) {
        file = new ParsingEnvironmentFile(editor()->currentUrl());
    }
    TopDUContext* ret = new PhpDUContext<TopDUContext>(editor()->currentUrl(), range, file);
    file->setTopContext(ret);
    return ret;
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

void ContextBuilder::addBaseType(IdentifierAst * identifier, bool implementsInterface)
{
    DUChainWriteLocker lock(DUChain::lock());
    
    Q_ASSERT(currentContext()->type() == DUContext::Class);
    
    ClassDeclaration* currentClass = dynamic_cast<ClassDeclaration*>(currentContext()->owner());
    
    ClassDeclaration* baseClass = dynamic_cast<ClassDeclaration*>(findDeclarationImport(ClassDeclarationType, identifier));
    
    if ( currentClass && baseClass ) {
        if ( DUContext* baseContext = baseClass->logicalInternalContext(0) ) {
            // prevent circular context imports which could lead to segfaults
            if ( !baseContext->imports(currentContext()) && !currentContext()->imports(baseContext) ) {
                currentContext()->addImportedParentContext( baseContext );
                if ( implementsInterface ) {
                    currentClass->addInterface( BaseClassInstance( baseClass->indexedType() ) );
                } else {
                    currentClass->setBaseClass( BaseClassInstance( baseClass->indexedType() ) );
                }
            } else {
                ///TODO report error
                reportError(i18n("Circular inheritance of %1 and %2", currentClass->toString(), baseClass->toString()), identifier);
            }
        }
    }
}


void ContextBuilder::visitUnaryExpression(UnaryExpressionAst* node)
{
    DefaultVisitor::visitUnaryExpression(node);
    if (node->includeExpression) {
        //find name of the constant (first argument of the function call)
        CommonScalarAst* scalar = findCommonScalar(node->includeExpression);
        if (scalar && scalar->string != -1) {
            QString str = editor()->parseSession()->symbol(scalar->string);
            str = str.mid(1, str.length()-2);
            IndexedString includeFile = findIncludeFileUrl(str, KUrl(editor()->currentUrl().str()));

            DUChainWriteLocker lock(DUChain::lock());
            TopDUContext *top = DUChain::self()->chainForDocument(includeFile);
            if (top) {
                currentContext()->topContext()->addImportedParentContext(top);
                currentContext()->topContext()->parsingEnvironmentFile()
                    ->addModificationRevisions(top->parsingEnvironmentFile()->allModificationRevisions());
            }
        }
    }
}

void ContextBuilder::reportError(const QString& errorMsg, AstNode* node)
{
    KDevelop::Problem *p = new KDevelop::Problem();
    p->setSource(KDevelop::ProblemData::DUChainBuilder);
    p->setDescription(errorMsg);
    p->setFinalLocation(KDevelop::DocumentRange(editor()->currentUrl().str(), editor()->findRange(node).textRange()));
    {
        DUChainWriteLocker lock(DUChain::lock());
        kDebug() << "Problem" << p->description();
        currentContext()->topContext()->addProblem(KDevelop::ProblemPointer(p));
    }
}

Declaration* ContextBuilder::findDeclarationImport(DeclarationType declarationType, IdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext(), identifierForNode(node), declarationType, node, editor(), true);
}

Declaration* ContextBuilder::findDeclarationImport(DeclarationType declarationType, VariableIdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext(), identifierForNode(node), declarationType, node, editor(), true);
}

Declaration* ContextBuilder::findDeclarationImport(DeclarationType declarationType, const QualifiedIdentifier &identifier, AstNode* node, bool createProblems)
{
    return findDeclarationImportHelper(currentContext(), identifier, declarationType, node, editor(), createProblems);
}

}
