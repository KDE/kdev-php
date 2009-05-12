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

#ifndef DUCHAINTESTBASE_H
#define DUCHAINTESTBASE_H

#include <QObject>
#include <QByteArray>
#include <QTest>
#include <language/duchain/dumpchain.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

#include "phpduchainexport.h"

#include "completion/item.h"
#include "phpparser.h"

namespace KDevelop
{
class TopDUContext;
}
/*
namespace QTest {
  template<>
  char* toString(const KTextEditor::Cursor& cursor)
  {
    QByteArray ba = "Cursor(";
    ba += QByteArray::number(cursor.line()) + ", " + QByteArray::number(cursor.column());
    ba += ')';
    return qstrdup(ba.data());
  }
  template<>
  char* toString(const KDevelop::QualifiedIdentifier& id)
  {
    QByteArray arr = id.toString().toLatin1();
    return qstrdup(arr.data());
  }
  template<>
  char* toString(const KDevelop::Identifier& id)
  {
    QByteArray arr = id.toString().toLatin1();
    return qstrdup(arr.data());
  }
  template<>
  char* toString(const KDevelop::Declaration& def)
  {
    QString s = QString("Declaration %1 (%2): %3").arg(def.identifier().toString()).arg(def.qualifiedIdentifier().toString()).arg(reinterpret_cast<long>(&def));
    return qstrdup(s.toLatin1().constData());
  }
  template<>
  char* toString(const TypePtr<KDevelop::AbstractType>& type)
  {
    QString s = QString("Type: %1").arg(type ? type->toString() : QString("<null>"));
    return qstrdup(s.toLatin1().constData());
  }
}
*/
namespace Php
{
/**
 * Manage pointer to TopDUContexts and release them properly, even if a test fails
 */
struct DUChainReleaser {
    DUChainReleaser(KDevelop::TopDUContext* top) : m_top(top) {}
    ~DUChainReleaser() {
        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
        if ( m_top->inDUChain() ) {
            KDevelop::DUChain::self()->removeDocumentChain(m_top);
        }
    }
    KDevelop::TopDUContext* m_top;
};

class KDEVPHPDUCHAIN_EXPORT DUChainTestBase : public QObject
{
    Q_OBJECT

public:
    DUChainTestBase();

public:
    enum DumpArea {
        DumpNone = 0,
        DumpAST = 1,
        DumpDUChain = 2,
        DumpType = 4,
        DumpAll = 7
    };
    Q_DECLARE_FLAGS(DumpAreas, DumpArea)

public slots:
    void initTestCase();

protected:
    KDevelop::TopDUContext* parse(const QByteArray& unit, DumpAreas dump = static_cast<DumpAreas>(DumpAST | DumpDUChain | DumpType), QString fileName = QString());

    KDevelop::TopDUContext* parseAdditionalFile(KDevelop::IndexedString fileName, QByteArray contents);

    KDevelop::DumpChain dumper;

    KDevelop::CompletionTreeItemPointer searchDeclaration(QList<KDevelop::CompletionTreeItemPointer> items, KDevelop::Declaration* declaration);
    bool hasImportedParentContext(KDevelop::TopDUContext* top, KDevelop::DUContext* lookingFor);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DUChainTestBase::DumpAreas)
}

#endif
