/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "expressionparser.h"

#include <QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/problem.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/declaration.h>

#include "../types/structuretype.h"
#include "../expressionparser.h"

using namespace KDevelop;

QTEST_MAIN(Php::TestExpressionParser)

namespace Php
{

TestExpressionParser::TestExpressionParser()
{
}

void TestExpressionParser::newClass_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? class A { function __construct($a){} function foo() {} } $i = new A(1);";

    QTest::newRow("trailingCommaInConstructor") << "<? class A { function __construct($a,){} function foo() {} } $i = new A(1);";

    QTest::newRow("trailingCommaInInstantiation") << "<? class A { function __construct($a,){} function foo() {} } $i = new A(1,);";
}

void TestExpressionParser::newClass()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$i"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QCOMPARE(res.type().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestExpressionParser::newSelf()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function self() {  } }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType( QByteArray("new self()"),
                                        DUContextPointer(top->childContexts().first()->childContexts().last()),
                                        CursorInRevision(0, 30));
    QVERIFY(res.type());
    QCOMPARE(res.type().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
}

void TestExpressionParser::newStatic()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function self() {  } }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType( QByteArray("new static()"),
                                        DUContextPointer(top->childContexts().first()->childContexts().last()),
                                        CursorInRevision(0, 30));
    QVERIFY(res.type().dynamicCast<StructureType>());
    QCOMPARE(res.type().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
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
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$i->foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first().data(), top->childContexts().first()->localDeclarations().first());
    QCOMPARE(res.type().staticCast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier(u"a"));
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
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$i->foo()"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeVoid);
    QCOMPARE(res.allDeclarations().size(), 1);
    QCOMPARE(res.allDeclarations().first().data(), top->childContexts().first()->localDeclarations().first());
}

void TestExpressionParser::newTrait()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? trait A { function foo() {} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());

    QCOMPARE(top->childContexts().size(), 1);
    QVERIFY(top->childContexts().at(0)->type() == DUContext::Class);
}

void TestExpressionParser::newTraitWithAbstractMethod()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? trait A { public abstract function foo(); }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());

    QCOMPARE(top->childContexts().size(), 1);
    QVERIFY(top->childContexts().at(0)->type() == DUContext::Class);
}

void TestExpressionParser::invalidTrait_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("constant") << "<? trait A { const FOO = ''; }\n";
}

void TestExpressionParser::invalidTrait()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
}

void TestExpressionParser::invalidTraitUse_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("abstractModifier") << "<? trait A { public function foo(){} } class Foo { use A { A::foo as abstract bla; } }\n";

    QTest::newRow("staticModifier") << "<? trait A { public function foo(){} } class Foo { use A { A::foo as static bla; } }\n";

    QTest::newRow("finalModifier") << "<? trait A { public function foo(){} } class Foo { use A { A::foo as final bla; } }\n";

    QTest::newRow("abstract") << "<? trait A { public function foo(){} } class Foo { use A { A::foo as abstract; } }\n";

    QTest::newRow("static") << "<? trait A { public function foo(){} } class Foo { use A { A::foo as static; } }\n";

    QTest::newRow("final") << "<? trait A { public function foo(){} } class Foo { use A { A::foo as final; } }\n";

    QTest::newRow("traitMethodCollision") << "<? trait A { public function foo(){} } trait B { public function foo(){} } class Foo { use A,B; }\n";

    QTest::newRow("propertyCollision") << "<? trait A { public $arg; } class Foo { use A; public $arg; }\n";
}

void TestExpressionParser::invalidTraitUse()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
}

void TestExpressionParser::namespaceUseNameConflict()
{
    QByteArray alias("<?php namespace Bar { class Foo {} use Foo; }\n");

    TopDUContext* top = parse(alias, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
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
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type().dynamicCast<FunctionType>());
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first().data(), top->localDeclarations().first());
}

void TestExpressionParser::globalFunctionCall_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? function foo($a) {} foo(1);";

    QTest::newRow("trailingComma") << "<? function foo($a) {} foo(1,);";
}

