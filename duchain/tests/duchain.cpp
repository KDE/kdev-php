/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "duchain.h"

#include <QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/problem.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/arraytype.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/editor/documentrange.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icompletionsettings.h>

#include "helper.h"

#include "../declarations/classdeclaration.h"
#include "../declarations/classmethoddeclaration.h"
#include "../declarations/functiondeclaration.h"
#include "../declarations/variabledeclaration.h"

#include "../types/structuretype.h"
#include "../types/integraltypeextended.h"

#include <QStandardPaths>

using namespace KDevelop;
using namespace Php;

QTEST_MAIN(Php::TestDUChain)

TestDUChain::TestDUChain()
{
}

void TestDUChain::declareFunction()
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

    // no return means void as return type
    auto ftype = dec->abstractType().dynamicCast<FunctionType>();
    QVERIFY(ftype);
    auto itype = ftype->returnType().dynamicCast<IntegralType>();
    QVERIFY(itype->dataType() == IntegralType::TypeVoid);


    QCOMPARE(top->childContexts().at(0)->type(), DUContext::Function);
    QCOMPARE(top->childContexts().at(1)->type(), DUContext::Other);
}

void TestDUChain::declareBaseTypeFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function string() {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 1);

    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec);
    QCOMPARE(dec->context(), top);
    QCOMPARE(dec->internalContext(), top->childContexts().at(1));

    // no return means void as return type
    auto ftype = dec->abstractType().dynamicCast<FunctionType>();
    QVERIFY(ftype);
    auto itype = ftype->returnType().dynamicCast<IntegralType>();
    QVERIFY(itype->dataType() == IntegralType::TypeVoid);


    QCOMPARE(top->childContexts().at(0)->type(), DUContext::Function);
    QCOMPARE(top->childContexts().at(1)->type(), DUContext::Other);
}

void TestDUChain::declareSemiReservedFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function switch() {}");

    TopDUContext* top = parse(method, DumpNone);
    QVERIFY(!top);
}

void TestDUChain::declareVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} class B {} $i = new A(); $j = new B(); $i = new B(); $i = 'foo';"
                        " $a = substr($i, 0, 1);");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 5);

    //class A
    Declaration* dec = top->localDeclarations().at(0);
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    //$i
    Declaration* decVar = top->localDeclarations().at(2);
    QCOMPARE(decVar->identifier(), Identifier(u"i"));
    qDebug() << decVar->abstractType()->toString();
    UnsureType::Ptr unsureType = decVar->type<UnsureType>();
    QVERIFY(unsureType);
    QCOMPARE(unsureType->typesSize(), 3u);
    // = new A();
    QCOMPARE(unsureType->types()[0].abstractType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QVERIFY(unsureType->types()[0].abstractType()->equals(dec->abstractType().data()));
    // = new B();
    //class B
    dec = top->localDeclarations().at(1);
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 2);
    QCOMPARE(unsureType->types()[1].abstractType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QVERIFY(unsureType->types()[1].abstractType()->equals(dec->abstractType().data()));
    // = 'foo';
    QVERIFY(unsureType->types()[2].abstractType().dynamicCast<IntegralType>());
    QVERIFY(unsureType->types()[2].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    //$j
    decVar = top->localDeclarations().at(3);
    QCOMPARE(decVar->identifier(), Identifier(u"j"));
    StructureType::Ptr classType = decVar->type<StructureType>();
    QVERIFY(classType);
    QCOMPARE(classType->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QVERIFY(classType->equals(dec->abstractType().data()));

    // $a
    decVar = top->localDeclarations().at(4);
    QCOMPARE(decVar->identifier(), Identifier(u"a"));
    QVERIFY(decVar->type<IntegralType>());
}

void TestDUChain::varTypehint()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} /** @var A **/ $i = foo();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //class A
    Declaration* dec = top->localDeclarations().at(0);

    //$i
    Declaration* decVar = top->localDeclarations().at(1);
    QCOMPARE(decVar->identifier(), Identifier(u"i"));
    StructureType::Ptr classType = decVar->type<StructureType>();
    QVERIFY(classType);
    QCOMPARE(classType->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QVERIFY(classType->equals(dec->abstractType().data()));
}

void TestDUChain::declareClass()
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
    QCOMPARE(dec->toString(), QString("class A"));
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    qDebug() << contextClassA->localScopeIdentifier().toString();
    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(contextClassA->childContexts().count(), 8);
    QCOMPARE(contextClassA->childContexts().first()->localScopeIdentifier(), QualifiedIdentifier(u"foo"));

    DUContext* contextMethodBodyFoo = contextClassA->childContexts().at(1);
    QCOMPARE(contextMethodBodyFoo->localScopeIdentifier(), QualifiedIdentifier(u"foo"));
    QCOMPARE(contextMethodBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextMethodBodyFoo->childContexts().count(), 0);
    QVERIFY(contextMethodBodyFoo->importedParentContexts().first().context(top) ==
            contextClassA->childContexts().first());

    //foo()
    dec = contextClassA->localDeclarations().at(0);
    ClassFunctionDeclaration* funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->kind(), Declaration::Type);
    QCOMPARE(funDec->identifier(), Identifier(u"foo"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Public);
    QCOMPARE(funDec->isStatic(), false);

    {
        // no return means void as return type
        auto ftype = dec->abstractType().dynamicCast<FunctionType>();
        QVERIFY(ftype);
        auto itype = ftype->returnType().dynamicCast<IntegralType>();
        QVERIFY(itype->dataType() == IntegralType::TypeVoid);
    }

    //bar()
    dec = contextClassA->localDeclarations().at(1);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier(u"bar"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Protected);
    QCOMPARE(funDec->isStatic(), true);

    //baz()
    dec = contextClassA->localDeclarations().at(2);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier(u"baz"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Private);
    QCOMPARE(funDec->isStatic(), false);

    //boo()
    dec = contextClassA->localDeclarations().at(3);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier(u"boo"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Public);
}

void TestDUChain::declareBaseTypeClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class String {}");

    TopDUContext* top = parse(method, DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->problems().count(), 1);
}

void TestDUChain::declareClassWithSemiReservedMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function switch($i) {} protected static function public() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);

    DUContext* contextClassA = top->childContexts().first();

    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration* dec = top->localDeclarations().first();
    QCOMPARE(dec->kind(), Declaration::Type);
    QCOMPARE(dec->toString(), QString("class A"));
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    qDebug() << contextClassA->localScopeIdentifier().toString();
    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(contextClassA->childContexts().count(), 4);
    QCOMPARE(contextClassA->childContexts().first()->localScopeIdentifier(), QualifiedIdentifier(u"switch"));

    DUContext* contextMethodBodyFoo = contextClassA->childContexts().at(1);
    QCOMPARE(contextMethodBodyFoo->localScopeIdentifier(), QualifiedIdentifier(u"switch"));
    QCOMPARE(contextMethodBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextMethodBodyFoo->childContexts().count(), 0);
    QVERIFY(contextMethodBodyFoo->importedParentContexts().first().context(top) ==
            contextClassA->childContexts().first());

    //switch()
    dec = contextClassA->localDeclarations().at(0);
    ClassFunctionDeclaration* funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->kind(), Declaration::Type);
    QCOMPARE(funDec->identifier(), Identifier(u"switch"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Public);
    QCOMPARE(funDec->isStatic(), false);

    {
        // no return means void as return type
        auto ftype = dec->abstractType().dynamicCast<FunctionType>();
        QVERIFY(ftype);
        auto itype = ftype->returnType().dynamicCast<IntegralType>();
        QVERIFY(itype->dataType() == IntegralType::TypeVoid);
    }

    //public()
    dec = contextClassA->localDeclarations().at(1);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier(u"public"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Protected);
    QCOMPARE(funDec->isStatic(), true);
}

void TestDUChain::declareClassWithBaseTypeMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function string($i) {} protected static function iterable() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);

    DUContext* contextClassA = top->childContexts().first();

    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration* dec = top->localDeclarations().first();
    QCOMPARE(dec->kind(), Declaration::Type);
    QCOMPARE(dec->toString(), QString("class A"));
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    qDebug() << contextClassA->localScopeIdentifier().toString();
    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(contextClassA->childContexts().count(), 4);
    QCOMPARE(contextClassA->childContexts().first()->localScopeIdentifier(), QualifiedIdentifier(u"string"));

    DUContext* contextMethodBodyFoo = contextClassA->childContexts().at(1);
    QCOMPARE(contextMethodBodyFoo->localScopeIdentifier(), QualifiedIdentifier(u"string"));
    QCOMPARE(contextMethodBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextMethodBodyFoo->childContexts().count(), 0);
    QVERIFY(contextMethodBodyFoo->importedParentContexts().first().context(top) ==
            contextClassA->childContexts().first());

    //string()
    dec = contextClassA->localDeclarations().at(0);
    ClassFunctionDeclaration* funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->kind(), Declaration::Type);
    QCOMPARE(funDec->identifier(), Identifier(u"string"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Public);
    QCOMPARE(funDec->isStatic(), false);

    {
        // no return means void as return type
        auto ftype = dec->abstractType().dynamicCast<FunctionType>();
        QVERIFY(ftype);
        auto itype = ftype->returnType().dynamicCast<IntegralType>();
        QVERIFY(itype->dataType() == IntegralType::TypeVoid);
    }

    //iterable()
    dec = contextClassA->localDeclarations().at(1);
    funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->identifier(), Identifier(u"iterable"));
    QCOMPARE(funDec->accessPolicy(), Declaration::Protected);
    QCOMPARE(funDec->isStatic(), true);
}

void TestDUChain::classMemberVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public $foo; /** @var A **/ protected $bar; private static $baz = ''; var $boo = 1; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);

    DUContext* contextClassA = top->childContexts().first();

    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration* dec = top->localDeclarations().first();
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(contextClassA->childContexts().count(), 0);
    QCOMPARE(contextClassA->localDeclarations().count(), 4);

    //$foo
    ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().first());
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"foo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(var->type<IntegralType>());
    QVERIFY(var->type<IntegralType>()->dataType() == IntegralType::TypeNull);

    //$bar
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(1));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"bar"));
    QCOMPARE(var->accessPolicy(), Declaration::Protected);
    QCOMPARE(var->isStatic(), false);
    StructureType::Ptr type = var->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    //$baz
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(2));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"baz"));
    QCOMPARE(var->accessPolicy(), Declaration::Private);
    QCOMPARE(var->isStatic(), true);
    QVERIFY(var->type<IntegralType>());
    QVERIFY(var->type<IntegralType>()->dataType() == IntegralType::TypeString);

    //$boo
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(3));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"boo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(var->type<IntegralType>());
    QVERIFY(var->type<IntegralType>()->dataType() == IntegralType::TypeInt);
}

void TestDUChain::classMemberVarTypehint()
{
    //Note: in practice, Traversable is defined by php, but this interface is not loaded in this test, so define it ourselves
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface Traversable { } class A { public iterable $foo; protected A $bar; private static ?string $baz; public int $boo = 1; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);

    DUContext* contextClassA = top->childContexts().at(1);

    QCOMPARE(top->localDeclarations().count(), 2);
    Declaration* dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassA);

    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(contextClassA->childContexts().count(), 0);
    QCOMPARE(contextClassA->localDeclarations().count(), 4);

    TypePtr<UnsureType> ut;

    //$foo
    ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().first());
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"foo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(var->type<UnsureType>());

    ut = var->type<UnsureType>();
    QVERIFY(ut);
    QCOMPARE(2u, ut->typesSize());

    QVERIFY(ut->types()[0].type<IntegralType>());
    QVERIFY(ut->types()[0].type<IntegralType>()->dataType() == IntegralType::TypeArray);

    QVERIFY(ut->types()[1].type<StructureType>());
    QVERIFY(ut->types()[1].type<StructureType>()->declaration(top));
    QCOMPARE(ut->types()[1].type<StructureType>()->declaration(top)->qualifiedIdentifier(), QualifiedIdentifier(u"traversable"));

    //$bar
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(1));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"bar"));
    QCOMPARE(var->accessPolicy(), Declaration::Protected);
    QCOMPARE(var->isStatic(), false);
    StructureType::Ptr type = var->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    //$baz
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(2));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"baz"));
    QCOMPARE(var->accessPolicy(), Declaration::Private);
    QCOMPARE(var->isStatic(), true);
    QVERIFY(var->type<UnsureType>());
    ut = var->type<UnsureType>();
    QVERIFY(ut);
    QCOMPARE(2u, ut->typesSize());

    QVERIFY(ut->types()[0].type<IntegralType>());
    QVERIFY(ut->types()[0].type<IntegralType>()->dataType() == IntegralType::TypeString);

    QVERIFY(ut->types()[1].type<IntegralType>());
    QVERIFY(ut->types()[1].type<IntegralType>()->dataType() == IntegralType::TypeNull);

    //$boo
    var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(3));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"boo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(var->type<IntegralType>());
    QVERIFY(var->type<IntegralType>()->dataType() == IntegralType::TypeInt);
}

void TestDUChain::classMemberVarAfterUse()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<?php class B { function x() { $this->a = 1; } public $a = 1; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);
    QVERIFY(top->problems().isEmpty());

    DUContext* contextClassB = top->childContexts().first();

    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration* dec = top->localDeclarations().first();
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QCOMPARE(dec->isDefinition(), true);
    QCOMPARE(dec->logicalInternalContext(top), contextClassB);

    QCOMPARE(contextClassB->localScopeIdentifier(), QualifiedIdentifier(u"b"));
    QCOMPARE(contextClassB->childContexts().count(), 2);
    QCOMPARE(contextClassB->localDeclarations().count(), 2);

    //$foo
    ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassB->localDeclarations().at(1));
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"a"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    QVERIFY(var->type<IntegralType>());
    QVERIFY(var->type<IntegralType>()->dataType() == IntegralType::TypeInt);
    QVERIFY(var->range() == RangeInRevision(0, 54, 0, 56));
}

void TestDUChain::classMemberVarDocBlockType()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? namespace Test { class A {} }\n"
                      "namespace Test2 { class B { /** @var \\Test\\A **/ public $foo; } }\n"
    );

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);

    DUContext* contextClassA = top->childContexts().at(0)->childContexts().first();
    DUContext* contextClassB = top->childContexts().at(1)->childContexts().first();

    QCOMPARE(top->localDeclarations().count(), 2);
    Declaration* dec = top->childContexts().first()->localDeclarations().first();
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"test::a"));
    QCOMPARE(dec->isDefinition(), true);

    QCOMPARE(contextClassA->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(contextClassA->childContexts().count(), 0);
    QCOMPARE(contextClassA->localDeclarations().count(), 0);

    QCOMPARE(contextClassB->localScopeIdentifier(), QualifiedIdentifier(u"b"));
    QCOMPARE(contextClassB->childContexts().count(), 0);
    QCOMPARE(contextClassB->localDeclarations().count(), 1);

    //$foo
    ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassB->localDeclarations().first());
    QVERIFY(var);
    QCOMPARE(var->identifier(), Identifier(u"foo"));
    QCOMPARE(var->accessPolicy(), Declaration::Public);
    QCOMPARE(var->isStatic(), false);
    StructureType::Ptr type = var->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier(u"test::a"));
}

