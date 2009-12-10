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
#include "phptokentext.h"

QTEST_MAIN(Php::LexerTest)
namespace Php
{

void compareEndPosition(TokenStream* tokenStream, qint64 index, qint64 expectedLine, qint64 expectedColumn)
{
    qint64 line;
    qint64 column;
    tokenStream->endPosition(index, &line, &column);
    kDebug() << "  end" << index << ": actual" << line << column << "expected" << expectedLine << expectedColumn;
    QCOMPARE(line, expectedLine);
    QCOMPARE(column, expectedColumn);
}

void compareStartPosition(TokenStream* tokenStream, qint64 index, qint64 expectedLine, qint64 expectedColumn)
{
    qint64 line;
    qint64 column;
    tokenStream->startPosition(index, &line, &column);
    kDebug() << "start" << index << ": actual" << line << column << "expected" << expectedLine << expectedColumn;
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
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_STRING);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 1, 2);

    QVERIFY(ts->token(2).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 2, 1, 3);
    compareEndPosition(ts, 2, 1, 3);
    delete ts;
}

void LexerTest::testOpenTagWithSpace()
{
    TokenStream* ts = tokenize("<?php foo;");
    QVERIFY(ts->size() == 3);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_STRING);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 0, 8);

    QVERIFY(ts->token(2).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 2, 0, 9);
    compareEndPosition(ts, 2, 0, 9);
    delete ts;
}

void LexerTest::testCommentOneLine()
{
    TokenStream* ts = tokenize("<?php\n//comment\nfoo;");
    QVERIFY(ts->size() == 4);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 1, 9);

    QVERIFY(ts->token(2).kind == Parser::Token_STRING);
    compareStartPosition(ts, 2, 2, 0);
    compareEndPosition(ts, 2, 2, 2);

    QVERIFY(ts->token(3).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 3, 2, 3);
    compareEndPosition(ts, 3, 2, 3);
    delete ts;
}

void LexerTest::testCommentOneLine2()
{
    TokenStream* ts = tokenize("<?php\n#comment\nfoo;");
    QVERIFY(ts->size() == 4);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 1, 8);

    QVERIFY(ts->token(2).kind == Parser::Token_STRING);
    compareStartPosition(ts, 2, 2, 0);
    compareEndPosition(ts, 2, 2, 2);

    QVERIFY(ts->token(3).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 3, 2, 3);
    compareEndPosition(ts, 3, 2, 3);
    delete ts;
}

void LexerTest::testCommentMultiLine()
{
    TokenStream* ts = tokenize("<?php\n/*com\nment*/\nfoo;", true);
    QVERIFY(ts->size() == 5);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 2, 5);

    QVERIFY(ts->token(2).kind == Parser::Token_WHITESPACE);
    compareStartPosition(ts, 2, 2, 6);
    compareEndPosition(ts, 2, 2, 6);

    QVERIFY(ts->token(3).kind == Parser::Token_STRING);
    compareStartPosition(ts, 3, 3, 0);
    compareEndPosition(ts, 3, 3, 2);

    QVERIFY(ts->token(4).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 4, 3, 3);
    compareEndPosition(ts, 4, 3, 3);
    delete ts;
}

void LexerTest::testCommentMultiLine2()
{
    TokenStream* ts = tokenize("<?php\n/*\nment*/\nfoo;", true);
    QVERIFY(ts->size() == 5);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 2, 5);

    QVERIFY(ts->token(2).kind == Parser::Token_WHITESPACE);
    compareStartPosition(ts, 2, 2, 6);
    compareEndPosition(ts, 2, 2, 6);

    QVERIFY(ts->token(3).kind == Parser::Token_STRING);
    compareStartPosition(ts, 3, 3, 0);
    compareEndPosition(ts, 3, 3, 2);

    QVERIFY(ts->token(4).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 4, 3, 3);
    compareEndPosition(ts, 4, 3, 3);
    delete ts;
}

void LexerTest::testEndTag()
{
    TokenStream* ts = tokenize("<?\n':\n'?>\n>", true, Lexer::DefaultState);
    //don't crash and we are fine
    delete ts;
}

void LexerTest::testNewlineInString()
{
    //0            1
    //012345 6 7 890123456789
    TokenStream* ts = tokenize("<?php \"\n\";", true);
    QVERIFY(ts->size() == 3);

    QVERIFY(ts->token(1).kind == Parser::Token_CONSTANT_ENCAPSED_STRING);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 1, 0);

    QVERIFY(ts->token(2).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 2, 1, 1);
    compareEndPosition(ts, 2, 1, 1);
    delete ts;
}

void LexerTest::testNewlineInString2()
{
    //0
    //0123 4567
    TokenStream* ts = tokenize("<?php '\n';", true);
    QCOMPARE((int)ts->size(), 3);

    QVERIFY(ts->token(1).kind == Parser::Token_CONSTANT_ENCAPSED_STRING);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 1, 0);

    QVERIFY(ts->token(2).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 2, 1, 1);
    compareEndPosition(ts, 2, 1, 1);
    delete ts;
}

