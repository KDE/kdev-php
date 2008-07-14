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

#include "declarationbuilder.h"

#include <QByteArray>

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/duchain/functiondeclaration.h>
#include "phpast.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

DeclarationBuilder::DeclarationBuilder (ParseSession* session)
    : m_lastVariableIdentifier(0)
{
  setEditor(session);
}

DeclarationBuilder::DeclarationBuilder (EditorIntegrator* editor)
    : m_lastVariableIdentifier(0)
{
  setEditor(editor);
}

void DeclarationBuilder::closeDeclaration()
{
    if (currentDeclaration()) {
        DUChainWriteLocker lock(DUChain::lock());
        currentDeclaration()->setType(lastType());
    }

  eventuallyAssignInternalContext();

  DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst * node)
{
    openDefinition(node->className, node, false);
    currentDeclaration()->setKind(KDevelop::Declaration::Type);

    DeclarationBuilderBase::visitClassDeclarationStatement(node);

    closeDeclaration();
}

void DeclarationBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
{
    openDefinition(node->interfaceName, node, false);
    currentDeclaration()->setKind(KDevelop::Declaration::Type);

    DeclarationBuilderBase::visitInterfaceDeclarationStatement(node);

    closeDeclaration();
}


void DeclarationBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration

        openDefinition(node->methodName, node, true);
        ClassFunctionDeclaration* dec = dynamic_cast<ClassFunctionDeclaration*>(currentDeclaration());
        Q_ASSERT(dec);
        {
            DUChainWriteLocker lock(DUChain::lock());
            dec->setKind(Declaration::Type);
            if (node->modifiers->modifiers & ModifierPublic) {
                dec->setAccessPolicy(Declaration::Public);
            } else if (node->modifiers->modifiers & ModifierProtected) {
                dec->setAccessPolicy(Declaration::Protected);
            } else if (node->modifiers->modifiers & ModifierPrivate) {
                dec->setAccessPolicy(Declaration::Private);
            }
            if (node->modifiers->modifiers & ModifierStatic) {
                dec->setStatic(true);
            }
            if (node->modifiers->modifiers & ModifierFinal) {
                //TODO: store this somewhere
            }
            if (node->modifiers->modifiers & ModifierAbstract) {
                //TODO: check if class is abstract
                //TODO: check if no methodBody exists
                //TODO: check if parent is not an interface
                //TODO: store somewhere that this function is abstract (?)
            }
            //TODO: if class is interface check if no methodBody exists
        }

        DeclarationBuilderBase::visitClassStatement(node);

        closeDeclaration();
    } else {
        if (node->modifiers) {
            m_currentModifers = node->modifiers->modifiers;
        } else {
            m_currentModifers = 0;
        }
        DeclarationBuilderBase::visitClassStatement(node);
        m_currentModifers = 0;
    }
}

void DeclarationBuilder::visitClassExtends(ClassExtendsAst *node)
{
    if (openTypeFromName(node->identifier, true)) {
        closeType();
        ClassType::Ptr extends = ClassType::Ptr::dynamicCast(lastType());
        if (extends) {
            addBaseType(extends, false);
        }
    }
}


void DeclarationBuilder::visitClassImplements(ClassImplementsAst *node)
{
    const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
    do
    {
        if (openTypeFromName(__it->element, true)) {
            closeType();
            ClassType::Ptr interface = ClassType::Ptr::dynamicCast(lastType());
            if (interface) {
                if (interface->classType() == Interface) {
                    addBaseType(interface, true);
                } else {
                    //TODO report error
                }
            }
        }
    }
    while (__it != __end);
    DeclarationBuilderBase::visitClassImplements(node);
}


void DeclarationBuilder::visitClassVariable(ClassVariableAst *node)
{
    {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->variable, node->variable);
        openDefinition(identifierForNode(node->variable), newRange, false);

        ClassMemberDeclaration* dec = dynamic_cast<ClassMemberDeclaration*>(currentDeclaration());
        Q_ASSERT(dec);
        if (m_currentModifers & ModifierPublic) {
            dec->setAccessPolicy(Declaration::Public);
        } else if (m_currentModifers & ModifierProtected) {
            dec->setAccessPolicy(Declaration::Protected);
        } else if (m_currentModifers & ModifierPrivate) {
            dec->setAccessPolicy(Declaration::Private);
        }
        if (m_currentModifers & ModifierStatic) {
            dec->setStatic(true);
        }
        if (m_currentModifers & ModifierFinal) {
            //TODO report error
        }
        if (m_currentModifers & ModifierAbstract) {
            //TODO report error
        }
        dec->setKind(Declaration::Instance);
    }

    DeclarationBuilderBase::visitClassVariable(node);
    closeDeclaration();
}

//copied from cpp
void DeclarationBuilder::classTypeOpened(AbstractType::Ptr type)
{
    //We override this so we can get the class-declaration into a usable state(with filled type) earlier
    DUChainWriteLocker lock(DUChain::lock());

    IdentifiedType* idType = dynamic_cast<IdentifiedType*>(type.unsafeData());

    if( idType && !idType->declarationId().isValid() ) //When the given type has no declaration yet, assume we are declaring it now
        idType->setDeclaration( currentDeclaration() );

    currentDeclaration()->setType(type);
}

void DeclarationBuilder::visitParameter(ParameterAst *node)
{
    {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->variable, node->variable);
        openDefinition(identifierForNode(node->variable), newRange, false);
    }

    currentDeclaration()->setKind(Declaration::Instance);
    DeclarationBuilderBase::visitParameter(node);
    closeDeclaration();
}

void DeclarationBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    openDefinition(node->functionName, node, true);

    currentDeclaration()->setKind(Declaration::Type);

    DeclarationBuilderBase::visitFunctionDeclarationStatement(node);

    closeDeclaration();
}

void DeclarationBuilder::visitExpr(ExprAst *node)
{
    m_lastVariableIdentifier = 0;
    DeclarationBuilderBase::visitExpr(node);
}

void DeclarationBuilder::visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
{
    DeclarationBuilderBase::visitAssignmentExpressionEqual(node);
    if (m_lastVariableIdentifier && m_expressionType) {
        //create new declaration for every assignment
        //TODO: don't create the same twice
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(m_lastVariableIdentifier, m_lastVariableIdentifier);
        openDefinition(identifierForNode(m_lastVariableIdentifier), newRange, false);
        currentDeclaration()->setKind(Declaration::Instance);

        //own closeDeclaration() that uses expressionType instead of lastType()
        currentDeclaration()->setType(m_expressionType);
        eventuallyAssignInternalContext();
        DeclarationBuilderBase::closeDeclaration();
    }
}

void DeclarationBuilder::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    //needed in assignmentExpressionEqual
    m_lastVariableIdentifier = node->variable;
    DeclarationBuilderBase::visitCompoundVariableWithSimpleIndirectReference(node);
}

}
