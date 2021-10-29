/*
    SPDX-FileCopyrightText: 2006 Hamish Rodda <rodda@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef DUMPTYPES_H
#define DUMPTYPES_H

#include <language/duchain/types/typesystem.h>
#include "phpduchainexport.h"

#include <QSet>

namespace Php
{

class KDEVPHPDUCHAIN_EXPORT DumpTypes : protected KDevelop::TypeVisitor
{
public:
    DumpTypes();
    ~DumpTypes() override;

    void dump(const KDevelop::AbstractType* type);

protected:
    bool preVisit(const KDevelop::AbstractType * type) override;
    void postVisit(const KDevelop::AbstractType *) override;

    void visit(const KDevelop::IntegralType *) override;

    bool visit(const KDevelop::AbstractType *) override;

    bool visit(const KDevelop::PointerType * type) override;
    void endVisit(const KDevelop::PointerType *) override;

    bool visit(const KDevelop::ReferenceType * type) override;
    void endVisit(const KDevelop::ReferenceType *) override;

    bool visit(const KDevelop::FunctionType * type) override;
    void endVisit(const KDevelop::FunctionType *) override;

    bool visit(const KDevelop::StructureType * type) override;
    void endVisit(const KDevelop::StructureType *) override;

    bool visit(const KDevelop::ArrayType * type) override;
    void endVisit(const KDevelop::ArrayType *) override;

private:
    bool seen(const KDevelop::AbstractType* type);

    class CppEditorIntegrator* m_editor;
    int indent;
    QSet<const KDevelop::AbstractType*> m_encountered;
};
}

#endif // DUMPTYPES_H

