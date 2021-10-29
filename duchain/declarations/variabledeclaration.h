/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef VARIABLEDECLARATION_H
#define VARIABLEDECLARATION_H

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>

#include "phpduchainexport.h"

namespace Php
{

class KDEVPHPDUCHAIN_EXPORT VariableDeclarationData : public KDevelop::DeclarationData
{
public:
    VariableDeclarationData()
            : KDevelop::DeclarationData(), m_isSuperglobal(false), m_isVariadic(false) {
    }

    VariableDeclarationData(const VariableDeclarationData& rhs)
            : KDevelop::DeclarationData(rhs) {
        m_isSuperglobal = rhs.m_isSuperglobal;
        m_isVariadic = rhs.m_isVariadic;
    }

    ~VariableDeclarationData() {
    }

bool m_isSuperglobal;
bool m_isVariadic;
};

/**
 * Declaration used for Php variables eg. $a = 0;
 */
class KDEVPHPDUCHAIN_EXPORT VariableDeclaration : public KDevelop::Declaration
{
public:
    VariableDeclaration(const VariableDeclaration& rhs);
    VariableDeclaration(const KDevelop::RangeInRevision& range, KDevelop::DUContext* context);
    VariableDeclaration(VariableDeclarationData& data);
    VariableDeclaration(VariableDeclarationData& data, const KDevelop::RangeInRevision&);
    ~VariableDeclaration() override;

    bool isSuperglobal() const;
    void setSuperglobal(bool superglobal);

    bool isVariadic() const;
    void setVariadic(bool variadic);

    uint additionalIdentity() const override;
    KDevelop::DeclarationId id(bool forceDirect = false) const override;

    enum {
        Identity = 83
    };
    typedef KDevelop::Declaration Base;

private:
    DUCHAIN_DECLARE_DATA(VariableDeclaration)
};

}

#endif // VARIABLEDECLARATION_H
