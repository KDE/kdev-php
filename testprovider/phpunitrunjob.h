#ifndef PHPUNITRUNJOB_H
#define PHPUNITRUNJOB_H

#include <outputview/outputjob.h>
#include <interfaces/itestsuite.h>

class PhpUnitTestSuite;
class KProcess;

class PhpUnitRunJob : public KDevelop::OutputJob
{
    Q_OBJECT
public:
    PhpUnitRunJob(PhpUnitTestSuite* suite, const QStringList& cases, QObject* parent = 0);
    virtual void start();

protected:
    virtual bool doKill();

private slots:
    void processFinished(int exitCode);

private:
    KProcess* m_process;
    PhpUnitTestSuite* m_suite;
    QStringList m_cases;
    KDevelop::TestResult m_result;

public slots:
    void linesReceived(const QStringList& lines);
};

#endif // PHPUNITRUNJOB_H
