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
#include <language/duchain/declaration.h>
#include <language/duchain/classdeclaration.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icompletionsettings.h>

#include <klocalizedstring.h>

#include "parsesession.h"
#include "../editorintegrator.h"
#include "../helper.h"
#include "phpducontext.h"
#include "phpast.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

ContextBuilder::ContextBuilder()
    : m_isInternalFunctions(false), m_reportErrors(true),
      m_mapAst(false), m_hadUnresolvedIdentifiers(false),
      m_openNamespaces(0)
{
}

ContextBuilder::~ContextBuilder()
{
}

ReferencedTopDUContext ContextBuilder::build(const KDevelop::IndexedString& url, AstNode* node,
        KDevelop::ReferencedTopDUContext updateContext, bool useSmart)
{
    m_isInternalFunctions = url == internalFunctionFile();
    if ( m_isInternalFunctions ) {
        m_reportErrors = false;
    } else if ( ICore::self() ) {
        m_reportErrors = ICore::self()->languageController()->completionSettings()->highlightSemanticProblems();
    }

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
    return top;
}

void ContextBuilder::setEditor(EditorIntegrator* editor)
{
    ContextBuilderBase::setEditor(editor, false);
}

void ContextBuilder::setEditor(ParseSession* session)
{
    EditorIntegrator* e = new EditorIntegrator(session);
    ContextBuilderBase::setEditor(e, true);
}

bool ContextBuilder::hadUnresolvedIdentifiers() const
{
    return m_hadUnresolvedIdentifiers;
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
    if (!hasImports && top->url() != internalFunctionFile()) {
        DUChainWriteLocker lock(DUChain::lock());
        TopDUContext* import = DUChain::self()->chainForDocument(internalFunctionFile());
        if (!import) {
            kWarning() << "importing internalFunctions failed" << currentContext()->url().str();
            Q_ASSERT(false);
        } else {
            top->addImportedParentContext(import);
        }
    }
    visitNode(node);
    if (m_openNamespaces) {
        closeNamespaces(m_openNamespaces);
        m_openNamespaces = 0;
    }
}

DUContext* ContextBuilder::newContext(const SimpleRange& range)
{
    return new PhpDUContext<DUContext>(range, currentContext());
}

TopDUContext* ContextBuilder::newTopContext(const SimpleRange& range, ParsingEnvironmentFile* file)
{
    if (!file) {
        file = new ParsingEnvironmentFile(editor()->currentUrl());
        /// Indexed string for 'Php', identifies environment files from this language plugin
        static const IndexedString phpLangString("Php");
        file->setLanguage(phpLangString);
    }
    TopDUContext* ret = new PhpDUContext<TopDUContext>(editor()->currentUrl(), range, file);
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

SimpleCursor ContextBuilder::startPos(AstNode* node)
{
    return editor()->findPosition(node->startToken, KDevelop::EditorIntegrator::FrontEdge);
}

QualifiedIdentifier ContextBuilder::identifierForNode(IdentifierAst* id)
{
    if (!id)
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}
QualifiedIdentifier ContextBuilder::identifierForNode(VariableIdentifierAst* id)
{
    if (!id)
        return QualifiedIdentifier();
    QString ret(stringForNode(id));
    ret = ret.mid(1); //cut off $
    return QualifiedIdentifier(ret);
}

IdentifierPair ContextBuilder::identifierPairForNode( IdentifierAst* id )
{
    if (!id) {
        return qMakePair(KDevelop::IndexedString(), QualifiedIdentifier());
    }
    const QString ret = stringForNode(id);

    return qMakePair(KDevelop::IndexedString(ret), QualifiedIdentifier(ret.toLower()));
}

QString ContextBuilder::stringForNode(IdentifierAst* node) const
{
    return editor()->parseSession()->symbol(node->string);
}
QString ContextBuilder::stringForNode(VariableIdentifierAst* node) const
{
    return editor()->parseSession()->symbol(node->variable);
}

void ContextBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst* node)
{
    openContext(node, editorFindRange(node, node), DUContext::Class, identifierPairForNode(node->className).second);
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
    openContext(node, editorFindRange(node, node), DUContext::Class, identifierPairForNode(node->interfaceName).second);
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
        Q_ASSERT(!parameters->inSymbolTable());

        visitNode(node->parameters);
        closeContext();

        if ( !m_isInternalFunctions && node->methodBody ) {
            // the internal functions file has only empty method bodies, so skip them
            DUContext* body = openContext(node->methodBody, DUContext::Other, node->methodName);
            {
                DUChainWriteLocker lock(DUChain::lock());
                body->addImportedParentContext(parameters);
                body->setInSymbolTable(false);
            }
            visitNode(node->methodBody);
            closeContext();
        }
    } else {
        //member-variable or const
        DefaultVisitor::visitClassStatement(node);
    }
}

void ContextBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    visitNode(node->functionName);

    DUContext* parameters = openContext(node->parameters, DUContext::Function, node->functionName);
    Q_ASSERT(!parameters->inSymbolTable());

    visitNode(node->parameters);
    closeContext();

    if ( !m_isInternalFunctions && node->functionBody ) {
        // the internal functions file has only empty method bodies, so skip them
        DUContext* body = openContext(node->functionBody, DUContext::Other, node->functionName);
        {
            DUChainWriteLocker lock(DUChain::lock());
            body->addImportedParentContext(parameters);
            body->setInSymbolTable(false);
        }
        visitNode(node->functionBody);
        closeContext();
    }
}

void ContextBuilder::visitNamespaceDeclarationStatement(NamespaceDeclarationStatementAst* node)
{
    // close existing namespace context
    if (m_openNamespaces) {
        closeNamespaces(m_openNamespaces);
        m_openNamespaces = 0;
    }

    if ( !node->namespaceNameSequence ) {
        if (node->body) {
            // global namespace
            DefaultVisitor::visitInnerStatementList(node->body);
        }
        return;
    }

    { // open
    ///TODO: support \ as separator

    Range bodyRange;
    if (node->body) {
        bodyRange = editorFindRange(node->body, node->body);
    } else {
        bodyRange = Range(editor()->parseSession()->positionAt(node->endToken).textCursor(), currentContext()->topContext()->range().end.textCursor());
    }
    const KDevPG::ListNode< IdentifierAst* >* it = node->namespaceNameSequence->front();
    do {
        openNamespace(node, it->element, identifierPairForNode(it->element), bodyRange);
    } while(it->hasNext() && (it = it->next));
    }

    if (node->body) {
        DefaultVisitor::visitInnerStatementList(node->body);
        closeNamespaces(node);
    } else {
        m_openNamespaces = node;
    }
}

void ContextBuilder::closeNamespaces(NamespaceDeclarationStatementAst* namespaces)
{
    ///TODO: support \ as separator
    const KDevPG::ListNode< IdentifierAst* >* it = namespaces->namespaceNameSequence->front();
    do {
        Q_ASSERT(currentContext()->type() == DUContext::Namespace);
        closeNamespace(namespaces, it->element, identifierPairForNode(it->element));
    } while(it->hasNext() && (it = it->next));
}

void ContextBuilder::openNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node, const IdentifierPair& identifier, const Range& range)
{
    if ( node == parent->namespaceNameSequence->back()->element ) {
        openContext(node, range, KDevelop::DUContext::Namespace, identifier.second);
    } else {
        openContext(node, range, KDevelop::DUContext::Namespace, identifier.second);
    }
}

void ContextBuilder::closeNamespace(NamespaceDeclarationStatementAst* parent, IdentifierAst* node, const IdentifierPair& identifier)
{
    closeContext();
}

