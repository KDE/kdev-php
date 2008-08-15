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
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/integraltype.h>

#include "phpparsejob.h"


using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestDUChain)

namespace Php
{

TestDUChain::TestDUChain()
{
}


void TestDUChain::testDeclareVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} class B {} $i = new A(); $j = new B(); $i = new B(); $i = 'foo';");

    TopDUContext* top = parse(method, DumpAll);
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

    release(top);
}

void TestDUChain::testDeclareClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo($i) {} protected static function bar() {} private function baz() {} function boo() {} }");

    TopDUContext* top = parse(method, DumpNone);
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
    QCOMPARE(contextClassA->childContexts().count(), 5);
    QCOMPARE(contextClassA->childContexts().first()->localScopeIdentifier(), QualifiedIdentifier("foo"));

    DUContext* contextMethodBodyFoo = contextClassA->childContexts().at(1);
    QCOMPARE(contextMethodBodyFoo->localScopeIdentifier(), QualifiedIdentifier("foo"));
    QCOMPARE(contextMethodBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextMethodBodyFoo->childContexts().count(), 0);
    QVERIFY(contextMethodBodyFoo->importedParentContexts().first().context() ==
                    contextClassA->childContexts().first());

    //foo()
    dec = contextClassA->localDeclarations().at(0);
    ClassFunctionDeclaration* funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
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

    release(top);
}

void TestDUChain::testClassMemberVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public $foo; /** @var A **/ protected $bar; private static $baz; var $boo; }");

    TopDUContext* top = parse(method, DumpNone);
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

    release(top);
}

void TestDUChain::testReturnTypeClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return new A(); } function bar() { $i = new A(); return $i; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
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
    
    release(top);
}

void TestDUChain::testDeclarationReturnType()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return new A(); } $i = foo(); ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);
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
    
    release(top);
}

void TestDUChain::testDeclarationMultipleReturnTypes()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return null; return new A(); return null; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    FunctionType::Ptr fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));

    release(top);
}

void TestDUChain::testDeclarationReturnTypeDocBlock()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { /** @return A **/ function bar() {} } class B {} /** @return A **/ function foo() { return new B(); } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
    QCOMPARE(top->localDeclarations().count(), 3);

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

    release(top);
}

void TestDUChain::testDeclareTypehintFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A $i) { return $i; } ");

    TopDUContext* top = parse(method, DumpNone);

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

    QVERIFY(contextFunctionBodyFoo->importedParentContexts().first().context() ==
                    contextFunctionFoo);

    FunctionType::Ptr fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(StructureType::Ptr::dynamicCast(fType->returnType()));
    QCOMPARE(StructureType::Ptr::dynamicCast(fType->returnType())->qualifiedIdentifier(), QualifiedIdentifier("A"));

    release(top);
}

void TestDUChain::testClassImplementsInterface()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface I { } class A implements I { }");

    TopDUContext* top = parse(method, DumpNone);

    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    //interface I
    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("I"));
    StructureType::Ptr typeI = dec->type<StructureType>();
    QCOMPARE(typeI->qualifiedIdentifier(), QualifiedIdentifier("I"));
    QCOMPARE(typeI->classType(), static_cast<uint>(StructureType::Interface));
    QVERIFY(typeI->declaration(top) == dec);

    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("I"));

    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);


    //class A
    dec = top->localDeclarations().at(1);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("A"));
    StructureType::Ptr typeA = dec->type<StructureType>();
    QCOMPARE(typeA->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(typeA->classType(), static_cast<uint>(StructureType::Class));
    QVERIFY(typeA->declaration(top) == dec);

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("A"));
    //class A imports interface I context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).context() == top->childContexts().at(0));

    QCOMPARE(dec->uses().count(), 0);

    release(top);
}

void TestDUChain::testClassExtends()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { } class B extends A { } ");

    TopDUContext* top = parse(method, DumpNone);

    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    //class A
    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("A"));
    StructureType::Ptr typeA = dec->type<StructureType>();
    QCOMPARE(typeA->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(typeA->classType(), static_cast<uint>(StructureType::Class));
    QVERIFY(typeA->declaration(top) == dec);

    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("A"));

    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);


    //class B
    dec = top->localDeclarations().at(1);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("B"));
    StructureType::Ptr typeB = dec->type<StructureType>();
    QCOMPARE(typeB->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QCOMPARE(typeB->classType(), static_cast<uint>(StructureType::Class));
    QVERIFY(typeB->declaration(top) == dec);

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("B"));
    //class B imports class A context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).context() == top->childContexts().at(0));

    QCOMPARE(dec->uses().count(), 0);

    release(top);
}


