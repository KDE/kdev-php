/* This file is part of KDevelop
    Copyright 2008 David Nolden <david.nolden.kdevelop@art-master.de>
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

#include "expressionevaluationresult.h"
#include <language/duchain/identifier.h>
#include <QString>
#include <language/duchain/duchainlock.h>
#include <language/duchain/repositories/itemrepository.h>
#include <language/duchain/duchain.h>
#include <language/duchain/types/identifiedtype.h>
#include <language/duchain/declaration.h>

#define ifDebug(x)

using namespace KDevelop;
namespace Php
{

ExpressionEvaluationResult::~ExpressionEvaluationResult()
{
}

ExpressionEvaluationResult::ExpressionEvaluationResult()/* : isInstance(false)*/
{
}

void ExpressionEvaluationResult::setDeclaration(Declaration* declaration)
{
    QList<Declaration*> decs;
    if (declaration) {
        decs << declaration;
    }
    setDeclarations(decs);
}

void ExpressionEvaluationResult::setDeclarations(QList<Declaration*> declarations)
{
    ifDebug(kDebug() << "setting declarations" << declarations.size();)

    m_allDeclarations = declarations;
    if (!m_allDeclarations.isEmpty()) {
        setType(m_allDeclarations.last()->abstractType());
    } else {
        setType(AbstractType::Ptr());
    }
    m_allDeclarationIds.clear();
    DUChainReadLocker lock(DUChain::lock());
    foreach(Declaration* dec, m_allDeclarations) {
        m_allDeclarationIds << dec->id();
        ifDebug(kDebug() << dec->toString();)
    }
}

AbstractType::Ptr ExpressionEvaluationResult::type() const
{
    return m_type;
}

QList<Declaration*> ExpressionEvaluationResult::allDeclarations() const
{
    return m_allDeclarations;
}

QList<DeclarationId> ExpressionEvaluationResult::allDeclarationIds() const
{
    return m_allDeclarationIds;
}

void ExpressionEvaluationResult::setType(AbstractType::Ptr type)
{
    ifDebug(kDebug() << "setting type" << (type ? type->toString() : QString("no type"));)

    m_type = type;
}

}
