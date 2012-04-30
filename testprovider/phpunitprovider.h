/***************************************************************************
 *   This file is part of KDevelop PHP support                             *
 *   Copyright 2012 Miha Čančula <miha@noughmad.eu>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef PHPUNITPROVIDER_H
#define PHPUNITPROVIDER_H

#include <interfaces/iplugin.h>
#include <interfaces/itestprovider.h>
#include <language/duchain/indexeddeclaration.h>
#include <language/duchain/indexedstring.h>
#include <language/duchain/topducontext.h>

#include <QVariant>

class KUrl;
namespace KDevelop {
class IProject;
class ParseJob;
}

class QVariant;

class PhpUnitProvider : public KDevelop::IPlugin, public KDevelop::ITestProvider
{
    Q_OBJECT
    Q_INTERFACES(KDevelop::ITestProvider)

public:
    PhpUnitProvider(QObject* parent, const QList<QVariant>& args = QList<QVariant>());
    virtual void unload();
    virtual KJob* findTests();

public slots:
    void updateReady(const KDevelop::IndexedString& document, const KDevelop::ReferencedTopDUContext& context);
    void parseJobFinished(KDevelop::ParseJob* job);

private:
    KDevelop::IndexedDeclaration m_testCaseDeclaration;
    QList<KDevelop::ReferencedTopDUContext> m_pendingContexts;
    KDevelop::Identifier m_testCaseIdentifier;

    void processContext(KDevelop::ReferencedTopDUContext context);
    void processTestCaseDeclaration(KDevelop::Declaration* declaration);
};

#endif // PHPUNITPROVIDER_H
