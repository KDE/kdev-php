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

#ifndef TESTDUCHAIN_H
#define TESTDUCHAIN_H

#include "duchain/tests/duchaintestbase.h"
#include <language/codecompletion/codecompletionitem.h>

namespace Php
{
  
class TestCompletion : public DUChainTestBase
{
  Q_OBJECT

public:
    TestCompletion();

private:
    void dumpCompletionItems(QList<KDevelop::CompletionTreeItemPointer> items);

private slots:
    void publicObjectCompletion();
    void publicStaticObjectCompletion();
    void protectedObjectCompletion();
    void protectedStaticObjectCompletion();
    void privateObjectCompletion();
    void privateStaticObjectCompletion();
    void methodCall();
    void functionCall();
    void newObjectFromOtherFile();
    void baseClass();
    void extendsFromOtherFile();
    void globalClassFromOtherFile();
    void codeModel();
    void projectFileClass();
    void variable();
    void variableStarted();
    void nameNormalVariable();
    void nameClassMember();
    void exceptions();
    void multipleVarialbeDeclarationsWithSameIdentifier();
    void abstractMethods();
    void interfaceMethods();
    void overrideMethods();
    void implementMethods();
    void inArray();
};

}

#endif