void TestDUChain::returnTypeGenerator_data()
{
    QTest::addColumn<QString>("code");

    //Note: in practice, Generator is defined by php, but this class is not loaded in this test, so define it ourselves
    QTest::newRow("simple yield expression") << QStringLiteral("<? class Generator {} function foo() { yield 1; }\n");
    QTest::newRow("yield assignment expression") << QStringLiteral("<? class Generator {} function foo() { yield $a = 1; }\n");
    QTest::newRow("yield null-coalesce expression") << QStringLiteral("<? class Generator {} function foo() { yield ?? 1; }\n");
    QTest::newRow("yield boolean expression") << QStringLiteral("<? class Generator {} function foo() { yield || 1; }\n");
    QTest::newRow("yield additive expression") << QStringLiteral("<? class Generator {} function foo() { yield + 1; }\n");
    QTest::newRow("yield multiplicative expression") << QStringLiteral("<? class Generator {} function foo() { yield * 2; }\n");
    QTest::newRow("yield relational expression") << QStringLiteral("<? class Generator {} function foo() { yield > 1; }\n");
    QTest::newRow("yield equality expression") << QStringLiteral("<? class Generator {} function foo() { yield == 1; }\n");
    QTest::newRow("yield shift expression") << QStringLiteral("<? class Generator {} function foo() { yield >> 1; }\n");
    QTest::newRow("yield bit expression") << QStringLiteral("<? class Generator {} function foo() { yield | 1; }\n");
    QTest::newRow("multiple yield expression") << QStringLiteral("<? class Generator {} function foo() { yield 1 || yield; }\n");
    QTest::newRow("yield key/value expression") << QStringLiteral("<? class Generator {} function foo() { yield 'key' => 'value'; }\n");
}

void TestDUChain::returnTypeGenerator()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
    QCOMPARE(top->localDeclarations().count(), 2);

    Declaration* dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"foo"));
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    auto retType = functionType->returnType().dynamicCast<StructureType>();
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier(u"generator"));
}

void TestDUChain::returnTypeGeneratorDelegation()
{
    //Note: in practice, Generator is defined by php, but this class is not loaded in this test, so define it ourselves
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class Generator {} function foo() { yield 1; } function bar() { yield from foo(); }\n");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 5);
    QCOMPARE(top->localDeclarations().count(), 3);

    Declaration* dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"foo"));
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    auto retType = functionType->returnType().dynamicCast<StructureType>();
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier(u"generator"));

    dec = top->localDeclarations().at(2);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"bar"));
    functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    retType = functionType->returnType().dynamicCast<StructureType>();
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier(u"generator"));
}

void TestDUChain::returnTypeClass()
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
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"foo"));
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    auto retType = functionType->returnType().dynamicCast<StructureType>();
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    dec = top->localDeclarations().at(2);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"bar"));
    functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    retType = functionType->returnType().dynamicCast<StructureType>();
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestDUChain::declarationReturnType()
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
    QVERIFY(fType->returnType().dynamicCast<StructureType>());
    QCOMPARE(fType->returnType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    dec = top->localDeclarations().at(2);
    QCOMPARE(dec->identifier(), Identifier(u"i"));
    StructureType::Ptr type = dec->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestDUChain::declarationReturnTypeInRecursingFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} /** @return A **/ function foo() { $i = foo(); } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList< Declaration* > decs = top->childContexts().last()->findDeclarations(Identifier(QStringLiteral("i")));
    QCOMPARE(decs.size(), 1);
    Declaration* dec = decs.first();
    StructureType::Ptr type = dec->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestDUChain::declarationMultipleReturnTypes()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo() { return null; return new A(); return null; }\n"
                      "function bar() { return 1; return 2; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    qDebug() << fType->toString();
    auto ut = fType->returnType().dynamicCast<UnsureType>();
    QVERIFY(ut);
    QCOMPARE(2u, ut->typesSize());

    ///TODO: why are the types not in the correct order, i.e. null, A
    QVERIFY(ut->types()[0].type<StructureType>());
    QVERIFY(ut->types()[0].type<StructureType>()->declaration(top));
    QCOMPARE(ut->types()[0].type<StructureType>()->declaration(top)->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    QVERIFY(ut->types()[1].type<IntegralType>());
    QVERIFY(ut->types()[1].type<IntegralType>()->dataType() == IntegralType::TypeNull);

    fType = top->localDeclarations().at(2)->type<FunctionType>();
    QVERIFY(fType);
    qDebug() << fType->toString();
    QVERIFY(fType->returnType().dynamicCast<IntegralType>());
    QVERIFY(fType->returnType().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
}

void TestDUChain::returnTypeViaMember()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class a { /** @return a **/ function fa() {} }\n"
                      "class b { /** @var a **/ static $astatic; /** @var a **/ var $anormal;\n"
                      "  function fb1($param) { $i = self::$astatic->fa($param); }\n"
                      "  function fb2($param) { $i = $this->anormal->fa($param); } }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVector<Declaration*> decs = top->localDeclarations();
    QCOMPARE(decs.size(), 2);

    ClassDeclaration* aDec = dynamic_cast<ClassDeclaration*>(decs.first());
    QVERIFY(aDec);

    ClassDeclaration* bDec = dynamic_cast<ClassDeclaration*>(decs.last());
    QVERIFY(bDec);
    QCOMPARE(bDec->logicalInternalContext(top)->localDeclarations().size(), 4);

    typedef QPair<QString, QString> idPair;
    foreach ( const idPair & pair, QList< idPair >()
                                        << qMakePair(QString("fb1"), QString("astatic"))
                                        << qMakePair(QString("fb2"), QString("anormal")) )
    {
        qDebug() << pair.first << pair.second;
        ClassMethodDeclaration* fDec = dynamic_cast<ClassMethodDeclaration*>(
            bDec->logicalInternalContext(top)->findDeclarations(Identifier(pair.first)).first()
        );
        QVERIFY(fDec);

        ClassMemberDeclaration* mDec = dynamic_cast<ClassMemberDeclaration*>(
            bDec->logicalInternalContext(top)->findDeclarations(Identifier(pair.second)).first()
        );
        QVERIFY(mDec);
        QVERIFY(mDec->type<StructureType>());
        QCOMPARE(mDec->type<StructureType>()->declaration(top), aDec);

        QCOMPARE(fDec->logicalInternalContext(top)->localDeclarations().size(), 1);
        Declaration* iDec = fDec->logicalInternalContext(top)->localDeclarations().first();
        QCOMPARE(iDec->identifier().toString(), QString("i"));
        QVERIFY(iDec->type<StructureType>());
        QCOMPARE(iDec->type<StructureType>()->declaration(top), aDec);
    }
}

void TestDUChain::declarationReturnTypeDocBlock()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { /** @return A **/ function bar() {} } "
                      "   class B {} "
                      "/** @return A **/ function foo() { return new B(); } "
                      "/** @return object **/ function bar() {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //function bar
    Declaration* dec = top->childContexts().at(0)->localDeclarations().at(0);
    FunctionType::Ptr fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<StructureType>());
    QCOMPARE(fType->returnType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    //function foo
    dec = top->localDeclarations().at(2);
    fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<StructureType>());
    QCOMPARE(fType->returnType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    //function bar
    dec = top->localDeclarations().at(3);
    fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<IntegralTypeExtended>());
    QVERIFY(fType->returnType().staticCast<IntegralTypeExtended>()->dataType() == IntegralTypeExtended::TypeObject);

    //test hint in internal functions file of a type that is added later on
    // function
    QList<Declaration*> decs = top->findDeclarations(Identifier(QStringLiteral("should_return_exception")));
    QCOMPARE(decs.size(), 1);
    dec = decs.first();
    fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<StructureType>());
    QCOMPARE(fType->returnType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"exception"));
    // method
    decs = top->findDeclarations(Identifier(QStringLiteral("internal_test_class")));
    QCOMPARE(decs.size(), 1);
    ClassDeclaration* cdec = dynamic_cast<ClassDeclaration*>(decs.first());
    QVERIFY(cdec);
    decs = cdec->logicalInternalContext(top)->findDeclarations(Identifier(QStringLiteral("should_return_exception")));
    QCOMPARE(decs.size(), 1);
    dec = decs.first();
    fType = dec->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<StructureType>());
    QCOMPARE(fType->returnType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"exception"));
}

void TestDUChain::declarationReturnTypeDocBlockIntegral()
{
    QByteArray method("<? /** @return string **/ function foo() {} /** @return mixed **/ function bar() {} class A { /** @return int **/ function aaa() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //function foo
    FunctionType::Ptr fType = top->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<IntegralType>());
    QVERIFY(fType->returnType().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    //function bar
    fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<IntegralType>());
    QVERIFY(fType->returnType().staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed);

    //function aaa
    fType = top->childContexts().at(4)->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<IntegralType>());
    QVERIFY(fType->returnType().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
}

void TestDUChain::declarationReturnTypeClassChain()
{
    QByteArray method("<? class A { /** @return this **/ function a() {} /** @return self **/ function b() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    // class a
    DUContext* ctx = top->childContexts().first();
    QCOMPARE(ctx->type(), DUContext::Class);
    QVERIFY(ctx->owner());
    QVERIFY(ctx->owner()->abstractType().dynamicCast<StructureType>());

    //function a
    // FIXME
    QEXPECT_FAIL("", "This test fails after porting the plugin to KF5.", Abort);
    QVERIFY(/* func a (this) */ ctx->localDeclarations().at(0)->type<FunctionType>().data() == ctx->owner()->abstractType().data());
    QVERIFY(/* func b (self) */ ctx->localDeclarations().at(1)->type<FunctionType>().data() == ctx->owner()->abstractType().data());
}

void TestDUChain::declarationReturnTypeTypehint()
{
    //Typehint preferred over phpdoc preferred over inferred type
    QByteArray method("<? /** @return string **/ function foo(): bool { return 5; }\n"
                      "/** @return string **/ function foo(): int { return 5.5; }\n"
                      "/** @return string **/ function foo(): float { return 5; }\n"
                      "/** @return int **/ function foo(): string { return 5.5; }\n"
                      "/** @return int **/ function foo(): mixed { return 5.5; }\n");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 10);
    QCOMPARE(top->localDeclarations().count(), 5);

    FunctionType::Ptr fun = top->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fun);
    auto returnType = fun->returnType().dynamicCast<IntegralType>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralType::TypeBoolean);

    fun = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fun);
    returnType = fun->returnType().dynamicCast<IntegralType>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralType::TypeInt);

    fun = top->localDeclarations().at(2)->type<FunctionType>();
    QVERIFY(fun);
    returnType = fun->returnType().dynamicCast<IntegralType>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralType::TypeFloat);

    fun = top->localDeclarations().at(3)->type<FunctionType>();
    QVERIFY(fun);
    returnType = fun->returnType().dynamicCast<IntegralType>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralType::TypeString);

    fun = top->localDeclarations().at(4)->type<FunctionType>();
    QVERIFY(fun);
    returnType = fun->returnType().dynamicCast<IntegralType>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralType::TypeMixed);
}

void TestDUChain::declarationReturnTypeTypehintVoid()
{
    //Typehint preferred over phpdoc preferred over inferred type
    QByteArray method("<? /** @return string **/ function foo(): void { return 5; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 1);

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    auto returnType = fun->returnType().dynamicCast<IntegralType>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralType::TypeVoid);
}

void TestDUChain::declarationReturnTypeTypehintObject()
{
    //Typehint preferred over phpdoc preferred over inferred type
    QByteArray method("<? /** @return string **/ function foo(): object { return new stdClass(); }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 1);

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    auto returnType = fun->returnType().dynamicCast<IntegralTypeExtended>();
    QVERIFY(returnType);
    QVERIFY(returnType->dataType() == IntegralTypeExtended::TypeObject);
}

void TestDUChain::declarationReturnTypeTypehintUnion()
{
    //                 0         1         2         3         4         5
    //                 012345678901234567890123456789012345678901234567890
    QByteArray method("<? function foo(): string|int|float|bool { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    auto returnType = fun->returnType().dynamicCast<UnsureType>();
    QVERIFY(returnType);

    QCOMPARE(returnType->typesSize(), 4u);
    QVERIFY(returnType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(returnType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);
    QVERIFY(returnType->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(returnType->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
    QVERIFY(returnType->types()[2].abstractType().dynamicCast<IntegralType>());
    QVERIFY(returnType->types()[2].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeFloat);
    QVERIFY(returnType->types()[3].abstractType().dynamicCast<IntegralType>());
    QVERIFY(returnType->types()[3].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);
}

void TestDUChain::declareTypehintFunction()
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

    QCOMPARE(top->childContexts().at(0)->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    QCOMPARE(top->childContexts().at(0)->childContexts().count(), 0);

    DUContext* contextFunctionFoo = top->childContexts().at(1);
    QCOMPARE(contextFunctionFoo->localScopeIdentifier(), QualifiedIdentifier(u"foo"));

    DUContext* contextFunctionBodyFoo = top->childContexts().at(2);
    QCOMPARE(contextFunctionBodyFoo->localScopeIdentifier(), QualifiedIdentifier(u"foo"));
    QCOMPARE(contextFunctionBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextFunctionBodyFoo->childContexts().count(), 0);

    QVERIFY(contextFunctionBodyFoo->importedParentContexts().first().context(top) ==
            contextFunctionFoo);

    QVERIFY(top->childContexts().at(1)->localDeclarations().first()->type<StructureType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    FunctionType::Ptr fType = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fType);
    QVERIFY(fType->returnType().dynamicCast<StructureType>());
    QCOMPARE(fType->returnType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestDUChain::declareVariadicFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(...$i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    AbstractType::Ptr arg = fun->arguments().first();
    QVERIFY(arg);
    QVERIFY(arg.dynamicCast<KDevelop::ArrayType>());

    AbstractType::Ptr typehint = arg.staticCast<KDevelop::ArrayType>()->elementType();
    QVERIFY(typehint);
    QVERIFY(typehint.dynamicCast<IntegralType>());
    QVERIFY(typehint.staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed);
}

void TestDUChain::declareTypehintVariadicFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A ...$i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    auto fun = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    AbstractType::Ptr arg = fun->arguments().first();
    QVERIFY(arg);
    QVERIFY(arg.dynamicCast<KDevelop::ArrayType>());

    auto typehint = arg.staticCast<KDevelop::ArrayType>()->elementType();
    QVERIFY(typehint);
    QCOMPARE(typehint->toString(), QStringLiteral("A"));
}

void TestDUChain::declareTypehintObjectFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(object $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralTypeExtended::TypeObject);

    IntegralTypeExtended::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralTypeExtended>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralTypeExtended::TypeObject);
}

void TestDUChain::declareTypehintObjectFunctionWithNullDefault()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(?object $i = NULL) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<UnsureType>());

    auto argType = fun->arguments().first().dynamicCast<UnsureType>();
    QVERIFY(argType);
    QCOMPARE(argType->typesSize(), 2u);
    QVERIFY(argType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralTypeExtended::TypeObject);
    QVERIFY(argType->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeNull);
}

void TestDUChain::declareTypehintObjectFunctionWithInvalidDefaultValue()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(object $i = '') { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->problems().isEmpty());
}

void TestDUChain::declaredTypehintOverridesDetectedValue()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(int $i = false) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());

    IntegralType::Ptr type = fun->arguments().first().dynamicCast<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeInt);
}

void TestDUChain::declareTypehintArrayFunction()
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
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeArray);
}

void TestDUChain::declareTypehintCallableFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(callable $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralTypeExtended>());
    QVERIFY(fun->arguments().first().staticCast<IntegralTypeExtended>()->dataType() == IntegralTypeExtended::TypeCallable);

    IntegralTypeExtended::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralTypeExtended>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralTypeExtended::TypeCallable);
}

