/* This file is part of KDevelop
    Copyright 2002-2005 Roberto Raggi <roberto@kdevelop.org>
    Copyright 2006 Adam Treat <treat@kde.org>
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>
    Copyright 2008 Niko Sams <niko.sams@gmail.com>

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

#ifndef PHP_TYPES_H
#define PHP_TYPES_H

#include <duchain/identifier.h>
#include <duchain/typesystemdata.h>
#include <duchain/typesystem.h>
#include <duchain/declaration.h>
#include <duchain/identifiedtype.h>

#include "phpduchainexport.h"

namespace Php {

typedef KDevelop::MergeIdentifiedType<KDevelop::StructureType> ClassTypeBase;
enum ClassTypeType
{
    Class,
    Interface
};

struct ClassTypeData : public ClassTypeBase::Data {
    ClassTypeType m_classType;
    bool m_closed;
    ClassTypeData() {
        m_classType = Class;
        m_closed = false;
    }

    ClassTypeData(const ClassTypeData& rhs) :ClassTypeBase::Data(rhs), m_classType(rhs.m_classType), m_closed(rhs.m_closed)  {
    }

    ~ClassTypeData() {
    }

private:
    ClassTypeData& operator=(const ClassTypeData&) {
        return *this;
    }
};

class KDEVPHPDUCHAIN_EXPORT ClassType : public ClassTypeBase
{
public:
    ClassType(const ClassType& rhs) : ClassTypeBase(copyData<ClassTypeData>(*rhs.d_func())) {
    }

    ClassType(ClassTypeData& data) : ClassTypeBase(data) {
    }

    typedef TypePtr<ClassType> Ptr;

    ClassType();

    void setClassType(ClassTypeType type);
    ClassTypeType classType() const;


    /// Php classes are closed types, once they are defined, they can't be changed.
    bool isClosed() const { return d_func()->m_closed; }
    void close() { d_func_dynamic()->m_closed = true; }

    ///After clearing, a class-type is open again.
    void clear();

    virtual uint hash() const;

    virtual QString toString() const;

    virtual AbstractType* clone() const;

    virtual bool equals(const AbstractType* rhs) const;

    virtual void accept0 (KDevelop::TypeVisitor *v) const;

    virtual void exchangeTypes(KDevelop::TypeExchanger*);

    enum {
        Identity = 18
    };

    typedef ClassTypeData Data;

protected:
    TYPE_DECLARE_DATA(ClassType);
};


typedef KDevelop::FunctionType FunctionTypeBase;

struct FunctionTypeData : public FunctionTypeBase::Data {
};

class KDEVPHPDUCHAIN_EXPORT FunctionType : public FunctionTypeBase
{
public:
    FunctionType(const FunctionType& rhs) : FunctionTypeBase(copyData<FunctionTypeData>(*rhs.d_func())) {
    }

    FunctionType(FunctionTypeData& data) : FunctionTypeBase(data) {
    }

    FunctionType() : FunctionTypeBase(createData<FunctionTypeData>()) {
        d_func_dynamic()->setTypeClassId<FunctionType>();
    }

    typedef TypePtr<FunctionType> Ptr;

    ///Declarations of this class(@see KDevelop::IdentifiedType::declaration()) are guaranteed to be based on AbstractFunctionDeclaration

    virtual QString toString() const;

    virtual uint hash() const;

    virtual AbstractType* clone() const;

    virtual bool equals(const AbstractType* rhs) const;

    enum {
        Identity = 15
    };

    typedef FunctionTypeData Data;

protected:
    TYPE_DECLARE_DATA(FunctionType);
};


typedef KDevelop::IntegralType IntegralTypeBase;

struct IntegralTypeData : IntegralTypeBase::Data {
};

class KDEVPHPDUCHAIN_EXPORT IntegralType : public KDevelop::IntegralType
{
public:
    IntegralType();
    IntegralType(const IntegralType& rhs) : IntegralTypeBase(copyData<IntegralTypeData>(*rhs.d_func())) {
    }
    IntegralType(IntegralTypeData& data) : IntegralTypeBase(data) {
    }

    typedef TypePtr<IntegralType> Ptr;

    virtual QString toString() const;

    virtual uint hash() const;

    virtual AbstractType* clone() const;

    virtual bool equals(const AbstractType* rhs) const;

    typedef IntegralTypeData Data;

    enum {
        Identity = 13
    };

protected:
  TYPE_DECLARE_DATA(IntegralType);
};

}

#endif
