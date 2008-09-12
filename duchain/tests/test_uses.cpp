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

#include "test_uses.h"

#include <QtTest/QtTest>

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

#include "phpparsejob.h"


using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestUses)

namespace Php
{

TestUses::TestUses()
{
}

void TestUses::newObject()
{

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class Foo {} $a = new Foo(); ");
    TopDUContext* top = parse(method, DumpNone, "/usestest/newObject.php");
    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->localDeclarations().first()->uses().keys().count(), 1);
    QCOMPARE(top->localDeclarations().first()->uses().values().count(), 1);
    QCOMPARE(top->localDeclarations().first()->uses().values().first().count(), 1);
    QCOMPARE(top->localDeclarations().first()->uses().keys().first(), IndexedString("/usestest/newObject.php"));
    QCOMPARE(top->localDeclarations().first()->uses().values().first().first(), SimpleRange(0, 25, 0, 28));
    release(top);
}

void TestUses::functionCall()
{

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo() {} foo(); ");
    TopDUContext* top = parse(method, DumpNone, "/usestest/functionCall.php");
    DUChainWriteLocker lock(DUChain::lock());
    Declaration* fun = top->localDeclarations().first();
    QCOMPARE(fun->uses().keys().count(), 1);
    QCOMPARE(fun->uses().values().count(), 1);
    QCOMPARE(fun->uses().values().first().count(), 1);
    QCOMPARE(fun->uses().keys().first(), IndexedString("/usestest/functionCall.php"));
    QCOMPARE(fun->uses().values().first().first(), SimpleRange(0, 21, 0, 24));
    release(top);
}

void TestUses::memberFunctionCall()
{

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function foo() {} } $a = new A(); $a->foo(); ");
    TopDUContext* top = parse(method, DumpNone, "/usestest/memberFunctionCall.php");
    DUChainWriteLocker lock(DUChain::lock());
    Declaration* fun = top->childContexts().first()->localDeclarations().first();
    QCOMPARE(fun->uses().keys().count(), 1);
    QCOMPARE(fun->uses().values().count(), 1);
    QCOMPARE(fun->uses().values().first().count(), 1);
    QCOMPARE(fun->uses().keys().first(), IndexedString("/usestest/memberFunctionCall.php"));
    QCOMPARE(fun->uses().values().first().first(), SimpleRange(0, 51, 0, 54));
    release(top);
}

void TestUses::memberVariable()
{

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public $foo; } $a = new A(); $a->foo; ");
    TopDUContext* top = parse(method, DumpNone, "/usestest/memberVariable.php");
    DUChainWriteLocker lock(DUChain::lock());
    Declaration* var = top->childContexts().first()->localDeclarations().first();
    QCOMPARE(var->uses().keys().count(), 1);
    QCOMPARE(var->uses().values().count(), 1);
    QCOMPARE(var->uses().values().first().count(), 1);
    QCOMPARE(var->uses().keys().first(), IndexedString("/usestest/memberVariable.php"));
    QCOMPARE(var->uses().values().first().first(), SimpleRange(0, 46, 0, 49));
    release(top);
}
void TestUses::variable()
{

    //                        0         1         2         3         4         5         6         7
    //                        01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<?php\nclass A { public $foo; } $a = new A(); $a; $a->foo; foo($a); ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());
    Declaration* var = top->localDeclarations().at(1);
    QCOMPARE(var->uses().keys().count(), 1);
    QCOMPARE(var->uses().values().count(), 1);
    QCOMPARE(var->uses().values().first().count(), 3);
    QCOMPARE(var->uses().values().first().at(0), SimpleRange(1, 42-3, 1, 44-3));
    QCOMPARE(var->uses().values().first().at(1), SimpleRange(1, 46-3, 1, 48-3));
    QCOMPARE(var->uses().values().first().at(2), SimpleRange(1, 59-3, 1, 61-3));
    release(top);
}

