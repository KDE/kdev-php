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

#include "duchaintestbase.h"

#include <QtTest/QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/indexedstring.h>
#include <kstandarddirs.h>
#include <kcomponentdata.h>

#include "dumptypes.h"
#include "parsesession.h"
#include "phpdebugvisitor.h"
#include "declarationbuilder.h"
#include "usebuilder.h"
#include "../helper.h"

using namespace KTextEditor;
using namespace KDevelop;


namespace Php
{

DUChainTestBase::DUChainTestBase()
{
    KComponentData kd("kdevphpsupport");
}

void DUChainTestBase::initTestCase()
{
    for (uint i=0; i < internalFunctionFilesCount; i++) {
        if (!DUChain::self()->chainForDocument(internalFunctionFiles[i])) {
            QByteArray content("<?php ");
            if (i==0) {
                content += "function substr() {} class stdClass {} ";
            }
            parseAdditionalFile(internalFunctionFiles[i], content);
        }
    }
}

CompletionTreeItemPointer DUChainTestBase::searchDeclaration(QList<CompletionTreeItemPointer> items, Declaration* declaration)
{
    foreach (CompletionTreeItemPointer item, items) {
        if (item->declaration().data() == declaration) {
            return item;
        }
    }
    return CompletionTreeItemPointer();
}

bool DUChainTestBase::hasImportedParentContext(TopDUContext* top, DUContext* lookingFor)
{
    foreach (DUContext::Import import, top->importedParentContexts()) {
        if (import.context() == lookingFor) {
            return true;
        }
    }
    return false;
}

void DUChainTestBase::release(TopDUContext* top)

{
  //KDevelop::EditorIntegrator::releaseTopRange(top->textRangePtr());

  TopDUContextPointer tp(top);
  DUChain::self()->removeDocumentChain(static_cast<TopDUContext*>(top));
  Q_ASSERT(!tp);
}

TopDUContext* DUChainTestBase::parseAdditionalFile(IndexedString fileName, QByteArray contents)
{
    ParseSession* session = new ParseSession();
    session->setContents(contents);
    StartAst* ast = 0;
    if (!session->parse(&ast)) qFatal("can't parse");

    DeclarationBuilder declarationBuilder(session);
    TopDUContext* top = declarationBuilder.build(fileName, ast);
    
    UseBuilder useBuilder(session);
    useBuilder.buildUses(ast);

    delete session;
    
    return top;
}

TopDUContext* DUChainTestBase::parse(const QByteArray& unit, DumpAreas dump, QString url)
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
    if (url.isEmpty()) url = QString("file:///internal/%1").arg(testNumber++);
    

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
            dt.dump(type.unsafeData());
    }

    if (dump)
        kDebug(9007) << "===== Finished test case.";

    delete session;

    return top;
}
}

#include "duchaintestbase.moc"

