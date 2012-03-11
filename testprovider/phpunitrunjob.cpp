#include "phpunitrunjob.h"
#include "phpunittestsuite.h"

#include <util/processlinemaker.h>
#include <outputview/outputmodel.h>
#include <interfaces/itestcontroller.h>
#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>

#include <KProcess>
#include <KStandardDirs>
#include <KDebug>

PhpUnitRunJob::PhpUnitRunJob(PhpUnitTestSuite* suite, const QStringList& cases, QObject* parent): OutputJob(parent, KDevelop::OutputJob::Verbose),
    m_suite(suite),
    m_cases(cases)
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

    m_process->setProgram(KStandardDirs::findExe("phpunit"), args);
    m_process->setOutputChannelMode(KProcess::MergedChannels);
    connect (m_process, SIGNAL(finished(int)), SLOT(processFinished(int)));

    KDevelop::ProcessLineMaker* maker = new KDevelop::ProcessLineMaker(m_process, this);
    connect (maker, SIGNAL(receivedStdoutLines(QStringList)), SLOT(linesReceived(QStringList)));

    setModel(new KDevelop::OutputModel, KDevelop::IOutputView::TakeOwnership);
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



