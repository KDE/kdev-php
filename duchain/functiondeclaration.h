/*
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

#ifndef PHP_FUNCTIONDECLARATION_H
#define PHP_FUNCTIONDECLARATION_H

#include <language/duchain/functiondeclaration.h>

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>
#include <language/duchain/indexedstring.h>

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
    FunctionDeclaration(const KDevelop::SimpleRange &range, KDevelop::DUContext *context);
    FunctionDeclaration(FunctionDeclarationData &data);
    FunctionDeclaration(FunctionDeclarationData &data, const KDevelop::SimpleRange &range, KDevelop::DUContext *context);
    ~FunctionDeclaration();

    virtual QString toString() const;

    void setPrettyName(const QString& name);
    QString prettyName() const;

    enum {
        Identity = 86
    };

    virtual KDevelop::Declaration* clonePrivate() const;
private:
    DUCHAIN_DECLARE_DATA(FunctionDeclaration)
};

}

#endif // PHP_FUNCTIONDECLARATION_H
