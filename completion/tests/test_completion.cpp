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
#include <language/codecompletion/codecompletiontesthelper.h>

#include "completion/context.h"
#include "completion/item.h"
#include "completion/helpers.h"
#include "completion/model.h"


using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestCompletion)

namespace Php
{

class TestCodeCompletionModel : public CodeCompletionModel
{
public:
    //normally set by worker, but in test we don't have a worker
    //NOTE: ignore the compiler warning about foundDeclarations being hidden
    //TODO: can this be fixed?
    void foundDeclarations(QList<KDevelop::CompletionTreeItemPointer> items, CodeCompletionContext* completionContext)
    {
        m_completionItems.clear();
        foreach (CompletionTreeItemPointer i, items) {
            m_completionItems << KSharedPtr<CompletionTreeElement>::staticCast(i);
        }
        m_completionContext = KDevelop::CodeCompletionContext::Ptr(completionContext);
        reset();
    }
};

/**
 * declaration of class A with a number of completion items
 * 
 * also introduces a instance of class A named $instA;
 */
const QByteArray testClassA(
  "class A {"
    // start non-static
    // public
    " public function pubf() {}"             // at(0)
    " public $pub;"                          // at(1)
    // protected
    " protected function protf() {}"         // at(2)
    " protected $prot;"                      // at(3)
    // private
    " private function privf() {}"           // at(4)
    " private $priv;"                        // at(5)
    // start static
    // public
    " static public function spubf() {}"     // at(6)
    " static public $spub;"                  // at(7)
    // const == static public
    " const c = 0;"                          // at(8)
    // protected
    " static protected function sprotf() {}" // at(9)
    " static protected $sprot;"              // at(10)
    // private
    " static private function sprivf() {}"   // at(11)
    " static private $spriv;"                // at(12)
  "} $instA = new A; "
);

/**
 * declaration of class B which extends class A
 * B has one new public member function
 * 
 * also introduces a instance of class B named $instB;
 */
const QByteArray testClassB(
  "class B extends A {"
    "public function __construct(){}" // at(0)
  "} $instB = new B; "
);

typedef CodeCompletionItemTester<CodeCompletionContext> PhpCompletionTester;

TestCompletion::TestCompletion()
{
}

void TestCompletion::dumpCompletionItems(QList<CompletionTreeItemPointer> items)
{
    kDebug() << items.count() << "completion items:";
    foreach ( CompletionTreeItemPointer item, items ) {
        kDebug() << item->declaration()->toString();
    }
}

void TestCompletion::publicObjectCompletion()
{
    TopDUContext* top = parse("<?php " + testClassA, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    PhpCompletionTester tester(top, "$blah; $instA->");
    
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::MemberAccess);
    
    QCOMPARE(tester.names, QStringList() << "pubf" << "pub");
}
void TestCompletion::publicStaticObjectCompletion()
{
    TopDUContext* top = parse("<?php " + testClassA, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    PhpCompletionTester tester(top, "$blah; A::");
    
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::StaticMemberAccess);
    
    QCOMPARE(tester.names, QStringList() << "spubf" << "$spub" << "c");
}
void TestCompletion::privateObjectCompletion()
{
    TopDUContext* top = parse("<?php " + testClassA, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());


    DUContext* funContext = top->childContexts().first()->localDeclarations().first()->internalContext();
    PhpCompletionTester tester(funContext, "$this->");
    
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::MemberAccess);
    
    QCOMPARE(tester.names, QStringList() << "pubf" << "pub" << "protf" << "prot" << "privf" << "priv");
}
void TestCompletion::privateStaticObjectCompletion()
{
    TopDUContext* top = parse("<?php " + testClassA, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().first()->localDeclarations().first()->internalContext();

    PhpCompletionTester tester(funContext, "self::");
    
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::StaticMemberAccess);
    
    QCOMPARE(tester.names, QStringList() << "spubf" << "$spub" << "c" << "sprotf" << "$sprot" << "sprivf" << "$spriv");
}
void TestCompletion::protectedObjectCompletion()
{
    TopDUContext* top = parse("<?php " + testClassA + testClassB, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().at(1)->localDeclarations().first()->internalContext();
    PhpCompletionTester tester(funContext, "$this->");
    
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::MemberAccess);
    
    QCOMPARE(tester.names, QStringList() << "__construct" << "pubf" << "pub" << "protf" << "prot");
}
void TestCompletion::protectedStaticObjectCompletion()
{
    TopDUContext* top = parse("<?php " + testClassA + testClassB, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().at(1)->localDeclarations().first()->internalContext();
    PhpCompletionTester tester(funContext, "self::");
    
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::StaticMemberAccess);
    
    QCOMPARE(tester.names, QStringList() << "spubf" << "$spub" << "c" << "sprotf" << "$sprot");
}