void TestExpressionParser::globalFunctionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type().dynamicCast<FunctionType>());
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first().data(), top->localDeclarations().first());
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
    QVERIFY(fn->returnType()->equals(top->localDeclarations().first()->abstractType().data()));

    ExpressionParser p(true);
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$a->foo()"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type()->equals(top->localDeclarations().first()->abstractType().data()));

    res = p.evaluateType(QByteArray("$a->foo()->foo()->foo()"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QVERIFY(res.type()->equals(top->localDeclarations().first()->abstractType().data()));
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
    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$this"), DUContextPointer(funContext), CursorInRevision(1, 0));
    QCOMPARE(res.allDeclarations().count(), 1);
    QCOMPARE(res.allDeclarations().first().data(), top->localDeclarations().first());
    QVERIFY(res.type());
    QVERIFY(res.type().dynamicCast<StructureType>());
    QCOMPARE(res.type().staticCast<StructureType>()->declaration(top), top->localDeclarations().first());
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

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("123"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeInt));

    res = p.evaluateType(QByteArray("123.1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeFloat));

    res = p.evaluateType(QByteArray("\"asdf\""), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("\"as $foo df\""), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("'asdf'"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("true"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeBoolean));

    res = p.evaluateType(QByteArray("TRUE"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeBoolean));

    res = p.evaluateType(QByteArray("null"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeNull));

    res = p.evaluateType(QByteArray("NULL"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeNull));
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

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("new A();"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<StructureType>());
    QCOMPARE(res.type().staticCast<StructureType>()->declaration(top), top->localDeclarations().first());
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

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("(string)$foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("(int)$foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("(double)$foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeFloat);

    res = p.evaluateType(QByteArray("(bool)$foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);

    res = p.evaluateType(QByteArray("(array)$foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeArray);

    res = p.evaluateType(QByteArray("(object)$foo"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<StructureType>());
    QVERIFY(res.type().staticCast<StructureType>()->qualifiedIdentifier() == QualifiedIdentifier(u"stdclass"));
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

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("'1' . '1'"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("1 . 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("1 + 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("1 ** 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("'1' + '1'"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo .= '1'"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("$foo .= 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeString);

    res = p.evaluateType(QByteArray("$foo += 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo += '1'"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo *= 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo *= '1'"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo **= 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);

    res = p.evaluateType(QByteArray("$foo = 3 > 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);

    res = p.evaluateType(QByteArray("$foo = 3 != 1"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);

    res = p.evaluateType(QByteArray("$foo = $a instanceof A"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeBoolean);

    res = p.evaluateType(QByteArray("$foo = 3 <=> 2"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QVERIFY(res.type().staticCast<IntegralType>()->dataType() == IntegralType::TypeInt);
}

void TestExpressionParser::findArg_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? class A{} function foo($arg, &$bar, A &$a) {  } ";

    QTest::newRow("trailingComma") << "<? class A{} function foo($arg, &$bar, A &$a,) {  } ";
}

void TestExpressionParser::findArg()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);

    QCOMPARE(top->childContexts().size(), 3);
    QVERIFY(top->childContexts().at(0)->type() == DUContext::Class);
    QVERIFY(top->childContexts().at(1)->type() == DUContext::Function);
    QVERIFY(top->childContexts().at(2)->type() != DUContext::Function);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$arg"), DUContextPointer(top->childContexts().last()),
                                                    CursorInRevision(0, 47));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));

    res = p.evaluateType(QByteArray("$bar"), DUContextPointer(top->childContexts().last()),
                         CursorInRevision(0, 47));
    auto type = res.type().dynamicCast<ReferenceType>();
    QVERIFY(type);
    QVERIFY(type->baseType().dynamicCast<IntegralType>());
    QCOMPARE(type->baseType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));

    res = p.evaluateType(QByteArray("$a"), DUContextPointer(top->childContexts().last()),
                         CursorInRevision(0, 47));
    type = res.type().dynamicCast<ReferenceType>();
    QVERIFY(type);
    QVERIFY(type->baseType().dynamicCast<StructureType>());
    QCOMPARE(type->baseType().staticCast<StructureType>()->declaration(top), top->localDeclarations().first());
}

void TestExpressionParser::array_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? $a = array(1,2,3);\n";

    QTest::newRow("shortSyntax") << "<? $a = [1,2,3];\n";

    QTest::newRow("staticNormalSyntax") << "<? static $a = array(1,2,3);\n";

    QTest::newRow("staticShortSyntax") << "<? static $a = [1,2,3];\n";
}

void TestExpressionParser::array()
{
    // see bug https://bugs.kde.org/show_bug.cgi?id=237110

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);
    QCOMPARE(top->localDeclarations().first()->abstractType().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeArray));

    ExpressionEvaluationResult res = p.evaluateType("$b = $a[0]", DUContextPointer(top), CursorInRevision(0, 22));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QEXPECT_FAIL("", "we'd need advanced array support to know that [0] returns a string...", Continue);
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));
    // fallback
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
}

void TestExpressionParser::arrayFunctionDereferencing_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("globalFunction") << "<? function foo() { return [1, 2]; }\n"
                                       "$a = foo()[0];\n";

    QTest::newRow("classMethod") << "<? class foo{ function bar() { return [1, 2]; } }\n"
                                       "$obj = new foo(); $a = $obj->bar()[0];\n";

    QTest::newRow("staticClassMethod") << "<? class foo{ static function bar() { return [1, 2]; } }\n"
                                       "$a = foo::bar()[0];\n";
}

void TestExpressionParser::arrayFunctionDereferencing()
{
    // see bug https://bugs.kde.org/show_bug.cgi?id=305779
    QFETCH(QString, code);
    /*
    QByteArray method("<? function foo() { return [1, 2]; }\n"
                      "class obj { static function bar() { return [1, 2]; } }\n"
                      "$myObj = new obj();\n"
                      // actual test stuff:
                      "$a = foo()[0];\n"
                      "$b = $myObj->bar()[0];\n"
                      "$c = obj::bar()[0];\n");*/

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    Declaration* decl = top->localDeclarations().last();
    auto type = decl->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QEXPECT_FAIL("", "we'd need advanced array support to know that [0] returns a int...", Continue);
    QCOMPARE(type->dataType(), static_cast<uint>(IntegralType::TypeInt));
    // fallback
    QCOMPARE(type->dataType(), static_cast<uint>(IntegralType::TypeMixed));
}

void TestExpressionParser::arrayLiteralDereferencing_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? $a = array(1,2,3)[1];\n";

    QTest::newRow("shortSyntax") << "<? $a = [1,2,3][1];\n";
}

void TestExpressionParser::arrayLiteralDereferencing()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    Declaration* decl = top->localDeclarations().last();
    auto type = decl->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QEXPECT_FAIL("", "we'd need advanced array support to know that [0] returns a int...", Continue);
    QCOMPARE(type->dataType(), static_cast<uint>(IntegralType::TypeInt));
    // fallback
    QCOMPARE(type->dataType(), static_cast<uint>(IntegralType::TypeMixed));
}

void TestExpressionParser::stringAsArray_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("constantEncapsedString") << "<? $a = 'string'[1];\n";

    QTest::newRow("dynamicString") << "<? $string = 'Hello';\n"
                                      "$a = \"$string World\"[1];\n";
}

void TestExpressionParser::stringAsArray()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    Declaration* decl = top->localDeclarations().last();
    auto type = decl->abstractType().dynamicCast<IntegralType>();
    QVERIFY(type);
    QCOMPARE(type->dataType(), static_cast<uint>(IntegralType::TypeString));
}

void TestExpressionParser::classMemberOnInstantiation()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A{ function foo(){ return 'a'; } } $a = (new A())->foo();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$a"), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));
}

void TestExpressionParser::classNameConstant_data()
{
    QTest::addColumn<QString>("NSconst");

    QTest::newRow("fullNamespace") << "\\NS\\ClassName::class";
    QTest::newRow("normalNamespace") << "NS\\ClassName::class";
    QTest::newRow("inNamespace") << "$n";
}

void TestExpressionParser::classNameConstant()
{
    QFETCH(QString, NSconst);

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? namespace NS { class ClassName { } $n=ClassName::class; }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);

    ExpressionEvaluationResult res = p.evaluateType(NSconst.toUtf8(), DUContextPointer(top), CursorInRevision(1, 0));
    QVERIFY(res.type());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));
}

void TestExpressionParser::invalidVariadicFunction_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("defaultValue") << "<? function foo(...$i=NULL) { } \n";

    QTest::newRow("multipleVariadics") << "<? function foo(...$i, ...$j) { } \n";
}

