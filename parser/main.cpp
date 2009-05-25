/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
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

void printToken(int token, const Lexer& lexer, const QString& content);
void showUsage(char**);

QTextStream qout(stdout);
QTextStream qerr(stderr);
QTextStream qin(stdin);

int main(int argc, char* argv[])
{
    qout.setCodec("UTF-8");

    QStringList files;
    bool debug = false;
    bool printTokens = false;
    for (int i = 1; i < argc; i++) {
        QString arg(argv[i]);
        if (arg.startsWith(QString("--"))) {
            arg = arg.mid(2);
            if (arg == "debug") {
                debug = true;
            } else if (arg == "print-tokens") {
                printTokens = true;
            } else {
                qerr << "unknown option: " << endl;
                showUsage(argv);
                return 1;
            }
        } else {
            files << arg;
        }
    }

    if ( files.isEmpty() ) {
        files << "-";
    }

    foreach(const QString &fileName, files) {
        Php::ParseSession session;
        session.setDebug(debug);
        if ( fileName == "-" ) {
            if ( isatty(STDIN_FILENO) ) {
                qerr << "no STDIN given" << endl;
                return 255;
            }
            qerr << "reading from stdin" << endl;
            session.setContents( qin.readAll().toUtf8() );
            qout << "Parsing input" << endl;
        } else if (!session.readFile(fileName, "utf-8")) {
            qerr << "Can't open file " << fileName << endl;
            return 255;
        } else {
            qout << "Parsing file " << fileName << endl;
        }

        if (printTokens) {
            TokenStream tokenStream;
            Lexer lexer(&tokenStream, session.contents());
            int token;
            while ((token = lexer.nextTokenKind())) {
                printToken(token, lexer, session.contents());
            }
            printToken(token, lexer, session.contents());

            qint64 line;
            qint64 column;
            tokenStream.endPosition(tokenStream.size() - 1, &line, &column);
//             tokenStream.endPosition(lastTokenEnd, &line, &column);
            qDebug() << "last token endPosition: " << line << column;

        }

        Php::StartAst* ast = 0;
        if (!session.parse(&ast)) {
            exit(EXIT_FAILURE);
            qerr << "parse error" << endl;
            return 255;
        } else {
            if (debug) {
                Php::DebugVisitor debugVisitor(session.tokenStream(), session.contents());
                debugVisitor.visitStart(ast);
            }
            qout << "successfully parsed" << endl;
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
    qout << "" << endl;
    qout << "If FILE is empty or -, read from STDIN." << endl;
}
/**
 * print the token with the same text as php tokens - so they can be compared with
 * the result of get_token_all (see test-tokenize.php)
 **/
void printToken(int token, const Lexer& lexer, const QString& content)
{
    int begin = lexer.tokenBegin();
    int end = lexer.tokenEnd();
    qout << content.mid(begin, end - begin + 1).replace('\n', "\\n")
    << tokenText(token) << endl;
}