void TestCompletion::methodCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo(A $a, $b = null) {} } $i = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
      PhpCompletionTester tester(top, "$blah; $i->foo(");
      QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::NoMemberAccess);
      QVERIFY(tester.completionContext->parentContext());
      QCOMPARE(tester.completionContext->parentContext()->memberAccessOperation(),
                  CodeCompletionContext::FunctionCallAccess);

      CompletionTreeItemPointer item = searchDeclaration(tester.items, top->childContexts().at(0)->localDeclarations().at(0));
      QVERIFY(item);
      NormalDeclarationCompletionItem* item2 = dynamic_cast<NormalDeclarationCompletionItem*>(item.data());

      QString ret;
      createArgumentList(*item2, ret, 0);
      QCOMPARE(ret, QString("(A $a, mixed $b = null)"));
    }
    {
      PhpCompletionTester tester(top, "blah; $i->foo(new A(), ");
      QVERIFY(searchDeclaration(tester.items, top->childContexts().at(0)->localDeclarations().at(0)));
    }
}

void TestCompletion::functionCall()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A $a, $b = null) {}");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    PhpCompletionTester tester(top, "blah; foo(");
    QVERIFY(tester.completionContext->parentContext());

    QVERIFY(tester.completionContext->parentContext());
    QVERIFY(!tester.completionContext->parentContext()->parentContext());
    QCOMPARE(tester.completionContext->parentContext()->memberAccessOperation(),
                CodeCompletionContext::FunctionCallAccess);

    QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(1)));
}

void TestCompletion::newObjectFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class Foo { function bar() {} } ");
    DUChainReleaser releaseAddTop(addTop);
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a = new Foo(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    PhpCompletionTester tester(top, "blah; $a->");
    QCOMPARE(tester.items.count(), 1);
    QCOMPARE(tester.items.first()->declaration().data(), addTop->childContexts().first()->localDeclarations().first());
}

void TestCompletion::baseClass()
{
    QByteArray method("<? class A { public $avar; } class B extends A { public $bvar; } $a = new A(); $b = new B(); ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
      PhpCompletionTester tester(top, "$a->");
      QCOMPARE(tester.names, QStringList() << "avar");
    }

    {
      PhpCompletionTester tester(top, "$b->");
      QCOMPARE(tester.names, QStringList() << "bvar" << "avar");
    }
}

void TestCompletion::extendsFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class A { public $avar; } ");
    DUChainReleaser releaseAddTop(addTop);
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class B extends A { public $bvar; } $b = new B();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    PhpCompletionTester tester(top, "$b->");
    QCOMPARE(tester.items.count(), 2);
    QCOMPARE(tester.items.at(1)->declaration().data(), addTop->childContexts().first()->localDeclarations().first());
    QCOMPARE(tester.items.at(0)->declaration().data(), top->childContexts().first()->localDeclarations().first());
}


void TestCompletion::globalClassFromOtherFile()
{

    TopDUContext* addTop = parseAdditionalFile(IndexedString("/duchaintest/foo.php"), "<?php class A { } ");
    DUChainReleaser releaseAddTop(addTop);
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
/*
    PhpCompletionTester tester(top, "new ");
    QVERIFY(searchDeclaration(tester.items, addTop->localDeclarations().first()));
*/
}

void TestCompletion::codeModel()
{
    DUChainWriteLocker lock(DUChain::lock());
    uint count;
    const CodeModelItem* items;

    CodeModel::self().addItem(IndexedString("file:///foo"), QualifiedIdentifier("identifier"), CodeModelItem::Class);

    CodeModel::self().items(IndexedString("file:///foo"), count, items);
    bool found = false;
    for(uint i =0;i<count;++i) {
        if (items[0].id.identifier() == QualifiedIdentifier("identifier")) {
            found = true;
            QCOMPARE(items[i].kind, CodeModelItem::Class);
        }
    }
    QVERIFY(found);
}

class TestCodeCompletionContext : public CodeCompletionContext {
public:
    TestCodeCompletionContext(KDevelop::DUContextPointer context, const QString& text, const QString& followingText, int depth = 0)
        : CodeCompletionContext(context, text, followingText, depth)
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
    DUChainReleaser releaseAddTop(addTop);

    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? ?>");

    TopDUContext* top = parse(method, DumpNone, "file:///internal/projecttest1");
    DUChainReleaser releaseTop(top);

    DUChainWriteLocker lock(DUChain::lock());
    
    CodeCompletionItemTester<TestCodeCompletionContext> tester(top, "");
    QVERIFY(searchDeclaration(tester.items, addTop->localDeclarations().first()));
}


void TestCompletion::variable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {  } $a = new A();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    PhpCompletionTester tester(top, "");
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::NoMemberAccess);

    QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(1)));
}

void TestCompletion::variableStarted()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {  } $aaa = new A();");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    PhpCompletionTester tester(top, "s");
    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::NoMemberAccess);
    QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(1)));
}

