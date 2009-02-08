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

#ifndef DECLARATIONBUILDER_H
#define DECLARATIONBUILDER_H

#include "declarationbuilderbase.h"

#include "predeclarationbuilder.h"

#include "typebuilder.h"
#include "helper.h"
#include <language/duchain/builders/abstractdeclarationbuilder.h>
namespace KDvelop {
    class Declaration;
}
namespace Php {
class ParseSession;
class EditorIntegrator;

class KDEVPHPDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase {
public:
    DeclarationBuilder(ParseSession* session)
      : DeclarationBuilderBase(session), m_lastVariableIdentifier(0)
    {}
    DeclarationBuilder(EditorIntegrator* editor)
      : DeclarationBuilderBase(editor), m_lastVariableIdentifier(0)
    {}
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, Php::AstNode* node,
                                            KDevelop::ReferencedTopDUContext updateContext
                                                = KDevelop::ReferencedTopDUContext(), bool useSmart = true );

protected:
    virtual void closeDeclaration();
    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node);
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node);
    virtual void visitClassStatement(ClassStatementAst *node);
    virtual void visitClassExtends(ClassExtendsAst *node);
    virtual void visitClassImplements(ClassImplementsAst *node);
    virtual void visitParameter(ParameterAst *node);
    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node);
    virtual void visitClassVariable(ClassVariableAst *node);
    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *node);
    virtual void visitExpr(ExprAst *node);
    virtual void visitTopStatement(TopStatementAst* node);
    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node);
    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node);
    virtual void visitFunctionCall(FunctionCallAst* node);
    virtual void visitStatement(StatementAst* node);
    virtual void visitStaticVar(StaticVarAst* node);
    virtual void visitGlobalVar(GlobalVarAst* node);
    
    /// checks whether the body is empty (i.e. equals ";" instead of "{...}")
    bool isEmptyMethodBody(const Php::MethodBodyAst* body) const {
        return !body || !body->statements;
    }

private:
    VariableIdentifierAst* m_lastVariableIdentifier;
    unsigned int m_currentModifers;
    QString m_lastTopStatementComment;
    
    QHash<qint64, ClassDeclaration*> m_types;
    QHash<qint64, KDevelop::FunctionDeclaration*> m_functions;
    
    /// handles common stuff for both interfaces and classes
    void openTypeDeclaration(AstNode *node, IdentifierAst *name, ClassDeclarationData::ClassType type);
    
    /// check if this declaration is lready defined
    /// @param context defaults to current top context
    bool isRedeclaration(const KDevelop::QualifiedIdentifier &identifier, AstNode *node,
                          DeclarationType type, KDevelop::DUContext* context = 0);
};

}

#endif // DECLARATIONBUILDER_H

