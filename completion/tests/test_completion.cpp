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

#include "test_completion.h"

#include <QtTest/QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainpointer.h>

#include "types.h"
#include "completion/context.h"
#include "completion/items.h"
#include "completion/helpers.h"


using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestCompletion)

namespace Php
{

TestCompletion::TestCompletion()
{
}


void TestCompletion::objectCompletion()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo() {} public $bar; } $i = new A();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; $i->"));
    
    QCOMPARE(cptr->memberAccessOperation(), CodeCompletionContext::MemberAccess);

    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 2);
    QCOMPARE(itemList.first()->declaration().data(), top->childContexts().at(0)->localDeclarations().at(0));
    QCOMPARE(itemList.at(1)->declaration().data(), top->childContexts().at(0)->localDeclarations().at(1));

    release(top);
}

void TestCompletion::staticMembers()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public static function foo() {} public static $bar; } $i = new A();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; $i->"));
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 0);
    
    cptr = new CodeCompletionContext(DUContextPointer(top), "$blah; A::");
    QCOMPARE(cptr->memberAccessOperation(), CodeCompletionContext::StaticMemberChoose);
    itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 2);
    QCOMPARE(itemList.first()->declaration().data(), top->childContexts().at(0)->localDeclarations().at(0));
    QCOMPARE(itemList.at(1)->declaration().data(), top->childContexts().at(0)->localDeclarations().at(1));

    release(top);
}

void TestCompletion::functionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo(A $a, $b = null) {} } $i = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; $i->foo("));
    QCOMPARE(cptr->memberAccessOperation(), CodeCompletionContext::NoMemberAccess);
    QVERIFY(cptr->parentContext());
    QCOMPARE(cptr->parentContext()->memberAccessOperation(), CodeCompletionContext::FunctionCallAccess);

    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 1);
    QCOMPARE(itemList.first()->declaration().data(), top->childContexts().at(0)->localDeclarations().at(0));
    CompletionTreeItem* item = itemList.first().data();
    NormalDeclarationCompletionItem* item2 = dynamic_cast<NormalDeclarationCompletionItem*>(item);
    
    QString ret;
    createArgumentList(*item2, ret, 0);
    QCOMPARE(ret, QString("(A $a, $b = null)"));

    release(top);
}

void TestCompletion::functionCall2()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo(A $a, $b = null) {} } $i = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; $i->foo(new A(), "));
    QVERIFY(cptr->parentContext());
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 1);
    QCOMPARE(itemList.first()->declaration().data(), top->childContexts().at(0)->localDeclarations().at(0));
    QVERIFY(cptr->parentContext());
    QVERIFY(!cptr->parentContext()->parentContext());
    
    itemList = cptr->parentContext()->completionItems(SimpleCursor(), abort);
    qDebug() << itemList.count();
    
// itemList.swap(1, 
    release(top);
}

void TestCompletion::functionCall3()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A $a, $b = null) {}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; foo("));
    QVERIFY(cptr->parentContext());
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 1);
    QCOMPARE(itemList.first()->declaration().data(), top->localDeclarations().at(1));
    QVERIFY(cptr->parentContext());
    QVERIFY(!cptr->parentContext()->parentContext());
    
    itemList = cptr->parentContext()->completionItems(SimpleCursor(), abort);
    qDebug() << itemList.count();
    
// itemList.swap(1, 
    release(top);
}
void TestCompletion::testExpressionAt()
{
//     QString expr("bar(); foo->");
//     int startExpr = expressionAt(expr, expr.length());
//     QCOMPARE(expr.mid(startExpr).trimmed(), QString("foo->"));
    
//     QString expr = "bar(); foo(";
//     int startExpr = expressionAt(expr, expr.length());
//     qDebug() << "RESULT: " << startExpr << expr.mid(startExpr);
//     QCOMPARE(expr.mid(startExpr).trimmed(), QString("foo(0,"));
//     
//     expr = "bar(); foo->bar(";
//     startExpr = expressionAt(expr, expr.length());
//     QCOMPARE(expr.mid(startExpr).trimmed(), QString("foo->bar("));
// 
//     expr = "bar(); foo->bar(0, ";
//     startExpr = expressionAt(expr, expr.length());
//     QCOMPARE(expr.mid(startExpr).trimmed(), QString("foo->bar(0,"));
//     expr.split(1, 
}

}

#include "test_completion.moc"