void TestDUChain::testStaticMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { static function foo() { return new B(); } } $i = A::foo();");

    TopDUContext* top = parse(method, DumpNone);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));

    release(top);
}

void TestDUChain::testOwnStaticMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { static function foo() { return new B(); } function bar() { $i = self::foo(); $j = A::foo(); } } ");

    TopDUContext* top = parse(method, DumpNone);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().at(1)->childContexts().at(1)->localDeclarations().at(0)
                ->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QCOMPARE(top->childContexts().at(1)->childContexts().at(1)->localDeclarations().at(1)
                ->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));

    release(top);
}
void TestDUChain::testThis()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function x() { return $this; } function y() { return $this->x(); } } ");

    TopDUContext* top = parse(method, DumpNone);

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

    release(top);
}

void TestDUChain::testObjectFunctionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { function x() { return new B(); } function y() { $a = new A(); return $a->x(); } } ");

    TopDUContext* top = parse(method, DumpNone);

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

    release(top);
}

void TestDUChain::testObjectFunctionCall2()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class C {} class B { function c() { return new C(); } } class A { function x() { return new B(); } function y() { $a = new A(); return $a->x()->c(); } } ");

    TopDUContext* top = parse(method, DumpNone);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(2)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    StructureType::Ptr cls = StructureType::Ptr::dynamicCast(fn->returnType());
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier("C"));

    release(top);
}

void TestDUChain::testObjectFunctionCall3()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { function b() { return new B(); } } $i = new A(); $j = $i->b();");

    TopDUContext* top = parse(method, DumpAll);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier("i"));
    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("A"));;
    QCOMPARE(top->localDeclarations().at(3)->qualifiedIdentifier(), QualifiedIdentifier("j"));
    QCOMPARE(top->localDeclarations().at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));;

    release(top);
}

void TestDUChain::testObjectVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public $foo; } $a = new A(); $i = $a->foo;");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(3)->qualifiedIdentifier(), QualifiedIdentifier("i"));
    QCOMPARE(top->localDeclarations().at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));;

    release(top);
}

void TestDUChain::testStaticMemberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public static $foo; } $i = A::$foo;");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier("i"));
    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));;

    release(top);
}
void TestDUChain::testOwnStaticMemberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public static $foo; function bar() { $i = self::$foo; $j = A::$foo; }} ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* barContext = top->childContexts().at(1)->childContexts().at(0);
    QCOMPARE(barContext->localDeclarations().at(0)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));
    QCOMPARE(barContext->localDeclarations().at(1)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("B"));

    release(top);
}

void TestDUChain::testClassConst()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { const FOO = 0; } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("A::FOO")).count(), 1);
    QCOMPARE(top->childContexts().at(0)->localDeclarations().at(0)->qualifiedIdentifier(),
                        QualifiedIdentifier("A::FOO"));

    release(top);
}

void TestDUChain::testDefine()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? define('FOO', 'foo'); function x() { define('BAR', 'bar'); } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("FOO")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier("BAR")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier("FOO")).first()->context(), top);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier("BAR")).first()->context(), top);

    release(top);
}
void TestDUChain::testDefaultFunctionParam()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo($a, $b = false, $c = null) {} ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());
    
    AbstractFunctionDeclaration* fun = dynamic_cast<AbstractFunctionDeclaration*>(top->localDeclarations().first());
    QVERIFY(fun);
    
    QCOMPARE(fun->defaultParametersSize(), 2);
    QCOMPARE(fun->defaultParameters()[0].str(), QString("false"));
    QCOMPARE(fun->defaultParameters()[1].str(), QString("null"));

    release(top);
}

void TestDUChain::testGlobalFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? substr(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());
    
    QCOMPARE(top->importedParentContexts().count(), 1);
    QVERIFY(DUChain::self()->chainForDocument(IndexedString("internalfunctions")));
    QCOMPARE(DUChain::self()->chainForDocument(IndexedString("internalfunctions")), top->importedParentContexts().first().context());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier("substr")).count(), 1);

    release(top);
}

void TestDUChain::testNewObjectFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class Foo { } ");
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = new Foo(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());
    
    QCOMPARE(top->importedParentContexts().count(), 2);
    bool found = false;
    foreach (DUContext::Import import, top->importedParentContexts()) {
        if (import.context() == addTop) {
            found = true;
            break;
        }
    }
    QVERIFY(found);
    
    QCOMPARE(top->localDeclarations().first()->type<StructureType>()->declaration(top),
                addTop->localDeclarations().first());

    release(addTop);
    release(top);
}
}

#include "test_duchain.moc"
