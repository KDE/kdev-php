/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
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
#ifndef PHPDUCHAINHELPER_H
#define PHPDUCHAINHELPER_H

#include "phpduchainexport.h"

#include <language/duchain/identifier.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/indexedstring.h>

namespace KDevelop
{
class Declaration;
class DUContext;
}
namespace Php
{
class UnaryExpressionAst;
class AstNode;
class CommonScalarAst;
class EditorIntegrator;

enum DeclarationType {
    ClassDeclarationType,
    FunctionDeclarationType,
    ConstantDeclarationType,
    GlobalVariableDeclarationType
};

/// Indexed string for 'Php', identifies environment files from this language plugin
const KDevelop::IndexedString phpLangString("Php");
/// Qualified identifier for 'this'
const KDevelop::QualifiedIdentifier thisQId("this");
/// Qualified identifier for 'exception'
const KDevelop::QualifiedIdentifier exceptionQId("exception");
/// Qualified identifier for 'iterator'
const KDevelop::QualifiedIdentifier iteratorQId("iterator");
/// Qualified identifier for 'stdclass'
const KDevelop::QualifiedIdentifier stdclassQId("stdclass");
/// Qualified identifier for 'self'
const KDevelop::QualifiedIdentifier selfQId("self");
/// Qualified identifier for 'parent'
const KDevelop::QualifiedIdentifier parentQId("parent");
/// Qualified identifier for 'current'
const KDevelop::QualifiedIdentifier currentQId("current");

KDEVPHPDUCHAIN_EXPORT bool isMatch(KDevelop::Declaration* declaration, DeclarationType declarationType);

KDEVPHPDUCHAIN_EXPORT KDevelop::Declaration* findDeclarationImportHelper(KDevelop::DUContext* currentContext,
        KDevelop::QualifiedIdentifier id,
        DeclarationType declarationType,
        AstNode* node,
        EditorIntegrator* editor);

KDEVPHPDUCHAIN_EXPORT QByteArray formatComment(AstNode* node, EditorIntegrator* editor);

KDEVPHPDUCHAIN_EXPORT CommonScalarAst* findCommonScalar(AstNode* node);

KDEVPHPDUCHAIN_EXPORT KDevelop::IndexedString findIncludeFileUrl(const QString &includeFile, const KUrl &currentUrl);

KDEVPHPDUCHAIN_EXPORT KUrl getUrlForBase(const QString &includeFile, const KUrl &baseUrl);

KDEVPHPDUCHAIN_EXPORT KDevelop::IndexedString getIncludeFileForNode(UnaryExpressionAst* node, EditorIntegrator* editor);

KDEVPHPDUCHAIN_EXPORT QString prettyName(KDevelop::Declaration* dec);

KDEVPHPDUCHAIN_EXPORT const KDevelop::IndexedString& internalFunctionFile();
}
#endif
