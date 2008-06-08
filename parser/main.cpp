/* KDevelop PHP Support
 *
 * Copyright 2008 Niko Sams <niko.sams@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include "phplexer.h"
#include "phpparser.h"
#include "phpdebugvisitor.h"
#include "phpast.h"
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <QTextCodec>

using namespace PhpParser;
using namespace std;

void printToken(int token, const Lexer& lexer, const QString& content);
void showUsage(char**);

QTextStream qout(stdout);
QTextStream qerr(stderr);

int main(int argc, char* argv[])
{
    qout.setCodec("UTF-8");

    if (argc <= 1) {
        showUsage(argv);
        return 1;
    }

    QStringList files;
    bool debug = false;
    bool printTokens = false;
    for (int i = 1; i < argc; i++) {
        QString arg(argv[i]);
        if (arg.startsWith("--")) {
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

    foreach (QString fileName, files) {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly)) {
            qerr << "Can't open file " << fileName << endl;
            return 1;
        }
        QString content = QString::fromUtf8(file.readAll());
        file.close();

        qout << "Parsing file " << fileName << endl;

        if (printTokens) {
            Lexer lexer(0, content);
            int token;
            while ((token = lexer.nextTokenKind())) {
                printToken(token, lexer, content);
            }
            printToken(token, lexer, content);
        }

        KDevPG::TokenStream tokenStream;
        Parser::memoryPoolType memoryPool;

        // 0) setup
        Parser factParser;
        factParser.setTokenStream(&tokenStream);
        factParser.setMemoryPool(&memoryPool);
        factParser.setDebug(debug);

        // 1) tokenize
        factParser.tokenize(content);

        // 2) parse
        StartAst *ast = 0;
        bool matched = factParser.parseStart(&ast);
        if (matched) {
            qout << "successfully parsed" << endl;
            if (debug) {
                DebugVisitor d(&tokenStream, content);
                d.visitNode(ast);
            }
        } else {
            qerr << "parse error in file " << fileName << endl;
            return 255;
        }
    }
    return 0;
}

void showUsage(char** argv)
{
    qout << "Usage: [options] " << argv[0] << "file" << endl;
    qout << "" << endl;
    qout << "--print-tokens Print all found tokens" << endl;
    qout << "--debug        Print AST" << endl;
}
/**
 * print the token with the same text as php tokens - so they can be compared with
 * the result of get_token_all (see test-tokenize.php)
 **/
