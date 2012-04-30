/***************************************************************************
 *   This file is part of KDevelop PHP support                             *
 *   Copyright 2012 Miha Čančula <miha@noughmad.eu>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "phpunitfindjob.h"

#include "phpunittestsuite.h"

#include <interfaces/icore.h>
#include <interfaces/iproject.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/itestcontroller.h>

#include <language/duchain/declaration.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/classdeclaration.h>
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/functiondefinition.h>

#include <KStandardDirs>

PhpUnitFindJob::PhpUnitFindJob(QObject* parent)
: KJob(parent)
{

}

PhpUnitFindJob::~PhpUnitFindJob()
{

}

void PhpUnitFindJob::start()
{
    QString file = KStandardDirs::locate("data", "kdevphpsupport/phpunitdeclarations.php");
    DUChain::self()->updateContextForUrl(IndexedString(file), KDevelop::TopDUContext::AllDeclarationsContextsAndUses, this, -10);
}

void PhpUnitFindJob::updateReady(const IndexedString& document, const KDevelop::ReferencedTopDUContext& context)
{
    Q_UNUSED(document)

    ITestController* tc = ICore::self()->testController();
    DUChainReadLocker lock(DUChain::lock());

    QVector<Declaration*> decl = context->localDeclarations();
    kDebug() << "Found" << decl.size() << "declarations using the direct method";

    foreach (Declaration* p, decl)
    {
        kDebug() << "Found PHP Unit declaration" << p->identifier().toString();
        uint steps = 1000;
        foreach (Declaration* d, DUChainUtils::getInheriters(p, steps))
        {

        }
    }

    emitResult();
}
