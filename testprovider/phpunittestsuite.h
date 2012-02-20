/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Miha ?an?ula <miha.cancula@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef PHPUNITTESTSUITE_H
#define PHPUNITTESTSUITE_H

#include <interfaces/itestsuite.h>
#include <language/duchain/indexeddeclaration.h>
#include <KUrl>

class KJob;
namespace KDevelop {
class IProject;
}


class PhpUnitTestSuite : public KDevelop::ITestSuite
{

public:
    PhpUnitTestSuite(const QString& name, const KUrl& url, const KDevelop::IndexedDeclaration& suiteDeclaration, const QMap<QString, KDevelop::IndexedDeclaration>& cases, KDevelop::IProject* project);
    virtual ~PhpUnitTestSuite();

    virtual KJob* launchCase(const QString& testCase);
    virtual KJob* launchCases(const QStringList& testCases);
    virtual KJob* launchAllCases();

    virtual KDevelop::IProject* project() const;
    virtual KUrl url() const;
    virtual QStringList cases() const;
    virtual QString name() const;
    virtual KDevelop::TestResult result() const;

    virtual KDevelop::IndexedDeclaration declaration() const;
    virtual KDevelop::IndexedDeclaration caseDeclaration(const QString& testCase) const;

private:
    QString m_name;
    KUrl m_url;
    KDevelop::IndexedDeclaration m_declaration;
    QMap<QString, KDevelop::IndexedDeclaration> m_cases;
    KDevelop::IProject* m_project;
};

#endif // PHPUNITTESTSUITE_H
