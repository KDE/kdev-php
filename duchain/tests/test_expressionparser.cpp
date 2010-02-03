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

#include "test_expressionparser.h"

#include <QtTest/QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/declaration.h>

#include "../types/structuretype.h"
#include "expressionparser.h"

using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestExpressionParser)

namespace Php
{

TestExpressionParser::TestExpressionParser()
{
}


void TestExpressionParser::newClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function foo() {} } $i = new A();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$i"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(res.type());
    QCOMPARE(StructureType::Ptr::staticCast(res.type())->qualifiedIdentifier(), QualifiedIdentifier("a"));
}
void TestExpressionParser::memberVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { /** @var A **/ public $foo; } $i = new A();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$i->foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(res.type());
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first(), top->childContexts().first()->localDeclarations().first());
    QCOMPARE(StructureType::Ptr::staticCast(res.type())->qualifiedIdentifier(), QualifiedIdentifier("a"));
}
void TestExpressionParser::memberFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo() {} } $i = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$i->foo()"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(res.type());
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type())->dataType() == IntegralType::TypeVoid);
    QCOMPARE(res.allDeclarations().size(), 1);
    QCOMPARE(res.allDeclarations().first(), top->childContexts().first()->localDeclarations().first());
}
void TestExpressionParser::globalFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo() {}");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(res.type());
    QVERIFY(FunctionType::Ptr::dynamicCast(res.type()));
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first(), top->localDeclarations().first());
}

void TestExpressionParser::chainCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function foo() { return $this; } } $a = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    FunctionType::Ptr fn = top->childContexts().first()->localDeclarations().first()->type<FunctionType>();
    QVERIFY(fn);
    QVERIFY(fn->returnType()->equals(top->localDeclarations().first()->abstractType().unsafeData()));

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$a->foo()"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type()->equals(top->localDeclarations().first()->abstractType().unsafeData()));

    res = p.evaluateType(QByteArray("$a->foo()->foo()->foo()"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type()->equals(top->localDeclarations().first()->abstractType().unsafeData()));
}
void TestExpressionParser::thisObject()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().first()->localDeclarations().first()->internalContext();
    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$this"), DUContextPointer(funContext), SimpleCursor(1, 0));
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first(), top->localDeclarations().first());
    QVERIFY(res.type());
    QVERIFY(StructureType::Ptr::dynamicCast(res.type()));
    QCOMPARE(StructureType::Ptr::dynamicCast(res.type())->declaration(top), top->localDeclarations().first());
}

void TestExpressionParser::integralTypes()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $foo=1;");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("123"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeInt));

    res = p.evaluateType(QByteArray("123.1"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeFloat));

    res = p.evaluateType(QByteArray("\"asdf\""), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("\"as $foo df\""), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("'asdf'"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("true"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeBoolean));

    res = p.evaluateType(QByteArray("TRUE"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeBoolean));

    res = p.evaluateType(QByteArray("null"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeNull));

    res = p.evaluateType(QByteArray("NULL"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeNull));
}

void TestExpressionParser::newObject()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("new A();"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(StructureType::Ptr::dynamicCast(res.type()));
    QCOMPARE(StructureType::Ptr::staticCast(res.type())->declaration(top), top->localDeclarations().first());
}

void TestExpressionParser::cast()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $foo = 1; ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("(string)$foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("(int)$foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("(double)$foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeFloat);

    res = p.evaluateType(QByteArray("(bool)$foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeBoolean);

    res = p.evaluateType(QByteArray("(array)$foo"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeArray);

    res = p.evaluateType(QByteArray("(object)$foo"), DUContextPointer(top), SimpleCursor(1, 0));
    kDebug() << res.type();
    kDebug() << res.type()->toString();
    QVERIFY(StructureType::Ptr::dynamicCast(res.type()));
    QVERIFY(StructureType::Ptr::staticCast(res.type())->qualifiedIdentifier() == QualifiedIdentifier("stdclass"));
}

void TestExpressionParser::operations()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $foo = 1; ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("'1' . '1'"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("1 . 1"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("1 + 1"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("'1' + '1'"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo .= '1'"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("$foo .= 1"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("$foo += 1"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo += '1'"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo *= 1"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo *= '1'"), DUContextPointer(top), SimpleCursor(1, 0));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QVERIFY(IntegralType::Ptr::staticCast(res.type())->dataType() == IntegralType::TypeInt);
}

void TestExpressionParser::findArg()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A{} function foo($arg, &$bar, A &$a) {  } ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);

    QCOMPARE(top->childContexts().size(), 3);
    QVERIFY(top->childContexts().at(0)->type() == DUContext::Class);
    QVERIFY(top->childContexts().at(1)->type() == DUContext::Function);
    QVERIFY(top->childContexts().at(2)->type() != DUContext::Function);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$arg"), DUContextPointer(top->childContexts().last()),
                                                    SimpleCursor(0, 47));
    QVERIFY(IntegralType::Ptr::dynamicCast(res.type()));
    QCOMPARE(IntegralType::Ptr::staticCast(res.type())->dataType(), static_cast<uint>(IntegralType::TypeMixed));

    res = p.evaluateType(QByteArray("$bar"), DUContextPointer(top->childContexts().last()),
                         SimpleCursor(0, 47));
    ReferenceType::Ptr type = ReferenceType::Ptr::dynamicCast(res.type());
    QVERIFY(type);
    QVERIFY(IntegralType::Ptr::dynamicCast(type->baseType()));
    QCOMPARE(IntegralType::Ptr::staticCast(type->baseType())->dataType(), static_cast<uint>(IntegralType::TypeMixed));

    res = p.evaluateType(QByteArray("$a"), DUContextPointer(top->childContexts().last()),
                         SimpleCursor(0, 47));
    type = ReferenceType::Ptr::dynamicCast(res.type());
    QVERIFY(type);
    QVERIFY(StructureType::Ptr::dynamicCast(type->baseType()));
    QCOMPARE(StructureType::Ptr::staticCast(type->baseType())->declaration(top), top->localDeclarations().first());
}

}

#include "test_expressionparser.moc"
