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

#include "typebuilder.h"

#include <ktexteditor/smartrange.h>

#include <language/duchain/identifier.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include "editorintegrator.h"
#include "parsesession.h"
#include "typerepository.h"
#include "phpdebugvisitor.h"

using namespace KDevelop;
namespace Php {

TypeRepository* TypeBuilder::typeRepository() const
{
  return TypeRepository::self();
}

bool TypeBuilder::nodeValid(AstNode* node) const
{
  return node && node->startToken <= node->endToken;
}

void TypeBuilder::visitClassDeclarationStatement( ClassDeclarationStatementAst* node )
{
    ClassType::Ptr classType = ClassType::Ptr(new ClassType());
    classType->setClassType(ClassType::Class);

    openType(classType);

    classTypeOpened( TypeRepository::self()->registerType(currentAbstractType()) ); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

    TypeBuilderBase::visitClassDeclarationStatement(node);

    // Prevent additional elements being added if this becomes the current type again
    classType->close();

    closeType();
}

void TypeBuilder::visitClassExtends(ClassExtendsAst *node)
{
    if (openTypeFromName(node->identifier, true)) {
        closeType();
        ClassType::Ptr extends = KSharedPtr<ClassType>::dynamicCast(lastType());
        if (extends) {
            addBaseType(extends, false);
        }
    }
}

void TypeBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst* node)
{
    ClassType::Ptr classType = ClassType::Ptr(new ClassType());
    classType->setClassType(ClassType::Interface);

    openType(classType);

    classTypeOpened( TypeRepository::self()->registerType(currentAbstractType()) ); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

    TypeBuilderBase::visitInterfaceDeclarationStatement(node);

    // Prevent additional elements being added if this becomes the current type again
    classType->close();

    closeType();

}

void TypeBuilder::visitClassImplements(ClassImplementsAst *node)
{
    const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
    do
    {
        if (openTypeFromName(__it->element, true)) {
            closeType();
            ClassType::Ptr interface = ClassType::Ptr::dynamicCast(lastType());
            if (interface) {
                if (interface->classType() == ClassType::Interface) {
                    addBaseType(interface, true);
                } else {
                    //TODO report error
                }
            }
        }
    }
    while (__it != __end);
    TypeBuilderBase::visitClassImplements(node);
}

void TypeBuilder::visitClassStatement(ClassStatementAst *node)
{
    if (node->methodName) {
        //method declaration
        FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType(parseModifiers(node->modifiers)));

        openType(functionType);

        TypeBuilderBase::visitClassStatement(node);

        closeType();

    } else {
        //member-variable
        TypeBuilderBase::visitClassStatement(node);
    }
}

TypeModifiers TypeBuilder::parseModifiers(OptionalModifiersAst * node) const
{
    return static_cast<TypeModifiers>(node->modifiers);
}

void TypeBuilder::visitParameter(ParameterAst *node)
{
    TypeBuilderBase::visitParameter(node);
    if (hasCurrentType()) {
        if (FunctionType::Ptr function = currentType<FunctionType>()) {
            if (node->parameterType && openTypeFromName(node->parameterType, true)) {
                closeType();
                function->addArgument(lastType());
            }
        }
    }
}

void TypeBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType(NoModifier));

    openType(functionType);

    TypeBuilderBase::visitFunctionDeclarationStatement(node);

    closeType();
}

void TypeBuilder::addBaseType(const ClassType::Ptr& base, bool implementsInterface)
{
    {
        DUChainWriteLocker lock(DUChain::lock());
        ClassType::Ptr klass = ClassType::Ptr::dynamicCast(currentAbstractType());
        Q_ASSERT(klass);
        if (implementsInterface) {
            klass->addImplementsInterface(base);
        } else {
            klass->addExtendsClass(base);
        }
    }
    TypeBuilderBase::addBaseType(base, implementsInterface);
}

}