void Php::TestDUChain::functionWithCallableAndFunctionReturn()
{
    QByteArray method("<? function foo(callable $i) { return $i; return function () {}; } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralTypeExtended>());
    QVERIFY(fun->arguments().first().staticCast<IntegralTypeExtended>()->dataType() == IntegralTypeExtended::TypeCallable);

    auto retType = fun->returnType().dynamicCast<IntegralTypeExtended>();
    QVERIFY(retType);
    QVERIFY(retType->dataType() == IntegralTypeExtended::TypeCallable);
}

void TestDUChain::declareTypehintIterableFunction()
{
    //Note: in practice, Traversable is defined by php, but this interface is not loaded in this test, so define it ourselves
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? interface Traversable { } function foo(iterable $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().count(), 2);
    FunctionType::Ptr fun = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    auto argType = fun->arguments().first().dynamicCast<UnsureType>();
    QVERIFY(argType);
    QCOMPARE(argType->typesSize(), 2u);
    QVERIFY(argType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(argType->types()[1].abstractType().dynamicCast<StructureType>());
    QCOMPARE(argType->types()[1].abstractType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"traversable"));
}

void TestDUChain::declareTypehintBoolFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(bool $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeBoolean);
}

void TestDUChain::declareTypehintFloatFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(float $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeFloat);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeFloat);
}

void TestDUChain::declareTypehintIntFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(int $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeInt);
}

void TestDUChain::declareTypehintStringFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(string $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeString);
}

void TestDUChain::declareTypehintMixedFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(mixed $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeMixed);
}

void TestDUChain::declareNullableTypehintArrayFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(?array $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    auto argType = fun->arguments().first().dynamicCast<UnsureType>();
    QVERIFY(argType);
    QCOMPARE(argType->typesSize(), 2u);
    QVERIFY(argType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(argType->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeNull);

    UnsureType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<UnsureType>();
    QVERIFY(type);
    QCOMPARE(type->typesSize(), 2u);
    QVERIFY(type->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(type->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(type->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(type->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeNull);
}

void TestDUChain::declareTypehintWithPhpdocFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? /**\n * @param string $i\n */ function foo(int $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeInt);
}

void TestDUChain::declareNullableTypehintMixedFunction()
{
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? function foo(?UnknownClass $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);
    QVERIFY(fun->arguments().first().dynamicCast<IntegralType>());
    QVERIFY(fun->arguments().first().staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed);

    IntegralType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeMixed);
}

void TestDUChain::declareTypehintNullableIterableFunction()
{
    //Note: in practice, Traversable is defined by php, but this interface is not loaded in this test, so define it ourselves
    //                 0         1         2         3
    //                 0123456789012345678901234567890123
    QByteArray method("<? interface Traversable { } function foo(?iterable $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().count(), 2);
    FunctionType::Ptr fun = top->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    auto argType = fun->arguments().first().dynamicCast<UnsureType>();
    QVERIFY(argType);
    QCOMPARE(argType->typesSize(), 3u);
    QVERIFY(argType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(argType->types()[1].abstractType().dynamicCast<StructureType>());
    QCOMPARE(argType->types()[1].abstractType().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"traversable"));
    QVERIFY(argType->types()[2].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[2].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeNull);
}

void TestDUChain::declareTypehintUnionFunction()
{
    //                 0         1         2         3         4         5
    //                 012345678901234567890123456789012345678901234567890
    QByteArray method("<? function foo(string|int|float|bool $i) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    auto argType = fun->arguments().first().dynamicCast<UnsureType>();
    QVERIFY(argType);
    QCOMPARE(argType->typesSize(), 4u);
    QVERIFY(argType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);
    QVERIFY(argType->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
    QVERIFY(argType->types()[2].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[2].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeFloat);
    QVERIFY(argType->types()[3].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[3].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);
}

void TestDUChain::classImplementsInterface()
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
    QCOMPARE(dec->identifier(), Identifier(u"i"));
    QCOMPARE(dec->toString(), QString("interface I"));
    StructureType::Ptr typeI = dec->type<StructureType>();
    QCOMPARE(typeI->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QVERIFY(typeI->declaration(top) == dec);
    ClassDeclaration* classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Interface);

    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier(u"i"));

    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    IndexedType indexedTypeI = classDec->indexedType();

    //class A
    dec = top->localDeclarations().at(1);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier(u"a"));
    StructureType::Ptr typeA = dec->type<StructureType>();
    QCOMPARE(typeA->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QVERIFY(typeA->declaration(top) == dec);
    classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Class);

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier(u"a"));
    //class A imports interface I context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).context(top) == top->childContexts().at(0));

    QCOMPARE(classDec->baseClassesSize(), 1u);
    QCOMPARE(classDec->baseClasses()[0].baseClass, indexedTypeI);

    QCOMPARE(dec->uses().count(), 0);
}

void TestDUChain::classExtends()
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
    QCOMPARE(dec->identifier(), Identifier(u"a"));
    StructureType::Ptr typeA = dec->type<StructureType>();
    QCOMPARE(typeA->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
    QVERIFY(typeA->declaration(top) == dec);
    ClassDeclaration* classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Class);

    QCOMPARE(dec->internalContext(), top->childContexts().at(0));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier(u"a"));

    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);

    IndexedType indexedTypeA = classDec->indexedType();

    //class B
    dec = top->localDeclarations().at(1);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier(u"b"));
    StructureType::Ptr typeB = dec->type<StructureType>();
    QCOMPARE(typeB->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QVERIFY(typeB->declaration(top) == dec);
    classDec = dynamic_cast<ClassDeclaration*>(dec);
    QVERIFY(classDec);
    QCOMPARE(classDec->classType(), ClassDeclarationData::Class);

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier(u"b"));
    //class B imports class A context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).context(top) == top->childContexts().at(0));

    QCOMPARE(classDec->baseClassesSize(), 1u);
    QCOMPARE(classDec->baseClasses()[0].baseClass, indexedTypeA);

    QCOMPARE(dec->uses().count(), 0);
}


void TestDUChain::staticMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { static function foo() { return new B(); } } $i = A::foo();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    StructureType::Ptr type = top->localDeclarations().at(2)->type<StructureType>();
    QVERIFY(type);
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
}

void TestDUChain::ownStaticMethod()
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

    QVERIFY(ret.dynamicCast<StructureType>());
    QCOMPARE(ret.staticCast<StructureType>()->declaration(top), top->localDeclarations().at(0));

    QVERIFY(top->childContexts().at(1)->childContexts().at(1 + 2));
    QVERIFY(top->childContexts().at(1)->childContexts().at(1 + 2)->localDeclarations().at(0));
    QVERIFY(top->childContexts().at(1)->childContexts().at(1 + 2)->localDeclarations().at(0)->type<StructureType>());
    QCOMPARE(top->childContexts().at(1)->childContexts().at(1 + 2)->localDeclarations().at(0)
             ->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QCOMPARE(top->childContexts().at(1)->childContexts().at(1 + 2)->localDeclarations().at(1)
             ->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
}
void TestDUChain::thisVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function x() { return $this; } function y() { return $this->x(); } } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(0)->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fn);
    auto cls = fn->returnType().dynamicCast<StructureType>();
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier(u"a"));

    fn = top->childContexts().at(0)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    cls = fn->returnType().dynamicCast<StructureType>();
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestDUChain::objectFunctionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { function x() { return new B(); } function y() { $a = new A(); return $a->x(); } } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(1)->localDeclarations().at(0)->type<FunctionType>();
    QVERIFY(fn);
    auto cls = fn->returnType().dynamicCast<StructureType>();
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier(u"b"));

    fn = top->childContexts().at(1)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    cls = fn->returnType().dynamicCast<StructureType>();
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
}

void TestDUChain::objectFunctionCall2()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class C {} class B { function c() { return new C(); } } class A { function x() { return new B(); } function y() { $a = new A(); return $a->x()->c(); } } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().at(2)->localDeclarations().at(1)->type<FunctionType>();
    QVERIFY(fn);
    auto cls = fn->returnType().dynamicCast<StructureType>();
    QVERIFY(cls);
    QCOMPARE(cls->qualifiedIdentifier(), QualifiedIdentifier(u"c"));
}

void TestDUChain::objectFunctionCall3()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { function b() { return new B(); } } $i = new A(); $j = $i->b();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));;
    QCOMPARE(top->localDeclarations().at(3)->qualifiedIdentifier(), QualifiedIdentifier(u"j"));
    QCOMPARE(top->localDeclarations().at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));;
}

void TestDUChain::objectVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public $foo; } $a = new A(); $i = $a->foo;");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(3)->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QCOMPARE(top->localDeclarations().at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));;
}

void TestDUChain::staticMemberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public static $foo; } $i = A::$foo;");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QCOMPARE(top->localDeclarations().at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));;
}
void TestDUChain::ownStaticMemberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B {} class A { /** @var B **/ public static $foo; function bar() { $i = self::$foo; $j = A::$foo; }} ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* barContext = top->childContexts().at(1)->childContexts().at(1);
    QCOMPARE(barContext->localDeclarations().at(0)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QCOMPARE(barContext->localDeclarations().at(1)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
}

void TestDUChain::classConst_data()
{
    QTest::addColumn<QString>("classBody");
    QTest::addColumn<int>("problems");

    QTest::newRow("int") << "const C = 1;" << 0;
    QTest::newRow("string") << "const C = 'asdf';" << 0;
    QTest::newRow("float") << "const C = 0.5;" << 0;
    QTest::newRow("bool") << "const C = true;" << 0;
    QTest::newRow("selfConst") << "const C2 = 1; const C = self::C2;" << 0;
    QTest::newRow("parentConst") << "const C = parent::P;" << 0;
    QTest::newRow("null") << "const C = null;" << 0;
    QTest::newRow("array") << "const C = array();" << 0;
    QTest::newRow("expression") << "const C = 'foo' . 'foo';" << 0;
}

void TestDUChain::classConst()
{
    QFETCH(QString, classBody);
    QFETCH(int, problems);

    QString fullClass("<? class B { const P = 1; } class A extends B { " + classBody + " } ");

    TopDUContext* top = parse(fullClass.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->problems().count(), problems);

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::C")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::C")).first()->context(), top->childContexts().last());
}

void TestDUChain::classConstWithTypeHint()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { /**\n* @var integer\n**/\nconst C = 1; } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().count(), 1);
    QCOMPARE(top->problems().count(), 0);

    QList< Declaration* > decs = top->findDeclarations(QualifiedIdentifier(u"a::C"));
    QCOMPARE(decs.count(), 1);
    QCOMPARE(decs.first()->context(), top->childContexts().last());

    auto type = decs.first()->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QCOMPARE(type->dataType(), IntegralType::TypeInt);
    QVERIFY(type->modifiers() & AbstractType::ConstModifier);
}

void TestDUChain::classConstVisibility()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public const B = 1; protected const C = 1; private const D = 1; } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().count(), 1);
    QCOMPARE(top->problems().count(), 0);

    QList< Declaration* > decs = top->findDeclarations(QualifiedIdentifier(u"a::B"));
    QCOMPARE(decs.count(), 1);
    QCOMPARE(decs.first()->context(), top->childContexts().last());

    auto type = decs.first()->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QCOMPARE(type->dataType(), IntegralType::TypeInt);
    QVERIFY(type->modifiers() & AbstractType::ConstModifier);

    ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec->accessPolicy() == Declaration::Public);

    decs = top->findDeclarations(QualifiedIdentifier(u"a::C"));
    QCOMPARE(decs.count(), 1);
    QCOMPARE(decs.first()->context(), top->childContexts().last());

    type = decs.first()->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QCOMPARE(type->dataType(), IntegralType::TypeInt);
    QVERIFY(type->modifiers() & AbstractType::ConstModifier);

    cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec->accessPolicy() == Declaration::Protected);

    decs = top->findDeclarations(QualifiedIdentifier(u"a::D"));
    QCOMPARE(decs.count(), 1);
    QCOMPARE(decs.first()->context(), top->childContexts().last());

    type = decs.first()->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QCOMPARE(type->dataType(), IntegralType::TypeInt);
    QVERIFY(type->modifiers() & AbstractType::ConstModifier);

    cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec->accessPolicy() == Declaration::Private);
}

void TestDUChain::semiReservedClassConst()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { const SWITCH = 1; const PUBLIC = 'foo'; const STRING = 'bar'; } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().count(), 1);
    QCOMPARE(top->problems().count(), 0);

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::SWITCH")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::SWITCH")).first()->context(), top->childContexts().last());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::PUBLIC")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::PUBLIC")).first()->context(), top->childContexts().last());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::STRING")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a::STRING")).first()->context(), top->childContexts().last());
}

void TestDUChain::illegalClassConst_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("final const") << QStringLiteral("<? class A { final const C = 1; } ");
    QTest::newRow("static const") << QStringLiteral("<? class A { static const C = 1; } ");
    QTest::newRow("abstract const") << QStringLiteral("<? class A { abstract const C = 1; } ");
}

void TestDUChain::illegalClassConst()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->problems().count(), 1);
}

void TestDUChain::fileConst_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<int>("problems");
    QTest::addColumn<uint>("dataType");

    QTest::newRow("int") << "const C = 1;" << 0 << (uint) IntegralType::TypeInt;
    QTest::newRow("string") << "const C = 'asdf';" << 0 << (uint) IntegralType::TypeString;
    QTest::newRow("float") << "const C = 0.5;" << 0 << (uint) IntegralType::TypeFloat;
    QTest::newRow("bool") << "const C = true;" << 0 << (uint) IntegralType::TypeBoolean;
    QTest::newRow("array") << "const C = array();" << 0 << (uint) IntegralType::TypeArray;
    QTest::newRow("expression") << "const C = 'foo' . 'foo';" << 0 << (uint) IntegralType::TypeString;
}

void TestDUChain::fileConst()
{
    QFETCH(QString, code);
    QFETCH(int, problems);
    QFETCH(uint, dataType);

    code.prepend("<?php ");

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->problems().count(), problems);

    QList< Declaration* > decs = top->findDeclarations(QualifiedIdentifier(QStringLiteral("C")));
    QCOMPARE(decs.count(), 1);
    auto type = decs.first()->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QCOMPARE(type->dataType(), dataType);
    QVERIFY(type->modifiers() & AbstractType::ConstModifier);
}

void TestDUChain::semiReservedFileConst()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? const SWITCH = 1; ");

    TopDUContext* top = parse(method, DumpNone);
    QVERIFY(!top);
}

void TestDUChain::define()
{
    // the last define tests that we don't crash under that circumstance
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? define('FOO', 'foo'); function x() { define('BAR', 'bar'); } define(); ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"FOO")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"BAR")).count(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"FOO")).first()->context(), top);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"BAR")).first()->context(), top);

    QVERIFY(top->findDeclarations(QualifiedIdentifier(u"FOO")).first()->abstractType()->modifiers() & AbstractType::ConstModifier);
    QVERIFY(top->findDeclarations(QualifiedIdentifier(u"BAR")).first()->abstractType()->modifiers() & AbstractType::ConstModifier);
}
void TestDUChain::defaultFunctionParam()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo($a, $b = false, $c = null) {} ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    AbstractFunctionDeclaration* fun = dynamic_cast<AbstractFunctionDeclaration*>(top->localDeclarations().first());
    QVERIFY(fun);

    QCOMPARE(fun->defaultParametersSize(), 3u);
    QVERIFY(fun->defaultParameters()[0].isEmpty());
    QCOMPARE(fun->defaultParameters()[1].str(), QString("false"));
    QCOMPARE(fun->defaultParameters()[2].str(), QString("null"));
}