void ContextBuilder::addBaseType(NamespacedIdentifierAst * identifier)
{
    DUChainWriteLocker lock(DUChain::lock());

    Q_ASSERT(currentContext()->type() == DUContext::Class);

    ClassDeclaration* currentClass = dynamic_cast<ClassDeclaration*>(currentContext()->owner());

    ClassDeclaration* baseClass = dynamic_cast<ClassDeclaration*>(
        findDeclarationImport(ClassDeclarationType, identifierForNamespace(identifier, editor()), identifier)
    );

    if (currentClass && baseClass) {
        if (DUContext* baseContext = baseClass->logicalInternalContext(0)) {
            // prevent circular context imports which could lead to segfaults
            if (!baseContext->imports(currentContext()) && !currentContext()->imports(baseContext)) {
                currentContext()->addImportedParentContext(baseContext);
                BaseClassInstance base;
                base.baseClass = baseClass->indexedType();
                base.access = Declaration::Public;
                base.virtualInheritance = false;
                currentClass->addBaseClass(base);
            } else if (m_reportErrors) {
                reportError(i18n("Circular inheritance of %1 and %2", currentClass->toString(), baseClass->toString()), identifier);
            }
        }
    }
    if (!baseClass) {
        kDebug() << "unresolved identifier";
        m_hadUnresolvedIdentifiers = true;
    }
}


void ContextBuilder::visitUnaryExpression(UnaryExpressionAst* node)
{
    DefaultVisitor::visitUnaryExpression(node);
    IndexedString includeFile = getIncludeFileForNode(node, editor());
    if ( !includeFile.isEmpty() ) {
        DUChainWriteLocker lock(DUChain::lock());
        TopDUContext *top = DUChain::self()->chainForDocument(includeFile);
        if (top) {
            currentContext()->topContext()->addImportedParentContext(top);
            currentContext()->topContext()->parsingEnvironmentFile()
            ->addModificationRevisions(top->parsingEnvironmentFile()->allModificationRevisions());
        }
    }
}

void ContextBuilder::reportError(const QString& errorMsg, AstNode* node, KDevelop::ProblemData::Severity severity)
{
    reportError(errorMsg, editor()->findRange(node).textRange(), severity);
}

void ContextBuilder::reportError(const QString& errorMsg, QList< AstNode* > nodes, KDevelop::ProblemData::Severity severity)
{
    KTextEditor::Range range = KTextEditor::Range::invalid();
    foreach ( AstNode* node, nodes ) {
        if ( !range.isValid() ) {
            range.setRange( editor()->findRange(node).textRange() );
        } else {
            range.expandToRange( editor()->findRange(node).textRange() );
        }
    }
    reportError(errorMsg, range, severity);
}

void ContextBuilder::reportError(const QString& errorMsg, KTextEditor::Range range, KDevelop::ProblemData::Severity severity)
{
    KDevelop::Problem *p = new KDevelop::Problem();
    p->setSeverity(severity);
    p->setSource(KDevelop::ProblemData::DUChainBuilder);
    p->setDescription(errorMsg);
    p->setFinalLocation(KDevelop::DocumentRange(editor()->currentUrl().str(), range));
    {
        DUChainWriteLocker lock(DUChain::lock());
        kDebug() << "Problem" << p->description() << p->finalLocation();
        currentContext()->topContext()->addProblem(KDevelop::ProblemPointer(p));
    }
}

Declaration* ContextBuilder::findDeclarationImport(DeclarationType declarationType, IdentifierAst* node)
{
    QualifiedIdentifier id;
    if ( declarationType == ClassDeclarationType || declarationType == FunctionDeclarationType ) {
        id = identifierPairForNode(node).second;
    } else {
        id = identifierForNode(node);
    }
    return findDeclarationImportHelper(currentContext(), id, declarationType, node, editor());
}

Declaration* ContextBuilder::findDeclarationImport(DeclarationType declarationType, VariableIdentifierAst* node)
{
    return findDeclarationImportHelper(currentContext(), identifierForNode(node), declarationType, node, editor());
}

Declaration* ContextBuilder::findDeclarationImport(DeclarationType declarationType, const QualifiedIdentifier &identifier, AstNode* node)
{
    return findDeclarationImportHelper(currentContext(), identifier, declarationType, node, editor());
}

}
