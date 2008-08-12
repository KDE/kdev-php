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
#include <language/duchain/types/delayedtype.h>

namespace Php {

ExpressionEvaluationResult::~ExpressionEvaluationResult() {
}

ExpressionEvaluationResult::ExpressionEvaluationResult()/* : isInstance(false)*/ {
}

}
