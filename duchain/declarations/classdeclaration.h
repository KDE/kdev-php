/*
    SPDX-FileCopyrightText: 2008 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PHP_CLASSDECLARATION_H
#define PHP_CLASSDECLARATION_H

#include <language/duchain/classdeclaration.h>

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>
#include <serialization/indexedstring.h>

#include "phpduchainexport.h"
namespace Php
{

class KDEVPHPDUCHAIN_EXPORT ClassDeclarationData : public KDevelop::ClassDeclarationData
{
public:
    ClassDeclarationData()
            : KDevelop::ClassDeclarationData() {}

    ClassDeclarationData(const ClassDeclarationData& rhs)
            : KDevelop::ClassDeclarationData(rhs)
    {
        prettyName = rhs.prettyName;
    }

    ~ClassDeclarationData() {}

    KDevelop::IndexedString prettyName;
};

class KDEVPHPDUCHAIN_EXPORT ClassDeclaration : public KDevelop::ClassDeclaration
{
public:
    ClassDeclaration(const ClassDeclaration &rhs);
    ClassDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ClassDeclaration(ClassDeclarationData &data);
    ClassDeclaration(ClassDeclarationData &data, const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ~ClassDeclaration() override;

    QString toString() const override;

    void setPrettyName(const KDevelop::IndexedString& name);
    KDevelop::IndexedString prettyName() const;

    void updateCompletionCodeModelItem();

    enum {
        Identity = 85
    };

    KDevelop::Declaration* clonePrivate() const override;
private:
    DUCHAIN_DECLARE_DATA(ClassDeclaration)
};

}

#endif // PHP_CLASSDECLARATION_H
