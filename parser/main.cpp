/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
 *   Copyright 2009 Milian Wolff <mail@milianw.de>                         *
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

#include "parsesession.h"
#include "phplexer.h"
#include "phpparser.h"
#include "phpdebugvisitor.h"
#include "phpast.h"
#include "tokenstream.h"
#include "phptokentext.h"

#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include <tests/autotestshell.h>
#include <tests/testcore.h>
#include <language/duchain/duchain.h>
#include <language/codegen/coderepresentation.h>
#include <KApplication>
#include <KLocalizedString>
#include <KAboutData>
#include <KCmdLineArgs>

using namespace Php;
using namespace std;

void showUsage(char**);

QTextStream qout(stdout);
QTextStream qerr(stderr);
QTextStream qin(stdin);

class PhpParser {
public:
    PhpParser(const bool debug, const bool printTokens)
        : m_debug(debug), m_printTokens(printTokens)
    {
        m_session.setDebug(debug);
    }

    /// parse contents of a file
    void parseFile( const QString &fileName )
    {
        if (!m_session.readFile(fileName, "utf-8")) {
            qerr << "Can't open file " << fileName << endl;
            exit(255);
        } else {
            qout << "Parsing file " << fileName << endl;
        }
        runSession();
    }

    /// parse code directly
    void parseCode( const QString &code )
    {
        m_session.setContents(code);

        qout << "Parsing input" << endl;
        runSession();
    }

private:
    /**
     * actually run the parse session
     */
    void runSession()
    {
        if (m_printTokens) {
            TokenStream tokenStream;
            Lexer lexer(&tokenStream, m_session.contents());
            int token;
            while ((token = lexer.nextTokenKind())) {
                Parser::Token &t = tokenStream.next();
                t.begin = lexer.tokenBegin();
                t.end = lexer.tokenEnd();
                t.kind = token;
                printToken(token, lexer);
            }
            printToken(token, lexer);
            if ( tokenStream.size() > 0 ) {
                qint64 line;
                qint64 column;
                tokenStream.endPosition(tokenStream.size() - 1, &line, &column);
                qDebug() << "last token endPosition: line" << line << "column" << column;
            } else {
                qDebug() << "empty token stream";
            }
        }

        Php::StartAst* ast = 0;
        if (!m_session.parse(&ast)) {
            qerr << "no AST tree could be generated" << endl;
        } else {
            qout << "AST tree successfully generated" << endl;
            if (m_debug) {
                Php::DebugVisitor debugVisitor(m_session.tokenStream(), m_session.contents());
                debugVisitor.visitStart(ast);
            }
        }
        if (!m_session.problems().isEmpty()) {
            qout << endl << "problems encountered during parsing:" << endl;
            foreach(KDevelop::ProblemPointer p, m_session.problems()) {
                qout << p->description() << endl;
            }
        } else {
            qout << "no problems encountered during parsing" << endl;
        }

        if (!ast) {
            exit(255);
        }
    }

    /**
     * print the token with the same text as php tokens - so they can be compared with
     * the result of get_token_all (see test-tokenize.php)
     **/
    void printToken(int token, const Lexer& lexer) const
    {
        int begin = lexer.tokenBegin();
        int end = lexer.tokenEnd();
        qout << m_session.contents().mid(begin, end - begin + 1).replace('\n', "\\n")
        << ' ' + tokenText(token) << endl;
    }

    Php::ParseSession m_session;
    const bool m_debug;
    const bool m_printTokens;
};

int main(int argc, char* argv[])
{
    qout.setCodec("UTF-8");
    qin.setCodec("UTF-8");

    KAboutData aboutData( "php-parser", 0, ki18n( "php-parser" ),
                          "1", ki18n("KDevelop PHP parser debugging utility"), KAboutData::License_GPL,
                          ki18n( "(c) 2008 Niko Sams, 2009 Milian Wolff" ), KLocalizedString(), "http://www.kdevelop.org" );
    KCmdLineArgs::init( argc, argv, &aboutData, KCmdLineArgs::CmdLineArgNone );
    KCmdLineOptions options;
    options.add("debug", ki18n("print generated AST tree"));
    options.add("print-tokens", ki18n("print generated token stream"));
    options.add("code <code>", ki18n("PHP code to parse"));
    options.add("+files", ki18n("files or - to read from STDIN, the latter is the default if nothing is provided"));
    KCmdLineArgs::addCmdLineOptions( options );

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    KApplication app(false);

    QStringList files = args->getOptionList("files");
    bool debug = args->isSet("debug");
    bool printTokens = args->isSet("print-tokens");

    KDevelop::AutoTestShell::init();
    KDevelop::Core::initialize(0, KDevelop::Core::NoUi);

    KDevelop::DUChain::self()->disablePersistentStorage();
    KDevelop::CodeRepresentation::setDiskChangesForbidden(true);

    PhpParser parser(debug, printTokens);

    if ( args->isSet("code") ) {
        parser.parseCode( args->getOption("code") );
    } else if ( files.isEmpty() ) {
        files << "-";
    }

    foreach(const QString &fileName, files) {
        if ( fileName == "-" ) {
            if ( isatty(STDIN_FILENO) ) {
                qerr << "no STDIN given" << endl;
                return 255;
            }
            parser.parseCode( qin.readAll().toUtf8() );
        } else {
            parser.parseFile(fileName);
        }

    }
    return 0;
}
