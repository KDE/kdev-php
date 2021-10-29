/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef TESTDUCHAIN_H
#define TESTDUCHAIN_H

#include "tests/duchaintestbase.h"

namespace Php
{
class TestDUChain : public DUChainTestBase
{
    Q_OBJECT

public:
    TestDUChain();

private slots:
    void declareFunction();
    void declareBaseTypeFunction();
    void declareSemiReservedFunction();
    void declareVar();
    void varTypehint();
    void declareClass();
    void declareBaseTypeClass();
    void declareClassWithSemiReservedMethod();
    void declareClassWithBaseTypeMethod();
    void classMemberVar();
    void classMemberVarTypehint();
    void classMemberVarAfterUse();
    void classMemberVarDocBlockType();
    void declareTypehintFunction();
    void declareVariadicFunction();
    void declareTypehintVariadicFunction();
    void declareTypehintObjectFunction();
    void declareTypehintArrayFunction();
    void declareTypehintCallableFunction();
    void functionWithCallableAndFunctionReturn();
    void declareTypehintIterableFunction();
    void declareTypehintBoolFunction();
    void declareTypehintFloatFunction();
    void declareTypehintIntFunction();
    void declareTypehintStringFunction();
    void declareNullableTypehintArrayFunction();
    void declareNullableTypehintMixedFunction();
    void declareTypehintNullableIterableFunction();
    void declareTypehintWithPhpdocFunction();
    void returnTypeGenerator_data();
    void returnTypeGenerator();
    void returnTypeGeneratorDelegation();
    void returnTypeClass();
    void declarationReturnType();
    void declarationReturnTypeInRecursingFunction();
    void returnTypeViaMember();
    void declarationMultipleReturnTypes();
    void declarationReturnTypeDocBlock();
    void declarationReturnTypeDocBlockIntegral();
    void declarationReturnTypeClassChain();
    void declarationReturnTypeTypehint();
    void declarationReturnTypeTypehintVoid();
    void declarationReturnTypeTypehintObject();
    void classImplementsInterface();
    void classExtends();
    void staticMethod();
    void ownStaticMethod();
    void thisVar();
    void objectFunctionCall();
    void objectFunctionCall2();
    void objectFunctionCall3();
    void objectVariable();
    void staticMemberVariable();
    void ownStaticMemberVariable();
    void classConst();
    void classConst_data();
    void classConstWithTypeHint();
    void classConstVisibility();
    void semiReservedClassConst();
    void illegalClassConst();
    void illegalClassConst_data();
    void fileConst();
    void fileConst_data();
    void semiReservedFileConst();
    void define();
    void defaultFunctionParam();
    void defaultFunctionParamWithTypehint();
    void nullDefaultFunctionParamWithTypehint();
    void globalFunction();
    void globalVariableFromInternalFunctions();
    void newObjectFromOtherFile();
    void unknownReturnType();
    void staticFunctionCallFromOtherFile();
    void classConstantFromOtherFile();
    void globalFunctionCallFromOtherFile();
    void constantFromOtherFile();
    void singleton();
    void internalFunctions();
    void trueFalse();
    void null();
    void array();
    void functionDocBlock();
    void variableDocBlock();
    void functionDocBlockParams();
    void memberFunctionDocBlockParams();
    void foreachLoop();
    void php4StyleConstructor();
    void constructor();
    void destructor();
    void functionInFunction();
    void objectWithClassName();
    void largeNumberOfDeclarations();
    void staticVariable();
    void returnTypeTwoDeclarations();
    void globalVariableNotVisibleInFunction();
    void globalVariableInFunction();
    void nonGlobalVariableInFunction();
    void superglobalInFunction();
    void returnWithoutFunction();
    void circularInheritance();
    void circularInterface();
    void findDeclarations();
    void memberTypeAfterMethod();
    void catchDeclaration();
    void multiCatchDeclaration();
    void resourceType();
    void foreachIterator();
    void foreachIterator2();
    void foreachIterator3();
    void foreachIterator4();
    void foreachArray();
    void returnThis();
    void unsureReturnType();
    void unsureReturnType2();
    void unsureReturnType3();
    void unsureReturnType4();
    void referencedArgument();
    void unsureReferencedArgument();
    void defaultArgument();
    void declareMemberOutOfClass();
    void declareMemberOutOfClass2();
    void declareMemberInClassMethod();
    void thisRedeclaration();
    void implicitArrayDeclaration();
    void implicitReferenceDeclaration();
    void classContextRange();
    void lateClassMembers();
    void list();
    void alternateDocCommentTypeHints();
    void findFunctionArgs();
    void undeclaredPropertyInString();
    void undeclaredVarPropertyInString();
    void upcommingClassInString();
    void namespaces();
    void namespacesNoCurly();
    void namespacesBaseType();
    void useNamespace();
    void useBaseTypeNamespace();
    void useNamespaceBaseTypeAlias();
    void namespaceStaticVar();
    void namespacedCatch();
    void errorRecovery_data();
    void errorRecovery();
    void varStatic();
    void staticNowdoc();
    void curlyVarAfterObj();
    void embeddedHTML_data();
    void embeddedHTML();
    void cases();
    void closureParser();
    void closures();
    void closureEmptyUse();
    void iifeParser();
    void iife();
    void gotoTest();
    void ternary();
    void bug296709();
    void declareFinalMethod();
    void testTodoExtractor();
    void useThisAsArray();
    void wrongUseOfThisAsArray();
    void staticFunctionClassPhp54();
    void functionArgumentUnpacking_data();
    void functionArgumentUnpacking();
    void illegalExpression_data();
    void illegalExpression();
    void printExpression_data();
    void printExpression();
    void simpleExpression_data();
    void simpleExpression();
    void generatorAssignment();
    void generatorClosure();
};

}

#endif
