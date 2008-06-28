/* This file is part of KDevelop
    Copyright 2006 Hamish Rodda <rodda@kde.org>
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

#include <parsingenvironment.h>
#include <duchain.h>
#include <duchainlock.h>
#include <topducontext.h>
#include <dumptypes.h>


#include "parsesession.h"
#include "phpdebugvisitor.h"
#include "declarationbuilder.h"
#include "usebuilder.h"
#include "types.h"

using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::TestDUChain)

namespace QTest {
  template<>
  char* toString(const Cursor& cursor)
  {
    QByteArray ba = "Cursor(";
    ba += QByteArray::number(cursor.line()) + ", " + QByteArray::number(cursor.column());
    ba += ')';
    return qstrdup(ba.data());
  }
  template<>
  char* toString(const QualifiedIdentifier& id)
  {
    QByteArray arr = id.toString().toLatin1();
    return qstrdup(arr.data());
  }
  template<>
  char* toString(const Identifier& id)
  {
    QByteArray arr = id.toString().toLatin1();
    return qstrdup(arr.data());
  }
  template<>
  char* toString(const Declaration& def)
  {
    QString s = QString("Declaration %1 (%2): %3").arg(def.identifier().toString()).arg(def.qualifiedIdentifier().toString()).arg(reinterpret_cast<long>(&def));
    return qstrdup(s.toLatin1().constData());
  }
  template<>
  char* toString(const KSharedPtr<AbstractType>& type)
  {
    QString s = QString("Type: %1").arg(type ? type->toString() : QString("<null>"));
    return qstrdup(s.toLatin1().constData());
  }
}

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
    QCOMPARE(decVar->identifier(), Identifier("$i"));
    ClassType::Ptr type = decVar->type<ClassType>();
    QVERIFY(type);
    QCOMPARE(type->identifier(), QualifiedIdentifier("A"));
    QCOMPARE(type, dec->type<ClassType>());

    //class B
    dec = top->localDeclarations().at(1);
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 2);

    //$j
    decVar = top->localDeclarations().at(3);
    QCOMPARE(decVar->identifier(), Identifier("$j"));
    type = decVar->type<ClassType>();
    QVERIFY(type);
    QCOMPARE(type->identifier(), QualifiedIdentifier("B"));
    QCOMPARE(type, dec->type<ClassType>());

    //$i (2nd)
    decVar = top->localDeclarations().at(4);
    QCOMPARE(decVar->identifier(), Identifier("$i"));
    type = decVar->type<ClassType>();
    QVERIFY(type);
    QCOMPARE(type->identifier(), QualifiedIdentifier("B"));
    QCOMPARE(type, dec->type<ClassType>());

    //$i (3rd)
    decVar = top->localDeclarations().at(5);
    QCOMPARE(decVar->identifier(), Identifier("$i"));
    QVERIFY(decVar->type<IntegralType>());

    release(top);
}

void TestDUChain::testDeclareClass()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public function foo($i) {} }");

    TopDUContext* top = parse(method, DumpAll);
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
    QCOMPARE(contextClassA->childContexts().count(), 2);
    QCOMPARE(contextClassA->childContexts().first()->localScopeIdentifier(), QualifiedIdentifier("foo"));

    DUContext* contextMethodBodyFoo = contextClassA->childContexts().at(1);
    QCOMPARE(contextMethodBodyFoo->localScopeIdentifier(), QualifiedIdentifier("foo"));
    QCOMPARE(contextMethodBodyFoo->importedParentContexts().count(), 1);
    QCOMPARE(contextMethodBodyFoo->childContexts().count(), 0);
    QVERIFY(contextMethodBodyFoo->importedParentContexts().first().data() ==
                    contextClassA->childContexts().first());
    release(top);
}

void TestDUChain::testClassMemberVar()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { public $foo; }");

    TopDUContext* top = parse(method, DumpAll);
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

    QCOMPARE(contextClassA->localDeclarations().count(), 1);
    Declaration* foo = contextClassA->localDeclarations().first();
    QCOMPARE(foo->identifier(), Identifier("$foo"));

    release(top);
}

void TestDUChain::testVariableDeclaration()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} $i = new A();");

    TopDUContext* top = parse(method, DumpAll);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(!top->parentContext());
    QCOMPARE(top->childContexts().count(), 1);
    QCOMPARE(top->localDeclarations().count(), 2);

    Declaration* dec = top->localDeclarations().at(0);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("A"));
    QCOMPARE(dec->logicalInternalContext(top), top->childContexts().at(0));
    QCOMPARE(dec->uses().count(), 1);
    QCOMPARE(dec->uses().begin()->count(), 1);
    QCOMPARE(top->localDeclarations().at(1)->identifier(), Identifier("$i"));
    ClassType::Ptr type = top->localDeclarations().at(1)->type<ClassType>();
    QCOMPARE(type->identifier(), QualifiedIdentifier("A"));

    release(top);
}

void TestDUChain::testDeclareTypehintFunction()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A {} function foo(A $i) {}");

    DUContext* top = parse(method, DumpAll);

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

    QVERIFY(contextFunctionBodyFoo->importedParentContexts().first().data() ==
                    contextFunctionFoo);

    release(top);
}

void TestDUChain::testClassImplementsInterface()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? interface I { } class A implements I { }");

    DUContext* top = parse(method, DumpAll);

    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    //interface I
    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("I"));
    ClassType::Ptr typeI = dec->type<ClassType>();
    QCOMPARE(typeI->identifier(), QualifiedIdentifier("I"));
    QCOMPARE(typeI->classType(), ClassType::Interface);
    QVERIFY(typeI->declaration() == dec);
    QCOMPARE(typeI->extendsClasses().count(), 0);
    QCOMPARE(typeI->implementsInterfaces().count(), 0);

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
    ClassType::Ptr typeA = dec->type<ClassType>();
    QCOMPARE(typeA->identifier(), QualifiedIdentifier("A"));
    QCOMPARE(typeA->classType(), ClassType::Class);
    QVERIFY(typeA->declaration() == dec);
    QCOMPARE(typeA->extendsClasses().count(), 0);
    QCOMPARE(typeA->implementsInterfaces().count(), 1);
    QVERIFY(typeA->implementsInterfaces().at(0).data() == typeI.data());

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("A"));
    //class A imports interface I context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).data() == top->childContexts().at(0));

    QCOMPARE(dec->uses().count(), 0);

    release(top);
}

void TestDUChain::testClassExtends()
{
    //                 0         1         2         3         4         5         6         7
    //                 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray method("<? class A { } class B extends A { } ");

    DUContext* top = parse(method, DumpAll);

    DUChainWriteLocker lock(DUChain::lock());
    QCOMPARE(top->childContexts().count(), 2);
    QCOMPARE(top->localDeclarations().count(), 2);

    //class A
    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec->isDefinition());
    QCOMPARE(dec->identifier(), Identifier("A"));
    ClassType::Ptr typeA = dec->type<ClassType>();
    QCOMPARE(typeA->identifier(), QualifiedIdentifier("A"));
    QCOMPARE(typeA->classType(), ClassType::Class);
    QVERIFY(typeA->declaration() == dec);
    QCOMPARE(typeA->extendsClasses().count(), 0);
    QCOMPARE(typeA->implementsInterfaces().count(), 0);

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
    ClassType::Ptr typeB = dec->type<ClassType>();
    QCOMPARE(typeB->identifier(), QualifiedIdentifier("B"));
    QCOMPARE(typeB->classType(), ClassType::Class);
    QVERIFY(typeB->declaration() == dec);
    QCOMPARE(typeB->implementsInterfaces().count(), 0);
    QCOMPARE(typeB->extendsClasses().count(), 1);
    QVERIFY(typeB->extendsClasses().at(0).data() == typeA.data());

    QCOMPARE(dec->internalContext(), top->childContexts().at(1));
    QCOMPARE(dec->internalContext()->childContexts().count(), 0);
    QCOMPARE(dec->internalContext()->localScopeIdentifier(), QualifiedIdentifier("B"));
    //class B imports class A context
    QCOMPARE(dec->internalContext()->importedParentContexts().count(), 1);
    QVERIFY(dec->internalContext()->importedParentContexts().at(0).data() == top->childContexts().at(0));

    QCOMPARE(dec->uses().count(), 0);

    release(top);
}
void TestDUChain::release(DUContext* top)
{
  //KDevelop::EditorIntegrator::releaseTopRange(top->textRangePtr());
  if(dynamic_cast<TopDUContext*>(top))
    DUChain::self()->removeDocumentChain(static_cast<TopDUContext*>(top)->identity());
  delete top;
}

TopDUContext* TestDUChain::parse(const QByteArray& unit, DumpAreas dump)
{
    if (dump)
        kDebug(9007) << "==== Beginning new test case...:" << endl << unit;

    ParseSession* session = new ParseSession();
    session->setContents(unit);
    StartAst* ast = 0;
    if (!session->parse(&ast)) {
        kDebug() << "Parse failed";
        return 0;
    }

    if (dump & DumpAST) {
        kDebug(9007) << "===== AST:";
        DebugVisitor debugVisitor(session->tokenStream(), session->contents());
        debugVisitor.visitNode(ast);
    }

    static int testNumber = 0;
    QString url(QString("file:///internal/%1").arg(testNumber++));

    DeclarationBuilder declarationBuilder(session);
    TopDUContext* top = declarationBuilder.build(IndexedString(url), ast);

    UseBuilder useBuilder(session);
    useBuilder.buildUses(ast);
  
    if (dump & DumpDUChain) {
        kDebug(9007) << "===== DUChain:";

        DUChainWriteLocker lock(DUChain::lock());
        dumper.dump(top);
    }

    if (dump & DumpType) {
        kDebug(9007) << "===== Types:";
        DUChainWriteLocker lock(DUChain::lock());
        DumpTypes dt;
        foreach (const AbstractType::Ptr& type, declarationBuilder.topTypes())
            dt.dump(type.data());
    }

    if (dump)
        kDebug(9007) << "===== Finished test case.";

    delete session;

    return top;
}
}

#include "test_duchain.moc"
