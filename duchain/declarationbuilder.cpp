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
#include "helper.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

//Helper visitor to extract a commonScalar node
//used to get the value of an function call argument
class ScalarExpressionVisitor : public DefaultVisitor
{
public:
    ScalarExpressionVisitor() : m_node(0) {}
    CommonScalarAst* node() const { return m_node; }
private:
    virtual void visitCommonScalar(CommonScalarAst* node) {
        m_node = node;
    }
    CommonScalarAst* m_node;
};

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
    openDefinition<Declaration>(node->className, node);
    currentDeclaration()->setKind(KDevelop::Declaration::Type);

    DeclarationBuilderBase::visitClassDeclarationStatement(node);
    closeDeclaration();
}

void DeclarationBuilder::classContextOpened(KDevelop::DUContext* context)
{
    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setInternalContext(context);
}

void DeclarationBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
{
    openDefinition<Declaration>(node->interfaceName, node);
    currentDeclaration()->setKind(KDevelop::Declaration::Type);

    DeclarationBuilderBase::visitInterfaceDeclarationStatement(node);

    closeDeclaration();
}


void DeclarationBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration

        openDefinition<ClassFunctionDeclaration>(node->methodName, node);
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
    Declaration* dec = findDeclarationImport(currentContext(), identifierForNode(node->identifier), ClassDeclarationType);
    if (dec) {
        StructureType::Ptr extends = StructureType::Ptr::dynamicCast(dec->abstractType());
        if (extends) {
            addBaseType(extends, false);
        }
    }
}


void DeclarationBuilder::visitClassImplements(ClassImplementsAst *node)
{
    const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
    do {
        Declaration* dec = findDeclarationImport(currentContext(), identifierForNode(__it->element), ClassDeclarationType);
        if (dec) {
            StructureType::Ptr interface = StructureType::Ptr::dynamicCast(dec->abstractType());
            if (interface && interface->classType() == StructureType::Interface) {
                addBaseType(interface, true);
            } else {
                //TODO report error
            }
        }
        __it = __it->next;
    }
    while (__it != __end);
    DeclarationBuilderBase::visitClassImplements(node);
}


void DeclarationBuilder::visitClassVariable(ClassVariableAst *node)
{
    {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->variable, node->variable);
        openDefinition<ClassMemberDeclaration>(identifierForNode(node->variable), newRange);

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

void DeclarationBuilder::visitClassConstantDeclaration(ClassConstantDeclarationAst *node)
{
qDebug() << identifierForNode(node->identifier).toString();
    openDefinition<ClassMemberDeclaration>(node->identifier, node->identifier);
    ClassMemberDeclaration* dec = dynamic_cast<ClassMemberDeclaration*>(currentDeclaration());
    Q_ASSERT(dec);
    dec->setAccessPolicy(Declaration::Public);
    dec->setStatic(true);
    dec->setKind(Declaration::Instance);
    DeclarationBuilderBase::visitClassConstantDeclaration(node);
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
    if (node->defaultValue) {
        AbstractFunctionDeclaration* funDec = dynamic_cast<AbstractFunctionDeclaration*>(currentDeclaration());
        if (funDec) {
            funDec->addDefaultParameter(IndexedString(editor()->parseSession()->symbol(node->defaultValue)));
        }
    }
    {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->variable, node->variable);
        openDefinition<Declaration>(identifierForNode(node->variable), newRange);
    }

    currentDeclaration()->setKind(Declaration::Instance);
    DeclarationBuilderBase::visitParameter(node);
    closeDeclaration();
}

void DeclarationBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    openDefinition<FunctionDeclaration>(node->functionName, node);

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
    VariableIdentifierAst* leftSideVariableIdentifier = m_lastVariableIdentifier;
    DeclarationBuilderBase::visitAssignmentExpressionEqual(node);

    if (leftSideVariableIdentifier && m_expressionType) {

        //create new declaration for every assignment
        //TODO: don't create the same twice
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(leftSideVariableIdentifier, leftSideVariableIdentifier);
        openDefinition<Declaration>(identifierForNode(leftSideVariableIdentifier), newRange);
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

void DeclarationBuilder::visitFunctionCall(FunctionCallAst* node)
{
    DeclarationBuilderBase::visitFunctionCall(node);
    if (node->stringFunctionNameOrClass && !node->stringFunctionName && !node->varFunctionName) {
        if (identifierForNode(node->stringFunctionNameOrClass) == QualifiedIdentifier("define")
            && node->stringParameterList->parametersSequence->count() > 0) {
            //constant, defined through define-function
            ScalarExpressionVisitor visitor;
            //find name of the constant (first argument of the function call)
            visitor.visitNode(node->stringParameterList->parametersSequence->at(0)->element);
            if (visitor.node() && visitor.node()->string != -1) {
                QString constant = editor()->parseSession()->symbol(visitor.node()->string);
                constant = constant.mid(1, constant.length()-2);
                SimpleRange newRange = editorFindRange(visitor.node(), visitor.node());
                DUChainWriteLocker lock(DUChain::lock());
                LockedSmartInterface iface = editor()->smart();
                injectContext(iface, currentContext()->topContext()); //constants are always global
                openDefinition<Declaration>(QualifiedIdentifier(constant), newRange);
                currentDeclaration()->setKind(Declaration::Instance);
                closeDeclaration();
                closeInjectedContext(iface);
            }
        }
    }
}

}
