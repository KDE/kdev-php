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

using namespace KTextEditor;
using namespace KDevelop;

QTEST_MAIN(Php::Benchmarks)

namespace Php
{

// makro defined by cmake
const QString srcPath(KDESRCDIR);

Benchmarks::Benchmarks()
{
}

void Benchmarks::phpParser()
{
    // cmake defines the makro KDESRCDIR
    QFile testFile(srcPath + "/../../create_functions.php");
    QVERIFY(testFile.exists());
    testFile.open(QIODevice::ReadOnly);
    QVERIFY(!testFile.error());
    QVERIFY(testFile.isReadable());
    QBENCHMARK {
        ParseSession session = ParseSession();
        session.setContents(testFile.readAll());
        StartAst* ast = 0;
        session.parse(&ast);
    }
}

}

#include "benchmarks.moc"
