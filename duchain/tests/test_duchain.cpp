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

#include "test_duchain.h"

#include <QtTest/QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/integraltype.h>

#include <kstandarddirs.h>

#include "phpparsejob.h"
#include "../constantdeclaration.h"
#include "../classdeclaration.h"
#include <variabledeclaration.h>


using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestDUChain)

namespace Php
{

TestDUChain::TestDUChain()
{
}

void TestDUChain::testDeclareFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo() {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 1);

    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec);
    QCOMPARE(dec->context(), top);
    QCOMPARE(dec->internalContext(), top->childContexts().at(1));

    QCOMPARE(top->childContexts().at(0)->type(), DUContext::Function);
    QCOMPARE(top->childContexts().at(1)->type(), DUContext::Other);
}

void TestDUChain::testDeclareVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} class B {} $i = new A(); $j = new B(); $i = new B(); $i = 'foo';");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 6);

    //class A
    Declaration* dec = top->localDeclarations().at(0);
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    //$i
    Declaration* decVar = top->localDeclarations().at(2);
    QCOMPARE(decVar->identifier(), Identifier("i"));
    StructureType::Ptr type = decVar->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QVERIFY(type->equals(dec->abstractType().unsafeData()));

    //class B
    dec = top->localDeclarations().at(1);
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 2);

    //$j
    decVar = top->localDeclarations().at(3);
    QCOMPARE(decVar->identifier(), Identifier("j"));
    type = decVar->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QVERIFY(type->equals(dec->abstractType().unsafeData()));

    //$i (2nd)
    decVar = top->localDeclarations().at(4);
    QCOMPARE(decVar->identifier(), Identifier("i"));
    type = decVar->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QVERIFY(type->equals(dec->abstractType().unsafeData()));

    //$i (3rd)
    decVar = top->localDeclarations().at(5);
    QCOMPARE(decVar->identifier(), Identifier("i"));
    QVERIFY(decVar->type<IntegralType>());
}

void TestDUChain::testDeclareClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo($i) {} protected static function bar() {} private function baz() {} function boo() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);

    DUContext* contextClassA = top->childContexts().first();


    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration* dec = top->localDeclarations().first();
    QCOMPARE(dec->kind(), Declaration::Type);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(contextClassA->childContexts().count(), 8);
    QCOMPARE(contextClassA->childContexts().first()->localScopeIdentifier(), QualifiedIdentifier("foo"));

    DUContext* contextMethodBodyFoo = contextClassA->childContexts().at(1);
    QCOMPARE(contextMethodBodyFoo->localScopeIdentifier(), QualifiedIdentifier("foo"));
    QCOMPARE(contextMethodBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextMethodBodyFoo->childContexts().count(), 0);
    QVERIFY(contextMethodBodyFoo->importedParentContexts().first().context(top) ==
                    contextClassA->childContexts().first());

    //foo()
    dec = contextClassA->localDeclarations().at(0);
    ClassFunctionDeclaration* funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->kind(), Declaration::Type);
    QCOMPARE(funDec->identifier(), Identifier("foo"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Public);
    QCOMPARE(funDec->isStatic(), false);

    //bar()
    dec = contextClassA->localDeclarations().at(1);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier("bar"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Protected);
    QCOMPARE(funDec->isStatic(), true);

    //baz()
    dec = contextClassA->localDeclarations().at(2);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier("baz"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Private);
    QCOMPARE(funDec->isStatic(), false);

    //boo()
    dec = contextClassA->localDeclarations().at(3);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier("boo"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Public);
}