void TestCompletion::nameNormalVariable()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $abc = 0; define('def', 0); class ghi {} ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    PhpCompletionTester tester(top, "");

    TestCodeCompletionModel* model = new TestCodeCompletionModel;
    model->foundDeclarations(tester.items, tester.completionContext.data());

    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::NoMemberAccess);

    CompletionTreeItemPointer itm = searchDeclaration(tester.items, top->localDeclarations().first());
    QVERIFY(itm);
    QCOMPARE(itm->data(model->index(0, Php::CodeCompletionModel::Name), Qt::DisplayRole, model).toString(),
        QString("ghi"));

    itm = searchDeclaration(tester.items, top->localDeclarations().at(1));
    QVERIFY(itm);
    QCOMPARE(itm->data(model->index(0, Php::CodeCompletionModel::Name), Qt::DisplayRole, model).toString(),
        QString("$abc"));

    itm = searchDeclaration(tester.items, top->localDeclarations().at(2));
    QVERIFY(itm);
    QCOMPARE(itm->data(model->index(0, Php::CodeCompletionModel::Name), Qt::DisplayRole, model).toString(),
        QString("def"));

    //don't delete model as its constructor does bad things (quit the current thread - we don't want that in test)
    //TODO find better solution that doesn't leak
}

void TestCompletion::nameClassMember()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public $abc = 0; } $b = new A;  ");

    TopDUContext* top = parse(method, DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    PhpCompletionTester tester(top, "$b->");

    TestCodeCompletionModel *model = new TestCodeCompletionModel;
    model->foundDeclarations(tester.items, tester.completionContext.data());

    QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::MemberAccess);

    CompletionTreeItemPointer itm = searchDeclaration(tester.items, top->childContexts().first()->localDeclarations().first());
    QVERIFY(itm);
    QCOMPARE(itm->data(model->index(0, Php::CodeCompletionModel::Name), Qt::DisplayRole, model).toString(),
        QString("abc"));

    //don't delete model as its constructor does bad things (quit the current thread - we don't want that in test)
    //TODO find better solution that doesn't leak
}

void TestCompletion::exceptions()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class MyExcpt extends Exception {} $excpt = new MyExcpt(); ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
      PhpCompletionTester tester(top, "throw");
      QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::ExceptionInstanceChoose);
      QCOMPARE(tester.items.count(), 1);
      QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(1)));
    }

    {
      PhpCompletionTester tester(top, "throw new");
      QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::ExceptionChoose);
      QCOMPARE(tester.items.count(), 2);
      QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(0)));
    }
    
    {
      PhpCompletionTester tester(top, "try { } catch(");
      QCOMPARE(tester.completionContext->memberAccessOperation(), CodeCompletionContext::ExceptionChoose);
      QCOMPARE(tester.items.count(), 2);
      QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(0)));
    }
}

void TestCompletion::multipleVarialbeDeclarationsWithSameIdentifier()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? $a=0;$a='0'; ");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    PhpCompletionTester tester(top, "");
    QVERIFY(searchDeclaration(tester.items, top->localDeclarations().at(1)));
    QVERIFY(!searchDeclaration(tester.items, top->localDeclarations().at(0)));
}

void TestCompletion::abstractMethods()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? abstract class A {  abstract function foo(); function bar(){} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().first()->localDeclarations().last()->internalContext();
    PhpCompletionTester tester(funContext, "$this->");
    QCOMPARE(tester.names, QStringList() << "bar");
}

void TestCompletion::interfaceMethods()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface A {  function foo(); } class B implements A { function bar(){} }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    DUContext* funContext = top->childContexts().last()->localDeclarations().first()->internalContext();
    PhpCompletionTester tester(funContext, "$this->");
    QCOMPARE(tester.names, QStringList() << "bar");
}
void TestCompletion::implementMethods()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface A { function foo(); } class B implements A {  }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    // context of class B
    DUContext* classContext = top->childContexts().last();
    PhpCompletionTester tester(classContext, "{");
    QCOMPARE(tester.items.count(), 1);
    QCOMPARE(tester.items.first()->declaration().data(), top->childContexts().first()->localDeclarations().first());
    
    //TODO: verify actual completion text
}

void TestCompletion::overrideMethods()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { function a(){} final function b(){}  } class B extends A {  }");

    TopDUContext* top = parse(method, DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    // context of class B
    DUContext* classContext = top->childContexts().last();
    PhpCompletionTester tester(classContext, "{");
    QCOMPARE(tester.items.count(), 1);
    QCOMPARE(tester.items.first()->declaration().data(), top->childContexts().first()->localDeclarations().first());
    
    //TODO: verify actual completion text
}

void TestCompletion::inArray() {
    TopDUContext* top = parse("", DumpAll);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());
    
    PhpCompletionTester tester(top, "<?php a = array(1, ");
    QVERIFY(tester.items.count() > 0);
    
    // TODO: compare to global completion list
}

}

#include "test_completion.moc"