void TestUses::variableTwoDeclarations()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { } $a = new A(); $a; $a = 0; $a; ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* var = top->localDeclarations().at(1);
    QCOMPARE(var->uses().keys().count(), 1);
    QCOMPARE(var->uses().values().count(), 1);
    QCOMPARE(var->uses().values().first().count(), 3);
    QCOMPARE(var->uses().values().first().at(0), SimpleRange(0, 29, 0, 31));
    QCOMPARE(var->uses().values().first().at(1), SimpleRange(0, 33, 0, 35));
    QCOMPARE(var->uses().values().first().at(2), SimpleRange(0, 41, 0, 43));

    var = top->localDeclarations().at(2);
    QCOMPARE(var->uses().keys().count(), 1);
    QCOMPARE(var->uses().values().count(), 1);
    QCOMPARE(var->uses().values().first().count(), 3);
    QCOMPARE(var->uses().values().first().at(0), SimpleRange(0, 29, 0, 31));
    QCOMPARE(var->uses().values().first().at(1), SimpleRange(0, 33, 0, 35));
    QCOMPARE(var->uses().values().first().at(2), SimpleRange(0, 41, 0, 43));

    release(top);
}

void TestUses::classExtends()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { } class B extends A { } ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* a = top->localDeclarations().at(0);
    QCOMPARE(a->uses().keys().count(), 1);
    QCOMPARE(a->uses().values().count(), 1);
    QCOMPARE(a->uses().values().first().count(), 1);
    QCOMPARE(a->uses().values().first().at(0), SimpleRange(0, 31, 0, 32));

    release(top);
}
void TestUses::classImplements()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface A { } class B implements A { } ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* a = top->localDeclarations().at(0);
    QCOMPARE(a->uses().keys().count(), 1);
    QCOMPARE(a->uses().values().count(), 1);
    QCOMPARE(a->uses().values().first().count(), 1);
    QCOMPARE(a->uses().values().first().at(0), SimpleRange(0, 38, 0, 39));

    release(top);
}
void TestUses::classImplementsMultiple()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface A { } interface B { } class C implements A, B { } ");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* a = top->localDeclarations().at(0);
    QCOMPARE(a->uses().keys().count(), 1);
    QCOMPARE(a->uses().values().count(), 1);
    QCOMPARE(a->uses().values().first().count(), 1);
    QCOMPARE(a->uses().values().first().at(0), SimpleRange(0, 54, 0, 55));

    Declaration* b = top->localDeclarations().at(1);
    QCOMPARE(b->uses().keys().count(), 1);
    QCOMPARE(b->uses().values().count(), 1);
    QCOMPARE(b->uses().values().first().count(), 1);
    QCOMPARE(b->uses().values().first().at(0), SimpleRange(0, 57, 0, 58));

    release(top);
}
void TestUses::interfaceExtends()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface A { } interface B extends A { }");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* a = top->localDeclarations().at(0);
    QCOMPARE(a->uses().keys().count(), 1);
    QCOMPARE(a->uses().values().count(), 1);
    QCOMPARE(a->uses().values().first().count(), 1);
    QCOMPARE(a->uses().values().first().at(0), SimpleRange(0, 39, 0, 40));

    release(top);
}
void TestUses::interfaceExtendsMultiple()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface A { } interface B { } interface C extends A, B { }");
    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration* a = top->localDeclarations().at(0);
    QCOMPARE(a->uses().keys().count(), 1);
    QCOMPARE(a->uses().values().count(), 1);
    QCOMPARE(a->uses().values().first().count(), 1);
    QCOMPARE(a->uses().values().first().at(0), SimpleRange(0, 55, 0, 56));

    Declaration* b = top->localDeclarations().at(1);
    QCOMPARE(b->uses().keys().count(), 1);
    QCOMPARE(b->uses().values().count(), 1);
    QCOMPARE(b->uses().values().first().count(), 1);
    QCOMPARE(b->uses().values().first().at(0), SimpleRange(0, 58, 0, 59));

    release(top);
}
/*
TODO:
- static function call
- static member variable
- constant
- parent::?
- self::
*/
}

#include "test_uses.moc"