void TestDUChain::testClassMemberVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public $foo; /** @var A **/ protected $bar; private static $baz; var $boo; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);

    DUContext* contextClassA = top->childContexts().first();

    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration* dec = top->localDeclarations().first();
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(contextClassA->childContexts().count(), 0);
    QCOMPARE(contextClassA->localDeclarations().count(), 4);

    //$foo
    ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().first());
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier("foo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(!var->abstractType());

    //$bar
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(1));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier("bar"));
    QCOMPARE(var->accessPolicy(), Declaration::Protected);
    QCOMPARE(var->isStatic(), false);
    StructureType::Ptr type = var->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("A"));

    //$baz
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(2));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier("baz"));
    QCOMPARE(var->accessPolicy(), Declaration::Private);
    QCOMPARE(var->isStatic(), true);
    QVERIFY(!var->abstractType());

    //$boo
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(3));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier("boo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(!var->abstractType());
}

void TestDUChain::testReturnTypeClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return new A(); } function bar() { $i = new A(); return $i; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 5);
    QCOMPARE(top->localDeclarations().count(), 3);

    Declaration* dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("foo"));
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    StructureType::Ptr retType = StructureType::Ptr::dynamicCast(functionType->returnType());
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier("A"));

    dec = top->localDeclarations().at(2);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("bar"));
    functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    retType = StructureType::Ptr::dynamicCast(functionType->returnType());
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier("A"));
}

void TestDUChain::testDeclarationReturnType()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return new A(); } $i = foo(); ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
    QCOMPARE(top->localDeclarations().count(), 3);

    Declaration* dec = top->localDeclarations().at(1);
    FunctionType::Ptr fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));

    dec = top->localDeclarations().at(2);
    QCOMPARE(dec->identifier(), Identifier("i"));
    StructureType::Ptr type = dec->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("A"));
}

void TestDUChain::testDeclarationMultipleReturnTypes()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return null; return new A(); return null; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));
}

void TestDUChain::testDeclarationReturnTypeDocBlock()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { /** @return A **/ function bar() {} } class B {} /** @return A **/ function foo() { return new B(); } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //function bar
    Declaration* dec = top->childContexts().at(0)->localDeclarations().at(0);
    FunctionType::Ptr fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));

    //function foo
    dec = top->localDeclarations().at(2);
    fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));
}

void TestDUChain::testDeclarationReturnTypeDocBlockIntegral()
{
    QByteArray method("<? /** @return string **/ function foo() {} /** @return mixed **/ function bar() {} class A { /** @return int **/ function aaa() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //function foo
    FunctionType::Ptr fType = top->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType()));
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType())->dataType() == IntegralType::TypeString);

    //function bar
    fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType()));
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType())->dataType() == IntegralType::TypeMixed);

    //function aaa
    fType = top->childContexts().at(4)->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType()));
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType())->dataType() == IntegralType::TypeInt);
}

void TestDUChain::testDeclareTypehintFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A $i) { return $i; } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
    QCOMPARE(top->localDeclarations().count(), 2);

    Declaration* dec = top->localDeclarations().at(0);
    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    QCOMPARE(top->childContexts().at(0)->localScopeIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(top->childContexts().at(0)->childContexts().count(), 0);

    DUContext* contextFunctionFoo = top->childContexts().at(1);
    QCOMPARE(contextFunctionFoo->localScopeIdentifier(), QualifiedIdentifier("foo"));

    DUContext* contextFunctionBodyFoo = top->childContexts().at(2);
    QCOMPARE(contextFunctionBodyFoo->localScopeIdentifier(), QualifiedIdentifier("foo"));
    QCOMPARE(contextFunctionBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextFunctionBodyFoo->childContexts().count(), 0);

    QVERIFY(contextFunctionBodyFoo->importedParentContexts().first().context(top) ==
                    contextFunctionFoo);

    QVERIFY(top->childContexts().at(1)->localDeclarations().first()->type<StructureType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("A"));

    FunctionType::Ptr fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));
}

void TestDUChain::testDeclareTypehintArrayFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(array $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(IntegralType::Ptr::dynamicCast(fun->arguments().first()));
    QVERIFY(IntegralType::Ptr::dynamicCast(fun->arguments().first())->dataType() == IntegralType::TypeArray);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeArray);
}

