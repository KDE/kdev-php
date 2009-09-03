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

#ifndef PHP_CLASSDECLARATION_H
#define PHP_CLASSDECLARATION_H

#include <language/duchain/classdeclaration.h>

#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>
#include <language/duchain/indexedstring.h>

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
    ClassDeclaration(const KDevelop::SimpleRange &range, KDevelop::DUContext *context);
    ClassDeclaration(ClassDeclarationData &data);
    ClassDeclaration(ClassDeclarationData &data, const KDevelop::SimpleRange &range, KDevelop::DUContext *context);
    ~ClassDeclaration();

    virtual QString toString() const;

    void setPrettyName(const QString& name);
    QString prettyName() const;

    enum {
        Identity = 85
    };

    virtual KDevelop::Declaration* clonePrivate() const;
private:
    DUCHAIN_DECLARE_DATA(ClassDeclaration)
};

}

#endif // PHP_CLASSDECLARATION_H