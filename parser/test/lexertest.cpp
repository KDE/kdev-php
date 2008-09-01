/* This file is part of KDevelop
    Copyright 2006 Hamish Rodda <rodda@kde.org>
    Copyright 2008 Niko Sams <niko.sams@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "lexertest.h"

#include <QtTest/QtTest>

#include "parsesession.h"
#include "phplexer.h"
#include "tokentext.h"

QTEST_MAIN(Php::LexerTest)
namespace Php
{

void compareEndPosition(TokenStream* tokenStream, qint64 index, qint64 expectedLine, qint64 expectedColumn)
{
    qint64 line;
    qint64 column;
    tokenStream->endPosition(index, &line, &column);
//     kDebug() << "  end" << index << ": actual" << line << column << "expected" << expectedLine << expectedColumn;
    QCOMPARE(line, expectedLine);
    QCOMPARE(column, expectedColumn);
}

void compareStartPosition(TokenStream* tokenStream, qint64 index, qint64 expectedLine, qint64 expectedColumn)
{
    qint64 line;
    qint64 column;
    tokenStream->startPosition(index, &line, &column);
//     kDebug() << "start" << index << ": actual" << line << column << "expected" << expectedLine << expectedColumn;
    QCOMPARE(line, expectedLine);
    QCOMPARE(column, expectedColumn);
}

LexerTest::LexerTest()
{
}

void LexerTest::testOpenTagWithNewline()
{
    TokenStream* ts = tokenize("<?php\nfoo;");
    QVERIFY(ts->size() == 3);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition  (ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_STRING);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition  (ts, 1, 1, 2);

    QVERIFY(ts->token(2).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 2, 1, 3);
    compareEndPosition  (ts, 2, 1, 3);
    delete ts;
}

void LexerTest::testOpenTagWithSpace()
{
    TokenStream* ts = tokenize("<?php foo;");
    QVERIFY(ts->size() == 3);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition  (ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_STRING);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition  (ts, 1, 0, 8);

    QVERIFY(ts->token(2).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 2, 0, 9);
    compareEndPosition  (ts, 2, 0, 9);
    delete ts;
}

void LexerTest::testCommentOneLine()
{
    TokenStream* ts = tokenize("<?php\n//comment\nfoo;");
    QVERIFY(ts->size() == 4);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition  (ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition  (ts, 1, 1, 9);

    QVERIFY(ts->token(2).kind == Parser::Token_STRING);
    compareStartPosition(ts, 2, 2, 0);
    compareEndPosition  (ts, 2, 2, 2);

    QVERIFY(ts->token(3).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 3, 2, 3);
    compareEndPosition  (ts, 3, 2, 3);
    delete ts;
}

void LexerTest::testCommentMultiLine()
{
    TokenStream* ts = tokenize("<?php\n/*com\nment*/\nfoo;", true);
    QVERIFY(ts->size() == 5);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition  (ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition  (ts, 1, 2, 5);

    QVERIFY(ts->token(2).kind == Parser::Token_WHITESPACE);
    compareStartPosition(ts, 2, 2, 6);
    compareEndPosition  (ts, 2, 2, 6);

    QVERIFY(ts->token(3).kind == Parser::Token_STRING);
    compareStartPosition(ts, 3, 3, 0);
    compareEndPosition  (ts, 3, 3, 2);

    QVERIFY(ts->token(4).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 4, 3, 3);
    compareEndPosition  (ts, 4, 3, 3);
    delete ts;
}

TokenStream* LexerTest::tokenize(const QString& unit, bool debug)
{
    TokenStream* tokenStream = new TokenStream;
    Lexer lexer(tokenStream, unit);
    int token;
    while ((token = lexer.nextTokenKind())) {
        Parser::Token &t = tokenStream->next();
        t.begin = lexer.tokenBegin();
        t.end = lexer.tokenEnd();
        t.kind = token;
    }
    if (debug) {
        for (int i=0; i < tokenStream->size(); ++i) {
            Parser::Token &t = tokenStream->token(i);
            qint64 beginLine;
            qint64 beginColumn;
            tokenStream->startPosition(i, &beginLine, &beginColumn);
            qint64 endLine;
            qint64 endColumn;
            tokenStream->endPosition(i, &endLine, &endColumn);
            kDebug() << tokenText(t.kind)
                     << unit.mid(t.begin, t.end - t.begin + 1)
                     << QString("[%0-%1] - [%2-%3]").arg(beginLine).arg(beginColumn).arg(endLine).arg(endColumn);
        }
    }
    return tokenStream;
}
}

#include "lexertest.moc"