void TestDUChain::testClassImplementsInterface()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface I { } class A implements I { }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    //interface I
    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("I"));
    StructureType::Ptr typeI = dec->type<StructureType>();
    QCOMPARE(typeI->qualifiedIdentifier(), QualifiedIdentifier("I"));
    QVERIFY(typeI->declaration(top) == dec);
    ClassDeclaration* classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Interface);

    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("I"));

    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    IndexedType indexedTypeI = classDec->indexedType();

    //class A
    dec = top->localDeclarations().at(1);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("A"));
    StructureType::Ptr typeA = dec->type<StructureType>();
    QCOMPARE(typeA->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QVERIFY(typeA->declaration(top) == dec);
    classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Class);

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("A"));
    //class A imports interface I context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).context(top) == top->childContexts().at(0));
    
    QCOMPARE(classDec->interfacesSize(), 1u);
    QCOMPARE(classDec->interfaces()[0].baseClass, indexedTypeI);
    QVERIFY(classDec->implements(indexedTypeI));
    QCOMPARE(classDec->baseClassesSize(), 0u);

    QCOMPARE(dec->uses().count(), 0);
}

void TestDUChain::testClassExtends()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { } class B extends A { } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    //class A
    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("A"));
    StructureType::Ptr typeA = dec->type<StructureType>();
    QCOMPARE(typeA->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QVERIFY(typeA->declaration(top) == dec);
    ClassDeclaration* classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Class);

    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("A"));

    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    IndexedType indexedTypeA = classDec->indexedType();
  
    //class B
    dec = top->localDeclarations().at(1);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("B"));
    StructureType::Ptr typeB = dec->type<StructureType>();
    QCOMPARE(typeB->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QVERIFY(typeB->declaration(top) == dec);
    classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Class);

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("B"));
    //class B imports class A context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).context(top) == top->childContexts().at(0));

    QCOMPARE(classDec->baseClassesSize(), 1u);
    QCOMPARE(classDec->baseClasses()[0].baseClass, indexedTypeA);
    QVERIFY(classDec->inherits(indexedTypeA));
    QCOMPARE(classDec->interfacesSize(), 0u);

    QCOMPARE(dec->uses().count(), 0);
}


void TestDUChain::testStaticMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { static function foo() { return new B(); } } $i = A::foo();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    StructureType::Ptr type = top->localDeclarations().at(2)->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("B"));
}

void TestDUChain::testOwnStaticMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { static function foo() { return new B(); } function bar() { $i = self::foo(); $j = A::foo(); } } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->childContexts().at(1));
    QVERIFY(top->childContexts().at(1)->localDeclarations().at(0));
    QVERIFY(top->childContexts().at(1)->localDeclarations().at(0)->type<FunctionType>());
    AbstractType::Ptr ret = top->childContexts().at(1)->localDeclarations().at(0)
                ->type<FunctionType>()->returnType();

    QVERIFY(StructureType::Ptr::dynamicCast(ret));
    QCOMPARE(StructureType::Ptr::dynamicCast(ret)->declaration(top), top->localDeclarations().at(0));

    QVERIFY(top->childContexts().at(1)->childContexts().at(1+2));
    QVERIFY(top->childContexts().at(1)->childContexts().at(1+2)->localDeclarations().at(0));
    QVERIFY(top->childContexts().at(1)->childContexts().at(1+2)->localDeclarations().at(0)->type<StructureType>());
    QCOMPARE(top->childContexts().at(1)->childContexts().at(1+2)->localDeclarations().at(0)
                ->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QCOMPARE(top->childContexts().at(1)->childContexts().at(1+2)->localDeclarations().at(1)
                ->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));
}
void TestDUChain::testThis()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function x() { return $this; } function y() { return $this->x(); } } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(0)->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fn);
    StructureType::Ptr cls = StructureType::Ptr::dynamicCast(fn->returnType());
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier("A"));

    fn = top->childContexts().at(0)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    cls = StructureType::Ptr::dynamicCast(fn->returnType());
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier("A"));
}

