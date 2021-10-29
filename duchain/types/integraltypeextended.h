/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef INTEGRALTYPEEXTENDED_H
#define INTEGRALTYPEEXTENDED_H

#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/typesystemdata.h>
#include "phpduchainexport.h"

namespace Php
{

typedef KDevelop::IntegralTypeData IntegralTypeExtendedData;

/**
 * Drop-In replacement for the IntegralType in KDevplatform with
 * some extended logic specific for PHP
 */
class KDEVPHPDUCHAIN_EXPORT IntegralTypeExtended: public KDevelop::IntegralType
{
public:
    typedef KDevelop::TypePtr<IntegralTypeExtended> Ptr;

    enum PHPIntegralTypes {
        TypeResource = KDevelop::IntegralType::TypeLanguageSpecific,
        TypeCallable,
        TypeObject
    };

    /// Default constructor
    IntegralTypeExtended(uint type = TypeNone);
    /// Copy constructor. \param rhs type to copy
    IntegralTypeExtended(const IntegralTypeExtended& rhs);
    /// Constructor using raw data. \param data internal data.
    IntegralTypeExtended(IntegralTypeExtendedData& data);

    QString toString() const override;

    KDevelop::AbstractType* clone() const override;

    bool equals(const KDevelop::AbstractType* rhs) const override;

    uint hash() const override;

    enum {
        ///TODO: is that value OK?
        Identity = 50
    };

  typedef KDevelop::IntegralTypeData Data;
  typedef KDevelop::IntegralType BaseType;

protected:
    TYPE_DECLARE_DATA(IntegralTypeExtended);
};

}

namespace KDevelop
{

template<>
inline Php::IntegralTypeExtended* fastCast<Php::IntegralTypeExtended*>(AbstractType* from) {
    if ( !from || from->whichType() != AbstractType::TypeIntegral ) {
        return nullptr;
    } else {
        return dynamic_cast<Php::IntegralTypeExtended*>(from);
    }
}

}

#endif // PHPINTEGRALTYPE_H

