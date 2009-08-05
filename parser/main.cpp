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
#include "tokentext.h"

#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <QTextCodec>

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
            qerr << "parse error" << endl;
            exit(255);
        } else {
            if (m_debug) {
                Php::DebugVisitor debugVisitor(m_session.tokenStream(), m_session.contents());
                debugVisitor.visitStart(ast);
            }
            qout << "successfully parsed" << endl;
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
        << tokenText(token) << endl;
    }

    Php::ParseSession m_session;
    const bool m_debug;
    const bool m_printTokens;
};

int main(int argc, char* argv[])
{
    qout.setCodec("UTF-8");
    qin.setCodec("UTF-8");

    QStringList files;
    bool debug = false;
    bool printTokens = false;
    QStringList code;
    for (int i = 1; i < argc; i++) {
        QString arg(argv[i]);
        if (arg.startsWith(QString("--"))) {
            arg = arg.mid(2);
            if (arg == "debug") {
                debug = true;
            } else if (arg == "print-tokens") {
                printTokens = true;
            } else if (arg == "code") {
                for (int j = i + 1; j < argc; ++j ) {
                    code << argv[j];
                }
                if ( code.isEmpty() ) {
                    qerr << "no code given" << endl;
                    showUsage(argv);
                    return 1;
                }
                break;
            } else {
                qerr << "unknown option: " << endl;
                showUsage(argv);
                return 1;
            }
        } else {
            files << arg;
        }
    }

    PhpParser parser(debug, printTokens);

    if ( !code.isEmpty() ) {
        parser.parseCode( code.join(" ") );
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

void showUsage(char** argv)
{
    qout << "Usage: " << argv[0] << " [options] FILE" << endl;
    qout << "" << endl;
    qout << "--print-tokens Print all found tokens" << endl;
    qout << "--debug        Print AST" << endl;
    qout << "--code ...     All following arguments will be interpreted as PHP code." << endl
         << "               Hence put this option at the end of the list." << endl;
    qout << "" << endl;
    qout << "If FILE is empty or -, read from STDIN." << endl;
}
