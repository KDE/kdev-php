/* This file is part of KDevelop
    Copyright 2008 Niko Sams <niko.sams@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef TESTDUCHAIN_H
#define TESTDUCHAIN_H

#include "duchain/tests/duchaintestbase.h"

namespace Php
{
class TestDUChain : public DUChainTestBase
{
    Q_OBJECT

public:
    TestDUChain();

private slots:
    void testDeclareFunction();
    void testDeclareVar();
    void testDeclareClass();
    void testClassMemberVar();
    void testDeclareTypehintFunction();
    void testDeclareTypehintArrayFunction();
    void testReturnTypeClass();
    void testDeclarationReturnType();
    void testDeclarationReturnTypeInRecursingFunction();
    void testReturnTypeViaMember();
    void testDeclarationMultipleReturnTypes();
    void testDeclarationReturnTypeDocBlock();
    void testDeclarationReturnTypeDocBlockIntegral();
    void testClassImplementsInterface();
    void testClassExtends();
    void testStaticMethod();
    void testOwnStaticMethod();
    void testThis();
    void testObjectFunctionCall();
    void testObjectFunctionCall2();
    void testObjectFunctionCall3();
    void testObjectVariable();
    void testStaticMemberVariable();
    void testOwnStaticMemberVariable();
    void testClassConst();
    void testDefine();
    void testDefaultFunctionParam();
    void testGlobalFunction();
    void testGlobalVariableFromInternalFunctions();
    void testNewObjectFromOtherFile();
    void testUnknownReturnType();
    void testStaticFunctionCallFromOtherFile();
    void testClassConstantFromOtherFile();
    void testGlobalFunctionCallFromOtherFile();
    void testConstantFromOtherFile();
    void testSingleton();
    void testInternalFunctions();
    void testTrueFalse();
    void testNull();
    void testArray();
    void testFunctionDocBlock();
    void testVariableDocBlock();
    void testFunctionDocBlockParams();
    void testMemberFunctionDocBlockParams();
    void testForeachLoop();
    void testPhp4StyleConstructor();
    void testConstructor();
    void testDestructor();
    void testFunctionInFunction();
    void testObjectWithClassName();
    void testLargeNumberOfDeclarations();
    void testStaticVariable();
    void testReturnTypeTwoDeclarations();
    void testGlobalVariableNotVisibleInFunction();
    void testGlobalVariableInFunction();
    void testSuperglobalInFunction();
    void testReturnWithoutFunction();
    void testCircularInheritance();
    void testFindDeclarations();
    void testMemberTypeAfterMethod();
    void testCatchDeclaration();
    void testResourceType();
    void testForeachIterator();
    void testForeachIterator2();
    void testForeachIterator3();
    void testReturnThis();
    void testUnsureReturnType();
    void testUnsureReturnType2();
    void testUnsureReturnType3();
    void testUnsureReturnType4();
    void testDeclareMemberOutOfClass();
    void testDeclareMemberInClassMethod();
    void testThisRedeclaration();
    void testImplicitArrayDeclaration();
    void testImplicitReferenceDeclaration();
    void testClassContextRange();
    void testLateClassMembers();
    void testList();
    void testAlternateDocCommentTypeHints();
    void testFindFunctionArgs();
    void testUndeclaredPropertyInString();
    void testUndeclaredVarPropertyInString();
};

}

#endif