void TestExpressionParser::invalidVariadicFunction()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
}

void TestExpressionParser::invalidArgumentUnpacking()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? function foo($a, $b, $c){}; $d = [ 1, 2 ]; foo(...$d, $e);");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
}

void TestExpressionParser::closure_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? $f = function($a, $b) { return $a + $b; }; \n";

    QTest::newRow("trailingComma") << "<? $f = function($a, $b,) { return $a + $b; }; \n";
}

void TestExpressionParser::closure()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);

    QCOMPARE(top->childContexts().size(), 2);
    QVERIFY(top->childContexts().at(0)->type() == DUContext::Function);
    QVERIFY(top->childContexts().at(1)->type() == DUContext::Other);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$a"), DUContextPointer(top->childContexts().at(0)),
                                                    CursorInRevision(0, 20));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));

    res = p.evaluateType(QByteArray("$b"), DUContextPointer(top->childContexts().at(0)),
                         CursorInRevision(0, 20));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
}

void TestExpressionParser::closureUse_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("normalSyntax") << "<? $c = 'foo'; $f = function($a, $b) use ($c) { return $c . ':' . $a . '/' . $b; }; \n";

    QTest::newRow("trailingCommaInParameterList") << "<? $c = 'foo'; $f = function($a, $b,) use ($c) { return $c . ':' . $a . '/' . $b; }; \n";

    QTest::newRow("trailingCommaInUseList") << "<? $c = 'foo'; $f = function($a, $b) use ($c,) { return $c . ':' . $a . '/' . $b; }; \n";
}

