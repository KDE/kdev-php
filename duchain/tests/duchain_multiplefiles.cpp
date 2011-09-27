/* This file is part of KDevelop
    Copyright 2010 Niko Sams <niko.sams@gmail.com>

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

#include "duchain_multiplefiles.h"

#include <QtTest/QtTest>

#include <qtest_kde.h>

#include <tests/testcore.h>
#include <interfaces/ilanguagecontroller.h>
#include <language/backgroundparser/backgroundparser.h>
#include <tests/testproject.h>
#include <language/duchain/declaration.h>

QTEST_KDEMAIN(Php::TestDUChainMultipleFiles, GUI)

namespace Php
{

void TestDUChainMultipleFiles::initTestCase()
{
    DUChainTestBase::initTestCase();
    KDevelop::TestCore* core = dynamic_cast<KDevelop::TestCore*>(KDevelop::ICore::self());
    Q_ASSERT(core);
    m_projectController = new KDevelop::TestProjectController(core);
    core->setProjectController(m_projectController);
}

class TestFile : public QObject
{
    Q_OBJECT
public:
    TestFile(QByteArray contents, KDevelop::TestProject *project) : m_file("XXXXXX.php"), m_ready(false) {
        m_file.open();
        m_file.write(contents);
        m_file.close();
        project->addToFileSet(KDevelop::IndexedString(m_file.fileName()));
    }

    ~TestFile()
    {
        if (m_topContext) {
            KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
            KDevelop::DUChain::self()->removeDocumentChain(m_topContext.data());
        }
    }


    void parse(KDevelop::TopDUContext::Features features, int priority = 1)
    {
        m_ready = false;
        KDevelop::DUChain::self()->updateContextForUrl(KDevelop::IndexedString(m_file.fileName()), features, this, priority);
    }

    void waitForParsed()
    {
        QTime t;
        t.start();
        while (!m_ready) {
            Q_ASSERT(t.elapsed() < 60000);
            QTest::qWait(10);
        }
    }

    KDevelop::ReferencedTopDUContext topContext()
    {
        waitForParsed();
        return m_topContext;
    }

public slots:
    void updateReady(KDevelop::IndexedString url, KDevelop::ReferencedTopDUContext topContext)
    {
        Q_ASSERT(url.str() == m_file.fileName());
        m_ready = true;
        m_topContext = topContext;
    }

private:
    QTemporaryFile m_file;
    bool m_ready;
    KDevelop::ReferencedTopDUContext m_topContext;
};


void TestDUChainMultipleFiles::testImportsGlobalFunction()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    TestFile f1("<? function foo() {}", project);
    f1.parse(features);
    f1.waitForParsed();

    TestFile f2("<? foo();", project);
    f2.parse(features);
    f2.waitForParsed();

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    QVERIFY(f1.topContext());
    QVERIFY(f2.topContext());
    QVERIFY(f2.topContext()->imports(f1.topContext(), KDevelop::CursorInRevision(0, 0)));
}

void TestDUChainMultipleFiles::testImportsBaseClassNotYetParsed()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);


    TestFile f2("<? class B extends A {}", project);
    f2.parse(features);

    TestFile f1("<? class A {}", project);
    f1.parse(features, 100); //low priority, to make sure f2 is parsed first

    f1.waitForParsed();
    QTest::qWait(100);

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    QVERIFY(f2.topContext()->imports(f1.topContext(), KDevelop::CursorInRevision(0, 0)));
    QVERIFY(KDevelop::ICore::self()->languageController()->backgroundParser()->queuedCount() == 0);
}

void TestDUChainMultipleFiles::testNonExistingBaseClass()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    TestFile f1("<? class B extends A {}", project);
    f1.parse(features);
    f1.waitForParsed();

    //there must not be a re-enqueued parsejob
    QVERIFY(KDevelop::ICore::self()->languageController()->backgroundParser()->queuedCount() == 0);
}

void TestDUChainMultipleFiles::testImportsGlobalFunctionNotYetParsed()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    TestFile f2("<? foo2();", project);
    f2.parse(features);

    TestFile f1("<? function foo2() {}", project);
    f1.parse(features, 100); //low priority, to make sure f2 is parsed first

    f2.waitForParsed();
    QTest::qWait(100);

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    QVERIFY(f2.topContext()->imports(f1.topContext(), KDevelop::CursorInRevision(0, 0)));

}

void TestDUChainMultipleFiles::testNonExistingGlobalFunction()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    TestFile f2("<? foo3();", project);
    f2.parse(features);

    f2.waitForParsed();
     //there must not be a re-enqueued parsejob
    QVERIFY(KDevelop::ICore::self()->languageController()->backgroundParser()->queuedCount() == 0);
}

void TestDUChainMultipleFiles::testImportsStaticFunctionNotYetParsed()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    TestFile f2("<? C::foo();", project);
    f2.parse(features);

    TestFile f1("<? class C { public static function foo() {} }", project);
    f1.parse(features, 100); //low priority, to make sure f2 is parsed first

    f2.waitForParsed();
    QTest::qWait(100);

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    QVERIFY(f2.topContext()->imports(f1.topContext(), KDevelop::CursorInRevision(0, 0)));
}

void TestDUChainMultipleFiles::testNonExistingStaticFunction()
{
    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    TestFile f2("<? D::foo();", project);
    f2.parse(features);

    f2.waitForParsed();
     //there must not be a re-enqueued parsejob
    QVERIFY(KDevelop::ICore::self()->languageController()->backgroundParser()->queuedCount() == 0);
}

void TestDUChainMultipleFiles::testForeachImportedIdentifier()
{
    // see https://bugs.kde.org/show_bug.cgi?id=269369

    KDevelop::TopDUContext::Features features = KDevelop::TopDUContext::VisibleDeclarationsAndContexts;

    KDevelop::TestProject* project = new KDevelop::TestProject;
    m_projectController->clearProjects();
    m_projectController->addProject(project);

    // build dependency
    TestFile f1("<? class SomeIterator implements Countable, Iterator { }", project);
    f1.parse(features);
    f1.waitForParsed();

    TestFile f2("<?\n"
                "class A {\n"
                "  public function foo() { $i = $this->bar(); foreach($i as $a => $b) {} } \n"
                "  public function bar() { $a = new SomeIterator(); return $a; }\n"
                " }\n", project);

    for(int i = 0; i < 2; ++i) {
        if (i > 0) {
            features = static_cast<KDevelop::TopDUContext::Features>(features | KDevelop::TopDUContext::ForceUpdate);
        }
        f2.parse(features);
        f2.waitForParsed();
        QTest::qWait(100);

        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
        KDevelop::DUContext* ACtx = f2.topContext()->childContexts().first();
        QVERIFY(ACtx);
        KDevelop::Declaration* iDec = ACtx->childContexts().at(1)->localDeclarations().first();
        QVERIFY(iDec);
        KDevelop::Declaration* SomeIteratorDec = f1.topContext()->localDeclarations().first();
        QVERIFY(SomeIteratorDec);
        if (i == 0) {
            QEXPECT_FAIL("", "needs a full two-pass (i.e. get rid of PreDeclarationBuilder)", Continue);
        }
        QVERIFY(iDec->abstractType()->equals(SomeIteratorDec->abstractType().constData()));
        QVERIFY(f2.topContext()->imports(f1.topContext(), KDevelop::CursorInRevision(0, 0)));
    }
}

}

#include "duchain_multiplefiles.moc"
#include "moc_duchain_multiplefiles.cpp"