void TestDUChain::defaultFunctionParamWithTypehint() {
    QByteArray method("<? function foo(array $i = array()) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    auto argType = fun->arguments().first().dynamicCast<IntegralType>();
    QVERIFY(argType);
    QVERIFY(argType->dataType() == IntegralType::TypeArray);
}

void TestDUChain::nullDefaultFunctionParamWithTypehint()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo(array $i = null) { } ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    QCOMPARE(fun->arguments().count(), 1);

    auto argType = fun->arguments().first().dynamicCast<UnsureType>();
    QVERIFY(argType);
    QCOMPARE(argType->typesSize(), 2u);
    QVERIFY(argType->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(argType->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(argType->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeNull);
}

void TestDUChain::globalFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? substr(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->importedParentContexts().count(), 1);
    QVERIFY(DUChain::self()->chainForDocument(internalFunctionFile()));
    QCOMPARE(DUChain::self()->chainForDocument(internalFunctionFile()), top->importedParentContexts().first().context(top));

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"substr")).count(), 1);
}

void TestDUChain::globalVariableFromInternalFunctions()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? substr(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->importedParentContexts().count(), 1);
    QVERIFY(DUChain::self()->chainForDocument(internalFunctionFile()));
    QCOMPARE(DUChain::self()->chainForDocument(internalFunctionFile()), top->importedParentContexts().first().context(top));

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"_GET")).count(), 1);
}

void TestDUChain::newObjectFromOtherFile()
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

void TestDUChain::unknownReturnType()
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
    QVERIFY(fType->returnType().dynamicCast<IntegralType>());
    QVERIFY(fType->returnType().staticCast<IntegralType>()->dataType() == IntegralType::TypeVoid);
}

void TestDUChain::staticFunctionCallFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo2.php"), "<?php class Foo { public static function a() {} } ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? Foo::a(); ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::classConstantFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo2.php"), "<?php class Foo { const BAR = 0; } ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? Foo::BAR; ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::globalFunctionCallFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo3.php"), "<?php function a() {} ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? a(); ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::constantFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo3.php"), "<?php define('A', 0); ");
    DUChainReleaser releaseAddTop(addTop);
    TopDUContext* top = parse("<? define('B', 0); A; ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVERIFY(hasImportedParentContext(top, addTop));
}

void TestDUChain::singleton()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public static function self() { static $i; if(!$i) $i = new self(); return $i; }}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fun = top->childContexts().first()->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fun);
    auto ret = fun->returnType().dynamicCast<StructureType>();
    qDebug() << fun->returnType()->toString();
    QVERIFY(ret);
    QCOMPARE(ret->declaration(top), top->localDeclarations().first());
}

void TestDUChain::internalFunctions()
{
    return; //disabled because it is too slow
    QString fileName = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kdevphpsupport/phpfunctions.php"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    TopDUContext* top = parse(file.readAll(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
}

void TestDUChain::trueFalse()
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