void TestExpressionParser::closureUse()
{
    QFETCH(QString, code);

    TopDUContext* top = parse(code.toUtf8(), DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(top->problems().isEmpty());

    ExpressionParser p(true);

    QCOMPARE(top->childContexts().size(), 3);
    QVERIFY(top->childContexts().at(0)->type() == DUContext::Function);
    QVERIFY(top->childContexts().at(1)->type() == DUContext::Other);
    QVERIFY(top->childContexts().at(2)->type() == DUContext::Other);

    ExpressionEvaluationResult res = p.evaluateType(QByteArray("$c"), DUContextPointer(top->childContexts().at(1)),
                                                    CursorInRevision(0, 50));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeString));

    res = p.evaluateType(QByteArray("$a"), DUContextPointer(top->childContexts().at(0)),
                                                    CursorInRevision(0, 34));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));

    res = p.evaluateType(QByteArray("$b"), DUContextPointer(top->childContexts().at(0)),
                         CursorInRevision(0, 34));
    QVERIFY(res.type().dynamicCast<IntegralType>());
    QCOMPARE(res.type().staticCast<IntegralType>()->dataType(), static_cast<uint>(IntegralType::TypeMixed));
}

void TestExpressionParser::closureInvalidUse()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $c = 'foo'; $f = function($a, $b) use () { return $c . ':' . $a . '/' . $b; }; \n");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock;

    QVERIFY(!top->problems().isEmpty());
}

}

#include "moc_expressionparser.cpp"
