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

#ifndef TESTDUCHAIN_H
#define TESTDUCHAIN_H

#include <QObject>
#include <QByteArray>
#include <dumpchain.h>

#include "phpparser.h"
namespace KDevelop {
    class TopDUContext;
}
namespace Php
{
class TestDUChain : public QObject
{
  Q_OBJECT

public:
  TestDUChain();

private slots:
  void testDeclareVar();
  void testDeclareClass();
  void testClassMemberVar();
  void testDeclareTypehintFunction();
  void testReturnTypeClass();
  void testDeclarationReturnType();
  void testDeclarationMultipleReturnTypes();
  void testDeclarationReturnTypeDocBlock();
  void testClassImplementsInterface();
  void testClassExtends();
  void testStaticMethod();
  void testOwnStaticMethod();
  void testThis();
  void testObjectFunctionCall();
  void testObjectFunctionCall2();
  void testObjectFunctionCall3();
  void testObjectVariable();
  void testStaticMemberVariable();
  void testOwnStaticMemberVariable();

public:
  enum DumpArea {
    DumpNone = 0,
    DumpAST = 1,
    DumpDUChain = 2,
    DumpType = 4,
    DumpAll = 7
  };
  Q_DECLARE_FLAGS(DumpAreas, DumpArea)

private:
  KDevelop::TopDUContext* parse(const QByteArray& unit, DumpAreas dump = static_cast<DumpAreas>(DumpAST | DumpDUChain | DumpType));

  void release(KDevelop::TopDUContext* top);

  KDevelop::DumpChain dumper;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TestDUChain::DumpAreas)
}

#endif