void TestDUChain::null()
{
    QByteArray method("<? $a = null; ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeNull);
}

void TestDUChain::array()
{
    QByteArray method("<? $a = array(); $b = array(1, 2, 3); $b[] = 'test';");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    QVERIFY(top->localDeclarations().at(1)->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    // $b[] = 'test'; is not a redeclaration of b! Esp. it's type should not change.
    QCOMPARE(top->findDeclarations(Identifier(u"b")).count(), 1);
}

void TestDUChain::functionDocBlock()
{
    {
        TopDUContext* top = parse("<? /**\n *Foo\n **/\nfunction foo() {} ", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    {
        TopDUContext* top = parse("<? /**\n *Bar\n **/\nclass A { /**\n *Foo\n **/\nfunction foo() {} }", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Bar"));
        QCOMPARE(top->childContexts().first()->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    {
        TopDUContext* top = parse("<? /**\n *Foo\n **/\ninterface A { }", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    {
        TopDUContext* top = parse("<? class A { /**\n *Foo\n **/\npublic $foo; }", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->childContexts().first()->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    {
        TopDUContext* top = parse("<? class A { /**\n *Foo\n **/\nconst FOO=0; }", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->childContexts().first()->localDeclarations().first()->comment(), QByteArray("Foo"));
    }

    {
        TopDUContext* top = parse("<?\n/// Foo\n/// Bar\nfunction foo() {} ", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo\n Bar"));
    }

    {
        // same as above but with indentation
        TopDUContext* top = parse("<?\n  /// Foo\n  /// Bar\n  function foo() {} ", DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo\n Bar"));
    }
}

void TestDUChain::variableDocBlock()
{
    {
        TopDUContext* top = parse("<? /**\n *Foo\n **/\n$a = 0; /**\n *Foo\n **/\nstatic $b;", DumpAll);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
        QCOMPARE(top->localDeclarations().at(1)->comment(), QByteArray("Foo"));
    }
    {
        TopDUContext* top = parse("<? /// Foo\n$a = 0; /// Foo\nstatic $b;", DumpAll);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());
        QCOMPARE(top->localDeclarations().first()->comment(), QByteArray("Foo"));
        QCOMPARE(top->localDeclarations().at(1)->comment(), QByteArray("Foo"));
    }
}

void TestDUChain::functionDocBlockParams()
{
    TopDUContext* top = parse("<? class A {} /**\n * @param\tint\n *\t@param A\n *  @param   mixed **/\nfunction foo($a, $b, $c, $d) {} ", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        QCOMPARE(top->localDeclarations().at(1)->type<FunctionType>()->arguments().count(), 4);

        AbstractType::Ptr arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(0);
        QVERIFY(arg.dynamicCast<IntegralType>());
        QVERIFY(arg.staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
        QVERIFY(top->childContexts().at(1)->localDeclarations().at(0)->type<IntegralType>());
        QVERIFY(top->childContexts().at(1)->localDeclarations().at(0)->type<IntegralType>()->dataType() == IntegralType::TypeInt);

        arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(1);
        QVERIFY(arg.dynamicCast<StructureType>());
        QCOMPARE(arg.staticCast<StructureType>()->declaration(top), top->localDeclarations().at(0));
        QCOMPARE(top->childContexts().at(1)->localDeclarations().at(1)->type<StructureType>()->declaration(top), top->localDeclarations().at(0));

        arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(2);
        QVERIFY(arg.dynamicCast<IntegralType>());
        QVERIFY(arg.staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed);

        arg = top->localDeclarations().at(1)->type<FunctionType>()->arguments().at(3);
        QVERIFY(arg.dynamicCast<IntegralType>());
        QVERIFY(arg.staticCast<IntegralType>()->dataType() == IntegralType::TypeMixed);
    }
}

void TestDUChain::memberFunctionDocBlockParams()
{
    TopDUContext* top = parse("<? class A { /**\n * @param bool\n * @param A\n * @param array\n **/\nfunction foo($a, $b, $c) {} }", DumpNone);
    {
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        QCOMPARE(top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().count(), 3);

        AbstractType::Ptr arg = top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().at(0);
        QVERIFY(arg.dynamicCast<IntegralType>());
        QVERIFY(arg.staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);

        arg = top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().at(1);
        QVERIFY(arg.dynamicCast<StructureType>());
        QCOMPARE(arg.staticCast<StructureType>()->declaration(top), top->localDeclarations().at(0));

        arg = top->childContexts().first()->localDeclarations().first()->type<FunctionType>()->arguments().at(2);
        QVERIFY(arg.dynamicCast<IntegralType>());
        QVERIFY(arg.staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);
    }
}

void TestDUChain::foreachLoop()
{
    {
    TopDUContext* top = parse("<? $a = array(1); foreach($a as $k=>$i) { $i; }", DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().count(), 3);
    QCOMPARE(top->localDeclarations().at(1)->qualifiedIdentifier(), QualifiedIdentifier(u"k"));
    QVERIFY(top->localDeclarations().at(1)->abstractType().dynamicCast<IntegralType>());
    QCOMPARE(top->localDeclarations().at(1)->abstractType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QVERIFY(top->localDeclarations().at(2)->abstractType().dynamicCast<IntegralType>());
    QCOMPARE(top->localDeclarations().at(2)->abstractType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
    }
    {
    // bug: https://bugs.kde.org/show_bug.cgi?id=237110
    TopDUContext* top = parse("<? $a = array(1); foreach($a as $b) { $c = new stdclass; }", DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().count(), 3);
    QCOMPARE(top->localDeclarations().at(1)->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    qDebug() << top->localDeclarations().at(1)->toString();
    QVERIFY(top->localDeclarations().at(1)->abstractType().dynamicCast<IntegralType>());
    QCOMPARE(top->localDeclarations().at(1)->abstractType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
    QCOMPARE(top->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier(u"c"));
    QVERIFY(top->localDeclarations().at(2)->abstractType().dynamicCast<StructureType>());
    QCOMPARE(top->localDeclarations().at(2)->abstractType().staticCast<StructureType>()->qualifiedIdentifier().toString(), QString("stdclass"));
    }
}

void TestDUChain::php4StyleConstructor()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class Aa { function Aa() { $this->bb(); } } ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->childContexts().first()->localDeclarations().at(0);
    QVERIFY(dec);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"aa::aa"));
    ClassFunctionDeclaration* classFuncDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(classFuncDec);
    QVERIFY(classFuncDec->isConstructor());
}

void TestDUChain::constructor()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    {
        QByteArray method("<? class foobar { function __construct() {} } ");
        TopDUContext* top = parse(method, DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        Declaration* dec = top->childContexts().first()->localDeclarations().at(0);
        QVERIFY(dec);
        ClassFunctionDeclaration* classFuncDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
        QVERIFY(classFuncDec);
        QVERIFY(!classFuncDec->isDestructor());
        QVERIFY(classFuncDec->isConstructor());
    }
    {
        QByteArray method("<? class foobar { function foobar() {} } ");
        TopDUContext* top = parse(method, DumpNone);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        Declaration* dec = top->childContexts().first()->localDeclarations().at(0);
        QVERIFY(dec);
        ClassFunctionDeclaration* classFuncDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
        QVERIFY(classFuncDec);
        QVERIFY(!classFuncDec->isDestructor());
        QVERIFY(classFuncDec->isConstructor());
    }
}

void TestDUChain::destructor()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class foobar { function __destruct() {} } ");
    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->childContexts().first()->localDeclarations().at(0);
    QVERIFY(dec);
    ClassFunctionDeclaration* classFuncDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(classFuncDec);
    QVERIFY(classFuncDec->isDestructor());
    QVERIFY(!classFuncDec->isConstructor());
}

void TestDUChain::functionInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function aaa() { function bbb() { } }");
    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().at(0)->qualifiedIdentifier(), QualifiedIdentifier(u"aaa"));
}

void TestDUChain::objectWithClassName()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class setupPage {} $setupPage = new setupPage; $setupPage->foo();");
    TopDUContext* top = parse(method, DumpNone, QUrl(QStringLiteral("file:///internal/testObjectWithClassName.php")));
    DUChainReleaser releaseTop(top);

    // update top (the pointer will be the same)
    QByteArray method2("<? $setupPage = new setupPage; $setupPage->foo();");
    TopDUContext* top2 = parse(method2, DumpNone, QUrl(QStringLiteral("file:///internal/testObjectWithClassName.php")));
    QVERIFY(top2 == top);
}

void TestDUChain::largeNumberOfDeclarations()
{
    TopDUContext* top = new TopDUContext(IndexedString(QUrl(QStringLiteral("file:///internal/testurl"))), RangeInRevision(0, 0, 6000, 0), nullptr);
    DUChain::self()->addDocumentChain(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    for (int i = 0; i < 6000; ++i) {
        RangeInRevision newRange(i, 0, i, 1);
        auto* dec = new Declaration(newRange, top);
        dec->setIdentifier(Identifier(QStringLiteral("dec%0").arg(i)));
        dec->setAbstractType(AbstractType::Ptr(nullptr));
    }
}

void TestDUChain::staticVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? define('AA', 0); function aaa() { static $foo; static $bar=0; static $baz='a'; static $bam=array(); static $woid=+'1'; static $a=AA; }");
    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().at(1)->localDeclarations().count(), 6);

    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->qualifiedIdentifier(), QualifiedIdentifier(u"aaa::foo"));
    QVERIFY(top->childContexts().at(1)->localDeclarations().first()->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->type<IntegralType>()->dataType(), (uint)IntegralType::TypeMixed);

    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(1)->qualifiedIdentifier(), QualifiedIdentifier(u"aaa::bar"));
    QVERIFY(top->childContexts().at(1)->localDeclarations().at(1)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(1)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);

    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(2)->qualifiedIdentifier(), QualifiedIdentifier(u"aaa::baz"));
    QVERIFY(top->childContexts().at(1)->localDeclarations().at(2)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(2)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeString);

    QVERIFY(top->childContexts().at(1)->localDeclarations().at(3)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(3)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeArray);

    QVERIFY(top->childContexts().at(1)->localDeclarations().at(4)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(4)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);

    QVERIFY(top->childContexts().at(1)->localDeclarations().at(5)->type<IntegralType>());
    QCOMPARE(top->childContexts().at(1)->localDeclarations().at(5)->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);
}

void TestDUChain::returnTypeTwoDeclarations()
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
    auto retType = functionType->returnType().dynamicCast<UnsureType>();
    QVERIFY(retType);
    QCOMPARE(retType->typesSize(), 2u);
    QVERIFY(retType->types()[0].abstractType().dynamicCast<IntegralType>());
    QCOMPARE(retType->types()[0].abstractType().staticCast<IntegralType>()->dataType(), (uint)IntegralType::TypeString);
    QVERIFY(retType->types()[1].abstractType().dynamicCast<IntegralType>());
    QCOMPARE(retType->types()[1].abstractType().staticCast<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);
}

void TestDUChain::globalVariableNotVisibleInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = 0; function foo() { $a; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a")).first()->uses().count(), 0);
}

void TestDUChain::globalVariableInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = 0; function foo() { global $a; $a; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a")).first()->uses().count(), 1);
}

void TestDUChain::nonGlobalVariableInFunction()
{
    // bug: https://bugs.kde.org/show_bug.cgi?id=240920

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = 0; function foo() { $a = 1; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->findLocalDeclarations(Identifier(u"a")).count(), 1);
    QCOMPARE(top->findLocalDeclarations(Identifier(u"a")).first()->uses().count(), 0);

    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->childContexts().last()->findLocalDeclarations(Identifier(u"a")).count(), 1);
    QCOMPARE(top->childContexts().last()->findLocalDeclarations(Identifier(u"a")).first()->uses().count(), 0);
}

void TestDUChain::superglobalInFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $_GET; function foo() { $_GET; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"_GET")).count(), 1);
    Declaration* dec = top->findDeclarations(QualifiedIdentifier(QStringLiteral("_GET"))).first();
    QVERIFY(dynamic_cast<VariableDeclaration*>(dec));
    QVERIFY(static_cast<VariableDeclaration*>(dec)->isSuperglobal());
    QCOMPARE(dec->uses().keys().count(), 1);
    QCOMPARE(dec->uses().values().count(), 1);
    QCOMPARE(dec->uses().values().first().count(), 2);
    QCOMPARE(dec->uses().values().first().first(), RangeInRevision(0, 3, 0, 8));
    QCOMPARE(dec->uses().values().first().at(1), RangeInRevision(0, 27, 0, 32));
}

void TestDUChain::returnWithoutFunction()
{
    //yes, this is possible in php, you then have $a as return value of an include call
    QByteArray method("<? $a = 0; return $a; ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
}

void TestDUChain::circularInheritance()
{
    //circular inheritance is not allowed in PHP and should not crash kdevelop
    QByteArray method("<? class a extends b {} class b extends c {} class c extends a {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().at(2)->internalContext()->importedParentContexts().empty());
    QCOMPARE(top->localDeclarations().at(1)->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(top->localDeclarations().at(1)->internalContext()->importedParentContexts().first().context(top),
             top->localDeclarations().at(2)->internalContext());
    QCOMPARE(top->localDeclarations().at(0)->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(top->localDeclarations().at(0)->internalContext()->importedParentContexts().first().context(top),
             top->localDeclarations().at(1)->internalContext());
}

void TestDUChain::circularInterface()
{
    QByteArray method("<? interface a {} class b implements a {} class c extends b implements a {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->problems().count(), 0);

    QVERIFY(top->localDeclarations().at(0)->internalContext()->importedParentContexts().empty());
    QCOMPARE(top->localDeclarations().at(1)->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(top->localDeclarations().at(1)->internalContext()->importedParentContexts().first().context(top),
             top->localDeclarations().at(0)->internalContext());
    QCOMPARE(top->localDeclarations().at(2)->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(top->localDeclarations().at(2)->internalContext()->importedParentContexts().first().context(top),
             top->localDeclarations().at(1)->internalContext());
}

void TestDUChain::findDeclarations()
{
    DUChainWriteLocker lock(DUChain::lock());

    TopDUContext* top1 = new TopDUContext(IndexedString(QUrl(QStringLiteral("file:///internal/testfile1"))), RangeInRevision(0, 0, 0, 10), nullptr);
    DUChainReleaser releaseTop1(top1);
    DUChain::self()->addDocumentChain(top1);
    TopDUContext* top2 = new TopDUContext(IndexedString(QUrl(QStringLiteral("file:///internal/testfile2"))), RangeInRevision(0, 0, 0, 10), nullptr);
    DUChainReleaser releaseTop2(top2);
    DUChain::self()->addDocumentChain(top2);

    Declaration* declaration = new Declaration(RangeInRevision(0, 0, 0, 3), top1);
    declaration->setIdentifier(Identifier(QStringLiteral("foo")));

    QVERIFY(!top1->usingImportsCache());
    QVERIFY(!top2->usingImportsCache());

    QCOMPARE(1, top1->findDeclarations(Identifier(u"foo")).count());
    QCOMPARE(0, top2->findDeclarations(Identifier(u"foo")).count());
    top2->addImportedParentContext(top1);

    QVERIFY(!top1->usingImportsCache());
    QVERIFY(!top2->usingImportsCache());

    QCOMPARE(1, top2->findDeclarations(Identifier(u"foo")).count());
    top2->clearImportedParentContexts();
    QCOMPARE(top2->importedParentContexts().size(), 0);

    QVERIFY(!top1->usingImportsCache());
    QVERIFY(!top2->usingImportsCache());

    QCOMPARE(0, top2->findDeclarations(Identifier(u"foo")).count());
    top2->addImportedParentContext(top1);
    QCOMPARE(1, top2->findDeclarations(Identifier(u"foo")).count());
}

void TestDUChain::memberTypeAfterMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function foo(){} public $bar; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* contextClassA = top->childContexts().first();

    // function foo
    {
        ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().first());
        QVERIFY(var);
        QCOMPARE(var->identifier(), Identifier(u"foo"));
        QCOMPARE(var->accessPolicy(), Declaration::Public);
        QCOMPARE(var->isStatic(), false);
        QVERIFY(var->type<FunctionType>());
        auto ret = var->type<FunctionType>()->returnType().dynamicCast<IntegralType>();
        QVERIFY(ret);
        QVERIFY(ret->dataType() == IntegralType::TypeVoid);
    }

    // public $bar
    {
        ClassMemberDeclaration* var = dynamic_cast<ClassMemberDeclaration*>(contextClassA->localDeclarations().at(1));
        QVERIFY(var);
        QCOMPARE(var->identifier(), Identifier(u"bar"));
        QCOMPARE(var->accessPolicy(), Declaration::Public);
        QCOMPARE(var->isStatic(), false);
        QVERIFY(var->type<IntegralType>());
        QVERIFY(var->type<IntegralType>()->dataType() == IntegralType::TypeNull);
    }
}


void TestDUChain::catchDeclaration()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? try {} catch (Exception $e) {}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    VariableDeclaration* ex = dynamic_cast<VariableDeclaration*>(top->localDeclarations().first());
    QVERIFY(ex);
    QCOMPARE(ex->identifier(), Identifier(u"e"));
    QVERIFY(ex->type<StructureType>());
    QCOMPARE(QualifiedIdentifier(u"exception"), ex->type<StructureType>()->declaration(top)->qualifiedIdentifier());
}

void TestDUChain::multiCatchDeclaration()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class ExceptionA {}; class ExceptionB {}; try {} catch (ExceptionA | ExceptionB $e) {}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->problems().count(), 0);

    VariableDeclaration* ex = dynamic_cast<VariableDeclaration*>(top->localDeclarations().at(2));
    QVERIFY(ex);
    QCOMPARE(ex->identifier(), Identifier(u"e"));
    QVERIFY(ex->type<UnsureType>());
    TypePtr<UnsureType> ut = ex->type<UnsureType>();
    QVERIFY(ut);
    QCOMPARE((uint)2, ut->typesSize());
    QVERIFY(ut->types()[0].type<StructureType>());
    QCOMPARE(QualifiedIdentifier(u"exceptiona"), ut->types()[0].type<StructureType>()->declaration(top)->qualifiedIdentifier());
    QVERIFY(ut->types()[1].type<StructureType>());
    QCOMPARE(QualifiedIdentifier(u"exceptionb"), ut->types()[1].type<StructureType>()->declaration(top)->qualifiedIdentifier());
}

void TestDUChain::resourceType()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? /**\n * @return resource\n**/\nfunction test() {}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionDeclaration* fun = dynamic_cast<FunctionDeclaration*>(top->localDeclarations().first());
    QVERIFY(fun);
    auto ftype = fun->abstractType().dynamicCast<FunctionType>();
    QVERIFY(ftype);
    auto rtype = ftype->returnType().dynamicCast<IntegralType>();
    QVERIFY(rtype);
    QCOMPARE(rtype->toString(), QString("resource"));
    QVERIFY(rtype->dataType() == IntegralTypeExtended::TypeResource);
}

void TestDUChain::foreachIterator()
{
    QByteArray code;
    code.append("<? class B {} class A implements Iterator {");
    code.append("public function rewind() {} ");
    code.append("/**\n * @return B\n */public function current() {} ");
    code.append("public function key() {} ");
    code.append("public function next() {} ");
    code.append("public function valid() {} ");
    code.append("} ");
    code.append("$a = new A();");
    code.append("foreach($a as $i) { $i; }");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* iDec = top->localDeclarations().at(3);
    QCOMPARE(iDec->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QVERIFY(iDec->type<StructureType>());
    QCOMPARE(iDec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QVERIFY(top->localDeclarations().first() == iDec->type<StructureType>()->declaration(top));
}

void TestDUChain::foreachIterator2()
{
    QByteArray code;
    code.append("<? class B {} class A implements Iterator {");
    code.append("public function rewind() {} ");
    code.append("/**\n * @return B\n */public function current() {} ");
    code.append("public function key() {} ");
    code.append("public function next() {} ");
    code.append("public function valid() {} ");
    code.append("} ");
    code.append("foreach(new A() as $i) { $i; }");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->localDeclarations().size(), 3);
    Declaration* iDec = top->localDeclarations().at(2);
    QCOMPARE(iDec->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    qDebug() << iDec->abstractType()->toString();
    QVERIFY(iDec->type<StructureType>());
    QCOMPARE(iDec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QVERIFY(top->localDeclarations().first() == iDec->type<StructureType>()->declaration(top));
}

void TestDUChain::foreachIterator3()
{
    QByteArray code;
    code.append("<? class B {} class A implements Iterator {");
    code.append("public function rewind() {} ");
    code.append("/**\n * @return B\n */public function current() {} ");
    code.append("public function key() {} ");
    code.append("public function next() {} ");
    code.append("public function valid() {} ");
    code.append("} ");
    code.append("class C extends A { }");
    code.append("foreach(new C() as $i) { $i; }");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* iDec = top->localDeclarations().at(3);
    QCOMPARE(iDec->qualifiedIdentifier(), QualifiedIdentifier(u"i"));
    QVERIFY(iDec->type<StructureType>());
    QCOMPARE(iDec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"b"));
    QVERIFY(top->localDeclarations().first() == iDec->type<StructureType>()->declaration(top));
}

void TestDUChain::foreachIterator4()
{
    // see also: https://bugs.kde.org/show_bug.cgi?id=276603
    QByteArray code = "<?\n"
                      "class A {\n"
                      "  public static $s;\n"
                      "  function foo() {\n"
                      "    foreach(array(1,2) as $this->i){}\n"
                      "    foreach(array(1,2) as $this->k => $this->v){}\n"
                      "    foreach(array(1,2) as A::$s){}\n"
                      "  }\n"
                      "}\n";

    TopDUContext* top = parse(code, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().isEmpty());

    Declaration* aDec = top->localDeclarations().first();

    DUContext* fooCtx = top->childContexts().first()->childContexts().last();
    QVERIFY(fooCtx->owner());

    QCOMPARE(aDec->uses().size(), 1);
    QCOMPARE(aDec->uses().begin()->size(), 4);
}

void TestDUChain::foreachArray()
{
    {
    QByteArray code = "<?\n"
                      "class Foo {};\n"
                      "/// @param Foo[]\n"
                      "function bar($a) {\n"
                      "    foreach($a as $e){ $e; }\n"
                      "}\n";
    TopDUContext* top = parse(code, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* barContext = top->childContexts().last();
    QCOMPARE(barContext->localScopeIdentifier(), QualifiedIdentifier(u"bar"));

    Declaration* eDec = barContext->localDeclarations().first();
    QCOMPARE(eDec->qualifiedIdentifier(), QualifiedIdentifier(u"bar::e"));
    QVERIFY(eDec->type<StructureType>());
    QCOMPARE(eDec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"foo"));
    }
}

void TestDUChain::returnThis()
{
    QByteArray code("<? class A { \n/**\n * @return $this\n */\npublic function x() {} } ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->childContexts().first()->localDeclarations().first();
    QVERIFY(dec->type<FunctionType>());
    AbstractType::Ptr t = dec->type<FunctionType>()->returnType();
    qDebug() << t->toString();
    QVERIFY(t.dynamicCast<StructureType>());
    QVERIFY(t.staticCast<StructureType>()->declaration(top) == top->localDeclarations().first());
}

void TestDUChain::unsureReturnType()
{
    QByteArray code("<? /**\n * @return bool|int\n */\nfunction x() {} ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().first();
    QVERIFY(dec->type<FunctionType>());
    auto ut = dec->type<FunctionType>()->returnType().dynamicCast<UnsureType>();
    QVERIFY(ut);
    QCOMPARE((uint)2, ut->typesSize());
    QVERIFY(ut->types()[0].type<IntegralType>());
    QVERIFY(ut->types()[0].type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
    QVERIFY(ut->types()[1].type<IntegralType>());
    QVERIFY(ut->types()[1].type<IntegralType>()->dataType() == IntegralType::TypeInt);
}


void TestDUChain::unsureReturnType2()
{
    QByteArray code("<? class A {} class B {}\n/**\n * @return A|B\n */\nfunction x() {} ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().at(2);
    QVERIFY(dec->type<FunctionType>());
    auto ut = dec->type<FunctionType>()->returnType().dynamicCast<UnsureType>();
    QVERIFY(ut);
    QCOMPARE((uint)2, ut->typesSize());
    QVERIFY(ut->types()[0].type<StructureType>());
    QCOMPARE(ut->types()[0].type<StructureType>()->toString(), QString("A"));
    QVERIFY(ut->types()[1].type<StructureType>());
    QCOMPARE(ut->types()[1].type<StructureType>()->toString(), QString("B"));
}

void TestDUChain::unsureReturnType3()
{
    QByteArray code("<? function x() { if(rand(0,1)) return false; else return 1; return \"a\"; } ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<FunctionType>());
    qDebug() << dec->type<FunctionType>()->returnType()->toString();
    auto ut = dec->type<FunctionType>()->returnType().dynamicCast<UnsureType>();
    QVERIFY(ut);
    QCOMPARE((uint)3, ut->typesSize());
    QVERIFY(ut->types()[0].type<IntegralType>());
    QVERIFY(ut->types()[0].type<IntegralType>()->dataType() == IntegralType::TypeInt);
    QVERIFY(ut->types()[1].type<IntegralType>());
    QVERIFY(ut->types()[1].type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
    QVERIFY(ut->types()[2].type<IntegralType>());
    QVERIFY(ut->types()[2].type<IntegralType>()->dataType() == IntegralType::TypeString);
}

void TestDUChain::unsureReturnType4()
{
    QByteArray code("<? \n/**\n * @param bool|int\n */\nfunction x($a) { return $a; } ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().first();
    QVERIFY(dec->type<FunctionType>());
    auto ut = dec->type<FunctionType>()->returnType().dynamicCast<UnsureType>();
    QVERIFY(ut);
    QCOMPARE((uint)2, ut->typesSize());
    QVERIFY(ut->types()[0].type<IntegralType>());
    QVERIFY(ut->types()[0].type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
    QVERIFY(ut->types()[1].type<IntegralType>());
    QVERIFY(ut->types()[1].type<IntegralType>()->dataType() == IntegralType::TypeInt);
}

void TestDUChain::referencedArgument()
{
    // php does not return references
    QByteArray code("<? \nfunction x(&$a) { $a = 1; return $a; } ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().first();
    QVERIFY(dec->type<FunctionType>());
    qDebug() << dec->abstractType()->toString();
    auto aType = dec->type<FunctionType>()->returnType().dynamicCast<IntegralType>();
    QVERIFY(aType);
    QCOMPARE(aType->dataType(), (uint)IntegralType::TypeInt);
    QCOMPARE(top->childContexts().first()->type(), DUContext::Function);
    auto rType = top->childContexts().first()->localDeclarations().first()->abstractType().dynamicCast<ReferenceType>();
    QVERIFY(rType);
    QVERIFY(rType->baseType()->equals(aType.data()));
}

void TestDUChain::unsureReferencedArgument()
{
    // php does not return references
    QByteArray code("<? \nfunction x(&$a) { $a = 1; $a = 'asdf'; return $a; } ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->localDeclarations().first();
    QVERIFY(dec->type<FunctionType>());
    qDebug() << dec->abstractType()->toString();
    auto aType = dec->type<FunctionType>()->returnType().dynamicCast<UnsureType>();
    QVERIFY(aType);
    QCOMPARE(aType->typesSize(), 2u);
    QCOMPARE(aType->types()[0].abstractType().staticCast<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);
    QCOMPARE(aType->types()[1].abstractType().staticCast<IntegralType>()->dataType(), (uint)IntegralType::TypeString);
    QCOMPARE(top->childContexts().first()->type(), DUContext::Function);
    auto rType = top->childContexts().first()->localDeclarations().first()->abstractType().dynamicCast<ReferenceType>();
    QVERIFY(rType);
    QVERIFY(rType->baseType()->equals(aType.data()));
}

void TestDUChain::defaultArgument()
{
    // php does not return references
    QByteArray code("<? \nfunction x($a = 1) {} ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* dec = top->childContexts().first()->localDeclarations().first();
    QVERIFY(dec->type<IntegralType>());
    QCOMPARE(dec->type<IntegralType>()->dataType(), (uint)IntegralType::TypeInt);
}

void TestDUChain::declareMemberOutOfClass()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? class foo{ protected $prot; private $priv; }\n"
                    // allowed, should only declare asdf once
                    "$bar = new foo; $bar->asdf = true; $bar->asdf = false;\n"
                    // not allowed:
                    "$bar->prot = 1;\n"
                    // not allowed:
                    "$bar->priv = 1;");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    { // $bar is only declared once
        QList<Declaration*> decs = top->findLocalDeclarations(Identifier(QStringLiteral("bar")));
        QCOMPARE(decs.size(), 1);
        Declaration *dec = decs.first();
        QVERIFY(dec->type<StructureType>());
        QVERIFY(dec->type<StructureType>()->declaration(top)->identifier().nameEquals(Identifier(u"foo")));

        // while we are at it, compare uses
        QCOMPARE(dec->uses().keys().count(), 1);
        QCOMPARE(dec->uses().values().count(), 1);
        QCOMPARE(dec->uses().values().first().count(), 4);
        qDebug() << dec->uses().values().first().at(0).castToSimpleRange();
        QCOMPARE(dec->uses().values().first().at(0), RangeInRevision(1, 16, 1, 20));
        qDebug() << dec->uses().values().first().at(1).castToSimpleRange();
        QCOMPARE(dec->uses().values().first().at(1), RangeInRevision(1, 35, 1, 39));
        qDebug() << dec->uses().values().first().at(2).castToSimpleRange();
        QCOMPARE(dec->uses().values().first().at(2), RangeInRevision(2, 0, 2, 4));
        qDebug() << dec->uses().values().first().at(3).castToSimpleRange();
        QCOMPARE(dec->uses().values().first().at(3), RangeInRevision(3, 0, 3, 4));
    }

    { // check if asdf got declared
        QList<Declaration*> decs = top->childContexts().first()->findDeclarations(Identifier(QStringLiteral("asdf")));
        // the type of both assignments to $bar->asdf are the same, hence it should only be declared once
        QCOMPARE(decs.size(), 1);
        ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
        QVERIFY(cmdec);
        QVERIFY(cmdec->accessPolicy() == Declaration::Public);
        QVERIFY(!cmdec->isStatic());
        QVERIFY(cmdec->type<IntegralType>());
        QVERIFY(cmdec->type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
    }

    // check that prot and priv don't get redeclared
    QCOMPARE(top->problems().count(), 2);
    QCOMPARE(top->problems().at(0)->finalLocation().start().line(), 2);
    QCOMPARE(top->problems().at(1)->finalLocation().start().line(), 3);
}

void TestDUChain::declareMemberOutOfClass2()
{
    // see also: https://bugs.kde.org/show_bug.cgi?id=283356
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? $a = new A();\n"
                    // allowed, should re-use existing declaration
                    "$a->x = 1;\n"
                    "class A { var $x = 1; }");
    TopDUContext* top = parse(code, DumpAST);
    QVERIFY(top);
    // update
    top = parse(code, DumpNone, top->url().toUrl(), ReferencedTopDUContext(top));
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    QList<Declaration*> decs = top->findLocalDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 2);
    {
        Declaration *dec = decs.first();
        QVERIFY(dynamic_cast<VariableDeclaration*>(dec));
        QVERIFY(dec->type<StructureType>());
        QVERIFY(dec->type<StructureType>()->declaration(top)->identifier().nameEquals(Identifier(u"a")));
    }
    {
        Declaration *dec = decs.last();
        QVERIFY(dynamic_cast<ClassDeclaration*>(dec));
        QVERIFY(dec->type<StructureType>());
        QVERIFY(dec->type<StructureType>()->declaration(top)->identifier().nameEquals(Identifier(u"a")));
    }

    { // check if x got declared
        QList<Declaration*> decs = top->childContexts().first()->findDeclarations(Identifier(QStringLiteral("x")));
        // the type of both assignments to $a->x are the same, hence it should only be declared once
        QCOMPARE(decs.size(), 1);
        ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
        QVERIFY(cmdec);
        QVERIFY(cmdec->accessPolicy() == Declaration::Public);
        QVERIFY(!cmdec->isStatic());
        QVERIFY(cmdec->type<IntegralType>());
        QCOMPARE(cmdec->type<IntegralType>()->dataType(), (uint) IntegralType::TypeInt);
    }
}

void TestDUChain::declareMemberInClassMethod()
{
    QByteArray code("<? class foo { private $priv = 0; protected $prot = 0; } class bar extends foo {\n"
                    // should declare member variable asdf (once!) as public
                    " function test() { $this->asdf = true; $this->asdf = false; }\n"
                    // should only declare bar once as private
                    " private $xyz = 0; function test2() { $this->xyz = 42; }\n"
                    // should create a local declaration for the private attribute
                    " function test3() { $this->prot = 42;\n$this->priv = 42; }\n"
                    " }");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    { // asdf
        QList<Declaration*> decs = top->childContexts().last()->findLocalDeclarations(Identifier(QStringLiteral("asdf")));
        QCOMPARE(decs.size(), 1);
        ClassMemberDeclaration *dec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
        QVERIFY(dec);
        QVERIFY(dec->accessPolicy() == Declaration::Public);
        QVERIFY(!dec->isStatic());
        QVERIFY(dec->type<IntegralType>());
        QVERIFY(dec->type<IntegralType>()->dataType() == IntegralType::TypeBoolean);
    }

    { // xyz
        QList<Declaration*> decs = top->childContexts().last()->findLocalDeclarations(Identifier(QStringLiteral("xyz")));
        QCOMPARE(decs.size(), 1);
        ClassMemberDeclaration *dec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
        QVERIFY(dec);
        QVERIFY(dec->accessPolicy() == Declaration::Private);
        QVERIFY(!dec->isStatic());
        QVERIFY(dec->type<IntegralType>());
        QVERIFY(dec->type<IntegralType>()->dataType() == IntegralType::TypeInt);
    }

    { // priv
        QList<Declaration*> decs = top->childContexts().last()->findLocalDeclarations(Identifier(QStringLiteral("priv")));
        QCOMPARE(decs.size(), 1);
        ClassMemberDeclaration *dec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
        QVERIFY(dec);
        QVERIFY(dec->accessPolicy() == Declaration::Public);
        QVERIFY(!dec->isStatic());
        QVERIFY(dec->type<IntegralType>());
        QVERIFY(dec->type<IntegralType>()->dataType() == IntegralType::TypeInt);
    }

    { // prot
        QVERIFY(top->childContexts().last()->findLocalDeclarations(Identifier(u"prot")).isEmpty());
    }

    QCOMPARE(top->problems().count(), 0);
}

void TestDUChain::thisRedeclaration()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? class foo{ function foo(){ $this->test = true; $this = false;} }");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    // only $this = false is a problem, $this->test = true is perfectly valid
    QCOMPARE(top->problems().count(), 1);
    qDebug() << top->problems().first()->finalLocation();
    QVERIFY(top->problems().first()->finalLocation() == KDevelop::DocumentRange(top->url(), KTextEditor::Range(0, 50, 0, 55)));
}

void TestDUChain::implicitArrayDeclaration()
{
    ///TODO: adapt to unsure type once it's supported
    {
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? $a[1] = true;");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration*> decs = top->findDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 1);
    VariableDeclaration* vdec = dynamic_cast<VariableDeclaration*>(decs.first());
    QVERIFY(vdec);
    QVERIFY(vdec->type<IntegralType>());
    QVERIFY(vdec->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    }

    {
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? $b = 1; $a[$b] = true;");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration*> decs = top->findDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 1);
    VariableDeclaration* vdec = dynamic_cast<VariableDeclaration*>(decs.first());
    QVERIFY(vdec);
    QVERIFY(vdec->type<IntegralType>());
    QVERIFY(vdec->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    }

    {
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? class foo{} $bar = new foo; $bar->a[1] = true;");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration*> decs = top->childContexts().first()->findDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 1);
    ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec);
    QVERIFY(cmdec->type<IntegralType>());
    QVERIFY(cmdec->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    }

    {
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? class foo{} $bar = new foo; $b = 1; $bar->a[$b] = true;");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration*> decs = top->childContexts().first()->findDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 1);
    ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec);
    QVERIFY(cmdec->type<IntegralType>());
    QVERIFY(cmdec->type<IntegralType>()->dataType() == IntegralType::TypeArray);
    }
}

void TestDUChain::implicitReferenceDeclaration()
{
    {
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? function asdf(&$foo) {} asdf($bar);");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration*> decs = top->findDeclarations(Identifier(QStringLiteral("bar")));
    QCOMPARE(decs.size(), 1);
    QVERIFY(dynamic_cast<VariableDeclaration*>(decs.first()));
    QVERIFY(decs.first()->type<IntegralType>());
    qDebug() << decs.first()->type<IntegralType>()->dataType() << decs.first()->toString();
    QVERIFY(decs.first()->type<IntegralType>()->dataType() == IntegralType::TypeNull);
    }

    {
    // a user reported a crash with the code example below

    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<? function test(&$p) {} class foo{ private $a; function test() {test($this->a);}  }");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY( top->childContexts().last()->localScopeIdentifier() == QualifiedIdentifier(u"foo"));

    // a is already declared
    QList<Declaration*> decs = top->childContexts().last()->findDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 1);
    ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec);
    QVERIFY(cmdec->type<IntegralType>());

    qDebug() << cmdec->type<IntegralType>()->dataType() << cmdec->toString();
    QVERIFY(cmdec->type<IntegralType>()->dataType() == IntegralType::TypeNull);
    }
}

void TestDUChain::classContextRange()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<?php class A { } $a = new A; ?> <?php $b = 1; $a->foobar = 1; $a->barFoo= 0;");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().first()->range(), KDevelop::RangeInRevision(0, 6, 0, 17));
    QCOMPARE(top->childContexts().first()->localDeclarations().count(), 2);
}

void TestDUChain::lateClassMembers()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("<?php class A { function f() { $this->val = 'b'; } private $val = 'a'; } ");
    TopDUContext* top = parse(code, DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ClassDeclaration* cdec = dynamic_cast<ClassDeclaration*>(top->localDeclarations().first());
    QVERIFY(cdec);
    QList<Declaration*> decs = cdec->logicalInternalContext(top)->findDeclarations(Identifier(QStringLiteral("val")));
    QCOMPARE(decs.count(), 1);
    ClassMemberDeclaration* cmdec = dynamic_cast<ClassMemberDeclaration*>(decs.first());
    QVERIFY(cmdec);
    QCOMPARE(cmdec->accessPolicy(), Declaration::Private);
}

void TestDUChain::list()
{
    foreach ( const QString& code, QStringList() << "<?php list($i, $j, $k) = array(1,2,3);"
                                                 << "<?php $a = array(1,2,3); list($i,$j,$k) = $a;"
                                                 << "<?php function t() { return array(1,2,3); } list($i,$j,$k) = t();" )
    {
        //               0         1         2         3         4         5         6         7
        //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
        TopDUContext* top = parse(code.toUtf8(), DumpAST);
        DUChainReleaser releaseTop(top);
        DUChainWriteLocker lock(DUChain::lock());

        foreach ( const QString& identifier, QStringList() << "i" << "j" << "k" ) {
            qDebug() << "searching for declaration of " << identifier;
            QList<Declaration*> decs = top->findDeclarations(Identifier(identifier));
            QCOMPARE(decs.size(), 1);
            Declaration *dec = decs.first();
            QVERIFY(dec->type<IntegralType>());
            QCOMPARE(dec->type<IntegralType>()->dataType(), (uint) IntegralType::TypeMixed);
            ///TODO: support arrays better and compare to actual type
        }
    }
}

void TestDUChain::alternateDocCommentTypeHints()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php class test {\n/// @var test\nprivate static $test;\n}", DumpAST);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ClassDeclaration* cdec = dynamic_cast<ClassDeclaration*>(top->localDeclarations().first());
    QVERIFY(cdec);
    QVERIFY(cdec->type<StructureType>());
    QVector<Declaration*> decs = cdec->logicalInternalContext(top)->localDeclarations();
    QCOMPARE(decs.size(), 1);
    Declaration *dec = decs.first();
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->declaration(top), cdec);
}

void TestDUChain::findFunctionArgs()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php function foo($bar, $asdf) {}", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionDeclaration* funcDec = dynamic_cast<FunctionDeclaration*>(top->localDeclarations().first());
    QVERIFY(funcDec);
    QVERIFY(funcDec->internalContext());
    QVERIFY(funcDec->internalFunctionContext());
    QVERIFY(funcDec->internalContext()->imports(funcDec->internalFunctionContext()));

    QList<Declaration*> decs;
    foreach ( Declaration* arg, funcDec->internalFunctionContext()->localDeclarations() ) {
        decs = funcDec->internalContext()->findDeclarations(arg->identifier());
        QCOMPARE(decs.size(), 1);
        decs = funcDec->internalContext()->findDeclarations(arg->qualifiedIdentifier());
        qDebug() << arg->qualifiedIdentifier().toString();
        QEXPECT_FAIL("", "strangely the arg dec is only found with its identifier, not by its qualifiedidentifier...", Continue);
        QCOMPARE(decs.size(), 1);
    }
}

void TestDUChain::undeclaredPropertyInString()
{
    // testcase for bug 209814

    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php class foo { var $foo; function bar() { \"$this->baz\"; } }", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().size(), 1);
    DUContext* classCtx = top->childContexts().first();
    QVERIFY(classCtx->type() == DUContext::Class);
    QCOMPARE(classCtx->localDeclarations().size(), 2);
    QCOMPARE(classCtx->findDeclarations(Identifier(u"foo")).size(), 1);
    QCOMPARE(classCtx->findDeclarations(Identifier(u"bar")).size(), 1);
}

void TestDUChain::undeclaredVarPropertyInString()
{
    // testcase for bug 210043

    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php \"$a->baz\";", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    // just don't crash
}

void TestDUChain::upcommingClassInString()
{
    // testcase for bug 232687

    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                                "class A {\n"
                                "    function A () {\n"
                                "        $b = new B();\n"
                                "        echo \"$b->blah\";\n"
                                "    }\n"
                                "}\n"
                                "class B {\n"
                                "  var $blah;\n"
                                "}\n", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    // just don't crash
}

void TestDUChain::namespaces()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace asdf{\n"
                              "function a(){}\n"
                              "define('b', 0);\n"
                              "class c {}\n"
                              "}\n"
                              "namespace NS1\\NS2 {\n"
                              "function a(){}\n"
                              "define('b', 0);\n"
                              "class c {}\n"
                              "}\n"
                              "namespace {\n"
                              "function a(){}\n"
                              "}\n"
                              , DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->problems().count(), 0);

    QCOMPARE(top->childContexts().size(), 4);
    QCOMPARE(top->childContexts().at(0)->localScopeIdentifier().toString(), QString("asdf"));
    QCOMPARE(top->childContexts().at(1)->localScopeIdentifier().toString(), QString("ns1"));

    QCOMPARE(top->childContexts().at(2)->type(), DUContext::Function);
    QCOMPARE(top->childContexts().at(3)->localScopeIdentifier().toString(), QString("a"));

    QCOMPARE(top->localDeclarations().size(), 3);
    QCOMPARE(top->localDeclarations().at(0)->kind(), Declaration::Namespace);
    QCOMPARE(top->localDeclarations().at(1)->kind(), Declaration::Namespace);
    QCOMPARE(top->localDeclarations().at(2)->kind(), Declaration::Type);

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"asdf")).size(), 1);
    QCOMPARE(top->childContexts().at(0)->localDeclarations().size(), 3);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"asdf::a")).size(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"asdf::b")).size(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"asdf::c")).size(), 1);

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1")).size(), 1);
    QCOMPARE(top->childContexts().at(1)->localDeclarations().size(), 1);
    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->kind(), Declaration::Namespace);
    ///TODO: support \ as separator
    QCOMPARE(top->childContexts().at(1)->localDeclarations().first()->qualifiedIdentifier().toString(), QString("ns1::ns2"));
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1::ns2")).size(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1::ns2")).first()->logicalInternalContext(top)->localDeclarations().size(), 3);
    QCOMPARE(top->childContexts().at(1)->childContexts().size(), 1);
    QCOMPARE(top->childContexts().at(1)->childContexts().first()->localDeclarations().size(), 3);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1::ns2")).first()->logicalInternalContext(top)->localDeclarations().first()->qualifiedIdentifier().toString(),
             QString("ns1::ns2::a"));
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1::ns2::a")).size(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1::ns2::b")).size(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"ns1::ns2::c")).size(), 1);

    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"a")).size(), 1);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"b")).size(), 0);
    QCOMPARE(top->findDeclarations(QualifiedIdentifier(u"c")).size(), 0);

    ///TODO: prevent redeclarations of namespaces
}

