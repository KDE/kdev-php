/*
    SPDX-FileCopyrightText: 2014 Heinz Wiesinger <pprkut@liwjatan.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef TRAITMEMBERALIASDECLARATION_H
#define TRAITMEMBERALIASDECLARATION_H

#include <language/duchain/classmemberdeclaration.h>
#include <language/duchain/classmemberdeclarationdata.h>

#include "phpduchainexport.h"

namespace Php
{

class KDEVPHPDUCHAIN_EXPORT TraitMemberAliasDeclarationData : public KDevelop::ClassMemberDeclarationData
{
public:
    TraitMemberAliasDeclarationData()
            : KDevelop::ClassMemberDeclarationData() {}

    TraitMemberAliasDeclarationData( const TraitMemberAliasDeclarationData& rhs )
            : KDevelop::ClassMemberDeclarationData(rhs)
    {
        m_aliasedDeclaration = rhs.m_aliasedDeclaration;
    }

    KDevelop::IndexedDeclaration m_aliasedDeclaration;
};

/**
 * Represents a single class member definition in a definition-use chain.
 */
class KDEVPHPDUCHAIN_EXPORT TraitMemberAliasDeclaration : public KDevelop::ClassMemberDeclaration
{
public:
    TraitMemberAliasDeclaration(const TraitMemberAliasDeclaration& rhs);
    TraitMemberAliasDeclaration(const KDevelop::RangeInRevision& range, KDevelop::DUContext* context);
    TraitMemberAliasDeclaration(TraitMemberAliasDeclarationData& dd);
    ~TraitMemberAliasDeclaration() override;

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

    enum {
        Identity = 130
    };

protected:
    TraitMemberAliasDeclaration(TraitMemberAliasDeclarationData& dd, const KDevelop::RangeInRevision& range);

private:
    DUCHAIN_DECLARE_DATA(TraitMemberAliasDeclaration)
    KDevelop::Declaration* clonePrivate() const override;

};
}

#endif // TRAITMEMBERALIASDECLARATION_H

