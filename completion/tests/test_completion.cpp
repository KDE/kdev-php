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
#include <language/duchain/types/structuretype.h>
#include <language/duchain/codemodel.h>

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

void TestCompletion::methodCall()
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
    CompletionTreeItemPointer item = searchDeclaration(itemList, top->childContexts().at(0)->localDeclarations().at(0));
    QVERIFY(item);
    NormalDeclarationCompletionItem* item2 = dynamic_cast<NormalDeclarationCompletionItem*>(item.data());

    QString ret;
    createArgumentList(*item2, ret, 0);
    QCOMPARE(ret, QString("(A $a, $b = null)"));


    cptr = new CodeCompletionContext(DUContextPointer(top), "$blah; $i->foo(new A(), ");
    itemList = cptr->completionItems(SimpleCursor(), abort);
    QVERIFY(searchDeclaration(itemList, top->childContexts().at(0)->localDeclarations().at(0)));

    release(top);
}

void TestCompletion::functionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A $a, $b = null) {}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());
    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; foo("));
    QVERIFY(cptr->parentContext());

    QVERIFY(cptr->parentContext());
    QVERIFY(!cptr->parentContext()->parentContext());
    QCOMPARE(cptr->parentContext()->memberAccessOperation(), CodeCompletionContext::FunctionCallAccess);

    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);

    bool found = false;
    foreach (CompletionTreeItemPointer item, itemList) {
        if (item->declaration().data() == top->localDeclarations().at(1)) {
            found = true;
        }
    }
    QVERIFY(found);
    
    release(top);
}

void TestCompletion::newObjectFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class Foo { function bar() {} } ");
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = new Foo(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$blah; $a->"));
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 1);
    QCOMPARE(itemList.first()->declaration().data(), addTop->childContexts().first()->localDeclarations().first());

    release(addTop);
    release(top);
}

void TestCompletion::baseClass()
{
    QByteArray method("<? class A { public $avar; } class B extends A { public $bvar; } $a = new A(); $b = new B(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$a->"));
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 1);
    QCOMPARE(itemList.first()->declaration().data(), top->childContexts().first()->localDeclarations().first());

    cptr = new CodeCompletionContext(DUContextPointer(top), "$b->");
    itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 2);
    QCOMPARE(itemList.at(1)->declaration().data(), top->childContexts().first()->localDeclarations().first());
    QCOMPARE(itemList.at(0)->declaration().data(), top->childContexts().at(1)->localDeclarations().first());

    release(top);
}

void TestCompletion::extendsFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class A { public $avar; } ");
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B extends A { public $bvar; } $b = new B();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "$b->"));
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 2);
    QCOMPARE(itemList.at(1)->declaration().data(), addTop->childContexts().first()->localDeclarations().first());
    QCOMPARE(itemList.at(0)->declaration().data(), top->childContexts().first()->localDeclarations().first());

    release(addTop);
    release(top);
}


void TestCompletion::globalClassFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class A { } ");
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());
/*
    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), "new "));
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QVERIFY(searchDeclaration(itemList, addTop->localDeclarations().first()));
*/
    release(addTop);
    release(top);
}

void TestCompletion::codeModel()
{
    DUChainWriteLocker lock(DUChain::lock());
    uint count;
    const CodeModelItem* items;

    CodeModel::self().addItem(IndexedString("file:///foo"), QualifiedIdentifier("identifier"), CodeModelItem::Class);

    CodeModel::self().items(IndexedString("file:///foo"), count, items);
    bool found = false;
    qDebug() << "found items: " << count;
    for(uint i =0;i<count;++i) {
        qDebug() << "item identifier: " << items[0].id.identifier().toString();
        if (items[0].id.identifier() == QualifiedIdentifier("identifier")) {
            found = true;
            QCOMPARE(items[i].kind, CodeModelItem::Class);
        }
    }
    QVERIFY(found);
}

class TestCodeCompletionContext : public CodeCompletionContext {
public:
    TestCodeCompletionContext(KDevelop::DUContextPointer context, const QString& text, int depth = 0)
        : CodeCompletionContext(context, text, depth)
    { }
protected:
    QList<QSet<IndexedString> > completionFiles() {
        QList<QSet<IndexedString> > ret;
        QSet<IndexedString> set;
        set << IndexedString("file:///internal/projecttest0");
        set << IndexedString("file:///internal/projecttest1");
        ret << set;
        return ret;
    }
};

void TestCompletion::projectFileClass()
{
    TopDUContext* addTop = parseAdditionalFile(IndexedString("file:///internal/projecttest0"), "<? class B {} ");

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? ?>");

    TopDUContext* top = parse(method, DumpNone, "file:///internal/projecttest1");

    DUChainWriteLocker lock(DUChain::lock());
    CodeCompletionContext::Ptr cptr(new TestCodeCompletionContext(DUContextPointer(top), ""));
    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QVERIFY(searchDeclaration(itemList, addTop->localDeclarations().first()));

    release(addTop);
    release(top);
}

void TestCompletion::thisCompletion()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo() {} public $bar; }");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().first()->localDeclarations().first()->internalContext();
    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(funContext), "$this->"));

    QCOMPARE(cptr->memberAccessOperation(), CodeCompletionContext::MemberAccess);

    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    QCOMPARE(itemList.count(), 2);
    QCOMPARE(itemList.first()->declaration().data(), top->childContexts().at(0)->localDeclarations().at(0));
    QCOMPARE(itemList.at(1)->declaration().data(), top->childContexts().at(0)->localDeclarations().at(1));

    release(top);
}


void TestCompletion::variable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {  } $a = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    CodeCompletionContext::Ptr cptr(new CodeCompletionContext(DUContextPointer(top), ""));

    QCOMPARE(cptr->memberAccessOperation(), CodeCompletionContext::NoMemberAccess);

    bool abort = false;
    QList<CompletionTreeItemPointer> itemList = cptr->completionItems(SimpleCursor(), abort);
    qDebug() << itemList.first()->declaration()->toString();
    QVERIFY(searchDeclaration(itemList, top->localDeclarations().at(1)));

    release(top);
}

}

#include "test_completion.moc"