void LexerTest::testNewlineInStringWithVar()
{
    TokenStream* ts = tokenize("<?php \"$a\n\";", true);
    QCOMPARE((int)ts->size(), 6);

    QVERIFY(ts->token(1).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 0, 6);

    QVERIFY(ts->token(2).kind == Parser::Token_VARIABLE);
    compareStartPosition(ts, 2, 0, 7);
    compareEndPosition(ts, 2, 0, 8);

    QVERIFY(ts->token(3).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 3, 0, 9);
    compareEndPosition(ts, 3, 0, 9);

    QVERIFY(ts->token(4).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 4, 1, 0);
    compareEndPosition(ts, 4, 1, 0);

    QVERIFY(ts->token(5).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 5, 1, 1);
    compareEndPosition(ts, 5, 1, 1);
    delete ts;
}

void LexerTest::testNewlineInStringWithVar2()
{
    //0            1
    //012345 6 789 0123456789
    TokenStream* ts = tokenize("<?php \"\n$a\n\";", true);
    QCOMPARE((int)ts->size(), 7);

    QVERIFY(ts->token(1).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 0, 6);

    QVERIFY(ts->token(2).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 2, 0, 7);
    compareEndPosition(ts, 2, 0, 7);

    QVERIFY(ts->token(3).kind == Parser::Token_VARIABLE);
    compareStartPosition(ts, 3, 1, 0);
    compareEndPosition(ts, 3, 1, 1);

    QVERIFY(ts->token(4).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 4, 1, 2);
    compareEndPosition(ts, 4, 1, 2);

    QVERIFY(ts->token(5).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 5, 2, 0);
    compareEndPosition(ts, 5, 2, 0);

    QVERIFY(ts->token(6).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 6, 2, 1);
    compareEndPosition(ts, 6, 2, 1);
    delete ts;
}

void LexerTest::testNewlineInStringWithVar3()
{
    //0            1
    //012345 6 789 0123456789
    TokenStream* ts = tokenize("<?php \"{$$a}\";", true);
    QCOMPARE((int)ts->size(), 7);

    QVERIFY(ts->token(1).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 0, 6);

    QVERIFY(ts->token(2).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 2, 0, 7);
    compareEndPosition(ts, 2, 0, 8);

    QVERIFY(ts->token(3).kind == Parser::Token_VARIABLE);
    compareStartPosition(ts, 3, 0, 9);
    compareEndPosition(ts, 3, 0, 10);

    QVERIFY(ts->token(4).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 4, 0, 11);
    compareEndPosition(ts, 4, 0, 11);

    QVERIFY(ts->token(5).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 5, 0, 12);
    compareEndPosition(ts, 5, 0, 12);

    QVERIFY(ts->token(6).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 6, 0, 13);
    compareEndPosition(ts, 6, 0, 13);
    delete ts;
}

void LexerTest::testMultiplePhpSections()
{

    //0            1
    //012345 6 789 0123456789
    TokenStream* ts = tokenize("<?php $a;?>\n<html>\n<?php $a;?>", true);
    QCOMPARE((int)ts->size(), 9);

    qint64 index = 0;
    for (qint64 line = 0; line <= 2; ++line) {
        if (line == 1) {
            // the html stuff in the middle
            QVERIFY(ts->token(index).kind == Parser::Token_INLINE_HTML);
            compareStartPosition(ts, index, 0, 11);
            compareEndPosition(ts, index, 1, 6);
            ++index;
        } else {
            // the php stuff (symmetric) at the start and end
            QVERIFY(ts->token(index).kind == Parser::Token_OPEN_TAG);
            compareStartPosition(ts, index, line, 0);
            compareEndPosition(ts, index, line, 5);
            ++index;

            QVERIFY(ts->token(index).kind == Parser::Token_VARIABLE);
            compareStartPosition(ts, index, line, 6);
            compareEndPosition(ts, index, line, 7);
            ++index;

            QVERIFY(ts->token(index).kind == Parser::Token_SEMICOLON);
            compareStartPosition(ts, index, line, 8);
            compareEndPosition(ts, index, line, 8);
            ++index;

            QVERIFY(ts->token(index).kind == Parser::Token_CLOSE_TAG);
            compareStartPosition(ts, index, line, 9);
            compareEndPosition(ts, index, line, 10);
            ++index;
        }
    }
    delete ts;
}

