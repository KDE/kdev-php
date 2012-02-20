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


#include "phpunittestsuite.h"

using namespace KDevelop;

PhpUnitTestSuite::PhpUnitTestSuite(const QString& name, const KUrl& url, const IndexedDeclaration& suiteDeclaration, const QMap< QString, IndexedDeclaration >& cases, IProject* project) :
m_name(name),
m_url(url),
m_declaration(suiteDeclaration),
m_cases(cases),
m_project(project)
{
}

PhpUnitTestSuite::~PhpUnitTestSuite()
{

}


KJob* PhpUnitTestSuite::launchCase(const QString& testCase)
{
    return 0;
}

KJob* PhpUnitTestSuite::launchCases(const QStringList& testCases)
{
    return 0;
}

KJob* PhpUnitTestSuite::launchAllCases()
{
    return 0;
}

KDevelop::IProject* PhpUnitTestSuite::project() const
{
    return m_project;
}

KUrl PhpUnitTestSuite::url() const
{
    return m_url;
}

QStringList PhpUnitTestSuite::cases() const
{
    return QStringList(m_cases.keys());
}

QString PhpUnitTestSuite::name() const
{
    return m_name;
}

TestResult PhpUnitTestSuite::result() const
{
    return TestResult();
}

IndexedDeclaration PhpUnitTestSuite::declaration() const
{
    return m_declaration;
}

IndexedDeclaration PhpUnitTestSuite::caseDeclaration(const QString& testCase) const
{
    return m_cases.value(testCase, IndexedDeclaration(0));
}



