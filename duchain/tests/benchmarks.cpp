/* This file is part of KDevelop
   Copyright 2009 Milian Wolff <mail@milianw.de>

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
#include "benchmarks.h"

#include <QtTest/QtTest>
#include <QtCore/QFile>

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

#include "phpparsejob.h"
#include "parsesession.h"
#include "declarationbuilder.h"
#include "usebuilder.h"

using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::Benchmarks)

namespace Php
{

// makro defined by cmake, points to the sourcedir of _this_ file
const QString srcPath(KDESRCDIR);

Benchmarks::Benchmarks()
{
}

void Benchmarks::initTestCase()
{
    DUChain::self()->disablePersistentStorage();
}

QFile* Benchmarks::getInternalFile()
{
    QFile* file = new QFile(srcPath + "../../phpfunctions.php");
    kDebug() << file->fileName();
    Q_ASSERT(file->exists());
    file->open(QIODevice::ReadOnly);
    Q_ASSERT(!file->error());
    Q_ASSERT(file->isReadable());
    return file;
}

void Benchmarks::parser()
{
    QFile* file = getInternalFile();
    QBENCHMARK {
        ParseSession session = ParseSession();
        session.setContents(file->readAll());
        StartAst* ast = 0;
        session.parse(&ast);
    }
    delete file;
}

void Benchmarks::declarationBuilder()
{
    QFile* file = getInternalFile();
    ParseSession session = ParseSession();
    session.setContents(file->readAll());
    delete file;
    StartAst* ast = 0;
    session.parse(&ast);
    QBENCHMARK {
        DeclarationBuilder builder(&session);
        ReferencedTopDUContext top = builder.build(IndexedString("InternalFunctions.php"), ast);

        if ( true ) {
            DUChainWriteLocker lock(DUChain::lock());
            kDebug() << top->localDeclarations().size();
        }
    }
}

void Benchmarks::useBuilder()
{
    QFile* file = getInternalFile();
    ParseSession session = ParseSession();
    session.setContents(file->readAll());
    delete file;
    StartAst* ast = 0;
    session.parse(&ast);
    DeclarationBuilder builder(&session);
    KDevelop::ReferencedTopDUContext chain = builder.build(IndexedString("BigTestFile.php"), ast);
    QBENCHMARK {
        UseBuilder useBuilder(&session);
        useBuilder.buildUses(ast);
    }
}

}

#include "benchmarks.moc"
