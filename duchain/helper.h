/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PHPDUCHAINHELPER_H
#define PHPDUCHAINHELPER_H

#include "phpduchainexport.h"

#include <language/duchain/identifier.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/types/abstracttype.h>
#include <serialization/indexedstring.h>

namespace KDevelop
{
class Declaration;
class DUContext;
}
namespace Php
{
struct UnaryExpressionAst;
struct AstNode;
struct CommonScalarAst;
struct NamespacedIdentifierAst;
struct ParameterAst;
struct GenericTypeHintAst;
struct ReturnTypeAst;
struct ClassStatementAst;
struct PropertyTypeHintAst;
class EditorIntegrator;

enum DeclarationType {
    ClassDeclarationType,
    FunctionDeclarationType,
    ConstantDeclarationType,
    GlobalVariableDeclarationType,
    NamespaceDeclarationType
};

enum DeclarationScope {
    GlobalScope,
    LocalScope
};

KDEVPHPDUCHAIN_EXPORT bool isMatch(KDevelop::Declaration* declaration, DeclarationType declarationType);

KDEVPHPDUCHAIN_EXPORT bool isGenericClassTypehint(NamespacedIdentifierAst* genericType, EditorIntegrator *editor);

KDEVPHPDUCHAIN_EXPORT bool isClassTypehint(GenericTypeHintAst* parameterType, EditorIntegrator *editor);

KDEVPHPDUCHAIN_EXPORT bool isClassTypehint(PropertyTypeHintAst* propertyType, EditorIntegrator *editor);

KDEVPHPDUCHAIN_EXPORT KDevelop::DeclarationPointer findDeclarationImportHelper(KDevelop::DUContext* currentContext,
                                                                               const KDevelop::QualifiedIdentifier& id,
                                                                               DeclarationType declarationType);

KDEVPHPDUCHAIN_EXPORT KDevelop::DeclarationPointer findDeclarationInPST(KDevelop::DUContext* currentContext,
                                                                        KDevelop::QualifiedIdentifier id,
                                                                        DeclarationType declarationType);

KDEVPHPDUCHAIN_EXPORT QByteArray formatComment(AstNode* node, EditorIntegrator* editor);

KDEVPHPDUCHAIN_EXPORT CommonScalarAst* findCommonScalar(AstNode* node);

KDEVPHPDUCHAIN_EXPORT KDevelop::IndexedString getIncludeFileForNode(UnaryExpressionAst* node, EditorIntegrator* editor);

KDEVPHPDUCHAIN_EXPORT QString prettyName(KDevelop::Declaration* dec);

KDEVPHPDUCHAIN_EXPORT const KDevelop::IndexedString& internalFunctionFile();

KDEVPHPDUCHAIN_EXPORT const KDevelop::IndexedString& internalTestFile();

/// Indexed string for 'Php', identifies environment files from this language plugin
KDEVPHPDUCHAIN_EXPORT const KDevelop::IndexedString& phpLanguageString();

/**
 * Get proper QualifiedIdentifier for a NamespacedIdentifierAst.
 *
 * Identifier will be all lowercase except for the last identifier if @p lastIsConstIdentifier is set to true.
 */
KDEVPHPDUCHAIN_EXPORT KDevelop::QualifiedIdentifier identifierForNamespace(NamespacedIdentifierAst* node, EditorIntegrator* editor,
                                                                           bool lastIsConstIdentifier = false);

/**
 * Get proper QualifiedIdentifier for a basic identifier.
 */
KDEVPHPDUCHAIN_EXPORT KDevelop::QualifiedIdentifier identifierWithNamespace(const KDevelop::QualifiedIdentifier& base, KDevelop::DUContext* context);

KDEVPHPDUCHAIN_EXPORT KDevelop::AbstractType::Ptr parameterType(const ParameterAst* node, KDevelop::AbstractType::Ptr phpDocTypehint, EditorIntegrator* editor, KDevelop::DUContext *currentContext);
KDEVPHPDUCHAIN_EXPORT KDevelop::AbstractType::Ptr propertyType(const ClassStatementAst* node, KDevelop::AbstractType::Ptr phpDocTypehint, EditorIntegrator* editor, KDevelop::DUContext *currentContext);
KDEVPHPDUCHAIN_EXPORT KDevelop::AbstractType::Ptr returnType(const ReturnTypeAst* node, KDevelop::AbstractType::Ptr phpDocTypehint, EditorIntegrator* editor, KDevelop::DUContext *currentContext);

}
#endif
