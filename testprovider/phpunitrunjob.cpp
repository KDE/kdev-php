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

#include "phpunitrunjob.h"
#include "phpunittestsuite.h"
#include "testdoxdelegate.h"

#include <util/processlinemaker.h>
#include <outputview/outputmodel.h>
#include <interfaces/itestcontroller.h>
#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>

#include <KProcess>
#include <KStandardDirs>
#include <KDebug>

PhpUnitRunJob::PhpUnitRunJob(PhpUnitTestSuite* suite, const QStringList& cases, QObject* parent)
: OutputJob(parent, KDevelop::OutputJob::Verbose)
, m_suite(suite)
, m_cases(cases)
{
}

void PhpUnitRunJob::start()
{
    m_process = new KProcess(this);
    // TODO: Arguments from test cases

    QStringList args;

    if (m_cases != m_suite->cases())
    {
        args << "--filter";
        args << '"' + m_cases.join("|") + '"';
    }

    args << "--testdox" << m_suite->name() << m_suite->url().toLocalFile();

    const QString exe = KStandardDirs::findExe("phpunit");
    if (exe.isEmpty()) {
        KDevelop::ITestController* tc = KDevelop::ICore::self()->pluginController()->pluginForExtension("org.kdevelop.ITestController")->extension<KDevelop::ITestController>();
        tc->notifyTestRunFinished(m_suite);
        emitResult();
        return;
    }
    m_process->setProgram(exe, args);
    m_process->setOutputChannelMode(KProcess::MergedChannels);
    connect (m_process, SIGNAL(finished(int)), SLOT(processFinished(int)));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));

    KDevelop::ProcessLineMaker* maker = new KDevelop::ProcessLineMaker(m_process, this);
    connect (maker, SIGNAL(receivedStdoutLines(QStringList)), SLOT(linesReceived(QStringList)));

    setModel(new KDevelop::OutputModel, KDevelop::IOutputView::TakeOwnership);
    setDelegate(new TestDoxDelegate, KDevelop::IOutputView::TakeOwnership);
    setStandardToolView(KDevelop::IOutputView::TestView);
    startOutput();

    m_process->start();
}

bool PhpUnitRunJob::doKill()
{
    m_process->kill();
    return true;
}

void PhpUnitRunJob::processFinished(int exitCode)
{
    Q_UNUSED(exitCode);
    m_suite->setResult(m_result);


    KDevelop::ITestController* tc = KDevelop::ICore::self()->pluginController()->pluginForExtension("org.kdevelop.ITestController")->extension<KDevelop::ITestController>();
    tc->notifyTestRunFinished(m_suite);

    emitResult();
}

void PhpUnitRunJob::processError(QProcess::ProcessError )
{

    KDevelop::ITestController* tc = KDevelop::ICore::self()->pluginController()->pluginForExtension("org.kdevelop.ITestController")->extension<KDevelop::ITestController>();
    tc->notifyTestRunFinished(m_suite);

    emitResult();
}

void PhpUnitRunJob::linesReceived(const QStringList& lines)
{
    static QRegExp testResultLineExp = QRegExp("\\[([x\\s])\\]");
    foreach (const QString& line, lines)
    {
        int i = testResultLineExp.indexIn(line);
        if (i > -1)
        {
            bool passed = testResultLineExp.cap(1) == "x";
            QString testCase = "test" + line.mid(i+4).toLower().remove(' ');
            kDebug() << "Got result in " << line << " for " << testCase;
            if (m_cases.contains(testCase, Qt::CaseInsensitive))
            {
                foreach (const QString& realCaseName, m_cases)
                {
                    if (QString::compare(testCase, realCaseName, Qt::CaseInsensitive) == 0)
                    {
                        m_result.testCaseResults[testCase] = (passed ? KDevelop::TestResult::Passed : KDevelop::TestResult::Failed);
                        break;
                    }
                }
            }
        }
        else
        {
            kDebug() << line << testResultLineExp.pattern() << i;
        }
    }
    qobject_cast<KDevelop::OutputModel*>(model())->appendLines(lines);
}