void TestDUChain::namespacesNoCurly()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace asdf;\n"
                              "function a(){}\n"
                              "define('b', 0);\n"
                              "class c {}\n"
                              "\n"
                              "namespace NS1\\NS2;\n"
                              "function a(){}\n"
                              "define('b', 0);\n"
                              "class c {}\n"
                              "\n"
                              , DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->problems().count(), 0);
    foreach(ProblemPointer p, top->problems()) {
        qDebug() << p->description() << p->explanation() << p->finalLocation();
    }
    QCOMPARE(top->childContexts().size(), 2);
    QCOMPARE(top->childContexts().at(0)->localScopeIdentifier().toString(), QString("asdf"));
    QCOMPARE(top->childContexts().at(1)->localScopeIdentifier().toString(), QString("ns1"));

    QCOMPARE(top->localDeclarations().size(), 2);
    QCOMPARE(top->localDeclarations().at(0)->kind(), Declaration::Namespace);
    QCOMPARE(top->localDeclarations().at(1)->kind(), Declaration::Namespace);
}

void TestDUChain::namespacesBaseType()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace string;\n"
                              "function a(){}\n"
                              "define('b', 0);\n"
                              "class c {}\n"
                              "\n"
                              , DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->problems().count(), 0);
    foreach(ProblemPointer p, top->problems()) {
        qDebug() << p->description() << p->explanation() << p->finalLocation();
    }
    QCOMPARE(top->childContexts().size(), 1);
    QCOMPARE(top->childContexts().at(0)->localScopeIdentifier().toString(), QString("string"));

    QCOMPARE(top->localDeclarations().size(), 1);
    QCOMPARE(top->localDeclarations().at(0)->kind(), Declaration::Namespace);
}