void TestDUChain::testObjectFunctionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { function x() { return new B(); } function y() { $a = new A(); return $a->x(); } } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(1)->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fn);
    StructureType::Ptr cls = StructureType::Ptr::dynamicCast(fn->returnType());
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier("B"));

    fn = top->childContexts().at(1)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    cls = StructureType::Ptr::dynamicCast(fn->returnType());
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier("B"));
}

void TestDUChain::testObjectFunctionCall2()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class C {} class B { function c() { return new C(); } } class A { function x() { return new B(); } function y() { $a = new A(); return $a->x()->c(); } } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(2)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    StructureType::Ptr cls = StructureType::Ptr::dynamicCast(fn->returnType());
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier("C"));
}

void TestDUChain::testObjectFunctionCall3()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { function b() { return new B(); } } $i = new A(); $j = $i->b();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier("i"));
    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("A"));;
    QCOMPARE(top->localDeclarations().at(3)->qualifiedIdentifier(), QualifiedIdentifier("j"));
    QCOMPARE(top->localDeclarations().at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));;
}

void TestDUChain::testObjectVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public $foo; } $a = new A(); $i = $a->foo;");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(3)->qualifiedIdentifier(), QualifiedIdentifier("i"));
    QCOMPARE(top->localDeclarations().at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));;
}

void TestDUChain::testStaticMemberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public static $foo; } $i = A::$foo;");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier("i"));
    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));;
}
void TestDUChain::testOwnStaticMemberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public static $foo; function bar() { $i = self::$foo; $j = A::$foo; }} ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* barContext = top->childContexts().at(1)->childContexts().at(1);
    QCOMPARE(barContext->localDeclarations().at(0)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QCOMPARE(barContext->localDeclarations().at(1)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));
}

void TestDUChain::testClassConst()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { const FOO = 0; } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("A::FOO")).count(), 1);
    QCOMPARE(top->childContexts().at(0)->localDeclarations().at(0)->qualifiedIdentifier(),
                        QualifiedIdentifier("A::FOO"));
}

void TestDUChain::testDefine()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? define('FOO', 'foo'); function x() { define('BAR', 'bar'); } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("FOO")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier("BAR")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier("FOO")).first()->context(), top);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier("BAR")).first()->context(), top);
    QVERIFY(dynamic_cast<ConstantDeclaration*>(top->localDeclarations().first()));
}
void TestDUChain::testDefaultFunctionParam()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo($a, $b = false, $c = null) {} ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    AbstractFunctionDeclaration* fun = dynamic_cast<AbstractFunctionDeclaration*>(top->localDeclarations().first());
    QVERIFY(fun);
    
    QCOMPARE(fun->defaultParametersSize(), 2);
    QCOMPARE(fun->defaultParameters()[0].str(), QString("false"));
    QCOMPARE(fun->defaultParameters()[1].str(), QString("null"));
}

void TestDUChain::testGlobalFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? substr(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->importedParentContexts().count(), 1);
    QVERIFY(DUChain::self()->chainForDocument(IndexedString("internalfunctions")));
    QCOMPARE(DUChain::self()->chainForDocument(IndexedString("internalfunctions")), top->importedParentContexts().first().context(top));

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("substr")).count(), 1);
}

void TestDUChain::testGlobalVariableFromInternalFunctions()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? substr(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->importedParentContexts().count(), 1);
    QVERIFY(DUChain::self()->chainForDocument(IndexedString("internalfunctions")));
    QCOMPARE(DUChain::self()->chainForDocument(IndexedString("internalfunctions")), top->importedParentContexts().first().context(top));

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("_GET")).count(), 1);
}