void LexerTest::testHereDoc()
{
    TokenStream* ts = tokenize("<?php\necho <<<EOD1\nstart $text\nend\nEOD1;\n$extern;", true);
    QCOMPARE((int)ts->size(), 12);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_ECHO);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 1, 3);

    QVERIFY(ts->token(3).kind == Parser::Token_START_HEREDOC);
    compareStartPosition(ts, 3, 1, 5);
    compareEndPosition(ts, 3, 1, 12);

    QVERIFY(ts->token(4).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 4, 2, 0);
    compareEndPosition(ts, 4, 2, 5);

    QVERIFY(ts->token(5).kind == Parser::Token_VARIABLE);
    compareStartPosition(ts, 5, 2, 6);
    compareEndPosition(ts, 5, 2, 10);

    QVERIFY(ts->token(6).kind == Parser::Token_ENCAPSED_AND_WHITESPACE);
    compareStartPosition(ts, 6, 2, 11);
    compareEndPosition(ts, 6, 3, 3);

    QVERIFY(ts->token(7).kind == Parser::Token_END_HEREDOC);
    compareStartPosition(ts, 7, 4, 0);
    compareEndPosition(ts, 7, 4, 3);

    QVERIFY(ts->token(8).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 8, 4, 4);
    compareEndPosition(ts, 8, 4, 4);

    QVERIFY(ts->token(10).kind == Parser::Token_VARIABLE);
    compareStartPosition(ts, 10, 5, 0);
    compareEndPosition(ts, 10, 5, 6);

    QVERIFY(ts->token(11).kind == Parser::Token_SEMICOLON);
    compareStartPosition(ts, 11, 5, 7);
    compareEndPosition(ts, 11, 5, 7);
    delete ts;
}

void LexerTest::testCommonStringTokens()
{
    // all these should have open_tag followed by constant encapsed string
    foreach ( const QString& code, QStringList() << "<?php ''" << "<?php \"\"" << "<?php '" << "<?php \"" ) {
        kDebug() << code;
        TokenStream* ts = tokenize(code, true);

        QCOMPARE((int)ts->size(), 2);

        QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
        compareStartPosition(ts, 0, 0, 0);
        compareEndPosition(ts, 0, 0, 5);

        QVERIFY(ts->token(1).kind == Parser::Token_CONSTANT_ENCAPSED_STRING);
        compareStartPosition(ts, 1, 0, 6);
        compareEndPosition(ts, 1, 0, code.size() - 1);

        delete ts;
    }
}

void LexerTest::testNonTerminatedStringWithVar()
{
    TokenStream* ts = tokenize("<?php \"$a", true);

    QCOMPARE((int)ts->size(), 3);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_DOUBLE_QUOTE);
    compareStartPosition(ts, 1, 0, 6);
    compareEndPosition(ts, 1, 0, 6);

    QVERIFY(ts->token(2).kind == Parser::Token_VARIABLE);
    compareStartPosition(ts, 2, 0, 7);
    compareEndPosition(ts, 2, 0, 8);

    delete ts;
}

void LexerTest::testPhpBlockWithComment()
{
    TokenStream* ts = tokenize(
        "<?php\n"
        "//asdf\n"
        "?>\n"
        "<?php\n"
    , true);

    QCOMPARE((int)ts->size(), 5);

    QVERIFY(ts->token(0).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 0, 0, 0);
    compareEndPosition(ts, 0, 0, 5);

    QVERIFY(ts->token(1).kind == Parser::Token_COMMENT);
    compareStartPosition(ts, 1, 1, 0);
    compareEndPosition(ts, 1, 1, 6);

    QVERIFY(ts->token(2).kind == Parser::Token_CLOSE_TAG);
    compareStartPosition(ts, 2, 2, 0);
    compareEndPosition(ts, 2, 2, 1);

    QVERIFY(ts->token(3).kind == Parser::Token_INLINE_HTML);
    compareStartPosition(ts, 3, 2, 2);
    compareEndPosition(ts, 3, 2, 2);

    QVERIFY(ts->token(4).kind == Parser::Token_OPEN_TAG);
    compareStartPosition(ts, 4, 3, 0);
    compareEndPosition(ts, 4, 3, 5);
}

TokenStream* LexerTest::tokenize(const QString& unit, bool debug, int initialState)
{
    TokenStream* tokenStream = new TokenStream;
    Lexer lexer(tokenStream, unit, initialState);
    int token;
    int i = 0;
    QList<Parser::Token> tokens;
    while ((token = lexer.nextTokenKind())) {
        Parser::Token &t = tokenStream->next();
        t.begin = lexer.tokenBegin();
        t.end = lexer.tokenEnd();
        t.kind = token;
        tokens << t;
    }
    if (debug) {
        foreach(const Parser::Token &t, tokens) {
            qint64 beginLine;
            qint64 beginColumn;
            tokenStream->startPosition(i, &beginLine, &beginColumn);
            qint64 endLine;
            qint64 endColumn;
            tokenStream->endPosition(i, &endLine, &endColumn);
            kDebug() << tokenText(t.kind)
            << unit.mid(t.begin, t.end - t.begin + 1).replace('\n', "\\n")
            << QString("[%0-%1] - [%2-%3]").arg(beginLine).arg(beginColumn).arg(endLine).arg(endColumn);
            ++i;
        }
    }
    return tokenStream;
}
}

#include "lexertest.moc"