void TestDUChain::useNamespace()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace ns1\\ns2 {\n"
                              "function a(){}\n"
                              "const b = 0;\n"
                              "class c {}\n"
                              "}\n"
                              "namespace ns3\\ns4 {\n"
                              "function a(){}\n"
                              "const b = 0;\n"
                              "class c {}\n"
                              "}\n"
                              "namespace {\n"
                              "use ns1\\ns2, ns3\\ns4 as ns5;\n"
                              "use \\ns3\\ns4 as ns6;\n"
                              "}\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->localDeclarations().count(), 5);

    Declaration* dec = top->localDeclarations().at(2);
    QCOMPARE(dec->qualifiedIdentifier().toString(), QString("ns2"));
    QVERIFY(dynamic_cast<NamespaceAliasDeclaration*>(dec));

    dec = top->localDeclarations().at(3);
    QCOMPARE(dec->qualifiedIdentifier().toString(), QString("ns5"));
    QVERIFY(dynamic_cast<NamespaceAliasDeclaration*>(dec));

    dec = top->localDeclarations().at(4);
    QCOMPARE(dec->qualifiedIdentifier().toString(), QString("ns6"));
    QVERIFY(dynamic_cast<NamespaceAliasDeclaration*>(dec));
    ///TODO: find out why this is explicitly required
    QVERIFY(!dynamic_cast<NamespaceAliasDeclaration*>(dec)->importIdentifier().explicitlyGlobal());
}

void TestDUChain::useGroupedNamespace_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("class group") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { class A {} }\n"
                       "namespace ns1\\ns2 { class B {} }\n"
                       "namespace ns3 {\n"
                       "use ns1\\ns2\\{A,B};\n"
                       "}\n");
    QTest::newRow("class group with partial namespace") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { class A {} }\n"
                       "namespace ns1\\ns3 { class B {} }\n"
                       "namespace ns3 {\n"
                       "use ns1\\{ns2\\A,ns3\\B};\n"
                       "}\n");
    QTest::newRow("class group with trailing comma") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { class A {} }\n"
                       "namespace ns1\\ns2 { class B {} }\n"
                       "namespace ns3 {\n"
                       "use ns1\\ns2\\{A,B,};\n"
                       "}\n");
    QTest::newRow("function group") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { function foo(){} }\n"
                       "namespace ns1\\ns2 { function bar(){} }\n"
                       "namespace ns3 {\n"
                       "use function ns1\\ns2\\{foo,bar};\n"
                       "}\n");
    QTest::newRow("function group with partial namespace") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { function foo(){} }\n"
                       "namespace ns1\\ns3 { function bar(){} }\n"
                       "namespace ns3 {\n"
                       "use function ns1\\{ns2\\foo,ns3\\bar};\n"
                       "}\n");
    QTest::newRow("function group with trailing comma") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { function foo(){} }\n"
                       "namespace ns1\\ns2 { function bar(){} }\n"
                       "namespace ns3 {\n"
                       "use function ns1\\ns2\\{foo,bar,};\n"
                       "}\n");
    QTest::newRow("constant group") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; }\n"
                       "namespace ns1\\ns2 { const B = ''; }\n"
                       "namespace ns3 {\n"
                       "use const ns1\\ns2\\{A,B};\n"
                       "}\n");
    QTest::newRow("constant group with partial namespace") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; }\n"
                       "namespace ns1\\ns3 { const B = ''; }\n"
                       "namespace ns3 {\n"
                       "use const ns1\\{ns2\\A,ns3\\B};\n"
                       "}\n");
    QTest::newRow("constant group with trailing comma") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; }\n"
                       "namespace ns1\\ns2 { const B = ''; }\n"
                       "namespace ns3 {\n"
                       "use const ns1\\ns2\\{A,B,};\n"
                       "}\n");
    QTest::newRow("mixed group") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; function foo(){} }\n"
                       "namespace ns1\\ns2 { class C {} }\n"
                       "namespace ns3 {\n"
                       "use ns1\\ns2\\{C, const A, function foo};\n"
                       "}\n");
    QTest::newRow("mixed group with trailing comma") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; function foo(){} }\n"
                       "namespace ns1\\ns2 { class C {} }\n"
                       "namespace ns3 {\n"
                       "use ns1\\ns2\\{C, const A, function foo,};\n"
                       "}\n");
}

void TestDUChain::useGroupedNamespace()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());
}

void TestDUChain::useInvalidGroupedNamespace_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("mixed in function import") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; function foo(){} }\n"
                       "namespace ns1\\ns2 { class C {} }\n"
                       "namespace ns3 {\n"
                       "use function ns1\\ns2\\{C, const A, function foo};\n"
                       "}\n");
    QTest::newRow("mixed in constant import") <<
        QStringLiteral("<?php\n"
                       "namespace ns1\\ns2 { const A = ''; function foo(){} }\n"
                       "namespace ns1\\ns2 { class C {} }\n"
                       "namespace ns3 {\n"
                       "use const ns1\\ns2\\{C, const A, function foo,};\n"
                       "}\n");
}

void TestDUChain::useInvalidGroupedNamespace()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
}

void TestDUChain::useBaseTypeNamespace()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace ns1\\string {\n"
                              "function a(){}\n"
                              "const b = 0;\n"
                              "class c {}\n"
                              "}\n"
                              "namespace ns3\\iterable {\n"
                              "function a(){}\n"
                              "const b = 0;\n"
                              "class c {}\n"
                              "}\n"
                              "namespace {\n"
                              "use ns1\\string, ns3\\iterable;\n"
                              "}\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->localDeclarations().count(), 4);

    Declaration* dec = top->localDeclarations().at(2);
    QCOMPARE(dec->qualifiedIdentifier().toString(), QString("string"));
    QVERIFY(dynamic_cast<NamespaceAliasDeclaration*>(dec));

    dec = top->localDeclarations().at(3);
    QCOMPARE(dec->qualifiedIdentifier().toString(), QString("iterable"));
    QVERIFY(dynamic_cast<NamespaceAliasDeclaration*>(dec));
}

void TestDUChain::useNamespaceBaseTypeAlias()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace ns1\\string {\n"
                              "function a(){}\n"
                              "const b = 0;\n"
                              "class c {}\n"
                              "}\n"
                              "namespace ns3\\iterable {\n"
                              "function a(){}\n"
                              "const b = 0;\n"
                              "class c {}\n"
                              "}\n"
                              "namespace {\n"
                              "use ns1\\string as iterable, ns3\\iterable as bool;\n"
                              "}\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->problems().count(), 2);
}

void TestDUChain::namespaceStaticVar()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace ns {\n"
                              "class c{ static public $foo; }\n"
                              "}\n"
                              "namespace {\n"
                              "\\ns\\c::$foo;\n"
                              "}\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());
    Declaration* fooDec = top->findDeclarations(QualifiedIdentifier(QStringLiteral("ns::c::foo"))).first();
    QVERIFY(fooDec);

    QVERIFY(!fooDec->uses().isEmpty());
    QVERIFY(!fooDec->uses().begin()->isEmpty());
    QCOMPARE(fooDec->uses().begin()->begin()->start.line, 5);
}

void TestDUChain::namespacedCatch()
{
    // see also: https://bugs.kde.org/show_bug.cgi?id=281451
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "namespace ns {\n"
                              "class e{}\n"
                              "}\n"
                              "namespace {\n"
                              "try { /* ... */ }\n"
                              "catch(\\ns\\e $exception) { /* ... */ }"
                              "}\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());
    Declaration* eDec = top->findDeclarations(QualifiedIdentifier(QStringLiteral("ns::e"))).first();
    QVERIFY(eDec);

    QVERIFY(!eDec->uses().isEmpty());
    QVERIFY(!eDec->uses().begin()->isEmpty());
    QCOMPARE(eDec->uses().begin()->begin()->start.line, 6);
}

struct TestUse {
    TestUse(const QString& _id, Declaration::Kind _kind, int _uses)
        : id(_id), kind(_kind), uses(_uses)
    {}
    TestUse()
    {}
    QualifiedIdentifier id;
    Declaration::Kind kind;
    int uses;
};

Q_DECLARE_METATYPE ( TestUse )
Q_DECLARE_METATYPE ( QList<TestUse> )

void TestDUChain::errorRecovery_data()
{
    QTest::addColumn<QString>("code");

    QTest::addColumn< QList<TestUse> >("usesMap");

    QTest::newRow("conditional") << QStringLiteral("<?php $a = 1; if ( false ) { in va lid } $a = 2; ")
                                 << (QList<TestUse>()
                                    << TestUse(QStringLiteral("a"), Declaration::Instance, 1));

    QTest::newRow("namespace") << QStringLiteral("<?php namespace foo { const a = 1; } namespace y { -a sdflyxjcv 91348 } namespace { foo\\a; }")
                                 << (QList<TestUse>()
                                    << TestUse(QStringLiteral("foo"), Declaration::Namespace, 1)
                                    << TestUse(QStringLiteral("y"), Declaration::Namespace, 0)
                                    << TestUse(QStringLiteral("foo::a"), Declaration::Instance, 1));

    QTest::newRow("class") << QStringLiteral("<?php class foo { const bar = 1; invalid static function func() {} } foo::bar; foo::func;")
                                 << (QList<TestUse>()
                                    << TestUse(QStringLiteral("foo"), Declaration::Type, 0)
                                    << TestUse(QStringLiteral("foo::bar"), Declaration::Instance, 1)
                                    << TestUse(QStringLiteral("foo::func"), Declaration::Type, 1)
                                    );
}

void TestDUChain::errorRecovery()
{
    QFETCH(QString, code);
    QFETCH(QList<TestUse>, usesMap);

    TopDUContext* top = parse(code.toLocal8Bit(), DumpAll);

    QVERIFY(top);

    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    foreach ( const TestUse& use, usesMap ) {
        QList< Declaration* > decs = top->findDeclarations(use.id);
        QCOMPARE(decs.count(), 1);
        Declaration* dec = decs.first();
        QCOMPARE(dec->kind(), use.kind);
        if (use.uses) {
            QCOMPARE(dec->uses().count(), 1);
            QCOMPARE(dec->uses().begin()->count(), use.uses);
        }
    }
}

void TestDUChain::varStatic()
{
    //bug: https://bugs.kde.org/244076

    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "class c { const a = 1; static function foo() {} }\n"
                              "$o = 'c';\n"
                              "$o::a;\n"
                              "$o::foo();\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());

    // we cannot support anything though :(
}

void TestDUChain::staticNowdoc()
{
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "class c {\n"
                              "public $bar = <<<'FOO'\nbar\nFOO;\n"
                              "public const C = <<<'FOO'\nbar\nFOO;\n"
                              "}\n"
                              , DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());

    QCOMPARE(top->childContexts().first()->localDeclarations().count(), 2);
    QCOMPARE(top->childContexts().first()->localDeclarations().first()->type<IntegralType>()->dataType(),
             static_cast<uint>(IntegralType::TypeString));
    QCOMPARE(top->childContexts().first()->localDeclarations().last()->type<IntegralType>()->dataType(),
             static_cast<uint>(IntegralType::TypeString));
}

void TestDUChain::curlyVarAfterObj()
{
    // bug: https://bugs.kde.org/show_bug.cgi?id=241645

    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse("<?php\n"
                              "class c {\n"
                              "public $bar = 'foo';\n"
                              "public $asdf = 'bar';\n"
                              "public function foo(){}\n"
                              "}\n"
                              "$a = new c;\n"
                              "$a->{$a->bar}();\n"
                              "$a->{$a->asdf};\n"
                              , DumpNone);
    QVERIFY(top);

    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());
}

void TestDUChain::embeddedHTML_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("if") << QStringLiteral("<?php if ( true ) : ?>\n<?php endif; ?>");
    QTest::newRow("elseif") << QStringLiteral("<?php if ( true ) : ?>\n<?php elseif ( false ) : ?>\n<?php endif; ?>");
    QTest::newRow("foreach") << QStringLiteral("<?php foreach ( array(1,2) as $i ) : ?>\n<?php endforeach; ?>\n");
    QTest::newRow("switch") << QStringLiteral("<?php switch ( 1 ) : case 1: ?>\n<?php break; endswitch; ?>\n");
    QTest::newRow("for") << QStringLiteral("<?php for ( ;; ) : ?>\n<?php endfor; ?>\n");
    QTest::newRow("while") << QStringLiteral("<?php while ( true ) : ?>\n<?php endwhile; ?>\n");
    QTest::newRow("else") << QStringLiteral("<?php if (true):\n echo 'ok1';\n else:\n echo 'ok2';\n endif; ?>");

}

void TestDUChain::embeddedHTML()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toLocal8Bit(), DumpNone);

    QVERIFY(top);

    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());
}

void TestDUChain::cases()
{
    // testcase for bug https://bugs.kde.org/show_bug.cgi?id=245832
    TopDUContext* top = parse("<?php switch(1) { case 1:\n case 2:\n break; default: break; }", DumpNone);

    QVERIFY(top);

    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());
}