void TestDUChain::testNewObjectFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class Foo { } ");
    DUChainReleaser releaseAddTop(addTop);
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = new Foo(); ");
    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(hasImportedParentContext(top, addTop));

    QCOMPARE(top->localDeclarations().first()->type<StructureType>()->declaration(top),
                addTop->localDeclarations().first());
}

void TestDUChain::testUnknownReturnType()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo() {} $a = foo();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //function bar
    Declaration* dec = top->localDeclarations().at(0);
    FunctionType::Ptr fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(IntegralType::Ptr::dynamicCast(fType->returnType()));
    QVERIFY(IntegralType::Ptr::staticCast(fType->returnType())->dataType() == IntegralType::TypeMixed);
}

void TestDUChain::testStaticFunctionCallFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo2.php"), "<?php class Foo { public static function a() {} } ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? Foo::a(); ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::testClassConstantFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo2.php"), "<?php class Foo { const BAR = 0; } ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? Foo::BAR; ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::testGlobalFunctionCallFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo3.php"), "<?php function a() {} ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? a(); ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::testConstantFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo3.php"), "<?php define('A', 0); ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? define('B', 0); A; ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::testSingleton()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public static function self() { static $i; if(!$i) $i = new self(); return $i; }}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->childContexts().first()->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    StructureType::Ptr ret = StructureType::Ptr::dynamicCast(fun->returnType());
    QVERIFY(ret);
    QCOMPARE(ret->declaration(top), top->localDeclarations().first());
}

