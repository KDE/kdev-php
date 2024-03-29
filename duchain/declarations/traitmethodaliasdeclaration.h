/*
    SPDX-FileCopyrightText: 2014 Heinz Wiesinger <pprkut@liwjatan.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef TRAITMETHODALIASDECLARATION_H
#define TRAITMETHODALIASDECLARATION_H

#include "classmethoddeclaration.h"

namespace Php
{

class TraitMethodAliasDeclarationData;

/**
 * inherits ClassMethodDeclaration to allow some trait specific functionality
 */
class KDEVPHPDUCHAIN_EXPORT TraitMethodAliasDeclaration : public ClassMethodDeclaration
{
public:
    TraitMethodAliasDeclaration(const TraitMethodAliasDeclaration &rhs);
    TraitMethodAliasDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    TraitMethodAliasDeclaration(TraitMethodAliasDeclarationData &data);
    TraitMethodAliasDeclaration(TraitMethodAliasDeclarationData &data, const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ~TraitMethodAliasDeclaration() override;

    QString toString() const override;

    /**
     * Set the declaration that is aliased by this declaration.
     *
     * \param decl the declaration that this declaration references
     */
    void setAliasedDeclaration(const KDevelop::IndexedDeclaration& decl);

    /**
     * Access the declaration that is aliased by this declaration.
     *
     * \returns the aliased declaration
     */
    KDevelop::IndexedDeclaration aliasedDeclaration() const;

    /**
     * Set the identifier for a context that contains a declaration overridden by this one.
     *
     * \param ids the identifiers of the context that contain an overridden declaration
     */
    void setOverrides(const QVector< KDevelop::IndexedQualifiedIdentifier >& ids);

    /**
     * Check whether a given identifier is registered as containing an overridden declaration
     *
     * \returns whether a given identifier is registered as containing an overridden declaration
     */
    bool isOverriding(const KDevelop::IndexedQualifiedIdentifier& id) const;

    enum {
        Identity = 131
    };

    KDevelop::Declaration* clonePrivate() const override;
private:
    DUCHAIN_DECLARE_DATA(TraitMethodAliasDeclaration)
};

}

#endif // TRAITMETHODALIASDECLARATION_H