void TestDUChain::closureParser()
{
    // testcase for the parser after closures where introduced,
    // to make sure nothing brakes and all parser conflicts are resolved
    TopDUContext* top = parse("<?php\n"
                              "$lambda1 = function() {return 0;};\n"
                              "$lambda2 = function() use ($lambda1) {return 0;};\n"
                              "$lambda3 = function & () use (&$lambda2, $lambda1) {return 0;};\n"
                              "$lambda4 = function & ($a, &$b, stdClass $c) use (&$lambda2, $lambda1) {return 0;};\n"
                              "\n"
                              "class a {\n"
                              "  function foo() {}\n"
                              "  function & bar() {}\n"
                              "}\n"
                              "function foo() {}\n"
                              "function & bar() {}\n", DumpNone);

    QVERIFY(top);

    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());
}

void TestDUChain::closures()
{
    TopDUContext* top = parse("<?php $l = function($a, stdClass $b) { return 0; };\n", DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().isEmpty());

    QCOMPARE(top->localDeclarations().count(), 2);
    Declaration* l = top->localDeclarations().first();
    QCOMPARE(l->identifier().toString(), QString("l"));
    Declaration* closure = top->localDeclarations().last();
    QVERIFY(closure->identifier().isEmpty());

    FunctionType::Ptr funcType = closure->type<FunctionType>();
    QVERIFY(funcType);

    QCOMPARE(funcType->arguments().count(), 2);
    QVERIFY(funcType->arguments().at(0).dynamicCast<IntegralType>());
    QCOMPARE(funcType->arguments().at(0).staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
    QVERIFY(funcType->arguments().at(1).dynamicCast<StructureType>());
    QCOMPARE(funcType->arguments().at(1).staticCast<StructureType>()->qualifiedIdentifier().toString(), QString("stdclass"));

    QVERIFY(funcType->returnType().dynamicCast<IntegralType>());
    QCOMPARE(funcType->returnType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeInt));

    QVERIFY(l->abstractType()->equals(closure->abstractType().constData()));
}

void TestDUChain::closureEmptyUse()
{
    // test case for: https://bugs.kde.org/show_bug.cgi?id=267105
    // don't crash but report parse error
    TopDUContext* top = parse("<?php $c = function ($v) use () { return $v > 2; };\n", DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QCOMPARE(top->problems().size(), 1);
}

void TestDUChain::iifeParser()
{
    // testcase for bug https://bugs.kde.org/show_bug.cgi?id=370515
    TopDUContext* top = parse("<?php\n"
                              "$lambda1 = (function() {return 5;})();\n"
                              "$lambda2 = (function($a) {return $a;})(50);\n"
                              "$lambda3 = (function($a){ return function($b) use ($a){echo $a + $b;};})(50); \n"
                              "$lambda4 = (function ($a){echo $a;})(10) + (function ($a){echo $a ;})(20);"
                              , DumpNone);

    QVERIFY(top);

    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().empty());
}

void TestDUChain::iife()
{
    TopDUContext* top = parse("<?php $l = (function($a){ return function($b) use ($a){echo $a + $b;};})(50); \n", DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().isEmpty());
    QCOMPARE(top->localDeclarations().count(), 2);
    Declaration* l = top->localDeclarations().first();
    QCOMPARE(l->identifier().toString(), QString("l"));
    Declaration* iife = top->localDeclarations().last();
    QVERIFY(iife->identifier().isEmpty());
}

void TestDUChain::gotoTest()
{
    TopDUContext* top = parse("<?php goto dest; dest: \n", DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().isEmpty());

    ///TODO: create declaration for destination label
    ///TODO: create use for goto label
    ///TODO: report error when trying to jump into loop or switch statement
}

void TestDUChain::ternary()
{
    TopDUContext* top = parse("<?php $a = true ? 1 : 2; $b = false ?: 3; \n", DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().isEmpty());
}

void TestDUChain::bug296709()
{
    // see also: https://bugs.kde.org/show_bug.cgi?id=296709
    //               0         1         2         3         4         5         6         7
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789
    TopDUContext* top = parse(
                    "<?php\n"
                    "foreach(array() as $a) {\n"
                    "  $a[0] = 1;\n"
                    "}\n", DumpAll);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;
    QVERIFY(top->problems().isEmpty());
    QList< Declaration* > decs = top->findLocalDeclarations(Identifier(QStringLiteral("a")));
    QCOMPARE(decs.size(), 1);
    QCOMPARE(decs.at(0)->range(), RangeInRevision(1, 19, 1, 21));
    QCOMPARE(decs.at(0)->uses().count(), 1);
    QCOMPARE(decs.at(0)->uses().begin()->count(), 1);
    QCOMPARE(decs.at(0)->uses().begin()->first(), RangeInRevision(2, 2, 2, 4));
}


void TestDUChain::declareFinalMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public final function foo() {} }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);

    DUContext* contextClassA = top->childContexts().first();

    Declaration* dec = contextClassA->localDeclarations().at(0);
    ClassFunctionDeclaration* funDec = dynamic_cast<ClassFunctionDeclaration*>(dec);
    QVERIFY(funDec);
    QCOMPARE(funDec->qualifiedIdentifier(), QualifiedIdentifier(u"a::foo"));
    QVERIFY(funDec->isFinal());
}

void Php::TestDUChain::testTodoExtractor()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<?\n"
                      "/* TODO: bla */\n"
                      "/// FIXME blub");

    QVERIFY(KDevelop::ICore::self()->languageController()->completionSettings()->todoMarkerWords().contains("TODO"));
    QVERIFY(KDevelop::ICore::self()->languageController()->completionSettings()->todoMarkerWords().contains("FIXME"));

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top);
    QCOMPARE(top->problems().size(), 2);
    QCOMPARE(top->problems().at(0)->description(), QString("TODO: bla"));
    QCOMPARE(top->problems().at(0)->range(), RangeInRevision(1, 3, 1, 12));
    QCOMPARE(top->problems().at(1)->description(), QString("FIXME blub"));
    QCOMPARE(top->problems().at(1)->range(), RangeInRevision(2, 4, 2, 14));
}

void TestDUChain::useThisAsArray()
{
    QByteArray method("<?php\n"
                      "  interface ArrayAccess{} "
                      "  class A implements \\ArrayAccess\n"
                      "  {\n"
                      "      $values = [];\n"
                      "      function offsetGet($offset) { return $this->values[$offset]; }\n"
                      "      function offsetSet($offset, $value) { $this->values[$offset] = $value; }\n"
                      "      function offsetExists($offset) { return array_key_exists($offset, $this->values); }\n"
                      "      function offsetUnset($offset) { unset($this->values[$offset]); }\n"
                      "      function setTest() { $this['test'] = 'test'; }  \n"
                      "  }\n");
    
    TopDUContext* top = parse(method);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    QCOMPARE(top->importedParentContexts().count(), 1);
    QVERIFY(DUChain::self()->chainForDocument(internalFunctionFile()));
    QCOMPARE(DUChain::self()->chainForDocument(internalFunctionFile()), top->importedParentContexts().first().context(top));
    
    QVERIFY(top->problems().isEmpty());
}

void TestDUChain::wrongUseOfThisAsArray()
{
    // missing functions from \ArrayAccess and not declared abstract
    QByteArray method("<?php\n"
                      "  interface ArrayAccess{} "
                      "  class A implements \\ArrayAccess\n"
                      "  {\n"
                      "      public function setTest() { $this['test'] = 'test'; }  \n"
                      "  }\n");

    TopDUContext* top = parse(method);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    QCOMPARE(top->problems().size(),1);
}

void TestDUChain::staticFunctionClassPhp54()
{
    QByteArray method("<?php\n"
                      "  class A\n"
                      "  {\n"
                      "      public static function func() {}  \n"
                      "  }\n"
                      " A::{'func'}();  \n");

    TopDUContext* top = parse(method);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());
    QCOMPARE(top->localDeclarations().count(),1);

    Declaration* dec = top->localDeclarations().at(0);
    ClassDeclaration* classDec = dynamic_cast<ClassDeclaration*>(dec);
    QCOMPARE(classDec->uses().count(),1);
}

void TestDUChain::functionArgumentUnpacking_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("unpackVariable") << QStringLiteral("<? $a = [ 1,2 ];\n$b = [ 3,4 ];\nfunction aaa($c,$d,$e,$f) { }\naaa(...$a, ...$b);\n");

    QTest::newRow("unpackLiteral") << QStringLiteral("<? function aaa($c,$d,$e,$f) { }\naaa(...[1,2], ...[3,4]);\n");

    QTest::newRow("unpackFunction") << QStringLiteral("<? function bbb() { return [1,2,3,4]; }\nfunction aaa($c,$d,$e,$f) { }\naaa(...bbb());\n");
}

void TestDUChain::functionArgumentUnpacking()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());
}

void TestDUChain::illegalExpression_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("equality expression") << QStringLiteral("<? 1 == '1' == 1.1;\n");
    QTest::newRow("relational expression") << QStringLiteral("<? 3 > 2 > 1;\n");
    QTest::newRow("double print expression") << QStringLiteral("<? print 1 print 2;\n");
    QTest::newRow("standalone print statement") << QStringLiteral("<? print;\n");
    QTest::newRow("expression inside isset()") << QStringLiteral("<? isset($a || $b);\n");
    QTest::newRow("instanceof with dynamic property of static class") << QStringLiteral("<? $a instanceof A->foo;\n");
    QTest::newRow("instanceof with class constant") << QStringLiteral("<? $a instanceof A::FOO;\n");
    QTest::newRow("instanceof with class method") << QStringLiteral("<? $a instanceof $b->foo();\n");
    QTest::newRow("instanceof with static method") << QStringLiteral("<? $a instanceof A::foo();\n");
}

void TestDUChain::illegalExpression()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(!top);
}

void TestDUChain::printExpression_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("simple print expression") << QStringLiteral("<? print 1;\n");
    QTest::newRow("print assignment") << QStringLiteral("<? print $a = 1;\n");
    QTest::newRow("print boolean expression") << QStringLiteral("<? print $a || $b;\n");
    QTest::newRow("double print token") << QStringLiteral("<? print print 1;\n");
    QTest::newRow("concatenated print expression") << QStringLiteral("<? print 1 . print 2;\n");
    QTest::newRow("boolean-chained print expression") << QStringLiteral("<? print 1 || print 2 && print 3;\n");
    QTest::newRow("ternary-chained print expression") << QStringLiteral("<? print 1 ? print 2 : print 3;\n");
    QTest::newRow("assignment-chained print expression") << QStringLiteral("<? print $a = $b += print 1;\n");
    QTest::newRow("null-coalesce-chained print expression") << QStringLiteral("<? print $a ?? print 1;\n");
    QTest::newRow("bit-chained print expression") << QStringLiteral("<? print 1 | print 2 & print 3 ^ print 4;\n");
    QTest::newRow("include print expression") << QStringLiteral("<? include print 'string';\n");
    QTest::newRow("print expression inside empty()") << QStringLiteral("<? empty(print 1);\n");
}

void TestDUChain::printExpression()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());
}

void TestDUChain::simpleExpression_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("string concat") << QStringLiteral("<? $var = 'string ' . 'concat';\n");
    QTest::newRow("variable concat") << QStringLiteral("<? $foo = 'concat'; $var = 'string ' . $foo;\n");
    QTest::newRow("variable array concat") << QStringLiteral("<? $arr = [ 'concat' ]; $var = 'string ' . $arr[1];\n");
    QTest::newRow("constant concat") << QStringLiteral("<? const FOO = 'concat'; $var = 'string ' . FOO;\n");
    QTest::newRow("constant array concat") << QStringLiteral("<? const ARR = [ 'concat' ]; $var = 'string ' . ARR[1];\n");
}

void TestDUChain::simpleExpression()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());
}

void TestDUChain::generatorAssignment()
{
    //Note: in practice, Generator is defined by php, but this class is not loaded in this test, so define it ourselves
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class Generator {} function foo() { $a = yield 1; }\n");

    TopDUContext* top = parse(method, DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
    QCOMPARE(top->localDeclarations().count(), 2);

    Declaration* dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"foo"));
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    auto retType = functionType->returnType().dynamicCast<StructureType>();
    QVERIFY(retType);
    QCOMPARE(retType->qualifiedIdentifier(), QualifiedIdentifier(u"generator"));

    dec = top->childContexts().at(2)->localDeclarations().at(0);
    QCOMPARE(dec->identifier(), Identifier(u"a"));
    IntegralType::Ptr type = dec->type<IntegralType>();
    QVERIFY(type);
    QVERIFY(type->dataType() == IntegralType::TypeMixed);
}

void TestDUChain::generatorClosure()
{
    //Note: in practice, Generator is defined by php, but this class is not loaded in this test, so define it ourselves
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class Generator {} function foo() { $a = function() { $b = function() { yield 1; }; }; }\n");

    TopDUContext* top = parse(method, DumpNone);
    QVERIFY(top);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 3);
    QCOMPARE(top->localDeclarations().count(), 2);

    Declaration* dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier(u"foo"));
    FunctionType::Ptr functionType = dec->type<FunctionType>();
    QVERIFY(functionType);
    auto retType = functionType->returnType().dynamicCast<IntegralType>();
    QVERIFY(retType);
    QVERIFY(retType->dataType() == IntegralType::TypeVoid);

    dec = top->childContexts().at(2)->localDeclarations().at(0);
    QCOMPARE(dec->identifier(), Identifier(u"a"));

    Declaration* closure = top->childContexts().at(2)->localDeclarations().at(1);
    QVERIFY(closure->identifier().isEmpty());

    FunctionType::Ptr funcType = closure->type<FunctionType>();
    QVERIFY(funcType);
    QVERIFY(funcType->returnType().dynamicCast<IntegralType>());
    QCOMPARE(funcType->returnType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeVoid));

    QVERIFY(dec->abstractType()->equals(closure->abstractType().constData()));

    dec = top->childContexts().at(2)->childContexts().at(1)->localDeclarations().at(0);
    QCOMPARE(dec->identifier(), Identifier(u"b"));

    closure = top->childContexts().at(2)->childContexts().at(1)->localDeclarations().at(1);
    QVERIFY(closure->identifier().isEmpty());

    funcType = closure->type<FunctionType>();
    QVERIFY(funcType);
    auto generatorType = funcType->returnType().dynamicCast<StructureType>();
    QVERIFY(generatorType);
    QCOMPARE(generatorType->qualifiedIdentifier(), QualifiedIdentifier(u"generator"));

    QVERIFY(dec->abstractType()->equals(closure->abstractType().constData()));
}

void TestDUChain::propertyUnionType()
{
    //                 0         1         2         3         4         5
    //                 012345678901234567890123456789012345678901234567890
    QByteArray method("<? class A { public string|int|float|bool $foo; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());

    StructureType::Ptr a = top->localDeclarations().first()->type<StructureType>();
    QVERIFY(a);

    QCOMPARE(top->childContexts().first()->localDeclarations().count(), 1);

    UnsureType::Ptr type = top->childContexts().first()->localDeclarations().first()->type<UnsureType>();

    QCOMPARE(type->typesSize(), 4u);
    QVERIFY(type->types()[0].abstractType().dynamicCast<IntegralType>());
    QVERIFY(type->types()[0].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);
    QVERIFY(type->types()[1].abstractType().dynamicCast<IntegralType>());
    QVERIFY(type->types()[1].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
    QVERIFY(type->types()[2].abstractType().dynamicCast<IntegralType>());
    QVERIFY(type->types()[2].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeFloat);
    QVERIFY(type->types()[3].abstractType().dynamicCast<IntegralType>());
    QVERIFY(type->types()[3].abstractType().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);
}

#include "moc_duchain.cpp"
