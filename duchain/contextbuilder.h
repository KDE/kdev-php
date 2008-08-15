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

#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include "phpdefaultvisitor.h"
#include <language/duchain/builders/abstractcontextbuilder.h>
#include <language/duchain/types/structuretype.h>

#include "phpduchainexport.h"
#include "editorintegrator.h"

namespace Php
{
class EditorIntegrator;
class ParseSession;

typedef KDevelop::AbstractContextBuilder<AstNode, IdentifierAst> ContextBuilderBase;

class KDEVPHPDUCHAIN_EXPORT ContextBuilder: public ContextBuilderBase, public DefaultVisitor
{

public:
    ContextBuilder();
    virtual ~ContextBuilder ();

    void setEditor(EditorIntegrator* editor);
    void setEditor(ParseSession* session);

    virtual KDevelop::ReferencedTopDUContext build( const KDevelop::IndexedString& url, AstNode* node);
protected:
    EditorIntegrator* editor() const;

    virtual void startVisiting( AstNode* node );
    virtual void setContextOnNode( AstNode* node, KDevelop::DUContext* ctx );
    virtual KDevelop::DUContext* contextFromNode( AstNode* node );
    virtual KTextEditor::Range editorFindRange( AstNode* fromRange, AstNode* toRange );

    virtual KDevelop::QualifiedIdentifier identifierForNode(IdentifierAst* id);
    KDevelop::QualifiedIdentifier identifierForNode(VariableIdentifierAst* id);

    virtual void visitClassDeclarationStatement( ClassDeclarationStatementAst* );
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node);
    virtual void visitClassStatement(ClassStatementAst *node);
    virtual void visitFunctionDeclarationStatement( FunctionDeclarationStatementAst* node );

    virtual void addBaseType(const KDevelop::StructureType::Ptr& base, bool implementsInterface);

    virtual void classContextOpened(KDevelop::DUContext* context);
};

}

#endif