void printToken(int token, const Lexer& lexer, const QString& content)
{
    int begin = lexer.tokenBegin();
    int end = lexer.tokenEnd();
    QString tokenText = content.mid(begin, end-begin+1).replace("\n", "\\n");
    if (token == Parser::Token_INLINE_HTML) {
        qout << tokenText << " T_INLINE_HTML" << endl;
    } else if (token == Parser::Token_OPEN_TAG) {
        qout << tokenText << " T_OPEN_TAG" << endl;
    } else if (token == Parser::Token_CLOSE_TAG) {
        qout << tokenText << " T_CLOSE_TAG" << endl;
    } else if (token == Parser::Token_ECHO) {
        qout << tokenText << " T_ECHO" << endl;
    } else if (token == Parser::Token_WHITESPACE) {
        qout << tokenText << " T_WHITESPACE" << endl;
    } else if (token == Parser::Token_CONSTANT_ENCAPSED_STRING) {
        qout << tokenText << " T_CONSTANT_ENCAPSED_STRING" << endl;
    } else if (token == Parser::Token_SEMICOLON) {
        qout << tokenText << " ;" << endl;
    } else if (token == Parser::Token_VARIABLE) {
        qout << tokenText << " T_VARIABLE" << endl;
    } else if (token == Parser::Token_DOUBLE_QUOTE) {
        qout << tokenText << " \"" << endl;
    } else if (token == Parser::Token_ENCAPSED_AND_WHITESPACE) {
        qout << tokenText << " T_ENCAPSED_AND_WHITESPACE" << endl;
    } else if (token == Parser::Token_OBJECT_OPERATOR) {
        qout << tokenText << " T_OBJECT_OPERATOR" << endl;
    } else if (token == Parser::Token_LBRACKET) {
        qout << tokenText << " [" << endl;
    } else if (token == Parser::Token_RBRACKET) {
        qout << tokenText << " ]" << endl;
    } else if (token == Parser::Token_NUM_STRING) {
        qout << tokenText << " T_NUM_STRING" << endl;
    } else if (token == Parser::Token_STRING) {
        qout << tokenText << " T_STRING" << endl;
    } else if (token == Parser::Token_ASSIGN) {
        qout << tokenText << " =" << endl;
    } else if (token == Parser::Token_DNUMBER) {
        qout << tokenText << " T_DNUMBER" << endl;
    } else if (token == Parser::Token_LNUMBER) {
        qout << tokenText << " T_LNUMBER" << endl;
    } else if (token == Parser::Token_PLUS) {
        qout << tokenText << " +" << endl;
    } else if (token == Parser::Token_MINUS) {
        qout << tokenText << " -" << endl;
    } else if (token == Parser::Token_CONCAT) {
        qout << tokenText << " ." << endl;
    } else if (token == Parser::Token_INC) {
        qout << tokenText << " T_INC" << endl;
    } else if (token == Parser::Token_DEC) {
        qout << tokenText << " T_DEC" << endl;
    } else if (token == Parser::Token_IS_EQUAL) {
        qout << tokenText << " T_IS_EQUAL" << endl;
    } else if (token == Parser::Token_IS_NOT_EQUAL) {
        qout << tokenText << " T_IS_NOT_EQUAL" << endl;
    } else if (token == Parser::Token_IS_IDENTICAL) {
        qout << tokenText << " T_IS_IDENTICAL" << endl;
    } else if (token == Parser::Token_IS_NOT_IDENTICAL) {
        qout << tokenText << " T_IS_NOT_IDENTICAL" << endl;
    } else if (token == Parser::Token_IS_SMALLER) {
        qout << tokenText << " <" << endl;
    } else if (token == Parser::Token_IS_GREATER) {
        qout << tokenText << " >" << endl;
    } else if (token == Parser::Token_IS_SMALLER_OR_EQUAL) {
        qout << tokenText << " T_IS_SMALLER_OR_EQUAL" << endl;
    } else if (token == Parser::Token_IS_GREATER_OR_EQUAL) {
        qout << tokenText << " T_IS_GREATER_OR_EQUAL" << endl;
    } else if (token == Parser::Token_BOOLEAN_OR) {
        qout << tokenText << " T_BOOLEAN_OR" << endl;
    } else if (token == Parser::Token_BOOLEAN_AND) {
        qout << tokenText << " T_BOOLEAN_AND" << endl;
    } else if (token == Parser::Token_PLUS_ASSIGN) {
        qout << tokenText << " T_PLUS_EQUAL" << endl;
    } else if (token == Parser::Token_MINUS_ASSIGN) {
        qout << tokenText << " T_MINUS_EQUAL" << endl;
    } else if (token == Parser::Token_MUL_ASSIGN) {
        qout << tokenText << " T_MUL_EQUAL" << endl;
    } else if (token == Parser::Token_DIV_ASSIGN) {
        qout << tokenText << " T_DIV_EQUAL" << endl;
    } else if (token == Parser::Token_CONCAT_ASSIGN) {
        qout << tokenText << " T_CONCAT_EQUAL" << endl;
    } else if (token == Parser::Token_MOD_ASSIGN) {
        qout << tokenText << " T_MOD_EQUAL" << endl;
    } else if (token == Parser::Token_AND_ASSIGN) {
        qout << tokenText << " T_AND_EQUAL" << endl;
    } else if (token == Parser::Token_OR_ASSIGN) {
        qout << tokenText << " T_OR_EQUAL" << endl;
    } else if (token == Parser::Token_XOR_ASSIGN) {
        qout << tokenText << " T_XOR_EQUAL" << endl;
    } else if (token == Parser::Token_SL_ASSIGN) {
        qout << tokenText << " T_SL_EQUAL" << endl;
    } else if (token == Parser::Token_SR_ASSIGN) {
        qout << tokenText << " T_SR_EQUAL" << endl;
    } else if (token == Parser::Token_BANG) {
        qout << tokenText << " !" << endl;
    } else if (token == Parser::Token_QUESTION) {
        qout << tokenText << " ?" << endl;
    } else if (token == Parser::Token_COLON) {
        qout << tokenText << " :" << endl;
    } else if (token == Parser::Token_BIT_AND) {
        qout << tokenText << " &" << endl;
    } else if (token == Parser::Token_BIT_OR) {
        qout << tokenText << " |" << endl;
    } else if (token == Parser::Token_BIT_XOR) {
        qout << tokenText << " ^" << endl;
    } else if (token == Parser::Token_SL) {
        qout << tokenText << " T_SL" << endl;
    } else if (token == Parser::Token_SR) {
        qout << tokenText << " T_SR" << endl;
    } else if (token == Parser::Token_MUL) {
        qout << tokenText << " *" << endl;
    } else if (token == Parser::Token_DIV) {
        qout << tokenText << " /" << endl;
    } else if (token == Parser::Token_MOD) {
        qout << tokenText << " %" << endl;
    } else if (token == Parser::Token_TILDE) {
        qout << tokenText << " ~" << endl;
    } else if (token == Parser::Token_LPAREN) {
        qout << tokenText << " (" << endl;
    } else if (token == Parser::Token_RPAREN) {
        qout << tokenText << " )" << endl;
    } else if (token == Parser::Token_LBRACE) {
        qout << tokenText << " {" << endl;
    } else if (token == Parser::Token_RBRACE) {
        qout << tokenText << " }" << endl;
    } else if (token == Parser::Token_COMMA) {
        qout << tokenText << " ," << endl;
    } else if (token == Parser::Token_AT) {
        qout << tokenText << " @" << endl;
    } else if (token == Parser::Token_INCLUDE) {
        qout << tokenText << " T_INCLUDE" << endl;
    } else if (token == Parser::Token_INCLUDE_ONCE) {
        qout << tokenText << " T_INCLUDE_ONCE" << endl;
    } else if (token == Parser::Token_EVAL) {
        qout << tokenText << " T_EVAL" << endl;
    } else if (token == Parser::Token_REQUIRE) {
        qout << tokenText << " T_REQUIRE" << endl;
    } else if (token == Parser::Token_REQUIRE_ONCE) {
        qout << tokenText << " T_REQUIRE_ONCE" << endl;
    } else if (token == Parser::Token_PRINT) {
        qout << tokenText << " T_PRINT" << endl;
    } else if (token == Parser::Token_ABSTRACT) {
        qout << tokenText << " T_ABSTRACT" << endl;
    } else if (token == Parser::Token_BREAK) {
        qout << tokenText << " T_BREAK" << endl;
    } else if (token == Parser::Token_CASE) {
        qout << tokenText << " T_CASE" << endl;
    } else if (token == Parser::Token_CATCH) {
        qout << tokenText << " T_CATCH" << endl;
    } else if (token == Parser::Token_CLASS) {
        qout << tokenText << " T_CLASS" << endl;
    } else if (token == Parser::Token_CONST) {
        qout << tokenText << " T_CONST" << endl;
    } else if (token == Parser::Token_CONTINUE) {
        qout << tokenText << " T_CONTINUE" << endl;
    } else if (token == Parser::Token_DEFAULT) {
        qout << tokenText << " T_DEFAULT" << endl;
    } else if (token == Parser::Token_DO) {
        qout << tokenText << " T_DO" << endl;
    } else if (token == Parser::Token_ELSE) {
        qout << tokenText << " T_ELSE" << endl;
    } else if (token == Parser::Token_EXTENDS) {
        qout << tokenText << " T_EXTENDS" << endl;
    } else if (token == Parser::Token_FINAL) {
        qout << tokenText << " T_FINAL" << endl;
    } else if (token == Parser::Token_FOR) {
        qout << tokenText << " T_FOR" << endl;
    } else if (token == Parser::Token_IF) {
        qout << tokenText << " T_IF" << endl;
    } else if (token == Parser::Token_IMPLEMENTS) {
        qout << tokenText << " T_IMPLEMENTS" << endl;
    } else if (token == Parser::Token_INSTANCEOF) {
        qout << tokenText << " T_INSTANCEOF" << endl;
    } else if (token == Parser::Token_INTERFACE) {
        qout << tokenText << " T_INTERFACE" << endl;
    } else if (token == Parser::Token_NEW) {
        qout << tokenText << " T_NEW" << endl;
    } else if (token == Parser::Token_PRIVATE) {
        qout << tokenText << " T_PRIVATE" << endl;
    } else if (token == Parser::Token_PROTECTED) {
        qout << tokenText << " T_PROTECTED" << endl;
    } else if (token == Parser::Token_PUBLIC) {
        qout << tokenText << " T_PUBLIC" << endl;
    } else if (token == Parser::Token_RETURN) {
        qout << tokenText << " T_RETURN" << endl;
    } else if (token == Parser::Token_STATIC) {
        qout << tokenText << " T_STATIC" << endl;
    } else if (token == Parser::Token_SWITCH) {
        qout << tokenText << " T_SWITCH" << endl;
    } else if (token == Parser::Token_THROW) {
        qout << tokenText << " T_THROW" << endl;
    } else if (token == Parser::Token_TRY) {
        qout << tokenText << " T_TRY" << endl;
    } else if (token == Parser::Token_WHILE) {
        qout << tokenText << " T_WHILE" << endl;
    } else if (token == Parser::Token_INT_CAST) {
        qout << tokenText << " T_INT_CAST" << endl;
    } else if (token == Parser::Token_DOUBLE_CAST) {
        qout << tokenText << " T_DOUBLE_CAST" << endl;
    } else if (token == Parser::Token_STRING_CAST) {
        qout << tokenText << " T_STRING_CAST" << endl;
    } else if (token == Parser::Token_ARRAY_CAST) {
        qout << tokenText << " T_ARRAY_CAST" << endl;
    } else if (token == Parser::Token_OBJECT_CAST) {
        qout << tokenText << " T_OBJECT_CAST" << endl;
    } else if (token == Parser::Token_BOOL_CAST) {
        qout << tokenText << " T_BOOL_CAST" << endl;
    } else if (token == Parser::Token_UNSET_CAST) {
        qout << tokenText << " T_UNSET_CAST" << endl;
    } else if (token == Parser::Token_CLONE) {
        qout << tokenText << " T_CLONE" << endl;
    } else if (token == Parser::Token_EXIT) {
        qout << tokenText << " T_EXIT" << endl;
    } else if (token == Parser::Token_ELSEIF) {
        qout << tokenText << " T_ELSEIF" << endl;
    } else if (token == Parser::Token_ENDIF) {
        qout << tokenText << " T_ENDIF" << endl;
    } else if (token == Parser::Token_ENDWHILE) {
        qout << tokenText << " T_ENDWHILE" << endl;
    } else if (token == Parser::Token_ENDFOR) {
        qout << tokenText << " T_ENDFOR" << endl;
    } else if (token == Parser::Token_FOREACH) {
        qout << tokenText << " T_FOREACH" << endl;
    } else if (token == Parser::Token_ENDFOREACH) {
        qout << tokenText << " T_ENDFOREACH" << endl;
    } else if (token == Parser::Token_DECLARE) {
        qout << tokenText << " T_DECLARE" << endl;
    } else if (token == Parser::Token_ENDDECLARE) {
        qout << tokenText << " T_ENDDECLARE" << endl;
    } else if (token == Parser::Token_AS) {
        qout << tokenText << " T_AS" << endl;
    } else if (token == Parser::Token_ENDSWITCH) {
        qout << tokenText << " T_ENDSWITCH" << endl;
    } else if (token == Parser::Token_FUNCTION) {
        qout << tokenText << " T_FUNCTION" << endl;
    } else if (token == Parser::Token_USE) {
        qout << tokenText << " T_USE" << endl;
    } else if (token == Parser::Token_GLOBAL) {
        qout << tokenText << " T_GLOBAL" << endl;
    } else if (token == Parser::Token_VAR) {
        qout << tokenText << " T_VAR" << endl;
    } else if (token == Parser::Token_UNSET) {
        qout << tokenText << " T_UNSET" << endl;
    } else if (token == Parser::Token_ISSET) {
        qout << tokenText << " T_ISSET" << endl;
    } else if (token == Parser::Token_ISSET) {
        qout << tokenText << " T_ISSET" << endl;
    } else if (token == Parser::Token_EMPTY) {
        qout << tokenText << " T_EMPTY" << endl;
    } else if (token == Parser::Token_HALT_COMPILER) {
        qout << tokenText << " T_HALT_COMPILER" << endl;
    } else if (token == Parser::Token_DOUBLE_ARROW) {
        qout << tokenText << " T_DOUBLE_ARROW" << endl;
    } else if (token == Parser::Token_LIST) {
        qout << tokenText << " T_LIST" << endl;
    } else if (token == Parser::Token_ARRAY) {
        qout << tokenText << " T_ARRAY" << endl;
    } else if (token == Parser::Token_CLASS_C) {
        qout << tokenText << " T_CLASS_C" << endl;
    } else if (token == Parser::Token_METHOD_C) {
        qout << tokenText << " T_METHOD_C" << endl;
    } else if (token == Parser::Token_FUNC_C) {
        qout << tokenText << " T_FUNC_C" << endl;
    } else if (token == Parser::Token_LINE) {
        qout << tokenText << " T_LINE" << endl;
    } else if (token == Parser::Token_FILE) {
        qout << tokenText << " T_FILE" << endl;
    } else if (token == Parser::Token_COMMENT) {
        qout << tokenText << " T_COMMENT" << endl;
    } else if (token == Parser::Token_DOC_COMMENT) {
        qout << tokenText << " T_DOC_COMMENT" << endl;
    } else if (token == Parser::Token_PAAMAYIM_NEKUDOTAYIM) {
        qout << tokenText << " T_DOUBLE_COLON" << endl;
    } else if (token == Parser::Token_OPEN_TAG_WITH_ECHO) {
        qout << tokenText << " T_OPEN_TAG_WITH_ECHO" << endl;
    } else if (token == Parser::Token_CURLY_OPEN) {
        qout << tokenText << " T_CURLY_OPEN" << endl;
    } else if (token == Parser::Token_STRING_VARNAME) {
        qout << tokenText << " T_STRING_VARNAME" << endl;
    } else if (token == Parser::Token_DOLLAR_OPEN_CURLY_BRACES) {
        qout << tokenText << " T_DOLLAR_OPEN_CURLY_BRACES" << endl;
    } else if (token == Parser::Token_DOLLAR) {
        qout << tokenText << " $" << endl;
    } else if (token == Parser::Token_LOGICAL_XOR) {
        qout << tokenText << " T_LOGICAL_XOR" << endl;
    } else if (token == Parser::Token_LOGICAL_AND) {
        qout << tokenText << " T_LOGICAL_AND" << endl;
    } else if (token == Parser::Token_LOGICAL_OR) {
        qout << tokenText << " T_LOGICAL_OR" << endl;
    } else if (token == Parser::Token_START_HEREDOC) {
        qout << tokenText << " T_START_HEREDOC" << endl;
    } else if (token == Parser::Token_END_HEREDOC) {
        qout << tokenText << " T_END_HEREDOC" << endl;
    } else if (token == Parser::Token_BACKTICK) {
        qout << tokenText << " `" << endl;
    } else if (token == 0) {
        qout << tokenText << " end of file" << endl;
    } else {
        qout << tokenText << " unknown token" << token;
    }
}
