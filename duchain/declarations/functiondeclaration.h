/*
    SPDX-FileCopyrightText: 2008 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PHP_FUNCTIONDECLARATION_H
#define PHP_FUNCTIONDECLARATION_H

#include <language/duchain/functiondeclaration.h>

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>
#include <serialization/indexedstring.h>

#include "phpduchainexport.h"
namespace Php
{

class KDEVPHPDUCHAIN_EXPORT FunctionDeclarationData : public KDevelop::FunctionDeclarationData
{
public:
    FunctionDeclarationData()
            : KDevelop::FunctionDeclarationData() {}

    FunctionDeclarationData(const FunctionDeclarationData& rhs)
            : KDevelop::FunctionDeclarationData(rhs)
    {
        prettyName = rhs.prettyName;
    }

    ~FunctionDeclarationData() {}

    KDevelop::IndexedString prettyName;
};

class KDEVPHPDUCHAIN_EXPORT FunctionDeclaration : public KDevelop::FunctionDeclaration
{
public:
    FunctionDeclaration(const FunctionDeclaration &rhs);
    FunctionDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    FunctionDeclaration(FunctionDeclarationData &data);
    FunctionDeclaration(FunctionDeclarationData &data, const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ~FunctionDeclaration() override;

    QString toString() const override;

    void setPrettyName(const KDevelop::IndexedString& name);
    KDevelop::IndexedString prettyName() const;

    enum {
        Identity = 86
    };

    KDevelop::Declaration* clonePrivate() const override;
private:
    DUCHAIN_DECLARE_DATA(FunctionDeclaration)
};

}

#endif // PHP_FUNCTIONDECLARATION_H
