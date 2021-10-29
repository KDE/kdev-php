/*
    SPDX-FileCopyrightText: 2008 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CLASSMETHODDECLARATION_H
#define CLASSMETHODDECLARATION_H

#include <language/duchain/classfunctiondeclaration.h>

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>
#include <serialization/indexedstring.h>

#include "phpduchainexport.h"

namespace Php
{

class KDEVPHPDUCHAIN_EXPORT ClassMethodDeclarationData : public KDevelop::ClassFunctionDeclarationData
{
public:
    ClassMethodDeclarationData()
            : KDevelop::ClassFunctionDeclarationData() {}

    ClassMethodDeclarationData(const ClassMethodDeclarationData& rhs)
            : KDevelop::ClassFunctionDeclarationData(rhs)
    {
        prettyName = rhs.prettyName;
    }

    ~ClassMethodDeclarationData() {}

    KDevelop::IndexedString prettyName;
};

/**
 * inherits ClassFunctionDeclaration to overwrite some stuff for PHP specific behaviour
 */
class KDEVPHPDUCHAIN_EXPORT ClassMethodDeclaration : public KDevelop::ClassFunctionDeclaration
{
public:
    ClassMethodDeclaration(const ClassMethodDeclaration &rhs);
    ClassMethodDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ClassMethodDeclaration(ClassMethodDeclarationData &data);
    ClassMethodDeclaration(ClassMethodDeclarationData &data, const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ~ClassMethodDeclaration() override;

    /// overwritten to check for __construct() method
    bool isConstructor() const override;
    /// overwritten to check for __destruct() method
    bool isDestructor() const override;

    QString toString() const override;

    void setPrettyName(const KDevelop::IndexedString& name);
    KDevelop::IndexedString prettyName() const;

    enum {
        Identity = 84
    };

    KDevelop::Declaration* clonePrivate() const override;
private:
    DUCHAIN_DECLARE_DATA(ClassMethodDeclaration)
};

}

#endif // CLASSMETHODDECLARATION_H

