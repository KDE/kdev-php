/* This file is part of KDevelop
    Copyright 2010 Milian Wolff <mail@milianw.de>

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

#include "bench_completion.h"

#include "helper.h"
#include "../context.h"

#include <language/codecompletion/codecompletiontesthelper.h>

#include <KZip>

using namespace Php;
using namespace KDevelop;

QTEST_MAIN(Php::BenchmarkCodeCompletion)

namespace Php {

typedef CodeCompletionItemTester<CodeCompletionContext> PhpCompletionTester;

void BenchmarkCodeCompletion::initTestCase()
{
    // make sure we have a valid duchain for the global file
    DUChainWriteLocker lock(DUChain::lock());
    if ( !DUChain::self()->chainForDocument(internalFunctionFile()) ) {
        kDebug() << "no internal function file found in DUChain, loading it manually";
        KZip file(internalFunctionFile().str());
        if ( !file.open(QIODevice::ReadOnly) || !file.directory() ) {
            kDebug() << "Could not open file" << internalFunctionFile().str();
            return;
        } else if ( file.directory()->entries().count() != 1 ) {
            kDebug() << "invalid zip file, too many entries:" << file.directory()->entries();
            return;
        }
        const KZipFileEntry* entry = static_cast<const KZipFileEntry*>(file.directory()->entry(file.directory()->entries().first()));
        if ( !entry ) {
            kDebug() << "invalid zip file, entry is not a file" << file.directory()->entries().first();
            return;
        }
        parseAdditionalFile(internalFunctionFile(), entry->data());
        file.close();
        lock.unlock();
        DUChain::self()->storeToDisk();
    }
}

void BenchmarkCodeCompletion::cleanupTestCase()
{
    // force cleanup
    QMetaObject::invokeMethod(DUChain::self(), "aboutToQuit");
}

void BenchmarkCodeCompletion::globalCompletion()
{
    kDebug() << "benching global completion";
    TopDUContext* top = parse("<?php ", DumpNone);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QBENCHMARK {
        PhpCompletionTester tester(top, "<?php ");
    }
}

}

#include "bench_completion.moc"