void TestDUChain::testInternalFunctions()
{
    return; //disabled because it is too slow
    QString fileName = KStandardDirs::locate("data", "kdevphpsupport/phpfunctions.php");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    TopDUContext* top = parse(file.readAll(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
}

void TestDUChain::testTrueFalse()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = true; $b = false; ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
    QVERIFY(top->localDeclarations().at(1)->type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
}

void TestDUChain::testNull()
{
    QByteArray method("<? $a = null; ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeNull);
}

void TestDUChain::testArray()
{
    QByteArray method("<? $a = array(); $b = array(1, 2, 3);");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(top->localDeclarations().at(1)->type<IntegralType>()->dataType() == IntegralType::TypeArray);
}

void TestDUChain::testFunctionDocBlock()
{
    TopDUContext* top = parse("<? /**\n *Foo\n **/\nfunction foo() {} ", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    top = parse("<? /**\n *Bar\n **/\nclass A { /**\n *Foo\n **/\nfunction foo() {} }", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Bar"));
        QCOMPARE(top->childContexts().first()->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    top = parse("<? /**\n *Foo\n **/\ninterface A { }", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    top = parse("<? class A { /**\n *Foo\n **/\npublic $foo; }", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->childContexts().first()->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    top = parse("<? class A { /**\n *Foo\n **/\nconst FOO=0; }", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->childContexts().first()->localDeclarations().first()->comment(), QByteArray("Foo"));
    }
}

void TestDUChain::testVariableDocBlock()
{
    TopDUContext* top = parse("<? /**\n *Foo\n **/\n$a = 0; /**\n *Foo\n **/\nstatic $b;", DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
    QCOMPARE(top->localDeclarations().at(1)->comment(), QByteArray("Foo"));
}

void TestDUChain::testFunctionDocBlockParams()
{
    TopDUContext* top = parse("<? class A {} /**\n * @param\tint\n *\t@param A\n * @param mixed **/\nfunction foo($a, $b, $c, $d) {} ", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        QCOMPARE(top->localDeclarations().at(1)->type<FunctionType>()->arguments().count(), 4);

        AbstractType::Ptr arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(0);
        QVERIFY(IntegralType::Ptr::dynamicCast(arg));
        QVERIFY(IntegralType::Ptr::dynamicCast(arg)->dataType() == IntegralType::TypeInt);
        QVERIFY(top->childContexts().at(1)->localDeclarations().at(0)->type<IntegralType>());
        QVERIFY(top->childContexts().at(1)->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeInt);

        arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(1);
        QVERIFY(StructureType::Ptr::dynamicCast(arg));
        QCOMPARE(StructureType::Ptr::dynamicCast(arg)->declaration(top), top->localDeclarations().at(0));
        QCOMPARE(top->childContexts().at(1)->localDeclarations().at(1)->type<StructureType>()->declaration(top), top->localDeclarations().at(0));

        arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(2);
        QVERIFY(IntegralType::Ptr::dynamicCast(arg));
        QVERIFY(IntegralType::Ptr::dynamicCast(arg)->dataType() == IntegralType::TypeMixed);

        arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(3);
        QVERIFY(IntegralType::Ptr::dynamicCast(arg));
        QVERIFY(IntegralType::Ptr::dynamicCast(arg)->dataType() == IntegralType::TypeMixed);
    }
}

void TestDUChain::testMemberFunctionDocBlockParams()
{
    TopDUContext* top = parse("<? class A { /**\n * @param bool\n * @param A\n * @param array\n **/\nfunction foo($a, $b, $c) {} }", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        QCOMPARE(top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().count(), 3);

        AbstractType::Ptr arg = top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().at(0);
        QVERIFY(IntegralType::Ptr::dynamicCast(arg));
        QVERIFY(IntegralType::Ptr::dynamicCast(arg)->dataType() == IntegralType::TypeBoolean);

        arg = top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().at(1);
        QVERIFY(StructureType::Ptr::dynamicCast(arg));
        QCOMPARE(StructureType::Ptr::dynamicCast(arg)->declaration(top), top->localDeclarations().at(0));

        arg = top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().at(2);
        QVERIFY(IntegralType::Ptr::dynamicCast(arg));
        QVERIFY(IntegralType::Ptr::dynamicCast(arg)->dataType() == IntegralType::TypeArray);
    }
}

void TestDUChain::testForeachLoop()
{
    TopDUContext* top = parse("<? $a = array(1); foreach($a as $k=>$i) { $i; }", DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().count(), 3);
    QCOMPARE(top->localDeclarations().at(1)->qualifiedIdentifier(), QualifiedIdentifier("k"));
    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier("i"));
}

void TestDUChain::testPhp4StyleConstructor()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class Aa { function Aa() { $this->bb(); } } ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().first()->localDeclarations().at(0)->qualifiedIdentifier(), QualifiedIdentifier("Aa::Aa"));
}

void TestDUChain::testFunctionInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function aaa() { function bbb() { } }");
    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(0)->qualifiedIdentifier(), QualifiedIdentifier("aaa"));
}

void TestDUChain::testObjectWithClassName()
{

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class setupPage {} $setupPage = new setupPage; $setupPage->foo();");
    TopDUContext* top = parse(method, DumpNone, "testObjectWithClassName.php");
    DUChainReleaser releaseTop(top);

    QByteArray method2("<? $setupPage = new setupPage; $setupPage->foo();");
    TopDUContext* top2 = parse(method2, DumpNone, "testObjectWithClassName.php");
    DUChainReleaser releaseTop2(top2);
}

void TestDUChain::testLargeNumberOfDeclarations()
{
    TopDUContext* top = new TopDUContext(IndexedString("testurl"), SimpleRange(0, 0, 6000, 0), 0);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    for (int i=0; i < 6000; ++i) {
        SimpleRange newRange(i, 0, i, 1);
        Declaration* dec = new Declaration(newRange, top);
        dec->setIdentifier(Identifier(QString("dec%0").arg(i)));
        dec->setAbstractType(AbstractType::Ptr(0));
    }
}

void TestDUChain::testStaticVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? define('AA', 0); function aaa() { static $foo; static $bar=0; static $baz='a'; static $bam=array(); static $woid=+'1'; static $a=AA; }");
    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().at(1)->localDeclarations().count(), 6);

    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->qualifiedIdentifier(), QualifiedIdentifier("aaa::foo"));
    QVERIFY(top->childContexts().at(1)->localDeclarations().first()->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->type<IntegralType>()->dataType(), (uint)IntegralType::TypeMixed);

    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(1)->qualifiedIdentifier(), QualifiedIdentifier("aaa::bar"));
    QVERIFY(top->childContexts().at(1)->localDeclarations().at(1)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(1)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);

    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier("aaa::baz"));
    QVERIFY(top->childContexts().at(1)->localDeclarations().at(2)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(2)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeString);

    QVERIFY(top->childContexts().at(1)->localDeclarations().at(3)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(3)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeArray);

    QVERIFY(top->childContexts().at(1)->localDeclarations().at(4)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(4)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);

    QVERIFY(top->childContexts().at(1)->localDeclarations().at(5)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(5)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);
}

void TestDUChain::testReturnTypeTwoDeclarations()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo() { $i='a'; $i=0; return $i; } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().at(0);
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    IntegralType::Ptr retType = IntegralType::Ptr::dynamicCast(functionType->returnType());
    QVERIFY(retType);
    QCOMPARE(retType->dataType(), (uint)IntegralType::TypeInt);
}

void TestDUChain::testGlobalVariableNotVisibleInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = 0; function foo() { $a; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(0)->uses().count(), 0);
}

void TestDUChain::testGlobalVariableInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = 0; function foo() { global $a; $a; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(0)->uses().count(), 1);
}

void TestDUChain::testSuperglobalInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $_GET; function foo() { $_GET; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("_GET")).count(), 1);
    Declaration* dec = top->findDeclarations(QualifiedIdentifier("_GET")).first();
    QVERIFY(dynamic_cast<VariableDeclaration*>(dec));
    QVERIFY(static_cast<VariableDeclaration*>(dec)->isSuperglobal());
    QCOMPARE(dec->uses().keys().count(), 1);
    QCOMPARE(dec->uses().values().count(), 1);
    QCOMPARE(dec->uses().values().first().count(), 2);
    QCOMPARE(dec->uses().values().first().first(), SimpleRange(0, 3, 0, 8));
    QCOMPARE(dec->uses().values().first().at(1), SimpleRange(0, 27, 0, 32));
}

void TestDUChain::testReturnWithoutFunction()
{
    //yes, this is possible in php, you then have $a as return value of an include call
    QByteArray method("<? $a = 0; return $a; ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
}

void TestDUChain::testCircularInheritance()
{
    //circular inheritance is not allowed in PHP and should not crash kdevelop
    QByteArray method("<? class a extends b {} class b extends c {} class c extends a {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    
    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->problems().count(), 1);
}

void TestDUChain::testFindDeclarations()
{
    DUChainWriteLocker lock(DUChain::lock());

    TopDUContext* top1 = new TopDUContext(IndexedString("testfile1"), SimpleRange(0, 0, 0, 10), 0);
    DUChainReleaser releaseTop1(top1);
    DUChain::self()->addDocumentChain(top1);
    TopDUContext* top2 = new TopDUContext(IndexedString("testfile2"), SimpleRange(0, 0, 0, 10), 0);
    DUChainReleaser releaseTop2(top2);
    DUChain::self()->addDocumentChain(top2);

    Declaration* declaration = new Declaration(SimpleRange(0, 0, 0, 3), top1);
    declaration->setIdentifier(Identifier("foo"));
    
    QCOMPARE(1, top1->findDeclarations(Identifier("foo")).count());
    QCOMPARE(0, top2->findDeclarations(Identifier("foo")).count());
    top2->addImportedParentContext(top1);
    QCOMPARE(1, top2->findDeclarations(Identifier("foo")).count());
    top2->clearImportedParentContexts();
    QCOMPARE(0, top2->findDeclarations(Identifier("foo")).count());
    top2->addImportedParentContext(top1);
    QCOMPARE(1, top2->findDeclarations(Identifier("foo")).count());
}

}

#include "test_duchain.moc"
