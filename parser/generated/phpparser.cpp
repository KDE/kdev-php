// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "phpparser.h"


#include "phplexer.h"
#include <QtCore/QDebug>

namespace Php
{

void Parser::tokenize( const QString& contents )
{
    m_contents = contents;
    Lexer lexer( tokenStream, contents );
    int kind = Parser::Token_EOF;
    int lastDocCommentBegin;
    int lastDocCommentEnd;

    do
    {
        lastDocCommentBegin = 0;
        lastDocCommentEnd = 0;
        kind = lexer.nextTokenKind();
        while (kind == Parser::Token_WHITESPACE || kind == Parser::Token_COMMENT || kind == Parser::Token_DOC_COMMENT)
        {
            if (kind == Parser::Token_DOC_COMMENT)
            {
                lastDocCommentBegin = lexer.tokenBegin();
                lastDocCommentEnd = lexer.tokenEnd();
            }
            kind = lexer.nextTokenKind();
        }
        if ( !kind ) // when the lexer returns 0, the end of file is reached
        {
            kind = Parser::Token_EOF;
        }
        Parser::Token &t = tokenStream->next();
        t.begin = lexer.tokenBegin();
        t.end = lexer.tokenEnd();
        t.kind = kind;
        t.docCommentBegin = lastDocCommentBegin;
        t.docCommentEnd = lastDocCommentEnd;
        //if ( m_debug ) qDebug() << kind << tokenText(t.begin,t.end) << t.begin << t.end;
    }
    while ( kind != Parser::Token_EOF );

    yylex(); // produce the look ahead token
}


QString Parser::tokenText(qint64 begin, qint64 end)
{
    return m_contents.mid(begin,end-begin+1);
}


void Parser::reportProblem( Parser::ProblemType type, const QString& message )
{
    if (type == Error)
        qDebug() << "** ERROR:" << message;
    else if (type == Warning)
        qDebug() << "** WARNING:" << message;
    else if (type == Info)
        qDebug() << "** Info:" << message;
}


// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
    reportProblem( Parser::Error, QString("Expected token \"%1\"").arg(name));
}

void Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
    qint64 line;
    qint64 col;
    qint64 index = tokenStream->index()-1;
    Token &token = tokenStream->token(index);
    kDebug() << "token starts at:" << token.begin;
    kDebug() << "index is:" << index;
    tokenStream->startPosition(index, &line, &col);
    QString tokenValue = tokenText(token.begin, token.end);
    reportProblem( Parser::Error,
                   QString("Expected symbol \"%1\" (current token: \"%2\" [%3] at line: %4 col: %5)")
                   .arg(name)
                   .arg(token.kind != 0 ? tokenValue : "EOF")
                   .arg(token.kind)
                   .arg(line)
                   .arg(col));
}

void Parser::setDebug( bool debug )
{
    m_debug = debug;
}

Parser::ParserState *Parser::copyCurrentState()
{
    ParserState *state = new ParserState();
    state->varExpressionState = m_state.varExpressionState;
    state->varExpressionIsVariable = m_state.varExpressionIsVariable;
    return state;
}

void Parser::restoreState( Parser::ParserState* state)
{
    m_state.varExpressionState = state->varExpressionState;
    m_state.varExpressionIsVariable = state->varExpressionIsVariable;
}

} // end of namespace Php


namespace Php
{

bool Parser::parseAdditiveExpression(AdditiveExpressionAst **yynode)
{
    *yynode = create<AdditiveExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        MultiplicativeExpressionAst *__node_0 = 0;
        if (!parseMultiplicativeExpression(&__node_0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MultiplicativeExpressionKind, "multiplicativeExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_0;

        while (yytoken == Token_PLUS
               || yytoken == Token_CONCAT
               || yytoken == Token_MINUS)
        {
            AdditiveExpressionRestAst *__node_1 = 0;
            if (!parseAdditiveExpressionRest(&__node_1))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AdditiveExpressionRestKind, "additiveExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_1, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAdditiveExpressionRest(AdditiveExpressionRestAst **yynode)
{
    *yynode = create<AdditiveExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PLUS
        || yytoken == Token_CONCAT
        || yytoken == Token_MINUS)
    {
        if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CONCAT)
        {
            if (yytoken != Token_CONCAT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONCAT, ".");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        MultiplicativeExpressionAst *__node_2 = 0;
        if (!parseMultiplicativeExpression(&__node_2))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MultiplicativeExpressionKind, "multiplicativeExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_2;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayPairValue(ArrayPairValueAst **yynode)
{
    *yynode = create<ArrayPairValueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_BIT_AND
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        if (yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_ARRAY
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_REQUIRE
            || yytoken == Token_CLASS_C
            || yytoken == Token_DNUMBER
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_LNUMBER
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_LPAREN
            || yytoken == Token_INT_CAST
            || yytoken == Token_FUNC_C
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_LIST
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_START_HEREDOC
            || yytoken == Token_NEW)
        {
            ExprAst *__node_3 = 0;
            if (!parseExpr(&__node_3))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_3;

            if (yytoken == Token_DOUBLE_ARROW)
            {
                if (yytoken != Token_DOUBLE_ARROW)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DOUBLE_ARROW, "=>");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_STRING_VARNAME
                    || yytoken == Token_DOUBLE_QUOTE
                    || yytoken == Token_EVAL
                    || yytoken == Token_ARRAY
                    || yytoken == Token_ARRAY_CAST
                    || yytoken == Token_CLONE
                    || yytoken == Token_INC
                    || yytoken == Token_ISSET
                    || yytoken == Token_REQUIRE
                    || yytoken == Token_CLASS_C
                    || yytoken == Token_DNUMBER
                    || yytoken == Token_OBJECT_CAST
                    || yytoken == Token_EXIT
                    || yytoken == Token_BACKTICK
                    || yytoken == Token_DEC
                    || yytoken == Token_EMPTY
                    || yytoken == Token_REQUIRE_ONCE
                    || yytoken == Token_METHOD_C
                    || yytoken == Token_AT
                    || yytoken == Token_LNUMBER
                    || yytoken == Token_BOOL_CAST
                    || yytoken == Token_TILDE
                    || yytoken == Token_BANG
                    || yytoken == Token_LPAREN
                    || yytoken == Token_INT_CAST
                    || yytoken == Token_FUNC_C
                    || yytoken == Token_PLUS
                    || yytoken == Token_UNSET_CAST
                    || yytoken == Token_INCLUDE
                    || yytoken == Token_DOLLAR
                    || yytoken == Token_DOUBLE_CAST
                    || yytoken == Token_CONSTANT_ENCAPSED_STRING
                    || yytoken == Token_LINE
                    || yytoken == Token_MINUS
                    || yytoken == Token_STRING
                    || yytoken == Token_INCLUDE_ONCE
                    || yytoken == Token_LIST
                    || yytoken == Token_STRING_CAST
                    || yytoken == Token_VARIABLE
                    || yytoken == Token_PRINT
                    || yytoken == Token_FILE
                    || yytoken == Token_START_HEREDOC
                    || yytoken == Token_NEW)
                {
                    ExprAst *__node_4 = 0;
                    if (!parseExpr(&__node_4))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ExprKind, "expr");
                        }
                        return false;
                    }
                    (*yynode)->exprValue = __node_4;

                }
                else if (yytoken == Token_BIT_AND)
                {
                    if (yytoken != Token_BIT_AND)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_BIT_AND, "&");
                        }
                        return false;
                    }
                    yylex();

                    VariableAst *__node_5 = 0;
                    if (!parseVariable(&__node_5))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableKind, "variable");
                        }
                        return false;
                    }
                    (*yynode)->varValue = __node_5;

                }
                else
                {
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

            VariableAst *__node_6 = 0;
            if (!parseVariable(&__node_6))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->variable = __node_6;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignmentExpression(AssignmentExpressionAst **yynode)
{
    *yynode = create<AssignmentExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        m_state.varExpressionIsVariable = false;
        ConditionalExpressionAst *__node_7 = 0;
        if (!parseConditionalExpression(&__node_7))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ConditionalExpressionKind, "conditionalExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_7;

        if (yytoken == Token_ASSIGN)
        {
            AssignmentExpressionEqualAst *__node_8 = 0;
            if (!parseAssignmentExpressionEqual(&__node_8))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssignmentExpressionEqualKind, "assignmentExpressionEqual");
                }
                return false;
            }
            (*yynode)->assignmentAxpressionEqual = __node_8;

        }
        else if (yytoken == Token_MUL_ASSIGN
                 || yytoken == Token_MOD_ASSIGN
                 || yytoken == Token_XOR_ASSIGN
                 || yytoken == Token_MINUS_ASSIGN
                 || yytoken == Token_CONCAT_ASSIGN
                 || yytoken == Token_OR_ASSIGN
                 || yytoken == Token_PLUS_ASSIGN
                 || yytoken == Token_SR_ASSIGN
                 || yytoken == Token_DIV_ASSIGN
                 || yytoken == Token_AND_ASSIGN
                 || yytoken == Token_SL_ASSIGN)
        {
            if (yytoken == Token_PLUS_ASSIGN)
            {
                if (yytoken != Token_PLUS_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PLUS_ASSIGN, "+=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_MINUS_ASSIGN)
            {
                if (yytoken != Token_MINUS_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_MINUS_ASSIGN, "-=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_MUL_ASSIGN)
            {
                if (yytoken != Token_MUL_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_MUL_ASSIGN, "*=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_DIV_ASSIGN)
            {
                if (yytoken != Token_DIV_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DIV_ASSIGN, "/=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_CONCAT_ASSIGN)
            {
                if (yytoken != Token_CONCAT_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_CONCAT_ASSIGN, ".=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_MOD_ASSIGN)
            {
                if (yytoken != Token_MOD_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_MOD_ASSIGN, "%=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_AND_ASSIGN)
            {
                if (yytoken != Token_AND_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_AND_ASSIGN, "&=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_OR_ASSIGN)
            {
                if (yytoken != Token_OR_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_OR_ASSIGN, "|=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_XOR_ASSIGN)
            {
                if (yytoken != Token_XOR_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_XOR_ASSIGN, "^=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_SL_ASSIGN)
            {
                if (yytoken != Token_SL_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SL_ASSIGN, "<<=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_SR_ASSIGN)
            {
                if (yytoken != Token_SR_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SR_ASSIGN, ">>=");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            AssignmentExpressionCheckIfVariableAst *__node_9 = 0;
            if (!parseAssignmentExpressionCheckIfVariable(&__node_9))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssignmentExpressionCheckIfVariableKind, "assignmentExpressionCheckIfVariable");
                }
                return false;
            }
            AssignmentExpressionAst *__node_10 = 0;
            if (!parseAssignmentExpression(&__node_10))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssignmentExpressionKind, "assignmentExpression");
                }
                return false;
            }
            (*yynode)->assignmentExpression = __node_10;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst **yynode)
{
    *yynode = create<AssignmentExpressionCheckIfVariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (true /*epsilon*/ || yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_EOF
        || yytoken == Token_ARRAY
        || yytoken == Token_BIT_AND
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_DOLLAR
        || yytoken == Token_INCLUDE
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {

        if (!m_state.varExpressionIsVariable)
        {
            reportProblem(Error, "Left side is not a variable");
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignmentExpressionEqual(AssignmentExpressionEqualAst **yynode)
{
    *yynode = create<AssignmentExpressionEqualAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASSIGN)
    {
        if (yytoken != Token_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ASSIGN, "=");
            }
            return false;
        }
        yylex();

        AssignmentExpressionCheckIfVariableAst *__node_11 = 0;
        if (!parseAssignmentExpressionCheckIfVariable(&__node_11))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AssignmentExpressionCheckIfVariableKind, "assignmentExpressionCheckIfVariable");
            }
            return false;
        }
        if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_NEW)
            {
                reportProblem(Warning, "=& new foo() is deprecated");
                m_state.varExpressionState = OnlyNewObject;
            }
            else
            {
                m_state.varExpressionState = OnlyVariable;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        AssignmentExpressionAst *__node_12 = 0;
        if (!parseAssignmentExpression(&__node_12))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AssignmentExpressionKind, "assignmentExpression");
            }
            return false;
        }
        (*yynode)->assignmentExpression = __node_12;

        m_state.varExpressionState = Normal;
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignmentList(AssignmentListAst **yynode)
{
    *yynode = create<AssignmentListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING
        || yytoken == Token_LIST
        || yytoken == Token_COMMA || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        AssignmentListElementAst *__node_13 = 0;
        if (!parseAssignmentListElement(&__node_13))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AssignmentListElementKind, "assignmentListElement");
            }
            return false;
        }
        (*yynode)->elementSequence = snoc((*yynode)->elementSequence, __node_13, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            AssignmentListElementAst *__node_14 = 0;
            if (!parseAssignmentListElement(&__node_14))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssignmentListElementKind, "assignmentListElement");
                }
                return false;
            }
            (*yynode)->elementSequence = snoc((*yynode)->elementSequence, __node_14, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignmentListElement(AssignmentListElementAst **yynode)
{
    *yynode = create<AssignmentListElementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING
        || yytoken == Token_LIST || yytoken == Token_EOF
        || yytoken == Token_RPAREN
        || yytoken == Token_COMMA)
    {
        if (yytoken == Token_VARIABLE
            || yytoken == Token_DOLLAR
            || yytoken == Token_STRING)
        {
            VariableAst *__node_15 = 0;
            if (!parseVariable(&__node_15))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->variable = __node_15;

        }
        else if (yytoken == Token_LIST)
        {
            if (yytoken != Token_LIST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LIST, "list");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            AssignmentListAst *__node_16 = 0;
            if (!parseAssignmentList(&__node_16))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssignmentListKind, "assignmentList");
                }
                return false;
            }
            (*yynode)->assignmentList = __node_16;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBaseVariable(BaseVariableAst **yynode)
{
    *yynode = create<BaseVariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING)
    {
        if (yytoken == Token_VARIABLE
            || yytoken == Token_DOLLAR)
        {
            CompoundVariableWithSimpleIndirectReferenceAst *__node_17 = 0;
            if (!parseCompoundVariableWithSimpleIndirectReference(&__node_17))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundVariableWithSimpleIndirectReferenceKind, "compoundVariableWithSimpleIndirectReference");
                }
                return false;
            }
            (*yynode)->var = __node_17;

            while (yytoken == Token_LBRACE
                   || yytoken == Token_LBRACKET)
            {
                DimListItemAst *__node_18 = 0;
                if (!parseDimListItem(&__node_18))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::DimListItemKind, "dimListItem");
                    }
                    return false;
                }
                (*yynode)->offsetItemsSequence = snoc((*yynode)->offsetItemsSequence, __node_18, memoryPool);

            }
        }
        else if (yytoken == Token_STRING)
        {
            StaticMemberAst *__node_19 = 0;
            if (!parseStaticMember(&__node_19))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticMemberKind, "staticMember");
                }
                return false;
            }
            (*yynode)->staticMember = __node_19;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst **yynode)
{
    *yynode = create<BaseVariableWithFunctionCallsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING)
    {
        bool blockErrors_1 = blockErrors(true);
        qint64 try_startToken_1 = tokenStream->index() - 1;
        ParserState *try_startState_1 = copyCurrentState();
        {
            FunctionCallAst *__node_20 = 0;
            if (!parseFunctionCall(&__node_20))
            {
                goto __catch_1;
            }
            (*yynode)->functionCall = __node_20;

        }
        blockErrors(blockErrors_1);
        if (try_startState_1)
            delete try_startState_1;

        if (false) // the only way to enter here is using goto
        {
__catch_1:
            if (try_startState_1)
            {
                restoreState(try_startState_1);
                delete try_startState_1;
            }
            blockErrors(blockErrors_1);
            rewind(try_startToken_1);

            BaseVariableAst *__node_21 = 0;
            if (!parseBaseVariable(&__node_21))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BaseVariableKind, "baseVariable");
                }
                return false;
            }
            (*yynode)->baseVariable = __node_21;

        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitAndExpression(BitAndExpressionAst **yynode)
{
    *yynode = create<BitAndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        EqualityExpressionAst *__node_22 = 0;
        if (!parseEqualityExpression(&__node_22))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EqualityExpressionKind, "equalityExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_22, memoryPool);

        while (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

            EqualityExpressionAst *__node_23 = 0;
            if (!parseEqualityExpression(&__node_23))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EqualityExpressionKind, "equalityExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_23, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitOrExpression(BitOrExpressionAst **yynode)
{
    *yynode = create<BitOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        BitXorExpressionAst *__node_24 = 0;
        if (!parseBitXorExpression(&__node_24))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitXorExpressionKind, "bitXorExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_24, memoryPool);

        while (yytoken == Token_BIT_OR)
        {
            if (yytoken != Token_BIT_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_OR, "|");
                }
                return false;
            }
            yylex();

            BitXorExpressionAst *__node_25 = 0;
            if (!parseBitXorExpression(&__node_25))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitXorExpressionKind, "bitXorExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_25, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitXorExpression(BitXorExpressionAst **yynode)
{
    *yynode = create<BitXorExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        BitAndExpressionAst *__node_26 = 0;
        if (!parseBitAndExpression(&__node_26))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitAndExpressionKind, "bitAndExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_26, memoryPool);

        while (yytoken == Token_BIT_XOR)
        {
            if (yytoken != Token_BIT_XOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_XOR, "^");
                }
                return false;
            }
            yylex();

            BitAndExpressionAst *__node_27 = 0;
            if (!parseBitAndExpression(&__node_27))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitAndExpressionKind, "bitAndExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_27, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBooleanAndExpression(BooleanAndExpressionAst **yynode)
{
    *yynode = create<BooleanAndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        BitOrExpressionAst *__node_28 = 0;
        if (!parseBitOrExpression(&__node_28))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitOrExpressionKind, "bitOrExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_28, memoryPool);

        while (yytoken == Token_BOOLEAN_AND)
        {
            if (yytoken != Token_BOOLEAN_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOOLEAN_AND, "&&");
                }
                return false;
            }
            yylex();

            BitOrExpressionAst *__node_29 = 0;
            if (!parseBitOrExpression(&__node_29))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitOrExpressionKind, "bitOrExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_29, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBooleanOrExpression(BooleanOrExpressionAst **yynode)
{
    *yynode = create<BooleanOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        BooleanAndExpressionAst *__node_30 = 0;
        if (!parseBooleanAndExpression(&__node_30))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BooleanAndExpressionKind, "booleanAndExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_30, memoryPool);

        while (yytoken == Token_BOOLEAN_OR)
        {
            if (yytoken != Token_BOOLEAN_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOOLEAN_OR, "||");
                }
                return false;
            }
            yylex();

            BooleanAndExpressionAst *__node_31 = 0;
            if (!parseBooleanAndExpression(&__node_31))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BooleanAndExpressionKind, "booleanAndExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_31, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCaseList(CaseListAst **yynode)
{
    *yynode = create<CaseListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DEFAULT
        || yytoken == Token_CASE || yytoken == Token_RBRACE
        || yytoken == Token_EOF
        || yytoken == Token_ENDSWITCH)
    {
        while (yytoken == Token_DEFAULT
               || yytoken == Token_CASE)
        {
            Case_itemAst *__node_32 = 0;
            if (!parseCase_item(&__node_32))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Case_itemKind, "case_item");
                }
                return false;
            }
            (*yynode)->caseItemsSequence = snoc((*yynode)->caseItemsSequence, __node_32, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCase_item(Case_itemAst **yynode)
{
    *yynode = create<Case_itemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->def = -1;

    if (yytoken == Token_DEFAULT
        || yytoken == Token_CASE)
    {
        if (yytoken == Token_CASE)
        {
            if (yytoken != Token_CASE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CASE, "case");
                }
                return false;
            }
            yylex();

            ExprAst *__node_33 = 0;
            if (!parseExpr(&__node_33))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_33;

            if (yytoken == Token_COLON)
            {
                if (yytoken != Token_COLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COLON, ":");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_SEMICOLON)
            {
                if (yytoken != Token_SEMICOLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SEMICOLON, ";");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            InnerStatementListAst *__node_34 = 0;
            if (!parseInnerStatementList(&__node_34))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_34;

        }
        else if (yytoken == Token_DEFAULT)
        {
            if (yytoken != Token_DEFAULT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEFAULT, "default");
                }
                return false;
            }
            (*yynode)->def = tokenStream->index() - 1;
            yylex();

            if (yytoken == Token_COLON)
            {
                if (yytoken != Token_COLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COLON, ":");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_SEMICOLON)
            {
                if (yytoken != Token_SEMICOLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SEMICOLON, ";");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            InnerStatementListAst *__node_35 = 0;
            if (!parseInnerStatementList(&__node_35))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_35;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCatch_item(Catch_itemAst **yynode)
{
    *yynode = create<Catch_itemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->catchClass = -1;

    if (yytoken == Token_CATCH)
    {
        if (yytoken != Token_CATCH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CATCH, "catch");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_STRING)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STRING, "string");
            }
            return false;
        }
        (*yynode)->catchClass = tokenStream->index() - 1;
        yylex();

        VariableIdentifierAst *__node_36 = 0;
        if (!parseVariableIdentifier(&__node_36))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
            }
            return false;
        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        InnerStatementListAst *__node_37 = 0;
        if (!parseInnerStatementList(&__node_37))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
            }
            return false;
        }
        (*yynode)->statements = __node_37;

        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassBody(ClassBodyAst **yynode)
{
    *yynode = create<ClassBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_PRIVATE
        || yytoken == Token_FINAL
        || yytoken == Token_FUNCTION
        || yytoken == Token_ABSTRACT
        || yytoken == Token_VAR
        || yytoken == Token_PUBLIC
        || yytoken == Token_PROTECTED
        || yytoken == Token_CONST
        || yytoken == Token_STATIC || yytoken == Token_RBRACE
        || yytoken == Token_EOF)
    {
        while (yytoken == Token_VARIABLE
               || yytoken == Token_PRIVATE
               || yytoken == Token_FINAL
               || yytoken == Token_FUNCTION
               || yytoken == Token_ABSTRACT
               || yytoken == Token_VAR
               || yytoken == Token_PUBLIC
               || yytoken == Token_PROTECTED
               || yytoken == Token_CONST
               || yytoken == Token_STATIC)
        {
            ClassStatementAst *__node_38 = 0;
            if (!parseClassStatement(&__node_38))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassStatementKind, "classStatement");
                }
                return false;
            }
            (*yynode)->classStatementsSequence = snoc((*yynode)->classStatementsSequence, __node_38, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassConstantDeclaration(ClassConstantDeclarationAst **yynode)
{
    *yynode = create<ClassConstantDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING)
    {
        IdentifierAst *__node_39 = 0;
        if (!parseIdentifier(&__node_39))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->identifier = __node_39;

        if (yytoken != Token_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ASSIGN, "=");
            }
            return false;
        }
        yylex();

        StaticScalarAst *__node_40 = 0;
        if (!parseStaticScalar(&__node_40))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
            }
            return false;
        }
        (*yynode)->scalar = __node_40;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassDeclarationStatement(ClassDeclarationStatementAst **yynode)
{
    *yynode = create<ClassDeclarationStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FINAL
        || yytoken == Token_CLASS
        || yytoken == Token_ABSTRACT)
    {
        if (yytoken == Token_ABSTRACT)
        {
            if (yytoken != Token_ABSTRACT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ABSTRACT, "abstract");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FINAL)
        {
            if (yytoken != Token_FINAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FINAL, "final");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_CLASS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CLASS, "class");
            }
            return false;
        }
        yylex();

        IdentifierAst *__node_41 = 0;
        if (!parseIdentifier(&__node_41))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->className = __node_41;

        if (yytoken == Token_EXTENDS)
        {
            if (yytoken != Token_EXTENDS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXTENDS, "extends");
                }
                return false;
            }
            yylex();

            ClassExtendsAst *__node_42 = 0;
            if (!parseClassExtends(&__node_42))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassExtendsKind, "classExtends");
                }
                return false;
            }
            (*yynode)->extends = __node_42;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_IMPLEMENTS)
        {
            if (yytoken != Token_IMPLEMENTS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IMPLEMENTS, "implements");
                }
                return false;
            }
            yylex();

            ClassImplementsAst *__node_43 = 0;
            if (!parseClassImplements(&__node_43))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassImplementsKind, "classImplements");
                }
                return false;
            }
            (*yynode)->implements = __node_43;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        ClassBodyAst *__node_44 = 0;
        if (!parseClassBody(&__node_44))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassBodyKind, "classBody");
            }
            return false;
        }
        (*yynode)->body = __node_44;

        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassExtends(ClassExtendsAst **yynode)
{
    *yynode = create<ClassExtendsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING)
    {
        IdentifierAst *__node_45 = 0;
        if (!parseIdentifier(&__node_45))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->identifier = __node_45;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassImplements(ClassImplementsAst **yynode)
{
    *yynode = create<ClassImplementsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING)
    {
        IdentifierAst *__node_46 = 0;
        if (!parseIdentifier(&__node_46))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->implementsSequence = snoc((*yynode)->implementsSequence, __node_46, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            IdentifierAst *__node_47 = 0;
            if (!parseIdentifier(&__node_47))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->implementsSequence = snoc((*yynode)->implementsSequence, __node_47, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassNameReference(ClassNameReferenceAst **yynode)
{
    *yynode = create<ClassNameReferenceAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING)
    {
        if ((yytoken == Token_STRING) && ( LA(2).kind != Token_PAAMAYIM_NEKUDOTAYIM ))
        {
            IdentifierAst *__node_48 = 0;
            if (!parseIdentifier(&__node_48))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->identifier = __node_48;

        }
        else if (yytoken == Token_VARIABLE
                 || yytoken == Token_DOLLAR
                 || yytoken == Token_STRING)
        {
            DynamicClassNameReferenceAst *__node_49 = 0;
            if (!parseDynamicClassNameReference(&__node_49))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DynamicClassNameReferenceKind, "dynamicClassNameReference");
                }
                return false;
            }
            (*yynode)->dynamicClassNameReference = __node_49;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassStatement(ClassStatementAst **yynode)
{
    *yynode = create<ClassStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_PRIVATE
        || yytoken == Token_FINAL
        || yytoken == Token_FUNCTION
        || yytoken == Token_ABSTRACT
        || yytoken == Token_VAR
        || yytoken == Token_PUBLIC
        || yytoken == Token_PROTECTED
        || yytoken == Token_CONST
        || yytoken == Token_STATIC)
    {
        if (yytoken == Token_CONST)
        {
            if (yytoken != Token_CONST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONST, "const");
                }
                return false;
            }
            yylex();

            ClassConstantDeclarationAst *__node_50 = 0;
            if (!parseClassConstantDeclaration(&__node_50))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassConstantDeclarationKind, "classConstantDeclaration");
                }
                return false;
            }
            (*yynode)->consts = __node_50;

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                ClassConstantDeclarationAst *__node_51 = 0;
                if (!parseClassConstantDeclaration(&__node_51))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassConstantDeclarationKind, "classConstantDeclaration");
                    }
                    return false;
                }
                (*yynode)->consts = __node_51;

            }
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VAR)
        {
            if (yytoken != Token_VAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VAR, "var ");
                }
                return false;
            }
            yylex();

            ClassVariableDeclarationAst *__node_52 = 0;
            if (!parseClassVariableDeclaration(&__node_52))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassVariableDeclarationKind, "classVariableDeclaration");
                }
                return false;
            }
            (*yynode)->variable = __node_52;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VARIABLE
                 || yytoken == Token_PRIVATE
                 || yytoken == Token_FINAL
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_ABSTRACT
                 || yytoken == Token_PUBLIC
                 || yytoken == Token_PROTECTED
                 || yytoken == Token_STATIC)
        {
            OptionalModifiersAst *__node_53 = 0;
            if (!parseOptionalModifiers(&__node_53))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                }
                return false;
            }
            (*yynode)->modifiers = __node_53;

            if (yytoken == Token_VARIABLE)
            {
                ClassVariableDeclarationAst *__node_54 = 0;
                if (!parseClassVariableDeclaration(&__node_54))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassVariableDeclarationKind, "classVariableDeclaration");
                    }
                    return false;
                }
                (*yynode)->variable = __node_54;

                if (yytoken != Token_SEMICOLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SEMICOLON, ";");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_FUNCTION)
            {
                if (yytoken != Token_FUNCTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FUNCTION, "function");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_BIT_AND)
                {
                    if (yytoken != Token_BIT_AND)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_BIT_AND, "&");
                        }
                        return false;
                    }
                    yylex();

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                IdentifierAst *__node_55 = 0;
                if (!parseIdentifier(&__node_55))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                (*yynode)->methodName = __node_55;

                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_VARIABLE
                    || yytoken == Token_ARRAY
                    || yytoken == Token_STRING
                    || yytoken == Token_BIT_AND)
                {
                    ParameterListAst *__node_56 = 0;
                    if (!parseParameterList(&__node_56))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ParameterListKind, "parameterList");
                        }
                        return false;
                    }
                    (*yynode)->parameters = __node_56;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

                MethodBodyAst *__node_57 = 0;
                if (!parseMethodBody(&__node_57))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodBodyKind, "methodBody");
                    }
                    return false;
                }
                (*yynode)->methodBody = __node_57;

            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassVariable(ClassVariableAst **yynode)
{
    *yynode = create<ClassVariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE)
    {
        VariableIdentifierAst *__node_58 = 0;
        if (!parseVariableIdentifier(&__node_58))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
            }
            return false;
        }
        (*yynode)->variable = __node_58;

        if (yytoken == Token_ASSIGN)
        {
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            StaticScalarAst *__node_59 = 0;
            if (!parseStaticScalar(&__node_59))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
                }
                return false;
            }
            (*yynode)->value = __node_59;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassVariableDeclaration(ClassVariableDeclarationAst **yynode)
{
    *yynode = create<ClassVariableDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE)
    {
        ClassVariableAst *__node_60 = 0;
        if (!parseClassVariable(&__node_60))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassVariableKind, "classVariable");
            }
            return false;
        }
        (*yynode)->varsSequence = snoc((*yynode)->varsSequence, __node_60, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ClassVariableAst *__node_61 = 0;
            if (!parseClassVariable(&__node_61))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassVariableKind, "classVariable");
                }
                return false;
            }
            (*yynode)->varsSequence = snoc((*yynode)->varsSequence, __node_61, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCommonScalar(CommonScalarAst **yynode)
{
    *yynode = create<CommonScalarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->string = -1;

    if (yytoken == Token_LNUMBER
        || yytoken == Token_CLASS_C
        || yytoken == Token_LINE
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_FUNC_C
        || yytoken == Token_METHOD_C
        || yytoken == Token_FILE)
    {
        if (yytoken == Token_LNUMBER)
        {
            if (yytoken != Token_LNUMBER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LNUMBER, "long number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DNUMBER)
        {
            if (yytoken != Token_DNUMBER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DNUMBER, "double number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CONSTANT_ENCAPSED_STRING)
        {
            if (yytoken != Token_CONSTANT_ENCAPSED_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT_ENCAPSED_STRING, "constant encapsed string");
                }
                return false;
            }
            (*yynode)->string = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_LINE)
        {
            if (yytoken != Token_LINE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE, "__LINE__");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FILE)
        {
            if (yytoken != Token_FILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FILE, "__FILE__");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLASS_C)
        {
            if (yytoken != Token_CLASS_C)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLASS_C, "__CLASS__");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_METHOD_C)
        {
            if (yytoken != Token_METHOD_C)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_METHOD_C, "__METHOD__");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FUNC_C)
        {
            if (yytoken != Token_FUNC_C)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNC_C, "__FUNCTION__");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompoundVariable(CompoundVariableAst **yynode)
{
    *yynode = create<CompoundVariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR)
    {
        if (yytoken == Token_VARIABLE)
        {
            VariableIdentifierAst *__node_62 = 0;
            if (!parseVariableIdentifier(&__node_62))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
                }
                return false;
            }
            (*yynode)->variable = __node_62;

        }
        else if (yytoken == Token_DOLLAR)
        {
            if (yytoken != Token_DOLLAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOLLAR, "$");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            ExprAst *__node_63 = 0;
            if (!parseExpr(&__node_63))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_63;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst **yynode)
{
    *yynode = create<CompoundVariableWithSimpleIndirectReferenceAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR)
    {
        if (yytoken == Token_DOLLAR)
        {
            if (yytoken != Token_DOLLAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOLLAR, "$");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_DOLLAR)
            {
                do
                {
                    if (yytoken != Token_DOLLAR)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_DOLLAR, "$");
                        }
                        return false;
                    }
                    yylex();

                }
                while (yytoken == Token_DOLLAR);
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken == Token_VARIABLE)
            {
                VariableIdentifierAst *__node_64 = 0;
                if (!parseVariableIdentifier(&__node_64))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
                    }
                    return false;
                }
                (*yynode)->indirectVariable = __node_64;

            }
            else if (yytoken == Token_LBRACE)
            {
                if (yytoken != Token_LBRACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACE, "{");
                    }
                    return false;
                }
                yylex();

                ExprAst *__node_65 = 0;
                if (!parseExpr(&__node_65))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->expr = __node_65;

                if (yytoken != Token_RBRACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACE, "}");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_VARIABLE)
        {
            VariableIdentifierAst *__node_66 = 0;
            if (!parseVariableIdentifier(&__node_66))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
                }
                return false;
            }
            (*yynode)->variable = __node_66;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseConditionalExpression(ConditionalExpressionAst **yynode)
{
    *yynode = create<ConditionalExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        BooleanOrExpressionAst *__node_67 = 0;
        if (!parseBooleanOrExpression(&__node_67))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BooleanOrExpressionKind, "booleanOrExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_67;

        if (yytoken == Token_QUESTION)
        {
            if (yytoken != Token_QUESTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_QUESTION, "?");
                }
                return false;
            }
            yylex();

            ExprAst *__node_68 = 0;
            if (!parseExpr(&__node_68))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->ifExpression = __node_68;

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            ConditionalExpressionAst *__node_69 = 0;
            if (!parseConditionalExpression(&__node_69))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ConditionalExpressionKind, "conditionalExpression");
                }
                return false;
            }
            (*yynode)->elseExpression = __node_69;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCtorArguments(CtorArgumentsAst **yynode)
{
    *yynode = create<CtorArgumentsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN || yytoken == Token_CONCAT
        || yytoken == Token_DIV_ASSIGN
        || yytoken == Token_LOGICAL_AND
        || yytoken == Token_IS_NOT_IDENTICAL
        || yytoken == Token_EOF
        || yytoken == Token_BIT_AND
        || yytoken == Token_RBRACE
        || yytoken == Token_SL_ASSIGN
        || yytoken == Token_BOOLEAN_AND
        || yytoken == Token_DIV
        || yytoken == Token_INC
        || yytoken == Token_CONCAT_ASSIGN
        || yytoken == Token_LOGICAL_XOR
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_BIT_OR
        || yytoken == Token_COMMA
        || yytoken == Token_SR_ASSIGN
        || yytoken == Token_ASSIGN
        || yytoken == Token_MOD
        || yytoken == Token_DEC
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_RBRACKET
        || yytoken == Token_MOD_ASSIGN
        || yytoken == Token_IS_GREATER
        || yytoken == Token_BIT_XOR
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_AND_ASSIGN
        || yytoken == Token_IS_SMALLER_OR_EQUAL
        || yytoken == Token_SL
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_QUESTION
        || yytoken == Token_DOUBLE_ARROW
        || yytoken == Token_RPAREN
        || yytoken == Token_OR_ASSIGN
        || yytoken == Token_IS_GREATER_OR_EQUAL
        || yytoken == Token_SR
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_MUL_ASSIGN
        || yytoken == Token_LOGICAL_OR
        || yytoken == Token_IS_IDENTICAL
        || yytoken == Token_COLON
        || yytoken == Token_XOR_ASSIGN
        || yytoken == Token_AS
        || yytoken == Token_BOOLEAN_OR
        || yytoken == Token_MUL)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_STRING_VARNAME
                || yytoken == Token_DOUBLE_QUOTE
                || yytoken == Token_EVAL
                || yytoken == Token_BIT_AND
                || yytoken == Token_ARRAY
                || yytoken == Token_ARRAY_CAST
                || yytoken == Token_CLONE
                || yytoken == Token_INC
                || yytoken == Token_ISSET
                || yytoken == Token_REQUIRE
                || yytoken == Token_CLASS_C
                || yytoken == Token_DNUMBER
                || yytoken == Token_OBJECT_CAST
                || yytoken == Token_EXIT
                || yytoken == Token_BACKTICK
                || yytoken == Token_DEC
                || yytoken == Token_EMPTY
                || yytoken == Token_REQUIRE_ONCE
                || yytoken == Token_METHOD_C
                || yytoken == Token_AT
                || yytoken == Token_BOOL_CAST
                || yytoken == Token_LNUMBER
                || yytoken == Token_TILDE
                || yytoken == Token_BANG
                || yytoken == Token_LPAREN
                || yytoken == Token_INT_CAST
                || yytoken == Token_FUNC_C
                || yytoken == Token_PLUS
                || yytoken == Token_UNSET_CAST
                || yytoken == Token_INCLUDE
                || yytoken == Token_DOLLAR
                || yytoken == Token_DOUBLE_CAST
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_LINE
                || yytoken == Token_MINUS
                || yytoken == Token_STRING
                || yytoken == Token_INCLUDE_ONCE
                || yytoken == Token_LIST
                || yytoken == Token_STRING_CAST
                || yytoken == Token_VARIABLE
                || yytoken == Token_PRINT
                || yytoken == Token_FILE
                || yytoken == Token_START_HEREDOC
                || yytoken == Token_NEW)
            {
                FunctionCallParameterListAst *__node_70 = 0;
                if (!parseFunctionCallParameterList(&__node_70))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FunctionCallParameterListKind, "functionCallParameterList");
                    }
                    return false;
                }
                (*yynode)->parameterList = __node_70;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclareItem(DeclareItemAst **yynode)
{
    *yynode = create<DeclareItemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING)
    {
        if (yytoken != Token_STRING)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STRING, "string");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ASSIGN, "=");
            }
            return false;
        }
        yylex();

        StaticScalarAst *__node_71 = 0;
        if (!parseStaticScalar(&__node_71))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
            }
            return false;
        }
        (*yynode)->scalar = __node_71;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclareStatement(DeclareStatementAst **yynode)
{
    *yynode = create<DeclareStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNSET
        || yytoken == Token_CONTINUE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_SWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_FOR
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_BREAK
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_FOREACH
        || yytoken == Token_REQUIRE
        || yytoken == Token_THROW
        || yytoken == Token_CLASS_C
        || yytoken == Token_IF
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_DNUMBER
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_DO
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_TRY
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_LPAREN
        || yytoken == Token_DECLARE
        || yytoken == Token_INT_CAST
        || yytoken == Token_WHILE
        || yytoken == Token_FUNC_C
        || yytoken == Token_GLOBAL
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_RETURN
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_ECHO
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_STATIC
        || yytoken == Token_COLON
        || yytoken == Token_LIST
        || yytoken == Token_LBRACE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_NEW
        || yytoken == Token_START_HEREDOC)
    {
        if (yytoken == Token_UNSET
            || yytoken == Token_CONTINUE
            || yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_SWITCH
            || yytoken == Token_ARRAY
            || yytoken == Token_FOR
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_BREAK
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_OPEN_TAG
            || yytoken == Token_FOREACH
            || yytoken == Token_REQUIRE
            || yytoken == Token_THROW
            || yytoken == Token_CLASS_C
            || yytoken == Token_IF
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_DNUMBER
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_CLOSE_TAG
            || yytoken == Token_DO
            || yytoken == Token_INLINE_HTML
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_TRY
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_LNUMBER
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_OPEN_TAG_WITH_ECHO
            || yytoken == Token_LPAREN
            || yytoken == Token_DECLARE
            || yytoken == Token_INT_CAST
            || yytoken == Token_WHILE
            || yytoken == Token_FUNC_C
            || yytoken == Token_GLOBAL
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_RETURN
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_ECHO
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_SEMICOLON
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_STATIC
            || yytoken == Token_LIST
            || yytoken == Token_LBRACE
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_NEW
            || yytoken == Token_START_HEREDOC)
        {
            StatementAst *__node_72 = 0;
            if (!parseStatement(&__node_72))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_72;

        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_73 = 0;
            if (!parseInnerStatementList(&__node_73))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_73;

            if (yytoken != Token_ENDDECLARE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENDDECLARE, "enddeclare");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_74 = 0;
            if (!parseSemicolonOrCloseTag(&__node_74))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDimListItem(DimListItemAst **yynode)
{
    *yynode = create<DimListItemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET)
    {
        if (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            DimOffsetAst *__node_75 = 0;
            if (!parseDimOffset(&__node_75))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DimOffsetKind, "dimOffset");
                }
                return false;
            }
            (*yynode)->dimOffset = __node_75;

            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            ExprAst *__node_76 = 0;
            if (!parseExpr(&__node_76))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_76;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDimOffset(DimOffsetAst **yynode)
{
    *yynode = create<DimOffsetAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW || yytoken == Token_EOF
        || yytoken == Token_RBRACKET)
    {
        if (yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_ARRAY
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_REQUIRE
            || yytoken == Token_CLASS_C
            || yytoken == Token_DNUMBER
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_LNUMBER
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_LPAREN
            || yytoken == Token_INT_CAST
            || yytoken == Token_FUNC_C
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_LIST
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_START_HEREDOC
            || yytoken == Token_NEW)
        {
            ExprAst *__node_77 = 0;
            if (!parseExpr(&__node_77))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_77;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDynamicClassNameReference(DynamicClassNameReferenceAst **yynode)
{
    *yynode = create<DynamicClassNameReferenceAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING)
    {
        BaseVariableAst *__node_78 = 0;
        if (!parseBaseVariable(&__node_78))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BaseVariableKind, "baseVariable");
            }
            return false;
        }
        (*yynode)->baseVariable = __node_78;

        if (yytoken == Token_OBJECT_OPERATOR)
        {
            if (yytoken != Token_OBJECT_OPERATOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OBJECT_OPERATOR, "->");
                }
                return false;
            }
            yylex();

            ObjectPropertyAst *__node_79 = 0;
            if (!parseObjectProperty(&__node_79))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ObjectPropertyKind, "objectProperty");
                }
                return false;
            }
            (*yynode)->objectProperty = __node_79;

            DynamicClassNameVariablePropertiesAst *__node_80 = 0;
            if (!parseDynamicClassNameVariableProperties(&__node_80))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DynamicClassNameVariablePropertiesKind, "dynamicClassNameVariableProperties");
                }
                return false;
            }
            (*yynode)->properties = __node_80;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst **yynode)
{
    *yynode = create<DynamicClassNameVariablePropertiesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_OBJECT_OPERATOR || yytoken == Token_CONCAT
        || yytoken == Token_DIV_ASSIGN
        || yytoken == Token_LOGICAL_AND
        || yytoken == Token_IS_NOT_IDENTICAL
        || yytoken == Token_EOF
        || yytoken == Token_BIT_AND
        || yytoken == Token_RBRACE
        || yytoken == Token_SL_ASSIGN
        || yytoken == Token_BOOLEAN_AND
        || yytoken == Token_DIV
        || yytoken == Token_INC
        || yytoken == Token_CONCAT_ASSIGN
        || yytoken == Token_LOGICAL_XOR
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_BIT_OR
        || yytoken == Token_COMMA
        || yytoken == Token_SR_ASSIGN
        || yytoken == Token_ASSIGN
        || yytoken == Token_MOD
        || yytoken == Token_DEC
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_RBRACKET
        || yytoken == Token_MOD_ASSIGN
        || yytoken == Token_IS_GREATER
        || yytoken == Token_BIT_XOR
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_LPAREN
        || yytoken == Token_AND_ASSIGN
        || yytoken == Token_IS_SMALLER_OR_EQUAL
        || yytoken == Token_SL
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_QUESTION
        || yytoken == Token_DOUBLE_ARROW
        || yytoken == Token_RPAREN
        || yytoken == Token_OR_ASSIGN
        || yytoken == Token_IS_GREATER_OR_EQUAL
        || yytoken == Token_SR
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_MUL_ASSIGN
        || yytoken == Token_LOGICAL_OR
        || yytoken == Token_IS_IDENTICAL
        || yytoken == Token_COLON
        || yytoken == Token_XOR_ASSIGN
        || yytoken == Token_AS
        || yytoken == Token_BOOLEAN_OR
        || yytoken == Token_MUL)
    {
        while (yytoken == Token_OBJECT_OPERATOR)
        {
            DynamicClassNameVariablePropertyAst *__node_81 = 0;
            if (!parseDynamicClassNameVariableProperty(&__node_81))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DynamicClassNameVariablePropertyKind, "dynamicClassNameVariableProperty");
                }
                return false;
            }
            (*yynode)->propertiesSequence = snoc((*yynode)->propertiesSequence, __node_81, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst **yynode)
{
    *yynode = create<DynamicClassNameVariablePropertyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_OBJECT_OPERATOR)
    {
        if (yytoken != Token_OBJECT_OPERATOR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_OBJECT_OPERATOR, "->");
            }
            return false;
        }
        yylex();

        ObjectPropertyAst *__node_82 = 0;
        if (!parseObjectProperty(&__node_82))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ObjectPropertyKind, "objectProperty");
            }
            return false;
        }
        (*yynode)->property = __node_82;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseElseSingle(ElseSingleAst **yynode)
{
    *yynode = create<ElseSingleAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ELSE || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_CASE
        || yytoken == Token_IF
        || yytoken == Token_THROW
        || yytoken == Token_FOREACH
        || yytoken == Token_ISSET
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_RBRACE
        || yytoken == Token_VARIABLE
        || yytoken == Token_TRY
        || yytoken == Token_ENDFOREACH
        || yytoken == Token_EMPTY
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_INC
        || yytoken == Token_CLASS
        || yytoken == Token_WHILE
        || yytoken == Token_DECLARE
        || yytoken == Token_HALT_COMPILER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_AT
        || yytoken == Token_DEC
        || yytoken == Token_DNUMBER
        || yytoken == Token_INTERFACE
        || yytoken == Token_ECHO
        || yytoken == Token_ENDDECLARE
        || yytoken == Token_INCLUDE
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_CONTINUE
        || yytoken == Token_LNUMBER
        || yytoken == Token_NEW
        || yytoken == Token_PRINT
        || yytoken == Token_LIST
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_DOLLAR
        || yytoken == Token_DEFAULT
        || yytoken == Token_CLONE
        || yytoken == Token_ENDSWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_EVAL
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_DO
        || yytoken == Token_STRING
        || yytoken == Token_EXIT
        || yytoken == Token_FUNCTION
        || yytoken == Token_CLASS_C
        || yytoken == Token_REQUIRE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_ELSE
        || yytoken == Token_ELSEIF
        || yytoken == Token_METHOD_C
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_BACKTICK
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_RETURN
        || yytoken == Token_ENDIF
        || yytoken == Token_GLOBAL
        || yytoken == Token_FUNC_C
        || yytoken == Token_INT_CAST
        || yytoken == Token_LPAREN
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_ABSTRACT
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_FINAL
        || yytoken == Token_STATIC
        || yytoken == Token_ENDWHILE
        || yytoken == Token_LINE
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BREAK
        || yytoken == Token_FOR
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_SWITCH
        || yytoken == Token_ENDFOR
        || yytoken == Token_UNSET
        || yytoken == Token_FILE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_LBRACE
        || yytoken == Token_MINUS)
    {
        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            StatementAst *__node_83 = 0;
            if (!parseStatement(&__node_83))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_83;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseElseifList(ElseifListAst **yynode)
{
    *yynode = create<ElseifListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ELSEIF || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_CASE
        || yytoken == Token_IF
        || yytoken == Token_THROW
        || yytoken == Token_FOREACH
        || yytoken == Token_ISSET
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_RBRACE
        || yytoken == Token_VARIABLE
        || yytoken == Token_TRY
        || yytoken == Token_ENDFOREACH
        || yytoken == Token_EMPTY
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_INC
        || yytoken == Token_CLASS
        || yytoken == Token_WHILE
        || yytoken == Token_DECLARE
        || yytoken == Token_HALT_COMPILER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_AT
        || yytoken == Token_DEC
        || yytoken == Token_DNUMBER
        || yytoken == Token_INTERFACE
        || yytoken == Token_ECHO
        || yytoken == Token_ENDDECLARE
        || yytoken == Token_INCLUDE
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_CONTINUE
        || yytoken == Token_LNUMBER
        || yytoken == Token_NEW
        || yytoken == Token_PRINT
        || yytoken == Token_LIST
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_DOLLAR
        || yytoken == Token_DEFAULT
        || yytoken == Token_CLONE
        || yytoken == Token_ENDSWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_EVAL
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_DO
        || yytoken == Token_STRING
        || yytoken == Token_EXIT
        || yytoken == Token_FUNCTION
        || yytoken == Token_CLASS_C
        || yytoken == Token_REQUIRE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_ELSE
        || yytoken == Token_ELSEIF
        || yytoken == Token_METHOD_C
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_BACKTICK
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_RETURN
        || yytoken == Token_ENDIF
        || yytoken == Token_GLOBAL
        || yytoken == Token_FUNC_C
        || yytoken == Token_INT_CAST
        || yytoken == Token_LPAREN
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_ABSTRACT
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_FINAL
        || yytoken == Token_STATIC
        || yytoken == Token_ENDWHILE
        || yytoken == Token_LINE
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BREAK
        || yytoken == Token_FOR
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_SWITCH
        || yytoken == Token_ENDFOR
        || yytoken == Token_UNSET
        || yytoken == Token_FILE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_LBRACE
        || yytoken == Token_MINUS)
    {
        while (yytoken == Token_ELSEIF)
        {
            ElseifListItemAst *__node_84 = 0;
            if (!parseElseifListItem(&__node_84))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ElseifListItemKind, "elseifListItem");
                }
                return false;
            }
            (*yynode)->elseifListItemSequence = snoc((*yynode)->elseifListItemSequence, __node_84, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseElseifListItem(ElseifListItemAst **yynode)
{
    *yynode = create<ElseifListItemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ELSEIF)
    {
        if (yytoken != Token_ELSEIF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ELSEIF, "elseif");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExprAst *__node_85 = 0;
        if (!parseExpr(&__node_85))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        (*yynode)->expr = __node_85;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        StatementAst *__node_86 = 0;
        if (!parseStatement(&__node_86))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::StatementKind, "statement");
            }
            return false;
        }
        (*yynode)->statement = __node_86;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEncaps(EncapsAst **yynode)
{
    *yynode = create<EncapsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;

    if (yytoken == Token_DOLLAR_OPEN_CURLY_BRACES
        || yytoken == Token_VARIABLE
        || yytoken == Token_CURLY_OPEN
        || yytoken == Token_ENCAPSED_AND_WHITESPACE)
    {
        if (yytoken == Token_DOLLAR_OPEN_CURLY_BRACES
            || yytoken == Token_VARIABLE
            || yytoken == Token_CURLY_OPEN)
        {
            EncapsVarAst *__node_87 = 0;
            if (!parseEncapsVar(&__node_87))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EncapsVarKind, "encapsVar");
                }
                return false;
            }
            (*yynode)->var = __node_87;

        }
        else if (yytoken == Token_ENCAPSED_AND_WHITESPACE)
        {
            if (yytoken != Token_ENCAPSED_AND_WHITESPACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENCAPSED_AND_WHITESPACE, "encapsed and whitespace");
                }
                return false;
            }
            (*yynode)->value = tokenStream->index() - 1;
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEncapsList(EncapsListAst **yynode)
{
    *yynode = create<EncapsListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DOLLAR_OPEN_CURLY_BRACES
        || yytoken == Token_VARIABLE
        || yytoken == Token_CURLY_OPEN
        || yytoken == Token_ENCAPSED_AND_WHITESPACE || yytoken == Token_BACKTICK
        || yytoken == Token_EOF
        || yytoken == Token_END_HEREDOC
        || yytoken == Token_DOUBLE_QUOTE)
    {
        while (yytoken == Token_DOLLAR_OPEN_CURLY_BRACES
               || yytoken == Token_VARIABLE
               || yytoken == Token_CURLY_OPEN
               || yytoken == Token_ENCAPSED_AND_WHITESPACE)
        {
            EncapsAst *__node_88 = 0;
            if (!parseEncaps(&__node_88))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EncapsKind, "encaps");
                }
                return false;
            }
            (*yynode)->encapsSequence = snoc((*yynode)->encapsSequence, __node_88, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEncapsVar(EncapsVarAst **yynode)
{
    *yynode = create<EncapsVarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DOLLAR_OPEN_CURLY_BRACES
        || yytoken == Token_VARIABLE
        || yytoken == Token_CURLY_OPEN)
    {
        if (yytoken == Token_DOLLAR_OPEN_CURLY_BRACES)
        {
            if (yytoken != Token_DOLLAR_OPEN_CURLY_BRACES)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOLLAR_OPEN_CURLY_BRACES, "${");
                }
                return false;
            }
            yylex();

            if ((yytoken == Token_STRING_VARNAME) && ( LA(2).kind == Token_LBRACKET))
            {
                if (yytoken != Token_STRING_VARNAME)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING_VARNAME, "string varname");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_LBRACKET)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACKET, "[");
                    }
                    return false;
                }
                yylex();

                ExprAst *__node_89 = 0;
                if (!parseExpr(&__node_89))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->expr = __node_89;

                if (yytoken != Token_RBRACKET)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACKET, "]");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_RBRACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACE, "}");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_STRING_VARNAME
                     || yytoken == Token_DOUBLE_QUOTE
                     || yytoken == Token_EVAL
                     || yytoken == Token_ARRAY
                     || yytoken == Token_ARRAY_CAST
                     || yytoken == Token_CLONE
                     || yytoken == Token_INC
                     || yytoken == Token_ISSET
                     || yytoken == Token_REQUIRE
                     || yytoken == Token_CLASS_C
                     || yytoken == Token_DNUMBER
                     || yytoken == Token_OBJECT_CAST
                     || yytoken == Token_EXIT
                     || yytoken == Token_BACKTICK
                     || yytoken == Token_DEC
                     || yytoken == Token_EMPTY
                     || yytoken == Token_REQUIRE_ONCE
                     || yytoken == Token_METHOD_C
                     || yytoken == Token_AT
                     || yytoken == Token_LNUMBER
                     || yytoken == Token_BOOL_CAST
                     || yytoken == Token_TILDE
                     || yytoken == Token_BANG
                     || yytoken == Token_LPAREN
                     || yytoken == Token_INT_CAST
                     || yytoken == Token_FUNC_C
                     || yytoken == Token_PLUS
                     || yytoken == Token_UNSET_CAST
                     || yytoken == Token_INCLUDE
                     || yytoken == Token_DOLLAR
                     || yytoken == Token_DOUBLE_CAST
                     || yytoken == Token_CONSTANT_ENCAPSED_STRING
                     || yytoken == Token_LINE
                     || yytoken == Token_MINUS
                     || yytoken == Token_STRING
                     || yytoken == Token_INCLUDE_ONCE
                     || yytoken == Token_LIST
                     || yytoken == Token_STRING_CAST
                     || yytoken == Token_VARIABLE
                     || yytoken == Token_PRINT
                     || yytoken == Token_FILE
                     || yytoken == Token_START_HEREDOC
                     || yytoken == Token_NEW)
            {
                ExprAst *__node_90 = 0;
                if (!parseExpr(&__node_90))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->expr = __node_90;

                if (yytoken != Token_RBRACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACE, "}");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_VARIABLE)
        {
            VariableIdentifierAst *__node_91 = 0;
            if (!parseVariableIdentifier(&__node_91))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
                }
                return false;
            }
            if (yytoken == Token_OBJECT_OPERATOR)
            {
                if (yytoken != Token_OBJECT_OPERATOR)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_OBJECT_OPERATOR, "->");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_STRING)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING, "string");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_LBRACKET)
            {
                if (yytoken != Token_LBRACKET)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACKET, "[");
                    }
                    return false;
                }
                yylex();

                EncapsVarOffsetAst *__node_92 = 0;
                if (!parseEncapsVarOffset(&__node_92))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EncapsVarOffsetKind, "encapsVarOffset");
                    }
                    return false;
                }
                (*yynode)->offset = __node_92;

                if (yytoken != Token_RBRACKET)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACKET, "]");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_CURLY_OPEN)
        {
            if (yytoken != Token_CURLY_OPEN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CURLY_OPEN, "curly open");
                }
                return false;
            }
            yylex();

            ExprAst *__node_93 = 0;
            if (!parseExpr(&__node_93))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_93;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEncapsVarOffset(EncapsVarOffsetAst **yynode)
{
    *yynode = create<EncapsVarOffsetAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_STRING
        || yytoken == Token_NUM_STRING)
    {
        if (yytoken == Token_STRING)
        {
            if (yytoken != Token_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING, "string");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_NUM_STRING)
        {
            if (yytoken != Token_NUM_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NUM_STRING, "num string");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VARIABLE)
        {
            VariableIdentifierAst *__node_94 = 0;
            if (!parseVariableIdentifier(&__node_94))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEqualityExpression(EqualityExpressionAst **yynode)
{
    *yynode = create<EqualityExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        RelationalExpressionAst *__node_95 = 0;
        if (!parseRelationalExpression(&__node_95))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RelationalExpressionKind, "relationalExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_95;

        while (yytoken == Token_IS_IDENTICAL
               || yytoken == Token_IS_NOT_EQUAL
               || yytoken == Token_IS_EQUAL
               || yytoken == Token_IS_NOT_IDENTICAL)
        {
            EqualityExpressionRestAst *__node_96 = 0;
            if (!parseEqualityExpressionRest(&__node_96))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EqualityExpressionRestKind, "equalityExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_96, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEqualityExpressionRest(EqualityExpressionRestAst **yynode)
{
    *yynode = create<EqualityExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IS_IDENTICAL
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_IS_NOT_IDENTICAL)
    {
        if (yytoken == Token_IS_EQUAL)
        {
            if (yytoken != Token_IS_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_EQUAL, "==");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_NOT_EQUAL)
        {
            if (yytoken != Token_IS_NOT_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_NOT_EQUAL, "!=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_IDENTICAL)
        {
            if (yytoken != Token_IS_IDENTICAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_IDENTICAL, "===");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_NOT_IDENTICAL)
        {
            if (yytoken != Token_IS_NOT_IDENTICAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_NOT_IDENTICAL, "!==");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        RelationalExpressionAst *__node_97 = 0;
        if (!parseRelationalExpression(&__node_97))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RelationalExpressionKind, "relationalExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_97;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr(ExprAst **yynode)
{
    *yynode = create<ExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        LogicalOrExpressionAst *__node_98 = 0;
        if (!parseLogicalOrExpression(&__node_98))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalOrExpressionKind, "logicalOrExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_98;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForExpr(ForExprAst **yynode)
{
    *yynode = create<ForExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW || yytoken == Token_SEMICOLON
        || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        if (yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_ARRAY
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_REQUIRE
            || yytoken == Token_CLASS_C
            || yytoken == Token_DNUMBER
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_LNUMBER
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_LPAREN
            || yytoken == Token_INT_CAST
            || yytoken == Token_FUNC_C
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_LIST
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_START_HEREDOC
            || yytoken == Token_NEW)
        {
            ExprAst *__node_99 = 0;
            if (!parseExpr(&__node_99))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->exprsSequence = snoc((*yynode)->exprsSequence, __node_99, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                ExprAst *__node_100 = 0;
                if (!parseExpr(&__node_100))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->exprsSequence = snoc((*yynode)->exprsSequence, __node_100, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForStatement(ForStatementAst **yynode)
{
    *yynode = create<ForStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNSET
        || yytoken == Token_CONTINUE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_SWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_FOR
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_BREAK
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_FOREACH
        || yytoken == Token_REQUIRE
        || yytoken == Token_THROW
        || yytoken == Token_CLASS_C
        || yytoken == Token_IF
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_DNUMBER
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_DO
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_TRY
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_LPAREN
        || yytoken == Token_DECLARE
        || yytoken == Token_INT_CAST
        || yytoken == Token_WHILE
        || yytoken == Token_FUNC_C
        || yytoken == Token_GLOBAL
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_RETURN
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_ECHO
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_STATIC
        || yytoken == Token_COLON
        || yytoken == Token_LIST
        || yytoken == Token_LBRACE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_NEW
        || yytoken == Token_START_HEREDOC)
    {
        if (yytoken == Token_UNSET
            || yytoken == Token_CONTINUE
            || yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_SWITCH
            || yytoken == Token_ARRAY
            || yytoken == Token_FOR
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_BREAK
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_OPEN_TAG
            || yytoken == Token_FOREACH
            || yytoken == Token_REQUIRE
            || yytoken == Token_THROW
            || yytoken == Token_CLASS_C
            || yytoken == Token_IF
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_DNUMBER
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_CLOSE_TAG
            || yytoken == Token_DO
            || yytoken == Token_INLINE_HTML
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_TRY
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_LNUMBER
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_OPEN_TAG_WITH_ECHO
            || yytoken == Token_LPAREN
            || yytoken == Token_DECLARE
            || yytoken == Token_INT_CAST
            || yytoken == Token_WHILE
            || yytoken == Token_FUNC_C
            || yytoken == Token_GLOBAL
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_RETURN
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_ECHO
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_SEMICOLON
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_STATIC
            || yytoken == Token_LIST
            || yytoken == Token_LBRACE
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_NEW
            || yytoken == Token_START_HEREDOC)
        {
            StatementAst *__node_101 = 0;
            if (!parseStatement(&__node_101))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_101;

        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_102 = 0;
            if (!parseInnerStatementList(&__node_102))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_102;

            if (yytoken != Token_ENDFOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENDFOR, "endfor");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_103 = 0;
            if (!parseSemicolonOrCloseTag(&__node_103))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForeachOptionalArg(ForeachOptionalArgAst **yynode)
{
    *yynode = create<ForeachOptionalArgAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DOUBLE_ARROW || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        if (yytoken == Token_DOUBLE_ARROW)
        {
            if (yytoken != Token_DOUBLE_ARROW)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_ARROW, "=>");
                }
                return false;
            }
            yylex();

            ForeachVariableAst *__node_104 = 0;
            if (!parseForeachVariable(&__node_104))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForeachVariableKind, "foreachVariable");
                }
                return false;
            }
            (*yynode)->foreachVariable = __node_104;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForeachStatement(ForeachStatementAst **yynode)
{
    *yynode = create<ForeachStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNSET
        || yytoken == Token_CONTINUE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_SWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_FOR
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_BREAK
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_FOREACH
        || yytoken == Token_REQUIRE
        || yytoken == Token_THROW
        || yytoken == Token_CLASS_C
        || yytoken == Token_IF
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_DNUMBER
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_DO
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_TRY
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_LPAREN
        || yytoken == Token_DECLARE
        || yytoken == Token_INT_CAST
        || yytoken == Token_WHILE
        || yytoken == Token_FUNC_C
        || yytoken == Token_GLOBAL
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_RETURN
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_ECHO
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_STATIC
        || yytoken == Token_COLON
        || yytoken == Token_LIST
        || yytoken == Token_LBRACE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_NEW
        || yytoken == Token_START_HEREDOC)
    {
        if (yytoken == Token_UNSET
            || yytoken == Token_CONTINUE
            || yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_SWITCH
            || yytoken == Token_ARRAY
            || yytoken == Token_FOR
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_BREAK
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_OPEN_TAG
            || yytoken == Token_FOREACH
            || yytoken == Token_REQUIRE
            || yytoken == Token_THROW
            || yytoken == Token_CLASS_C
            || yytoken == Token_IF
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_DNUMBER
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_CLOSE_TAG
            || yytoken == Token_DO
            || yytoken == Token_INLINE_HTML
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_TRY
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_LNUMBER
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_OPEN_TAG_WITH_ECHO
            || yytoken == Token_LPAREN
            || yytoken == Token_DECLARE
            || yytoken == Token_INT_CAST
            || yytoken == Token_WHILE
            || yytoken == Token_FUNC_C
            || yytoken == Token_GLOBAL
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_RETURN
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_ECHO
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_SEMICOLON
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_STATIC
            || yytoken == Token_LIST
            || yytoken == Token_LBRACE
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_NEW
            || yytoken == Token_START_HEREDOC)
        {
            StatementAst *__node_105 = 0;
            if (!parseStatement(&__node_105))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_105;

        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_106 = 0;
            if (!parseInnerStatementList(&__node_106))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_106;

            if (yytoken != Token_ENDFOREACH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENDFOREACH, "endforeach");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_107 = 0;
            if (!parseSemicolonOrCloseTag(&__node_107))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForeachVariable(ForeachVariableAst **yynode)
{
    *yynode = create<ForeachVariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING
        || yytoken == Token_BIT_AND)
    {
        if (yytoken == Token_VARIABLE
            || yytoken == Token_DOLLAR
            || yytoken == Token_STRING)
        {
            VariableAst *__node_108 = 0;
            if (!parseVariable(&__node_108))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->variable = __node_108;

        }
        else if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

            VariableAst *__node_109 = 0;
            if (!parseVariable(&__node_109))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->variable = __node_109;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionCall(FunctionCallAst **yynode)
{
    *yynode = create<FunctionCallAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING)
    {
        if (yytoken == Token_STRING)
        {
            IdentifierAst *__node_110 = 0;
            if (!parseIdentifier(&__node_110))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->stringFunctionNameOrClass = __node_110;

            if (yytoken == Token_LPAREN)
            {
                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                FunctionCallParameterListAst *__node_111 = 0;
                if (!parseFunctionCallParameterList(&__node_111))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FunctionCallParameterListKind, "functionCallParameterList");
                    }
                    return false;
                }
                (*yynode)->stringParameterList = __node_111;

                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_PAAMAYIM_NEKUDOTAYIM)
            {
                if (yytoken != Token_PAAMAYIM_NEKUDOTAYIM)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PAAMAYIM_NEKUDOTAYIM, "::");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_STRING)
                {
                    IdentifierAst *__node_112 = 0;
                    if (!parseIdentifier(&__node_112))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::IdentifierKind, "identifier");
                        }
                        return false;
                    }
                    (*yynode)->stringFunctionName = __node_112;

                    if (yytoken != Token_LPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_LPAREN, "(");
                        }
                        return false;
                    }
                    yylex();

                    FunctionCallParameterListAst *__node_113 = 0;
                    if (!parseFunctionCallParameterList(&__node_113))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::FunctionCallParameterListKind, "functionCallParameterList");
                        }
                        return false;
                    }
                    (*yynode)->stringParameterList = __node_113;

                    if (yytoken != Token_RPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_RPAREN, ")");
                        }
                        return false;
                    }
                    yylex();

                }
                else if (yytoken == Token_VARIABLE
                         || yytoken == Token_DOLLAR)
                {
                    VariableWithoutObjectsAst *__node_114 = 0;
                    if (!parseVariableWithoutObjects(&__node_114))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableWithoutObjectsKind, "variableWithoutObjects");
                        }
                        return false;
                    }
                    (*yynode)->varFunctionName = __node_114;

                    if (yytoken != Token_LPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_LPAREN, "(");
                        }
                        return false;
                    }
                    yylex();

                    FunctionCallParameterListAst *__node_115 = 0;
                    if (!parseFunctionCallParameterList(&__node_115))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::FunctionCallParameterListKind, "functionCallParameterList");
                        }
                        return false;
                    }
                    (*yynode)->stringParameterList = __node_115;

                    if (yytoken != Token_RPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_RPAREN, ")");
                        }
                        return false;
                    }
                    yylex();

                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_VARIABLE
                 || yytoken == Token_DOLLAR)
        {
            VariableWithoutObjectsAst *__node_116 = 0;
            if (!parseVariableWithoutObjects(&__node_116))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableWithoutObjectsKind, "variableWithoutObjects");
                }
                return false;
            }
            (*yynode)->varFunctionName = __node_116;

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            FunctionCallParameterListAst *__node_117 = 0;
            if (!parseFunctionCallParameterList(&__node_117))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionCallParameterListKind, "functionCallParameterList");
                }
                return false;
            }
            (*yynode)->varParameterList = __node_117;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionCallParameterList(FunctionCallParameterListAst **yynode)
{
    *yynode = create<FunctionCallParameterListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_BIT_AND
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        if (yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_BIT_AND
            || yytoken == Token_ARRAY
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_REQUIRE
            || yytoken == Token_CLASS_C
            || yytoken == Token_DNUMBER
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_LNUMBER
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_LPAREN
            || yytoken == Token_INT_CAST
            || yytoken == Token_FUNC_C
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_LIST
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_START_HEREDOC
            || yytoken == Token_NEW)
        {
            FunctionCallParameterListElementAst *__node_118 = 0;
            if (!parseFunctionCallParameterListElement(&__node_118))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionCallParameterListElementKind, "functionCallParameterListElement");
                }
                return false;
            }
            (*yynode)->parametersSequence = snoc((*yynode)->parametersSequence, __node_118, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                FunctionCallParameterListElementAst *__node_119 = 0;
                if (!parseFunctionCallParameterListElement(&__node_119))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FunctionCallParameterListElementKind, "functionCallParameterListElement");
                    }
                    return false;
                }
                (*yynode)->parametersSequence = snoc((*yynode)->parametersSequence, __node_119, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionCallParameterListElement(FunctionCallParameterListElementAst **yynode)
{
    *yynode = create<FunctionCallParameterListElementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_BIT_AND
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

            VariableAst *__node_120 = 0;
            if (!parseVariable(&__node_120))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->variable = __node_120;

        }
        else if (yytoken == Token_STRING_VARNAME
                 || yytoken == Token_DOUBLE_QUOTE
                 || yytoken == Token_EVAL
                 || yytoken == Token_ARRAY
                 || yytoken == Token_ARRAY_CAST
                 || yytoken == Token_CLONE
                 || yytoken == Token_INC
                 || yytoken == Token_ISSET
                 || yytoken == Token_REQUIRE
                 || yytoken == Token_CLASS_C
                 || yytoken == Token_DNUMBER
                 || yytoken == Token_OBJECT_CAST
                 || yytoken == Token_EXIT
                 || yytoken == Token_BACKTICK
                 || yytoken == Token_DEC
                 || yytoken == Token_EMPTY
                 || yytoken == Token_REQUIRE_ONCE
                 || yytoken == Token_METHOD_C
                 || yytoken == Token_AT
                 || yytoken == Token_LNUMBER
                 || yytoken == Token_BOOL_CAST
                 || yytoken == Token_TILDE
                 || yytoken == Token_BANG
                 || yytoken == Token_LPAREN
                 || yytoken == Token_INT_CAST
                 || yytoken == Token_FUNC_C
                 || yytoken == Token_PLUS
                 || yytoken == Token_UNSET_CAST
                 || yytoken == Token_INCLUDE
                 || yytoken == Token_DOLLAR
                 || yytoken == Token_DOUBLE_CAST
                 || yytoken == Token_CONSTANT_ENCAPSED_STRING
                 || yytoken == Token_LINE
                 || yytoken == Token_MINUS
                 || yytoken == Token_STRING
                 || yytoken == Token_INCLUDE_ONCE
                 || yytoken == Token_LIST
                 || yytoken == Token_STRING_CAST
                 || yytoken == Token_VARIABLE
                 || yytoken == Token_PRINT
                 || yytoken == Token_FILE
                 || yytoken == Token_START_HEREDOC
                 || yytoken == Token_NEW)
        {
            ExprAst *__node_121 = 0;
            if (!parseExpr(&__node_121))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_121;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionDeclarationStatement(FunctionDeclarationStatementAst **yynode)
{
    *yynode = create<FunctionDeclarationStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FUNCTION)
    {
        if (yytoken != Token_FUNCTION)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_FUNCTION, "function");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        IdentifierAst *__node_122 = 0;
        if (!parseIdentifier(&__node_122))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->functionName = __node_122;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_VARIABLE
            || yytoken == Token_ARRAY
            || yytoken == Token_STRING
            || yytoken == Token_BIT_AND)
        {
            ParameterListAst *__node_123 = 0;
            if (!parseParameterList(&__node_123))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ParameterListKind, "parameterList");
                }
                return false;
            }
            (*yynode)->parameters = __node_123;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        InnerStatementListAst *__node_124 = 0;
        if (!parseInnerStatementList(&__node_124))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
            }
            return false;
        }
        (*yynode)->functionBody = __node_124;

        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseGlobalVar(GlobalVarAst **yynode)
{
    *yynode = create<GlobalVarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR)
    {
        if (yytoken == Token_VARIABLE)
        {
            VariableIdentifierAst *__node_125 = 0;
            if (!parseVariableIdentifier(&__node_125))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
                }
                return false;
            }
            (*yynode)->var = __node_125;

        }
        else if (yytoken == Token_DOLLAR)
        {
            if (yytoken != Token_DOLLAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOLLAR, "$");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_VARIABLE
                || yytoken == Token_DOLLAR
                || yytoken == Token_STRING)
            {
                VariableAst *__node_126 = 0;
                if (!parseVariable(&__node_126))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::VariableKind, "variable");
                    }
                    return false;
                }
                (*yynode)->dollarVar = __node_126;

            }
            else if (yytoken == Token_LBRACE)
            {
                if (yytoken != Token_LBRACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACE, "{");
                    }
                    return false;
                }
                yylex();

                ExprAst *__node_127 = 0;
                if (!parseExpr(&__node_127))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->expr = __node_127;

                if (yytoken != Token_RBRACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACE, "}");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIdentifier(IdentifierAst **yynode)
{
    *yynode = create<IdentifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->string = -1;

    if (yytoken == Token_STRING)
    {
        if (yytoken != Token_STRING)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STRING, "string");
            }
            return false;
        }
        (*yynode)->string = tokenStream->index() - 1;
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInnerStatementList(InnerStatementListAst **yynode)
{
    *yynode = create<InnerStatementListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_IF
        || yytoken == Token_THROW
        || yytoken == Token_FOREACH
        || yytoken == Token_ISSET
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_TRY
        || yytoken == Token_EMPTY
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_INC
        || yytoken == Token_CLASS
        || yytoken == Token_WHILE
        || yytoken == Token_DECLARE
        || yytoken == Token_HALT_COMPILER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_AT
        || yytoken == Token_DEC
        || yytoken == Token_DNUMBER
        || yytoken == Token_INTERFACE
        || yytoken == Token_ECHO
        || yytoken == Token_INCLUDE
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_CONTINUE
        || yytoken == Token_LNUMBER
        || yytoken == Token_NEW
        || yytoken == Token_PRINT
        || yytoken == Token_LIST
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_DOLLAR
        || yytoken == Token_CLONE
        || yytoken == Token_ARRAY
        || yytoken == Token_EVAL
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_DO
        || yytoken == Token_STRING
        || yytoken == Token_EXIT
        || yytoken == Token_FUNCTION
        || yytoken == Token_CLASS_C
        || yytoken == Token_REQUIRE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_METHOD_C
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_BACKTICK
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_RETURN
        || yytoken == Token_GLOBAL
        || yytoken == Token_FUNC_C
        || yytoken == Token_INT_CAST
        || yytoken == Token_LPAREN
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_ABSTRACT
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_FINAL
        || yytoken == Token_STATIC
        || yytoken == Token_LINE
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_PLUS
        || yytoken == Token_BREAK
        || yytoken == Token_FOR
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_SWITCH
        || yytoken == Token_UNSET
        || yytoken == Token_FILE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_LBRACE
        || yytoken == Token_MINUS || yytoken == Token_ENDIF
        || yytoken == Token_RBRACE
        || yytoken == Token_EOF
        || yytoken == Token_ENDDECLARE
        || yytoken == Token_ELSEIF
        || yytoken == Token_DEFAULT
        || yytoken == Token_ENDFOR
        || yytoken == Token_ENDSWITCH
        || yytoken == Token_ENDWHILE
        || yytoken == Token_ELSE
        || yytoken == Token_CASE
        || yytoken == Token_ENDFOREACH)
    {
        while (yytoken == Token_CONSTANT_ENCAPSED_STRING
               || yytoken == Token_IF
               || yytoken == Token_THROW
               || yytoken == Token_FOREACH
               || yytoken == Token_ISSET
               || yytoken == Token_ARRAY_CAST
               || yytoken == Token_VARIABLE
               || yytoken == Token_TRY
               || yytoken == Token_EMPTY
               || yytoken == Token_OBJECT_CAST
               || yytoken == Token_INC
               || yytoken == Token_CLASS
               || yytoken == Token_WHILE
               || yytoken == Token_DECLARE
               || yytoken == Token_HALT_COMPILER
               || yytoken == Token_BOOL_CAST
               || yytoken == Token_AT
               || yytoken == Token_DEC
               || yytoken == Token_DNUMBER
               || yytoken == Token_INTERFACE
               || yytoken == Token_ECHO
               || yytoken == Token_INCLUDE
               || yytoken == Token_UNSET_CAST
               || yytoken == Token_BANG
               || yytoken == Token_TILDE
               || yytoken == Token_CONTINUE
               || yytoken == Token_LNUMBER
               || yytoken == Token_NEW
               || yytoken == Token_PRINT
               || yytoken == Token_LIST
               || yytoken == Token_INCLUDE_ONCE
               || yytoken == Token_SEMICOLON
               || yytoken == Token_DOLLAR
               || yytoken == Token_CLONE
               || yytoken == Token_ARRAY
               || yytoken == Token_EVAL
               || yytoken == Token_DOUBLE_QUOTE
               || yytoken == Token_START_HEREDOC
               || yytoken == Token_DO
               || yytoken == Token_STRING
               || yytoken == Token_EXIT
               || yytoken == Token_FUNCTION
               || yytoken == Token_CLASS_C
               || yytoken == Token_REQUIRE
               || yytoken == Token_STRING_VARNAME
               || yytoken == Token_METHOD_C
               || yytoken == Token_REQUIRE_ONCE
               || yytoken == Token_BACKTICK
               || yytoken == Token_OPEN_TAG
               || yytoken == Token_RETURN
               || yytoken == Token_GLOBAL
               || yytoken == Token_FUNC_C
               || yytoken == Token_INT_CAST
               || yytoken == Token_LPAREN
               || yytoken == Token_INLINE_HTML
               || yytoken == Token_ABSTRACT
               || yytoken == Token_CLOSE_TAG
               || yytoken == Token_FINAL
               || yytoken == Token_STATIC
               || yytoken == Token_LINE
               || yytoken == Token_DOUBLE_CAST
               || yytoken == Token_PLUS
               || yytoken == Token_BREAK
               || yytoken == Token_FOR
               || yytoken == Token_OPEN_TAG_WITH_ECHO
               || yytoken == Token_SWITCH
               || yytoken == Token_UNSET
               || yytoken == Token_FILE
               || yytoken == Token_STRING_CAST
               || yytoken == Token_LBRACE
               || yytoken == Token_MINUS)
        {
            TopStatementAst *__node_128 = 0;
            if (!parseTopStatement(&__node_128))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopStatementKind, "topStatement");
                }
                return false;
            }
            (*yynode)->statementsSequence = snoc((*yynode)->statementsSequence, __node_128, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInterfaceDeclarationStatement(InterfaceDeclarationStatementAst **yynode)
{
    *yynode = create<InterfaceDeclarationStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_INTERFACE)
    {
        if (yytoken != Token_INTERFACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTERFACE, "interface");
            }
            return false;
        }
        yylex();

        IdentifierAst *__node_129 = 0;
        if (!parseIdentifier(&__node_129))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->interfaceName = __node_129;

        if (yytoken == Token_EXTENDS)
        {
            if (yytoken != Token_EXTENDS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXTENDS, "extends");
                }
                return false;
            }
            yylex();

            ClassImplementsAst *__node_130 = 0;
            if (!parseClassImplements(&__node_130))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassImplementsKind, "classImplements");
                }
                return false;
            }
            (*yynode)->extends = __node_130;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        ClassBodyAst *__node_131 = 0;
        if (!parseClassBody(&__node_131))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassBodyKind, "classBody");
            }
            return false;
        }
        (*yynode)->body = __node_131;

        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalAndExpression(LogicalAndExpressionAst **yynode)
{
    *yynode = create<LogicalAndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        PrintExpressionAst *__node_132 = 0;
        if (!parsePrintExpression(&__node_132))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::PrintExpressionKind, "printExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_132, memoryPool);

        while (yytoken == Token_LOGICAL_AND)
        {
            if (yytoken != Token_LOGICAL_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LOGICAL_AND, "logical and");
                }
                return false;
            }
            yylex();

            PrintExpressionAst *__node_133 = 0;
            if (!parsePrintExpression(&__node_133))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PrintExpressionKind, "printExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_133, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalOrExpression(LogicalOrExpressionAst **yynode)
{
    *yynode = create<LogicalOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        LogicalXorExpressionAst *__node_134 = 0;
        if (!parseLogicalXorExpression(&__node_134))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalXorExpressionKind, "logicalXorExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_134, memoryPool);

        while (yytoken == Token_LOGICAL_OR)
        {
            if (yytoken != Token_LOGICAL_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LOGICAL_OR, "logical or");
                }
                return false;
            }
            yylex();

            LogicalXorExpressionAst *__node_135 = 0;
            if (!parseLogicalXorExpression(&__node_135))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LogicalXorExpressionKind, "logicalXorExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_135, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalXorExpression(LogicalXorExpressionAst **yynode)
{
    *yynode = create<LogicalXorExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        LogicalAndExpressionAst *__node_136 = 0;
        if (!parseLogicalAndExpression(&__node_136))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalAndExpressionKind, "logicalAndExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_136, memoryPool);

        while (yytoken == Token_LOGICAL_XOR)
        {
            if (yytoken != Token_LOGICAL_XOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LOGICAL_XOR, "logical xor");
                }
                return false;
            }
            yylex();

            LogicalAndExpressionAst *__node_137 = 0;
            if (!parseLogicalAndExpression(&__node_137))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LogicalAndExpressionKind, "logicalAndExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_137, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodBody(MethodBodyAst **yynode)
{
    *yynode = create<MethodBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SEMICOLON
        || yytoken == Token_LBRACE)
    {
        if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_138 = 0;
            if (!parseInnerStatementList(&__node_138))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_138;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicativeExpression(MultiplicativeExpressionAst **yynode)
{
    *yynode = create<MultiplicativeExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        UnaryExpressionAst *__node_139 = 0;
        if (!parseUnaryExpression(&__node_139))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_139;

        while (yytoken == Token_MUL
               || yytoken == Token_MOD
               || yytoken == Token_DIV)
        {
            MultiplicativeExpressionRestAst *__node_140 = 0;
            if (!parseMultiplicativeExpressionRest(&__node_140))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MultiplicativeExpressionRestKind, "multiplicativeExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_140, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicativeExpressionRest(MultiplicativeExpressionRestAst **yynode)
{
    *yynode = create<MultiplicativeExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MUL
        || yytoken == Token_MOD
        || yytoken == Token_DIV)
    {
        if (yytoken == Token_MUL)
        {
            if (yytoken != Token_MUL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MUL, "*");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DIV)
        {
            if (yytoken != Token_DIV)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DIV, "/");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MOD)
        {
            if (yytoken != Token_MOD)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MOD, "%");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        UnaryExpressionAst *__node_141 = 0;
        if (!parseUnaryExpression(&__node_141))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_141;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNewElseSingle(NewElseSingleAst **yynode)
{
    *yynode = create<NewElseSingleAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ELSE || yytoken == Token_ENDIF
        || yytoken == Token_EOF)
    {
        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_142 = 0;
            if (!parseInnerStatementList(&__node_142))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_142;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNewElseifList(NewElseifListAst **yynode)
{
    *yynode = create<NewElseifListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ELSEIF || yytoken == Token_ENDIF
        || yytoken == Token_EOF
        || yytoken == Token_ELSE)
    {
        while (yytoken == Token_ELSEIF)
        {
            NewelseifListItemAst *__node_143 = 0;
            if (!parseNewelseifListItem(&__node_143))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NewelseifListItemKind, "newelseifListItem");
                }
                return false;
            }
            (*yynode)->newElseifListItemSequence = snoc((*yynode)->newElseifListItemSequence, __node_143, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNewelseifListItem(NewelseifListItemAst **yynode)
{
    *yynode = create<NewelseifListItemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ELSEIF)
    {
        if (yytoken != Token_ELSEIF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ELSEIF, "elseif");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExprAst *__node_144 = 0;
        if (!parseExpr(&__node_144))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        (*yynode)->expr = __node_144;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COLON, ":");
            }
            return false;
        }
        yylex();

        InnerStatementListAst *__node_145 = 0;
        if (!parseInnerStatementList(&__node_145))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
            }
            return false;
        }
        (*yynode)->statements = __node_145;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseObjectDimList(ObjectDimListAst **yynode)
{
    *yynode = create<ObjectDimListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE
        || yytoken == Token_STRING)
    {
        VariableNameAst *__node_146 = 0;
        if (!parseVariableName(&__node_146))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableNameKind, "variableName");
            }
            return false;
        }
        (*yynode)->variableName = __node_146;

        while (yytoken == Token_LBRACE
               || yytoken == Token_LBRACKET)
        {
            DimListItemAst *__node_147 = 0;
            if (!parseDimListItem(&__node_147))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DimListItemKind, "dimListItem");
                }
                return false;
            }
            (*yynode)->offsetItemsSequence = snoc((*yynode)->offsetItemsSequence, __node_147, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseObjectProperty(ObjectPropertyAst **yynode)
{
    *yynode = create<ObjectPropertyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_LBRACE
        || yytoken == Token_STRING)
    {
        if (yytoken == Token_LBRACE
            || yytoken == Token_STRING)
        {
            ObjectDimListAst *__node_148 = 0;
            if (!parseObjectDimList(&__node_148))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ObjectDimListKind, "objectDimList");
                }
                return false;
            }
            (*yynode)->objectDimList = __node_148;

        }
        else if (yytoken == Token_VARIABLE
                 || yytoken == Token_DOLLAR)
        {
            VariableWithoutObjectsAst *__node_149 = 0;
            if (!parseVariableWithoutObjects(&__node_149))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableWithoutObjectsKind, "variableWithoutObjects");
                }
                return false;
            }
            (*yynode)->variableWithoutObjects = __node_149;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalModifiers(OptionalModifiersAst **yynode)
{
    *yynode = create<OptionalModifiersAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
        || yytoken == Token_FINAL
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_PROTECTED
        || yytoken == Token_STATIC || yytoken == Token_VARIABLE
        || yytoken == Token_EOF
        || yytoken == Token_FUNCTION)
    {
        while (yytoken == Token_PRIVATE
               || yytoken == Token_FINAL
               || yytoken == Token_ABSTRACT
               || yytoken == Token_PUBLIC
               || yytoken == Token_PROTECTED
               || yytoken == Token_STATIC)
        {
            if (yytoken == Token_PUBLIC)
            {
                if (yytoken != Token_PUBLIC)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PUBLIC, "public");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierPublic;
            }
            else if (yytoken == Token_PROTECTED)
            {
                if (yytoken != Token_PROTECTED)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PROTECTED, "protected");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierProtected;
            }
            else if (yytoken == Token_PRIVATE)
            {
                if (yytoken != Token_PRIVATE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PRIVATE, "private");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierPrivate;
            }
            else if (yytoken == Token_STATIC)
            {
                if (yytoken != Token_STATIC)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STATIC, "static");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierStatic;
            }
            else if (yytoken == Token_ABSTRACT)
            {
                if (yytoken != Token_ABSTRACT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ABSTRACT, "abstract");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierAbstract;
            }
            else if (yytoken == Token_FINAL)
            {
                if (yytoken != Token_FINAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FINAL, "final");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierFinal;
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameter(ParameterAst **yynode)
{
    *yynode = create<ParameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->arrayType = -1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_ARRAY
        || yytoken == Token_STRING
        || yytoken == Token_BIT_AND)
    {
        if (yytoken == Token_STRING)
        {
            IdentifierAst *__node_150 = 0;
            if (!parseIdentifier(&__node_150))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->parameterType = __node_150;

        }
        else if (yytoken == Token_ARRAY)
        {
            if (yytoken != Token_ARRAY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ARRAY, "array");
                }
                return false;
            }
            (*yynode)->arrayType = tokenStream->index() - 1;
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        VariableIdentifierAst *__node_151 = 0;
        if (!parseVariableIdentifier(&__node_151))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
            }
            return false;
        }
        (*yynode)->variable = __node_151;

        if (yytoken == Token_ASSIGN)
        {
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            StaticScalarAst *__node_152 = 0;
            if (!parseStaticScalar(&__node_152))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
                }
                return false;
            }
            (*yynode)->defaultValue = __node_152;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameterList(ParameterListAst **yynode)
{
    *yynode = create<ParameterListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_ARRAY
        || yytoken == Token_STRING
        || yytoken == Token_BIT_AND)
    {
        ParameterAst *__node_153 = 0;
        if (!parseParameter(&__node_153))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ParameterKind, "parameter");
            }
            return false;
        }
        (*yynode)->parametersSequence = snoc((*yynode)->parametersSequence, __node_153, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ParameterAst *__node_154 = 0;
            if (!parseParameter(&__node_154))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ParameterKind, "parameter");
                }
                return false;
            }
            (*yynode)->parametersSequence = snoc((*yynode)->parametersSequence, __node_154, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePostprefixOperator(PostprefixOperatorAst **yynode)
{
    *yynode = create<PostprefixOperatorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->op = -1;
    (*yynode)->op = -1;

    if (yytoken == Token_INC
        || yytoken == Token_DEC)
    {
        if (yytoken == Token_INC)
        {
            if (yytoken != Token_INC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INC, "++");
                }
                return false;
            }
            (*yynode)->op = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_DEC)
        {
            if (yytoken != Token_DEC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEC, "--");
                }
                return false;
            }
            (*yynode)->op = tokenStream->index() - 1;
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrintExpression(PrintExpressionAst **yynode)
{
    *yynode = create<PrintExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->print = -1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        while (yytoken == Token_PRINT)
        {
            if (yytoken != Token_PRINT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PRINT, "print");
                }
                return false;
            }
            (*yynode)->print = tokenStream->index() - 1;
            yylex();

        }
        AssignmentExpressionAst *__node_155 = 0;
        if (!parseAssignmentExpression(&__node_155))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AssignmentExpressionKind, "assignmentExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_155;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRelationalExpression(RelationalExpressionAst **yynode)
{
    *yynode = create<RelationalExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        ShiftExpressionAst *__node_156 = 0;
        if (!parseShiftExpression(&__node_156))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ShiftExpressionKind, "shiftExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_156;

        if (yytoken == Token_IS_SMALLER_OR_EQUAL
            || yytoken == Token_IS_GREATER
            || yytoken == Token_IS_SMALLER
            || yytoken == Token_IS_GREATER_OR_EQUAL)
        {
            do
            {
                RelationalExpressionRestAst *__node_157 = 0;
                if (!parseRelationalExpressionRest(&__node_157))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::RelationalExpressionRestKind, "relationalExpressionRest");
                    }
                    return false;
                }
                (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_157, memoryPool);

            }
            while (yytoken == Token_IS_SMALLER_OR_EQUAL
                   || yytoken == Token_IS_GREATER
                   || yytoken == Token_IS_SMALLER
                   || yytoken == Token_IS_GREATER_OR_EQUAL);
        }
        else if (yytoken == Token_INSTANCEOF)
        {
            if (yytoken != Token_INSTANCEOF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INSTANCEOF, "instanceof");
                }
                return false;
            }
            yylex();

            ClassNameReferenceAst *__node_158 = 0;
            if (!parseClassNameReference(&__node_158))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassNameReferenceKind, "classNameReference");
                }
                return false;
            }
            (*yynode)->instanceofType = __node_158;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRelationalExpressionRest(RelationalExpressionRestAst **yynode)
{
    *yynode = create<RelationalExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IS_SMALLER_OR_EQUAL
        || yytoken == Token_IS_GREATER
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_IS_GREATER_OR_EQUAL)
    {
        if (yytoken == Token_IS_SMALLER)
        {
            if (yytoken != Token_IS_SMALLER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_SMALLER, "<");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_GREATER)
        {
            if (yytoken != Token_IS_GREATER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_GREATER, ">");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_SMALLER_OR_EQUAL)
        {
            if (yytoken != Token_IS_SMALLER_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_SMALLER_OR_EQUAL, "<=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_GREATER_OR_EQUAL)
        {
            if (yytoken != Token_IS_GREATER_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_GREATER_OR_EQUAL, ">=");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        ShiftExpressionAst *__node_159 = 0;
        if (!parseShiftExpression(&__node_159))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ShiftExpressionKind, "shiftExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_159;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseScalar(ScalarAst **yynode)
{
    *yynode = create<ScalarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->string = -1;
    (*yynode)->constname = -1;
    (*yynode)->varname = -1;

    if (yytoken == Token_LNUMBER
        || yytoken == Token_CLASS_C
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_LINE
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_STRING
        || yytoken == Token_FUNC_C
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_METHOD_C
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_FILE)
    {
        if (yytoken == Token_LNUMBER
            || yytoken == Token_CLASS_C
            || yytoken == Token_LINE
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_DNUMBER
            || yytoken == Token_FUNC_C
            || yytoken == Token_METHOD_C
            || yytoken == Token_FILE)
        {
            CommonScalarAst *__node_160 = 0;
            if (!parseCommonScalar(&__node_160))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CommonScalarKind, "commonScalar");
                }
                return false;
            }
            (*yynode)->commonScalar = __node_160;

        }
        else if (yytoken == Token_STRING)
        {
            if (yytoken != Token_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING, "string");
                }
                return false;
            }
            (*yynode)->string = tokenStream->index() - 1;
            yylex();

            if (yytoken == Token_PAAMAYIM_NEKUDOTAYIM)
            {
                if (yytoken != Token_PAAMAYIM_NEKUDOTAYIM)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PAAMAYIM_NEKUDOTAYIM, "::");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_STRING)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING, "string");
                    }
                    return false;
                }
                (*yynode)->constname = tokenStream->index() - 1;
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_STRING_VARNAME)
        {
            if (yytoken != Token_STRING_VARNAME)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_VARNAME, "string varname");
                }
                return false;
            }
            (*yynode)->varname = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_DOUBLE_QUOTE)
        {
            if (yytoken != Token_DOUBLE_QUOTE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_QUOTE, "\"");
                }
                return false;
            }
            yylex();

            EncapsListAst *__node_161 = 0;
            if (!parseEncapsList(&__node_161))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EncapsListKind, "encapsList");
                }
                return false;
            }
            (*yynode)->encapsList = __node_161;

            if (yytoken != Token_DOUBLE_QUOTE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_QUOTE, "\"");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_START_HEREDOC)
        {
            if (yytoken != Token_START_HEREDOC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_START_HEREDOC, "start heredoc");
                }
                return false;
            }
            yylex();

            EncapsListAst *__node_162 = 0;
            if (!parseEncapsList(&__node_162))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EncapsListKind, "encapsList");
                }
                return false;
            }
            (*yynode)->encapsList = __node_162;

            if (yytoken != Token_END_HEREDOC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END_HEREDOC, "end heredoc");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSemicolonOrCloseTag(SemicolonOrCloseTagAst **yynode)
{
    *yynode = create<SemicolonOrCloseTagAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SEMICOLON
        || yytoken == Token_CLOSE_TAG)
    {
        if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLOSE_TAG)
        {
            if (yytoken != Token_CLOSE_TAG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLOSE_TAG, "?>");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShiftExpression(ShiftExpressionAst **yynode)
{
    *yynode = create<ShiftExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        AdditiveExpressionAst *__node_163 = 0;
        if (!parseAdditiveExpression(&__node_163))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AdditiveExpressionKind, "additiveExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_163;

        while (yytoken == Token_SR
               || yytoken == Token_SL)
        {
            ShiftExpressionRestAst *__node_164 = 0;
            if (!parseShiftExpressionRest(&__node_164))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ShiftExpressionRestKind, "shiftExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_164, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShiftExpressionRest(ShiftExpressionRestAst **yynode)
{
    *yynode = create<ShiftExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SR
        || yytoken == Token_SL)
    {
        if (yytoken == Token_SL)
        {
            if (yytoken != Token_SL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SL, "<<");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SR)
        {
            if (yytoken != Token_SR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SR, ">>");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        AdditiveExpressionAst *__node_165 = 0;
        if (!parseAdditiveExpression(&__node_165))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AdditiveExpressionKind, "additiveExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_165;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStart(StartAst **yynode)
{
    *yynode = create<StartAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_IF
        || yytoken == Token_THROW
        || yytoken == Token_FOREACH
        || yytoken == Token_ISSET
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_TRY
        || yytoken == Token_EMPTY
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_INC
        || yytoken == Token_CLASS
        || yytoken == Token_WHILE
        || yytoken == Token_DECLARE
        || yytoken == Token_HALT_COMPILER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_AT
        || yytoken == Token_DEC
        || yytoken == Token_DNUMBER
        || yytoken == Token_INTERFACE
        || yytoken == Token_ECHO
        || yytoken == Token_INCLUDE
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_CONTINUE
        || yytoken == Token_LNUMBER
        || yytoken == Token_NEW
        || yytoken == Token_PRINT
        || yytoken == Token_LIST
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_DOLLAR
        || yytoken == Token_CLONE
        || yytoken == Token_ARRAY
        || yytoken == Token_EVAL
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_DO
        || yytoken == Token_STRING
        || yytoken == Token_EXIT
        || yytoken == Token_FUNCTION
        || yytoken == Token_CLASS_C
        || yytoken == Token_REQUIRE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_METHOD_C
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_BACKTICK
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_RETURN
        || yytoken == Token_GLOBAL
        || yytoken == Token_FUNC_C
        || yytoken == Token_INT_CAST
        || yytoken == Token_LPAREN
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_ABSTRACT
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_FINAL
        || yytoken == Token_STATIC
        || yytoken == Token_LINE
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_PLUS
        || yytoken == Token_BREAK
        || yytoken == Token_FOR
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_SWITCH
        || yytoken == Token_UNSET
        || yytoken == Token_FILE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_LBRACE
        || yytoken == Token_MINUS || yytoken == Token_EOF)
    {
        InnerStatementListAst *__node_166 = 0;
        if (!parseInnerStatementList(&__node_166))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
            }
            return false;
        }
        (*yynode)->statements = __node_166;

        if (Token_EOF != yytoken)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatement(StatementAst **yynode)
{
    *yynode = create<StatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNSET
        || yytoken == Token_CONTINUE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_SWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_FOR
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_BREAK
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_FOREACH
        || yytoken == Token_REQUIRE
        || yytoken == Token_THROW
        || yytoken == Token_CLASS_C
        || yytoken == Token_IF
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_DNUMBER
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_DO
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_TRY
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_LPAREN
        || yytoken == Token_DECLARE
        || yytoken == Token_INT_CAST
        || yytoken == Token_WHILE
        || yytoken == Token_FUNC_C
        || yytoken == Token_GLOBAL
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_RETURN
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_ECHO
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_STATIC
        || yytoken == Token_LIST
        || yytoken == Token_LBRACE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_NEW
        || yytoken == Token_START_HEREDOC)
    {
        if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_167 = 0;
            if (!parseInnerStatementList(&__node_167))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_167;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IF)
        {
            if (yytoken != Token_IF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IF, "if");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_168 = 0;
            if (!parseExpr(&__node_168))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->ifExpr = __node_168;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_COLON)
            {
                if (yytoken != Token_COLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COLON, ":");
                    }
                    return false;
                }
                yylex();

                InnerStatementListAst *__node_169 = 0;
                if (!parseInnerStatementList(&__node_169))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                    }
                    return false;
                }
                (*yynode)->statements = __node_169;

                NewElseifListAst *__node_170 = 0;
                if (!parseNewElseifList(&__node_170))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::NewElseifListKind, "newElseifList");
                    }
                    return false;
                }
                NewElseSingleAst *__node_171 = 0;
                if (!parseNewElseSingle(&__node_171))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::NewElseSingleKind, "newElseSingle");
                    }
                    return false;
                }
                if (yytoken != Token_ENDIF)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ENDIF, "endif");
                    }
                    return false;
                }
                yylex();

                SemicolonOrCloseTagAst *__node_172 = 0;
                if (!parseSemicolonOrCloseTag(&__node_172))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_UNSET
                     || yytoken == Token_CONTINUE
                     || yytoken == Token_STRING_VARNAME
                     || yytoken == Token_DOUBLE_QUOTE
                     || yytoken == Token_EVAL
                     || yytoken == Token_SWITCH
                     || yytoken == Token_ARRAY
                     || yytoken == Token_FOR
                     || yytoken == Token_ARRAY_CAST
                     || yytoken == Token_BREAK
                     || yytoken == Token_CLONE
                     || yytoken == Token_INC
                     || yytoken == Token_ISSET
                     || yytoken == Token_OPEN_TAG
                     || yytoken == Token_FOREACH
                     || yytoken == Token_REQUIRE
                     || yytoken == Token_THROW
                     || yytoken == Token_CLASS_C
                     || yytoken == Token_IF
                     || yytoken == Token_OBJECT_CAST
                     || yytoken == Token_DNUMBER
                     || yytoken == Token_EXIT
                     || yytoken == Token_BACKTICK
                     || yytoken == Token_DEC
                     || yytoken == Token_EMPTY
                     || yytoken == Token_CLOSE_TAG
                     || yytoken == Token_DO
                     || yytoken == Token_INLINE_HTML
                     || yytoken == Token_REQUIRE_ONCE
                     || yytoken == Token_TRY
                     || yytoken == Token_METHOD_C
                     || yytoken == Token_AT
                     || yytoken == Token_BOOL_CAST
                     || yytoken == Token_LNUMBER
                     || yytoken == Token_TILDE
                     || yytoken == Token_BANG
                     || yytoken == Token_OPEN_TAG_WITH_ECHO
                     || yytoken == Token_LPAREN
                     || yytoken == Token_DECLARE
                     || yytoken == Token_INT_CAST
                     || yytoken == Token_WHILE
                     || yytoken == Token_FUNC_C
                     || yytoken == Token_GLOBAL
                     || yytoken == Token_PLUS
                     || yytoken == Token_UNSET_CAST
                     || yytoken == Token_INCLUDE
                     || yytoken == Token_DOLLAR
                     || yytoken == Token_RETURN
                     || yytoken == Token_DOUBLE_CAST
                     || yytoken == Token_CONSTANT_ENCAPSED_STRING
                     || yytoken == Token_ECHO
                     || yytoken == Token_LINE
                     || yytoken == Token_MINUS
                     || yytoken == Token_SEMICOLON
                     || yytoken == Token_STRING
                     || yytoken == Token_INCLUDE_ONCE
                     || yytoken == Token_STATIC
                     || yytoken == Token_LIST
                     || yytoken == Token_LBRACE
                     || yytoken == Token_STRING_CAST
                     || yytoken == Token_VARIABLE
                     || yytoken == Token_PRINT
                     || yytoken == Token_FILE
                     || yytoken == Token_NEW
                     || yytoken == Token_START_HEREDOC)
            {
                StatementAst *__node_173 = 0;
                if (!parseStatement(&__node_173))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StatementKind, "statement");
                    }
                    return false;
                }
                (*yynode)->ifStatement = __node_173;

                ElseifListAst *__node_174 = 0;
                if (!parseElseifList(&__node_174))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ElseifListKind, "elseifList");
                    }
                    return false;
                }
                (*yynode)->elseifList = __node_174;

                ElseSingleAst *__node_175 = 0;
                if (!parseElseSingle(&__node_175))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ElseSingleKind, "elseSingle");
                    }
                    return false;
                }
                (*yynode)->elseSingle = __node_175;

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_WHILE)
        {
            if (yytoken != Token_WHILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHILE, "while");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_176 = 0;
            if (!parseExpr(&__node_176))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->whileExpr = __node_176;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            WhileStatementAst *__node_177 = 0;
            if (!parseWhileStatement(&__node_177))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::WhileStatementKind, "whileStatement");
                }
                return false;
            }
            (*yynode)->whilteStatement = __node_177;

        }
        else if (yytoken == Token_FOR)
        {
            if (yytoken != Token_FOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FOR, "for");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ForExprAst *__node_178 = 0;
            if (!parseForExpr(&__node_178))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForExprKind, "forExpr");
                }
                return false;
            }
            (*yynode)->forExpr1 = __node_178;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            ForExprAst *__node_179 = 0;
            if (!parseForExpr(&__node_179))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForExprKind, "forExpr");
                }
                return false;
            }
            (*yynode)->forExpr2 = __node_179;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            ForExprAst *__node_180 = 0;
            if (!parseForExpr(&__node_180))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForExprKind, "forExpr");
                }
                return false;
            }
            (*yynode)->forExpr3 = __node_180;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            ForStatementAst *__node_181 = 0;
            if (!parseForStatement(&__node_181))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForStatementKind, "forStatement");
                }
                return false;
            }
            (*yynode)->forStatement = __node_181;

        }
        else if (yytoken == Token_SWITCH)
        {
            if (yytoken != Token_SWITCH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SWITCH, "switch");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_182 = 0;
            if (!parseExpr(&__node_182))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->swtichExpr = __node_182;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            SwitchCaseListAst *__node_183 = 0;
            if (!parseSwitchCaseList(&__node_183))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SwitchCaseListKind, "switchCaseList");
                }
                return false;
            }
            (*yynode)->switchCaseList = __node_183;

        }
        else if (yytoken == Token_FOREACH)
        {
            if (yytoken != Token_FOREACH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FOREACH, "foreach");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            bool blockErrors_2 = blockErrors(true);
            qint64 try_startToken_2 = tokenStream->index() - 1;
            ParserState *try_startState_2 = copyCurrentState();
            {
                VariableAst *__node_184 = 0;
                if (!parseVariable(&__node_184))
                {
                    goto __catch_2;
                }
                (*yynode)->foreachVar = __node_184;

                if (yytoken != Token_AS)
                    goto __catch_2;
                yylex();

                ForeachVariableAst *__node_185 = 0;
                if (!parseForeachVariable(&__node_185))
                {
                    goto __catch_2;
                }
                (*yynode)->foreachVarAsVar = __node_185;

            }
            blockErrors(blockErrors_2);
            if (try_startState_2)
                delete try_startState_2;

            if (false) // the only way to enter here is using goto
            {
__catch_2:
                if (try_startState_2)
                {
                    restoreState(try_startState_2);
                    delete try_startState_2;
                }
                blockErrors(blockErrors_2);
                rewind(try_startToken_2);

                ExprAst *__node_186 = 0;
                if (!parseExpr(&__node_186))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->foreachExpr = __node_186;

                if (yytoken != Token_AS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_AS, "as");
                    }
                    return false;
                }
                yylex();

                VariableAst *__node_187 = 0;
                if (!parseVariable(&__node_187))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::VariableKind, "variable");
                    }
                    return false;
                }
                (*yynode)->foreachExprAsVar = __node_187;

            }

            ForeachOptionalArgAst *__node_188 = 0;
            if (!parseForeachOptionalArg(&__node_188))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForeachOptionalArgKind, "foreachOptionalArg");
                }
                return false;
            }
            (*yynode)->foreachArg = __node_188;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            ForeachStatementAst *__node_189 = 0;
            if (!parseForeachStatement(&__node_189))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForeachStatementKind, "foreachStatement");
                }
                return false;
            }
            (*yynode)->foreachStatement = __node_189;

        }
        else if (yytoken == Token_DECLARE)
        {
            if (yytoken != Token_DECLARE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DECLARE, "declare");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            DeclareItemAst *__node_190 = 0;
            if (!parseDeclareItem(&__node_190))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DeclareItemKind, "declareItem");
                }
                return false;
            }
            (*yynode)->declareItem = __node_190;

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                DeclareItemAst *__node_191 = 0;
                if (!parseDeclareItem(&__node_191))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::DeclareItemKind, "declareItem");
                    }
                    return false;
                }
                (*yynode)->declareItem = __node_191;

            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            DeclareStatementAst *__node_192 = 0;
            if (!parseDeclareStatement(&__node_192))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DeclareStatementKind, "declareStatement");
                }
                return false;
            }
        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_TRY)
        {
            if (yytoken != Token_TRY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TRY, "try");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_193 = 0;
            if (!parseInnerStatementList(&__node_193))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_193;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

            while (yytoken == Token_CATCH)
            {
                Catch_itemAst *__node_194 = 0;
                if (!parseCatch_item(&__node_194))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Catch_itemKind, "catch_item");
                    }
                    return false;
                }
                (*yynode)->catchesSequence = snoc((*yynode)->catchesSequence, __node_194, memoryPool);

            }
        }
        else if (yytoken == Token_UNSET)
        {
            if (yytoken != Token_UNSET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNSET, "unset");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            VariableAst *__node_195 = 0;
            if (!parseVariable(&__node_195))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->unsetVariablesSequence = snoc((*yynode)->unsetVariablesSequence, __node_195, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                VariableAst *__node_196 = 0;
                if (!parseVariable(&__node_196))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::VariableKind, "variable");
                    }
                    return false;
                }
                (*yynode)->unsetVariablesSequence = snoc((*yynode)->unsetVariablesSequence, __node_196, memoryPool);

            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_197 = 0;
            if (!parseSemicolonOrCloseTag(&__node_197))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_STRING_VARNAME
                 || yytoken == Token_DOUBLE_QUOTE
                 || yytoken == Token_EVAL
                 || yytoken == Token_ARRAY
                 || yytoken == Token_ARRAY_CAST
                 || yytoken == Token_CLONE
                 || yytoken == Token_INC
                 || yytoken == Token_ISSET
                 || yytoken == Token_REQUIRE
                 || yytoken == Token_CLASS_C
                 || yytoken == Token_DNUMBER
                 || yytoken == Token_OBJECT_CAST
                 || yytoken == Token_EXIT
                 || yytoken == Token_BACKTICK
                 || yytoken == Token_DEC
                 || yytoken == Token_EMPTY
                 || yytoken == Token_REQUIRE_ONCE
                 || yytoken == Token_METHOD_C
                 || yytoken == Token_AT
                 || yytoken == Token_LNUMBER
                 || yytoken == Token_BOOL_CAST
                 || yytoken == Token_TILDE
                 || yytoken == Token_BANG
                 || yytoken == Token_LPAREN
                 || yytoken == Token_INT_CAST
                 || yytoken == Token_FUNC_C
                 || yytoken == Token_PLUS
                 || yytoken == Token_UNSET_CAST
                 || yytoken == Token_INCLUDE
                 || yytoken == Token_DOLLAR
                 || yytoken == Token_DOUBLE_CAST
                 || yytoken == Token_CONSTANT_ENCAPSED_STRING
                 || yytoken == Token_LINE
                 || yytoken == Token_MINUS
                 || yytoken == Token_STRING
                 || yytoken == Token_INCLUDE_ONCE
                 || yytoken == Token_LIST
                 || yytoken == Token_STRING_CAST
                 || yytoken == Token_VARIABLE
                 || yytoken == Token_PRINT
                 || yytoken == Token_FILE
                 || yytoken == Token_START_HEREDOC
                 || yytoken == Token_NEW)
        {
            ExprAst *__node_198 = 0;
            if (!parseExpr(&__node_198))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_198;

            SemicolonOrCloseTagAst *__node_199 = 0;
            if (!parseSemicolonOrCloseTag(&__node_199))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_DO)
        {
            if (yytoken != Token_DO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DO, "do");
                }
                return false;
            }
            yylex();

            StatementAst *__node_200 = 0;
            if (!parseStatement(&__node_200))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->doStatement = __node_200;

            if (yytoken != Token_WHILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHILE, "while");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_201 = 0;
            if (!parseExpr(&__node_201))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->whilteExpr = __node_201;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_202 = 0;
            if (!parseSemicolonOrCloseTag(&__node_202))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_BREAK)
        {
            if (yytoken != Token_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BREAK, "break");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_STRING_VARNAME
                || yytoken == Token_DOUBLE_QUOTE
                || yytoken == Token_EVAL
                || yytoken == Token_ARRAY
                || yytoken == Token_ARRAY_CAST
                || yytoken == Token_CLONE
                || yytoken == Token_INC
                || yytoken == Token_ISSET
                || yytoken == Token_REQUIRE
                || yytoken == Token_CLASS_C
                || yytoken == Token_DNUMBER
                || yytoken == Token_OBJECT_CAST
                || yytoken == Token_EXIT
                || yytoken == Token_BACKTICK
                || yytoken == Token_DEC
                || yytoken == Token_EMPTY
                || yytoken == Token_REQUIRE_ONCE
                || yytoken == Token_METHOD_C
                || yytoken == Token_AT
                || yytoken == Token_LNUMBER
                || yytoken == Token_BOOL_CAST
                || yytoken == Token_TILDE
                || yytoken == Token_BANG
                || yytoken == Token_LPAREN
                || yytoken == Token_INT_CAST
                || yytoken == Token_FUNC_C
                || yytoken == Token_PLUS
                || yytoken == Token_UNSET_CAST
                || yytoken == Token_INCLUDE
                || yytoken == Token_DOLLAR
                || yytoken == Token_DOUBLE_CAST
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_LINE
                || yytoken == Token_MINUS
                || yytoken == Token_STRING
                || yytoken == Token_INCLUDE_ONCE
                || yytoken == Token_LIST
                || yytoken == Token_STRING_CAST
                || yytoken == Token_VARIABLE
                || yytoken == Token_PRINT
                || yytoken == Token_FILE
                || yytoken == Token_START_HEREDOC
                || yytoken == Token_NEW)
            {
                ExprAst *__node_203 = 0;
                if (!parseExpr(&__node_203))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->breakExpr = __node_203;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            SemicolonOrCloseTagAst *__node_204 = 0;
            if (!parseSemicolonOrCloseTag(&__node_204))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_CONTINUE)
        {
            if (yytoken != Token_CONTINUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONTINUE, "continue");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_STRING_VARNAME
                || yytoken == Token_DOUBLE_QUOTE
                || yytoken == Token_EVAL
                || yytoken == Token_ARRAY
                || yytoken == Token_ARRAY_CAST
                || yytoken == Token_CLONE
                || yytoken == Token_INC
                || yytoken == Token_ISSET
                || yytoken == Token_REQUIRE
                || yytoken == Token_CLASS_C
                || yytoken == Token_DNUMBER
                || yytoken == Token_OBJECT_CAST
                || yytoken == Token_EXIT
                || yytoken == Token_BACKTICK
                || yytoken == Token_DEC
                || yytoken == Token_EMPTY
                || yytoken == Token_REQUIRE_ONCE
                || yytoken == Token_METHOD_C
                || yytoken == Token_AT
                || yytoken == Token_LNUMBER
                || yytoken == Token_BOOL_CAST
                || yytoken == Token_TILDE
                || yytoken == Token_BANG
                || yytoken == Token_LPAREN
                || yytoken == Token_INT_CAST
                || yytoken == Token_FUNC_C
                || yytoken == Token_PLUS
                || yytoken == Token_UNSET_CAST
                || yytoken == Token_INCLUDE
                || yytoken == Token_DOLLAR
                || yytoken == Token_DOUBLE_CAST
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_LINE
                || yytoken == Token_MINUS
                || yytoken == Token_STRING
                || yytoken == Token_INCLUDE_ONCE
                || yytoken == Token_LIST
                || yytoken == Token_STRING_CAST
                || yytoken == Token_VARIABLE
                || yytoken == Token_PRINT
                || yytoken == Token_FILE
                || yytoken == Token_START_HEREDOC
                || yytoken == Token_NEW)
            {
                ExprAst *__node_205 = 0;
                if (!parseExpr(&__node_205))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->continueExpr = __node_205;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            SemicolonOrCloseTagAst *__node_206 = 0;
            if (!parseSemicolonOrCloseTag(&__node_206))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_RETURN)
        {
            if (yytoken != Token_RETURN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RETURN, "return");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_STRING_VARNAME
                || yytoken == Token_DOUBLE_QUOTE
                || yytoken == Token_EVAL
                || yytoken == Token_ARRAY
                || yytoken == Token_ARRAY_CAST
                || yytoken == Token_CLONE
                || yytoken == Token_INC
                || yytoken == Token_ISSET
                || yytoken == Token_REQUIRE
                || yytoken == Token_CLASS_C
                || yytoken == Token_DNUMBER
                || yytoken == Token_OBJECT_CAST
                || yytoken == Token_EXIT
                || yytoken == Token_BACKTICK
                || yytoken == Token_DEC
                || yytoken == Token_EMPTY
                || yytoken == Token_REQUIRE_ONCE
                || yytoken == Token_METHOD_C
                || yytoken == Token_AT
                || yytoken == Token_LNUMBER
                || yytoken == Token_BOOL_CAST
                || yytoken == Token_TILDE
                || yytoken == Token_BANG
                || yytoken == Token_LPAREN
                || yytoken == Token_INT_CAST
                || yytoken == Token_FUNC_C
                || yytoken == Token_PLUS
                || yytoken == Token_UNSET_CAST
                || yytoken == Token_INCLUDE
                || yytoken == Token_DOLLAR
                || yytoken == Token_DOUBLE_CAST
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_LINE
                || yytoken == Token_MINUS
                || yytoken == Token_STRING
                || yytoken == Token_INCLUDE_ONCE
                || yytoken == Token_LIST
                || yytoken == Token_STRING_CAST
                || yytoken == Token_VARIABLE
                || yytoken == Token_PRINT
                || yytoken == Token_FILE
                || yytoken == Token_START_HEREDOC
                || yytoken == Token_NEW)
            {
                ExprAst *__node_207 = 0;
                if (!parseExpr(&__node_207))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->returnExpr = __node_207;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            SemicolonOrCloseTagAst *__node_208 = 0;
            if (!parseSemicolonOrCloseTag(&__node_208))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_GLOBAL)
        {
            if (yytoken != Token_GLOBAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GLOBAL, "global");
                }
                return false;
            }
            yylex();

            GlobalVarAst *__node_209 = 0;
            if (!parseGlobalVar(&__node_209))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::GlobalVarKind, "globalVar");
                }
                return false;
            }
            (*yynode)->globalVarsSequence = snoc((*yynode)->globalVarsSequence, __node_209, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                GlobalVarAst *__node_210 = 0;
                if (!parseGlobalVar(&__node_210))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::GlobalVarKind, "globalVar");
                    }
                    return false;
                }
                (*yynode)->globalVarsSequence = snoc((*yynode)->globalVarsSequence, __node_210, memoryPool);

            }
            SemicolonOrCloseTagAst *__node_211 = 0;
            if (!parseSemicolonOrCloseTag(&__node_211))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_STATIC)
        {
            if (yytoken != Token_STATIC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STATIC, "static");
                }
                return false;
            }
            yylex();

            StaticVarAst *__node_212 = 0;
            if (!parseStaticVar(&__node_212))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticVarKind, "staticVar");
                }
                return false;
            }
            (*yynode)->staticVarsSequence = snoc((*yynode)->staticVarsSequence, __node_212, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                StaticVarAst *__node_213 = 0;
                if (!parseStaticVar(&__node_213))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StaticVarKind, "staticVar");
                    }
                    return false;
                }
                (*yynode)->staticVarsSequence = snoc((*yynode)->staticVarsSequence, __node_213, memoryPool);

            }
            SemicolonOrCloseTagAst *__node_214 = 0;
            if (!parseSemicolonOrCloseTag(&__node_214))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_ECHO)
        {
            if (yytoken != Token_ECHO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ECHO, "echo");
                }
                return false;
            }
            yylex();

            ExprAst *__node_215 = 0;
            if (!parseExpr(&__node_215))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->echoExprsSequence = snoc((*yynode)->echoExprsSequence, __node_215, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                ExprAst *__node_216 = 0;
                if (!parseExpr(&__node_216))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprKind, "expr");
                    }
                    return false;
                }
                (*yynode)->echoExprsSequence = snoc((*yynode)->echoExprsSequence, __node_216, memoryPool);

            }
            SemicolonOrCloseTagAst *__node_217 = 0;
            if (!parseSemicolonOrCloseTag(&__node_217))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_THROW)
        {
            if (yytoken != Token_THROW)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_THROW, "throw");
                }
                return false;
            }
            yylex();

            ExprAst *__node_218 = 0;
            if (!parseExpr(&__node_218))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->throwExpr = __node_218;

            SemicolonOrCloseTagAst *__node_219 = 0;
            if (!parseSemicolonOrCloseTag(&__node_219))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_CLOSE_TAG)
        {
            if (yytoken != Token_CLOSE_TAG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLOSE_TAG, "?>");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_OPEN_TAG)
        {
            if (yytoken != Token_OPEN_TAG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OPEN_TAG, "<?");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_OPEN_TAG_WITH_ECHO)
        {
            if (yytoken != Token_OPEN_TAG_WITH_ECHO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OPEN_TAG_WITH_ECHO, "<?=");
                }
                return false;
            }
            yylex();

            ExprAst *__node_220 = 0;
            if (!parseExpr(&__node_220))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_220;

            SemicolonOrCloseTagAst *__node_221 = 0;
            if (!parseSemicolonOrCloseTag(&__node_221))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else if (yytoken == Token_INLINE_HTML)
        {
            if (yytoken != Token_INLINE_HTML)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INLINE_HTML, "inline html");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStaticArrayPairValue(StaticArrayPairValueAst **yynode)
{
    *yynode = create<StaticArrayPairValueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PLUS
        || yytoken == Token_LNUMBER
        || yytoken == Token_CLASS_C
        || yytoken == Token_LINE
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_ARRAY
        || yytoken == Token_FUNC_C
        || yytoken == Token_STRING
        || yytoken == Token_MINUS
        || yytoken == Token_METHOD_C
        || yytoken == Token_FILE)
    {
        StaticScalarAst *__node_222 = 0;
        if (!parseStaticScalar(&__node_222))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
            }
            return false;
        }
        (*yynode)->val1Sequence = snoc((*yynode)->val1Sequence, __node_222, memoryPool);

        if (yytoken == Token_DOUBLE_ARROW)
        {
            if (yytoken != Token_DOUBLE_ARROW)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_ARROW, "=>");
                }
                return false;
            }
            yylex();

            StaticScalarAst *__node_223 = 0;
            if (!parseStaticScalar(&__node_223))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
                }
                return false;
            }
            (*yynode)->val2Sequence = snoc((*yynode)->val2Sequence, __node_223, memoryPool);

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStaticMember(StaticMemberAst **yynode)
{
    *yynode = create<StaticMemberAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING)
    {
        IdentifierAst *__node_224 = 0;
        if (!parseIdentifier(&__node_224))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->className = __node_224;

        if (yytoken != Token_PAAMAYIM_NEKUDOTAYIM)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_PAAMAYIM_NEKUDOTAYIM, "::");
            }
            return false;
        }
        yylex();

        VariableWithoutObjectsAst *__node_225 = 0;
        if (!parseVariableWithoutObjects(&__node_225))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableWithoutObjectsKind, "variableWithoutObjects");
            }
            return false;
        }
        (*yynode)->variable = __node_225;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStaticScalar(StaticScalarAst **yynode)
{
    *yynode = create<StaticScalarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PLUS
        || yytoken == Token_LNUMBER
        || yytoken == Token_CLASS_C
        || yytoken == Token_LINE
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_ARRAY
        || yytoken == Token_FUNC_C
        || yytoken == Token_STRING
        || yytoken == Token_MINUS
        || yytoken == Token_METHOD_C
        || yytoken == Token_FILE)
    {
        if (yytoken == Token_LNUMBER
            || yytoken == Token_CLASS_C
            || yytoken == Token_LINE
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_DNUMBER
            || yytoken == Token_FUNC_C
            || yytoken == Token_METHOD_C
            || yytoken == Token_FILE)
        {
            CommonScalarAst *__node_226 = 0;
            if (!parseCommonScalar(&__node_226))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CommonScalarKind, "commonScalar");
                }
                return false;
            }
            (*yynode)->value = __node_226;

        }
        else if (yytoken == Token_STRING)
        {
            if (yytoken != Token_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING, "string");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_PAAMAYIM_NEKUDOTAYIM)
            {
                if (yytoken != Token_PAAMAYIM_NEKUDOTAYIM)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PAAMAYIM_NEKUDOTAYIM, "::");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_STRING)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING, "string");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

            StaticScalarAst *__node_227 = 0;
            if (!parseStaticScalar(&__node_227))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
                }
                return false;
            }
            (*yynode)->plusValue = __node_227;

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

            StaticScalarAst *__node_228 = 0;
            if (!parseStaticScalar(&__node_228))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
                }
                return false;
            }
            (*yynode)->minusValue = __node_228;

        }
        else if (yytoken == Token_ARRAY)
        {
            if (yytoken != Token_ARRAY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ARRAY, "array");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_PLUS
                || yytoken == Token_LNUMBER
                || yytoken == Token_CLASS_C
                || yytoken == Token_LINE
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_DNUMBER
                || yytoken == Token_ARRAY
                || yytoken == Token_FUNC_C
                || yytoken == Token_STRING
                || yytoken == Token_MINUS
                || yytoken == Token_METHOD_C
                || yytoken == Token_FILE)
            {
                StaticArrayPairValueAst *__node_229 = 0;
                if (!parseStaticArrayPairValue(&__node_229))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StaticArrayPairValueKind, "staticArrayPairValue");
                    }
                    return false;
                }
                (*yynode)->arrayValuesSequence = snoc((*yynode)->arrayValuesSequence, __node_229, memoryPool);

                while (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_COMMA, ",");
                        }
                        return false;
                    }
                    yylex();

                    if (yytoken == Token_RPAREN)
                    {
                        break;
                    }
                    StaticArrayPairValueAst *__node_230 = 0;
                    if (!parseStaticArrayPairValue(&__node_230))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::StaticArrayPairValueKind, "staticArrayPairValue");
                        }
                        return false;
                    }
                    (*yynode)->arrayValuesSequence = snoc((*yynode)->arrayValuesSequence, __node_230, memoryPool);

                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStaticVar(StaticVarAst **yynode)
{
    *yynode = create<StaticVarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE)
    {
        VariableIdentifierAst *__node_231 = 0;
        if (!parseVariableIdentifier(&__node_231))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableIdentifierKind, "variableIdentifier");
            }
            return false;
        }
        if (yytoken == Token_ASSIGN)
        {
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            StaticScalarAst *__node_232 = 0;
            if (!parseStaticScalar(&__node_232))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StaticScalarKind, "staticScalar");
                }
                return false;
            }
            (*yynode)->staticScalar = __node_232;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSwitchCaseList(SwitchCaseListAst **yynode)
{
    *yynode = create<SwitchCaseListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON
        || yytoken == Token_LBRACE)
    {
        if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_SEMICOLON)
            {
                if (yytoken != Token_SEMICOLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SEMICOLON, ";");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            CaseListAst *__node_233 = 0;
            if (!parseCaseList(&__node_233))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CaseListKind, "caseList");
                }
                return false;
            }
            (*yynode)->caseList = __node_233;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_SEMICOLON)
            {
                if (yytoken != Token_SEMICOLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SEMICOLON, ";");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            CaseListAst *__node_234 = 0;
            if (!parseCaseList(&__node_234))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CaseListKind, "caseList");
                }
                return false;
            }
            (*yynode)->caseList = __node_234;

            if (yytoken != Token_ENDSWITCH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENDSWITCH, "endswitch");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_235 = 0;
            if (!parseSemicolonOrCloseTag(&__node_235))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTopStatement(TopStatementAst **yynode)
{
    *yynode = create<TopStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_IF
        || yytoken == Token_THROW
        || yytoken == Token_FOREACH
        || yytoken == Token_ISSET
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_TRY
        || yytoken == Token_EMPTY
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_INC
        || yytoken == Token_CLASS
        || yytoken == Token_WHILE
        || yytoken == Token_DECLARE
        || yytoken == Token_HALT_COMPILER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_AT
        || yytoken == Token_DEC
        || yytoken == Token_DNUMBER
        || yytoken == Token_INTERFACE
        || yytoken == Token_ECHO
        || yytoken == Token_INCLUDE
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_CONTINUE
        || yytoken == Token_LNUMBER
        || yytoken == Token_NEW
        || yytoken == Token_PRINT
        || yytoken == Token_LIST
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_DOLLAR
        || yytoken == Token_CLONE
        || yytoken == Token_ARRAY
        || yytoken == Token_EVAL
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_DO
        || yytoken == Token_STRING
        || yytoken == Token_EXIT
        || yytoken == Token_FUNCTION
        || yytoken == Token_CLASS_C
        || yytoken == Token_REQUIRE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_METHOD_C
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_BACKTICK
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_RETURN
        || yytoken == Token_GLOBAL
        || yytoken == Token_FUNC_C
        || yytoken == Token_INT_CAST
        || yytoken == Token_LPAREN
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_ABSTRACT
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_FINAL
        || yytoken == Token_STATIC
        || yytoken == Token_LINE
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_PLUS
        || yytoken == Token_BREAK
        || yytoken == Token_FOR
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_SWITCH
        || yytoken == Token_UNSET
        || yytoken == Token_FILE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_LBRACE
        || yytoken == Token_MINUS)
    {
        if (yytoken == Token_UNSET
            || yytoken == Token_CONTINUE
            || yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_SWITCH
            || yytoken == Token_ARRAY
            || yytoken == Token_FOR
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_BREAK
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_OPEN_TAG
            || yytoken == Token_FOREACH
            || yytoken == Token_REQUIRE
            || yytoken == Token_THROW
            || yytoken == Token_CLASS_C
            || yytoken == Token_IF
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_DNUMBER
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_CLOSE_TAG
            || yytoken == Token_DO
            || yytoken == Token_INLINE_HTML
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_TRY
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_LNUMBER
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_OPEN_TAG_WITH_ECHO
            || yytoken == Token_LPAREN
            || yytoken == Token_DECLARE
            || yytoken == Token_INT_CAST
            || yytoken == Token_WHILE
            || yytoken == Token_FUNC_C
            || yytoken == Token_GLOBAL
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_RETURN
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_ECHO
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_SEMICOLON
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_STATIC
            || yytoken == Token_LIST
            || yytoken == Token_LBRACE
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_NEW
            || yytoken == Token_START_HEREDOC)
        {
            StatementAst *__node_236 = 0;
            if (!parseStatement(&__node_236))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_236;

        }
        else if (yytoken == Token_FUNCTION)
        {
            FunctionDeclarationStatementAst *__node_237 = 0;
            if (!parseFunctionDeclarationStatement(&__node_237))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionDeclarationStatementKind, "functionDeclarationStatement");
                }
                return false;
            }
            (*yynode)->functionDeclaration = __node_237;

        }
        else if (yytoken == Token_FINAL
                 || yytoken == Token_CLASS
                 || yytoken == Token_ABSTRACT)
        {
            ClassDeclarationStatementAst *__node_238 = 0;
            if (!parseClassDeclarationStatement(&__node_238))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassDeclarationStatementKind, "classDeclarationStatement");
                }
                return false;
            }
            (*yynode)->classDeclaration = __node_238;

        }
        else if (yytoken == Token_INTERFACE)
        {
            InterfaceDeclarationStatementAst *__node_239 = 0;
            if (!parseInterfaceDeclarationStatement(&__node_239))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InterfaceDeclarationStatementKind, "interfaceDeclarationStatement");
                }
                return false;
            }
            (*yynode)->interfaceDeclaration = __node_239;

        }
        else if (yytoken == Token_HALT_COMPILER)
        {
            if (yytoken != Token_HALT_COMPILER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_HALT_COMPILER, "halt compiler");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnaryExpression(UnaryExpressionAst **yynode)
{
    *yynode = create<UnaryExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_ARRAY
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_REQUIRE
        || yytoken == Token_CLASS_C
        || yytoken == Token_DNUMBER
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_LNUMBER
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_LPAREN
        || yytoken == Token_INT_CAST
        || yytoken == Token_FUNC_C
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_LIST
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_FILE
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_NEW)
    {
        if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_240 = 0;
            if (!parseUnaryExpression(&__node_240))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_240;

        }
        else if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_241 = 0;
            if (!parseUnaryExpression(&__node_241))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_241;

        }
        else if (yytoken == Token_BANG)
        {
            if (yytoken != Token_BANG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BANG, "!");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_242 = 0;
            if (!parseUnaryExpression(&__node_242))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_242;

        }
        else if (yytoken == Token_TILDE)
        {
            if (yytoken != Token_TILDE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TILDE, "~");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_243 = 0;
            if (!parseUnaryExpression(&__node_243))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_243;

        }
        else if (yytoken == Token_INT_CAST)
        {
            if (yytoken != Token_INT_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INT_CAST, "int cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_244 = 0;
            if (!parseUnaryExpression(&__node_244))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_244;

        }
        else if (yytoken == Token_DOUBLE_CAST)
        {
            if (yytoken != Token_DOUBLE_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_CAST, "double cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_245 = 0;
            if (!parseUnaryExpression(&__node_245))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_245;

        }
        else if (yytoken == Token_STRING_CAST)
        {
            if (yytoken != Token_STRING_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_CAST, "string cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_246 = 0;
            if (!parseUnaryExpression(&__node_246))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_246;

        }
        else if (yytoken == Token_ARRAY_CAST)
        {
            if (yytoken != Token_ARRAY_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ARRAY_CAST, "array cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_247 = 0;
            if (!parseUnaryExpression(&__node_247))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_247;

        }
        else if (yytoken == Token_OBJECT_CAST)
        {
            if (yytoken != Token_OBJECT_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OBJECT_CAST, "object cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_248 = 0;
            if (!parseUnaryExpression(&__node_248))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_248;

        }
        else if (yytoken == Token_BOOL_CAST)
        {
            if (yytoken != Token_BOOL_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOOL_CAST, "bool cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_249 = 0;
            if (!parseUnaryExpression(&__node_249))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_249;

        }
        else if (yytoken == Token_UNSET_CAST)
        {
            if (yytoken != Token_UNSET_CAST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNSET_CAST, "unset cast");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_250 = 0;
            if (!parseUnaryExpression(&__node_250))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_250;

        }
        else if (yytoken == Token_AT)
        {
            if (yytoken != Token_AT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AT, "@");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_251 = 0;
            if (!parseUnaryExpression(&__node_251))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_251;

        }
        else if (yytoken == Token_LIST)
        {
            if (yytoken != Token_LIST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LIST, "list");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            AssignmentListAst *__node_252 = 0;
            if (!parseAssignmentList(&__node_252))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssignmentListKind, "assignmentList");
                }
                return false;
            }
            (*yynode)->assignmentList = __node_252;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_253 = 0;
            if (!parseUnaryExpression(&__node_253))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_253;

        }
        else if (yytoken == Token_EXIT)
        {
            if (yytoken != Token_EXIT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXIT, "exit");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LPAREN)
            {
                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_STRING_VARNAME
                    || yytoken == Token_DOUBLE_QUOTE
                    || yytoken == Token_EVAL
                    || yytoken == Token_ARRAY
                    || yytoken == Token_ARRAY_CAST
                    || yytoken == Token_CLONE
                    || yytoken == Token_INC
                    || yytoken == Token_ISSET
                    || yytoken == Token_REQUIRE
                    || yytoken == Token_CLASS_C
                    || yytoken == Token_DNUMBER
                    || yytoken == Token_OBJECT_CAST
                    || yytoken == Token_EXIT
                    || yytoken == Token_BACKTICK
                    || yytoken == Token_DEC
                    || yytoken == Token_EMPTY
                    || yytoken == Token_REQUIRE_ONCE
                    || yytoken == Token_METHOD_C
                    || yytoken == Token_AT
                    || yytoken == Token_LNUMBER
                    || yytoken == Token_BOOL_CAST
                    || yytoken == Token_TILDE
                    || yytoken == Token_BANG
                    || yytoken == Token_LPAREN
                    || yytoken == Token_INT_CAST
                    || yytoken == Token_FUNC_C
                    || yytoken == Token_PLUS
                    || yytoken == Token_UNSET_CAST
                    || yytoken == Token_INCLUDE
                    || yytoken == Token_DOLLAR
                    || yytoken == Token_DOUBLE_CAST
                    || yytoken == Token_CONSTANT_ENCAPSED_STRING
                    || yytoken == Token_LINE
                    || yytoken == Token_MINUS
                    || yytoken == Token_STRING
                    || yytoken == Token_INCLUDE_ONCE
                    || yytoken == Token_LIST
                    || yytoken == Token_STRING_CAST
                    || yytoken == Token_VARIABLE
                    || yytoken == Token_PRINT
                    || yytoken == Token_FILE
                    || yytoken == Token_START_HEREDOC
                    || yytoken == Token_NEW)
                {
                    ExprAst *__node_254 = 0;
                    if (!parseExpr(&__node_254))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ExprKind, "expr");
                        }
                        return false;
                    }
                    (*yynode)->expression = __node_254;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_EVAL)
        {
            if (yytoken != Token_EVAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EVAL, "eval");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_255 = 0;
            if (!parseExpr(&__node_255))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expression = __node_255;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INCLUDE)
        {
            if (yytoken != Token_INCLUDE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INCLUDE, "include");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_256 = 0;
            if (!parseUnaryExpression(&__node_256))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_256;

        }
        else if (yytoken == Token_INCLUDE_ONCE)
        {
            if (yytoken != Token_INCLUDE_ONCE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INCLUDE_ONCE, "include_once");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_257 = 0;
            if (!parseUnaryExpression(&__node_257))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_257;

        }
        else if (yytoken == Token_REQUIRE)
        {
            if (yytoken != Token_REQUIRE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REQUIRE, "require");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_258 = 0;
            if (!parseUnaryExpression(&__node_258))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_258;

        }
        else if (yytoken == Token_REQUIRE_ONCE)
        {
            if (yytoken != Token_REQUIRE_ONCE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REQUIRE_ONCE, "require_once");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_259 = 0;
            if (!parseUnaryExpression(&__node_259))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_259;

        }
        else if (yytoken == Token_DEC
                 || yytoken == Token_STRING
                 || yytoken == Token_DNUMBER
                 || yytoken == Token_CONSTANT_ENCAPSED_STRING
                 || yytoken == Token_FILE
                 || yytoken == Token_METHOD_C
                 || yytoken == Token_DOLLAR
                 || yytoken == Token_EMPTY
                 || yytoken == Token_START_HEREDOC
                 || yytoken == Token_STRING_VARNAME
                 || yytoken == Token_CLONE
                 || yytoken == Token_LNUMBER
                 || yytoken == Token_VARIABLE
                 || yytoken == Token_NEW
                 || yytoken == Token_FUNC_C
                 || yytoken == Token_ARRAY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_INC
                 || yytoken == Token_DOUBLE_QUOTE
                 || yytoken == Token_LINE
                 || yytoken == Token_CLASS_C
                 || yytoken == Token_BACKTICK
                 || yytoken == Token_ISSET)
        {
            UnaryExpressionNotPlusminusAst *__node_260 = 0;
            if (!parseUnaryExpressionNotPlusminus(&__node_260))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionNotPlusminusKind, "unaryExpressionNotPlusminus");
                }
                return false;
            }
            (*yynode)->unaryExpressionNotPlusminus = __node_260;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnaryExpressionNotPlusminus(UnaryExpressionNotPlusminusAst **yynode)
{
    *yynode = create<UnaryExpressionNotPlusminusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DEC
        || yytoken == Token_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_FILE
        || yytoken == Token_METHOD_C
        || yytoken == Token_DOLLAR
        || yytoken == Token_EMPTY
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_CLONE
        || yytoken == Token_LNUMBER
        || yytoken == Token_VARIABLE
        || yytoken == Token_NEW
        || yytoken == Token_FUNC_C
        || yytoken == Token_ARRAY
        || yytoken == Token_LPAREN
        || yytoken == Token_INC
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_LINE
        || yytoken == Token_CLASS_C
        || yytoken == Token_BACKTICK
        || yytoken == Token_ISSET)
    {
        while (yytoken == Token_INC
               || yytoken == Token_DEC)
        {
            PostprefixOperatorAst *__node_261 = 0;
            if (!parsePostprefixOperator(&__node_261))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PostprefixOperatorKind, "postprefixOperator");
                }
                return false;
            }
            (*yynode)->prefixOperatorSequence = snoc((*yynode)->prefixOperatorSequence, __node_261, memoryPool);

        }
        VarExpressionAst *__node_262 = 0;
        if (!parseVarExpression(&__node_262))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VarExpressionKind, "varExpression");
            }
            return false;
        }
        (*yynode)->varExpression = __node_262;

        while (yytoken == Token_INC
               || yytoken == Token_DEC)
        {
            PostprefixOperatorAst *__node_263 = 0;
            if (!parsePostprefixOperator(&__node_263))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PostprefixOperatorKind, "postprefixOperator");
                }
                return false;
            }
            (*yynode)->postfixOperatorSequence = snoc((*yynode)->postfixOperatorSequence, __node_263, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVarExpression(VarExpressionAst **yynode)
{
    *yynode = create<VarExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_FILE
        || yytoken == Token_METHOD_C
        || yytoken == Token_DOLLAR
        || yytoken == Token_EMPTY
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_CLONE
        || yytoken == Token_LNUMBER
        || yytoken == Token_VARIABLE
        || yytoken == Token_NEW
        || yytoken == Token_FUNC_C
        || yytoken == Token_ARRAY
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_LINE
        || yytoken == Token_CLASS_C
        || yytoken == Token_BACKTICK
        || yytoken == Token_ISSET)
    {
        if ((yytoken == Token_VARIABLE
             || yytoken == Token_DOLLAR
             || yytoken == Token_STRING) && ( m_state.varExpressionState == OnlyVariable ))
        {
            m_state.varExpressionState = Normal;
            VariableAst *__node_264 = 0;
            if (!parseVariable(&__node_264))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->variable = __node_264;

        }
        else if ((yytoken == Token_NEW) && ( m_state.varExpressionState == OnlyNewObject ))
        {
            m_state.varExpressionState = Normal;
            VarExpressionNewObjectAst *__node_265 = 0;
            if (!parseVarExpressionNewObject(&__node_265))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VarExpressionNewObjectKind, "varExpressionNewObject");
                }
                return false;
            }
            (*yynode)->newObject = __node_265;

        }
        else if (yytoken == Token_STRING
                 || yytoken == Token_DNUMBER
                 || yytoken == Token_CONSTANT_ENCAPSED_STRING
                 || yytoken == Token_FILE
                 || yytoken == Token_METHOD_C
                 || yytoken == Token_DOLLAR
                 || yytoken == Token_EMPTY
                 || yytoken == Token_START_HEREDOC
                 || yytoken == Token_STRING_VARNAME
                 || yytoken == Token_CLONE
                 || yytoken == Token_LNUMBER
                 || yytoken == Token_VARIABLE
                 || yytoken == Token_NEW
                 || yytoken == Token_FUNC_C
                 || yytoken == Token_ARRAY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_DOUBLE_QUOTE
                 || yytoken == Token_LINE
                 || yytoken == Token_CLASS_C
                 || yytoken == Token_BACKTICK
                 || yytoken == Token_ISSET)
        {
            VarExpressionNormalAst *__node_266 = 0;
            if (!parseVarExpressionNormal(&__node_266))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VarExpressionNormalKind, "varExpressionNormal");
                }
                return false;
            }
            (*yynode)->varExpressionNormal = __node_266;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVarExpressionNewObject(VarExpressionNewObjectAst **yynode)
{
    *yynode = create<VarExpressionNewObjectAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NEW)
    {
        if (yytoken != Token_NEW)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_NEW, "new");
            }
            return false;
        }
        yylex();

        ClassNameReferenceAst *__node_267 = 0;
        if (!parseClassNameReference(&__node_267))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassNameReferenceKind, "classNameReference");
            }
            return false;
        }
        (*yynode)->className = __node_267;

        CtorArgumentsAst *__node_268 = 0;
        if (!parseCtorArguments(&__node_268))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::CtorArgumentsKind, "ctorArguments");
            }
            return false;
        }
        (*yynode)->ctor = __node_268;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVarExpressionNormal(VarExpressionNormalAst **yynode)
{
    *yynode = create<VarExpressionNormalAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRING
        || yytoken == Token_DNUMBER
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_FILE
        || yytoken == Token_METHOD_C
        || yytoken == Token_DOLLAR
        || yytoken == Token_EMPTY
        || yytoken == Token_START_HEREDOC
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_CLONE
        || yytoken == Token_LNUMBER
        || yytoken == Token_VARIABLE
        || yytoken == Token_NEW
        || yytoken == Token_FUNC_C
        || yytoken == Token_ARRAY
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_LINE
        || yytoken == Token_CLASS_C
        || yytoken == Token_BACKTICK
        || yytoken == Token_ISSET)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_269 = 0;
            if (!parseExpr(&__node_269))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expression = __node_269;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BACKTICK)
        {
            if (yytoken != Token_BACKTICK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BACKTICK, "`");
                }
                return false;
            }
            yylex();

            EncapsListAst *__node_270 = 0;
            if (!parseEncapsList(&__node_270))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EncapsListKind, "encapsList");
                }
                return false;
            }
            (*yynode)->encapsList = __node_270;

            if (yytoken != Token_BACKTICK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BACKTICK, "`");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VARIABLE
                 || yytoken == Token_DOLLAR
                 || yytoken == Token_LNUMBER
                 || yytoken == Token_CLASS_C
                 || yytoken == Token_STRING_VARNAME
                 || yytoken == Token_LINE
                 || yytoken == Token_CONSTANT_ENCAPSED_STRING
                 || yytoken == Token_DNUMBER
                 || yytoken == Token_STRING
                 || yytoken == Token_FUNC_C
                 || yytoken == Token_START_HEREDOC
                 || yytoken == Token_METHOD_C
                 || yytoken == Token_DOUBLE_QUOTE
                 || yytoken == Token_FILE)
        {
            bool blockErrors_3 = blockErrors(true);
            qint64 try_startToken_3 = tokenStream->index() - 1;
            ParserState *try_startState_3 = copyCurrentState();
            {
                VariableAst *__node_271 = 0;
                if (!parseVariable(&__node_271))
                {
                    goto __catch_3;
                }
                (*yynode)->variable = __node_271;

                m_state.varExpressionIsVariable = true;
            }
            blockErrors(blockErrors_3);
            if (try_startState_3)
                delete try_startState_3;

            if (false) // the only way to enter here is using goto
            {
__catch_3:
                if (try_startState_3)
                {
                    restoreState(try_startState_3);
                    delete try_startState_3;
                }
                blockErrors(blockErrors_3);
                rewind(try_startToken_3);

                ScalarAst *__node_272 = 0;
                if (!parseScalar(&__node_272))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ScalarKind, "scalar");
                    }
                    return false;
                }
                (*yynode)->scalar = __node_272;

            }

        }
        else if (yytoken == Token_ARRAY)
        {
            if (yytoken != Token_ARRAY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ARRAY, "array");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_STRING_VARNAME
                || yytoken == Token_DOUBLE_QUOTE
                || yytoken == Token_EVAL
                || yytoken == Token_BIT_AND
                || yytoken == Token_ARRAY
                || yytoken == Token_ARRAY_CAST
                || yytoken == Token_CLONE
                || yytoken == Token_INC
                || yytoken == Token_ISSET
                || yytoken == Token_REQUIRE
                || yytoken == Token_CLASS_C
                || yytoken == Token_DNUMBER
                || yytoken == Token_OBJECT_CAST
                || yytoken == Token_EXIT
                || yytoken == Token_BACKTICK
                || yytoken == Token_DEC
                || yytoken == Token_EMPTY
                || yytoken == Token_REQUIRE_ONCE
                || yytoken == Token_METHOD_C
                || yytoken == Token_AT
                || yytoken == Token_BOOL_CAST
                || yytoken == Token_LNUMBER
                || yytoken == Token_TILDE
                || yytoken == Token_BANG
                || yytoken == Token_LPAREN
                || yytoken == Token_INT_CAST
                || yytoken == Token_FUNC_C
                || yytoken == Token_PLUS
                || yytoken == Token_UNSET_CAST
                || yytoken == Token_INCLUDE
                || yytoken == Token_DOLLAR
                || yytoken == Token_DOUBLE_CAST
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_LINE
                || yytoken == Token_MINUS
                || yytoken == Token_STRING
                || yytoken == Token_INCLUDE_ONCE
                || yytoken == Token_LIST
                || yytoken == Token_STRING_CAST
                || yytoken == Token_VARIABLE
                || yytoken == Token_PRINT
                || yytoken == Token_FILE
                || yytoken == Token_START_HEREDOC
                || yytoken == Token_NEW)
            {
                ArrayPairValueAst *__node_273 = 0;
                if (!parseArrayPairValue(&__node_273))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ArrayPairValueKind, "arrayPairValue");
                    }
                    return false;
                }
                (*yynode)->arrayValuesSequence = snoc((*yynode)->arrayValuesSequence, __node_273, memoryPool);

                while (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_COMMA, ",");
                        }
                        return false;
                    }
                    yylex();

                    if (yytoken == Token_RPAREN)
                    {
                        break;
                    }
                    ArrayPairValueAst *__node_274 = 0;
                    if (!parseArrayPairValue(&__node_274))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ArrayPairValueKind, "arrayPairValue");
                        }
                        return false;
                    }
                    (*yynode)->arrayValuesSequence = snoc((*yynode)->arrayValuesSequence, __node_274, memoryPool);

                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ISSET)
        {
            if (yytoken != Token_ISSET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ISSET, "isset");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            VariableAst *__node_275 = 0;
            if (!parseVariable(&__node_275))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->issetVariableSequence = snoc((*yynode)->issetVariableSequence, __node_275, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                VariableAst *__node_276 = 0;
                if (!parseVariable(&__node_276))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::VariableKind, "variable");
                    }
                    return false;
                }
                (*yynode)->issetVariableSequence = snoc((*yynode)->issetVariableSequence, __node_276, memoryPool);

            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_EMPTY)
        {
            if (yytoken != Token_EMPTY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EMPTY, "empty");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            VariableAst *__node_277 = 0;
            if (!parseVariable(&__node_277))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
            (*yynode)->emptyVarialbe = __node_277;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_NEW)
        {
            VarExpressionNewObjectAst *__node_278 = 0;
            if (!parseVarExpressionNewObject(&__node_278))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VarExpressionNewObjectKind, "varExpressionNewObject");
                }
                return false;
            }
            (*yynode)->newObject = __node_278;

        }
        else if (yytoken == Token_CLONE)
        {
            if (yytoken != Token_CLONE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLONE, "clone");
                }
                return false;
            }
            yylex();

            VarExpressionNormalAst *__node_279 = 0;
            if (!parseVarExpressionNormal(&__node_279))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VarExpressionNormalKind, "varExpressionNormal");
                }
                return false;
            }
            (*yynode)->cloneCar = __node_279;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariable(VariableAst **yynode)
{
    *yynode = create<VariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR
        || yytoken == Token_STRING)
    {
        BaseVariableWithFunctionCallsAst *__node_280 = 0;
        if (!parseBaseVariableWithFunctionCalls(&__node_280))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BaseVariableWithFunctionCallsKind, "baseVariableWithFunctionCalls");
            }
            return false;
        }
        (*yynode)->var = __node_280;

        while (yytoken == Token_OBJECT_OPERATOR)
        {
            VariablePropertyAst *__node_281 = 0;
            if (!parseVariableProperty(&__node_281))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariablePropertyKind, "variableProperty");
                }
                return false;
            }
            (*yynode)->variablePropertiesSequence = snoc((*yynode)->variablePropertiesSequence, __node_281, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableIdentifier(VariableIdentifierAst **yynode)
{
    *yynode = create<VariableIdentifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->variable = -1;

    if (yytoken == Token_VARIABLE)
    {
        if (yytoken != Token_VARIABLE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_VARIABLE, "variable");
            }
            return false;
        }
        (*yynode)->variable = tokenStream->index() - 1;
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableName(VariableNameAst **yynode)
{
    *yynode = create<VariableNameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE
        || yytoken == Token_STRING)
    {
        if (yytoken == Token_STRING)
        {
            IdentifierAst *__node_282 = 0;
            if (!parseIdentifier(&__node_282))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->name = __node_282;

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            ExprAst *__node_283 = 0;
            if (!parseExpr(&__node_283))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_283;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableProperty(VariablePropertyAst **yynode)
{
    *yynode = create<VariablePropertyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->isFunctionCall = -1;

    if (yytoken == Token_OBJECT_OPERATOR)
    {
        if (yytoken != Token_OBJECT_OPERATOR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_OBJECT_OPERATOR, "->");
            }
            return false;
        }
        yylex();

        ObjectPropertyAst *__node_284 = 0;
        if (!parseObjectProperty(&__node_284))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ObjectPropertyKind, "objectProperty");
            }
            return false;
        }
        (*yynode)->objectProperty = __node_284;

        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            (*yynode)->isFunctionCall = tokenStream->index() - 1;
            yylex();

            if (yytoken == Token_STRING_VARNAME
                || yytoken == Token_DOUBLE_QUOTE
                || yytoken == Token_EVAL
                || yytoken == Token_BIT_AND
                || yytoken == Token_ARRAY
                || yytoken == Token_ARRAY_CAST
                || yytoken == Token_CLONE
                || yytoken == Token_INC
                || yytoken == Token_ISSET
                || yytoken == Token_REQUIRE
                || yytoken == Token_CLASS_C
                || yytoken == Token_DNUMBER
                || yytoken == Token_OBJECT_CAST
                || yytoken == Token_EXIT
                || yytoken == Token_BACKTICK
                || yytoken == Token_DEC
                || yytoken == Token_EMPTY
                || yytoken == Token_REQUIRE_ONCE
                || yytoken == Token_METHOD_C
                || yytoken == Token_AT
                || yytoken == Token_BOOL_CAST
                || yytoken == Token_LNUMBER
                || yytoken == Token_TILDE
                || yytoken == Token_BANG
                || yytoken == Token_LPAREN
                || yytoken == Token_INT_CAST
                || yytoken == Token_FUNC_C
                || yytoken == Token_PLUS
                || yytoken == Token_UNSET_CAST
                || yytoken == Token_INCLUDE
                || yytoken == Token_DOLLAR
                || yytoken == Token_DOUBLE_CAST
                || yytoken == Token_CONSTANT_ENCAPSED_STRING
                || yytoken == Token_LINE
                || yytoken == Token_MINUS
                || yytoken == Token_STRING
                || yytoken == Token_INCLUDE_ONCE
                || yytoken == Token_LIST
                || yytoken == Token_STRING_CAST
                || yytoken == Token_VARIABLE
                || yytoken == Token_PRINT
                || yytoken == Token_FILE
                || yytoken == Token_START_HEREDOC
                || yytoken == Token_NEW)
            {
                FunctionCallParameterListAst *__node_285 = 0;
                if (!parseFunctionCallParameterList(&__node_285))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FunctionCallParameterListKind, "functionCallParameterList");
                    }
                    return false;
                }
                (*yynode)->parameterList = __node_285;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableWithoutObjects(VariableWithoutObjectsAst **yynode)
{
    *yynode = create<VariableWithoutObjectsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE
        || yytoken == Token_DOLLAR)
    {
        CompoundVariableWithSimpleIndirectReferenceAst *__node_286 = 0;
        if (!parseCompoundVariableWithSimpleIndirectReference(&__node_286))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::CompoundVariableWithSimpleIndirectReferenceKind, "compoundVariableWithSimpleIndirectReference");
            }
            return false;
        }
        (*yynode)->variable = __node_286;

        while (yytoken == Token_LBRACE
               || yytoken == Token_LBRACKET)
        {
            DimListItemAst *__node_287 = 0;
            if (!parseDimListItem(&__node_287))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DimListItemKind, "dimListItem");
                }
                return false;
            }
            (*yynode)->offsetItemsSequence = snoc((*yynode)->offsetItemsSequence, __node_287, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseWhileStatement(WhileStatementAst **yynode)
{
    *yynode = create<WhileStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNSET
        || yytoken == Token_CONTINUE
        || yytoken == Token_STRING_VARNAME
        || yytoken == Token_DOUBLE_QUOTE
        || yytoken == Token_EVAL
        || yytoken == Token_SWITCH
        || yytoken == Token_ARRAY
        || yytoken == Token_FOR
        || yytoken == Token_ARRAY_CAST
        || yytoken == Token_BREAK
        || yytoken == Token_CLONE
        || yytoken == Token_INC
        || yytoken == Token_ISSET
        || yytoken == Token_OPEN_TAG
        || yytoken == Token_FOREACH
        || yytoken == Token_REQUIRE
        || yytoken == Token_THROW
        || yytoken == Token_CLASS_C
        || yytoken == Token_IF
        || yytoken == Token_OBJECT_CAST
        || yytoken == Token_DNUMBER
        || yytoken == Token_EXIT
        || yytoken == Token_BACKTICK
        || yytoken == Token_DEC
        || yytoken == Token_EMPTY
        || yytoken == Token_CLOSE_TAG
        || yytoken == Token_DO
        || yytoken == Token_INLINE_HTML
        || yytoken == Token_REQUIRE_ONCE
        || yytoken == Token_TRY
        || yytoken == Token_METHOD_C
        || yytoken == Token_AT
        || yytoken == Token_BOOL_CAST
        || yytoken == Token_LNUMBER
        || yytoken == Token_TILDE
        || yytoken == Token_BANG
        || yytoken == Token_OPEN_TAG_WITH_ECHO
        || yytoken == Token_LPAREN
        || yytoken == Token_DECLARE
        || yytoken == Token_INT_CAST
        || yytoken == Token_WHILE
        || yytoken == Token_FUNC_C
        || yytoken == Token_GLOBAL
        || yytoken == Token_PLUS
        || yytoken == Token_UNSET_CAST
        || yytoken == Token_INCLUDE
        || yytoken == Token_DOLLAR
        || yytoken == Token_RETURN
        || yytoken == Token_DOUBLE_CAST
        || yytoken == Token_CONSTANT_ENCAPSED_STRING
        || yytoken == Token_ECHO
        || yytoken == Token_LINE
        || yytoken == Token_MINUS
        || yytoken == Token_SEMICOLON
        || yytoken == Token_STRING
        || yytoken == Token_INCLUDE_ONCE
        || yytoken == Token_STATIC
        || yytoken == Token_COLON
        || yytoken == Token_LIST
        || yytoken == Token_LBRACE
        || yytoken == Token_STRING_CAST
        || yytoken == Token_VARIABLE
        || yytoken == Token_PRINT
        || yytoken == Token_FILE
        || yytoken == Token_NEW
        || yytoken == Token_START_HEREDOC)
    {
        if (yytoken == Token_UNSET
            || yytoken == Token_CONTINUE
            || yytoken == Token_STRING_VARNAME
            || yytoken == Token_DOUBLE_QUOTE
            || yytoken == Token_EVAL
            || yytoken == Token_SWITCH
            || yytoken == Token_ARRAY
            || yytoken == Token_FOR
            || yytoken == Token_ARRAY_CAST
            || yytoken == Token_BREAK
            || yytoken == Token_CLONE
            || yytoken == Token_INC
            || yytoken == Token_ISSET
            || yytoken == Token_OPEN_TAG
            || yytoken == Token_FOREACH
            || yytoken == Token_REQUIRE
            || yytoken == Token_THROW
            || yytoken == Token_CLASS_C
            || yytoken == Token_IF
            || yytoken == Token_OBJECT_CAST
            || yytoken == Token_DNUMBER
            || yytoken == Token_EXIT
            || yytoken == Token_BACKTICK
            || yytoken == Token_DEC
            || yytoken == Token_EMPTY
            || yytoken == Token_CLOSE_TAG
            || yytoken == Token_DO
            || yytoken == Token_INLINE_HTML
            || yytoken == Token_REQUIRE_ONCE
            || yytoken == Token_TRY
            || yytoken == Token_METHOD_C
            || yytoken == Token_AT
            || yytoken == Token_BOOL_CAST
            || yytoken == Token_LNUMBER
            || yytoken == Token_TILDE
            || yytoken == Token_BANG
            || yytoken == Token_OPEN_TAG_WITH_ECHO
            || yytoken == Token_LPAREN
            || yytoken == Token_DECLARE
            || yytoken == Token_INT_CAST
            || yytoken == Token_WHILE
            || yytoken == Token_FUNC_C
            || yytoken == Token_GLOBAL
            || yytoken == Token_PLUS
            || yytoken == Token_UNSET_CAST
            || yytoken == Token_INCLUDE
            || yytoken == Token_DOLLAR
            || yytoken == Token_RETURN
            || yytoken == Token_DOUBLE_CAST
            || yytoken == Token_CONSTANT_ENCAPSED_STRING
            || yytoken == Token_ECHO
            || yytoken == Token_LINE
            || yytoken == Token_MINUS
            || yytoken == Token_SEMICOLON
            || yytoken == Token_STRING
            || yytoken == Token_INCLUDE_ONCE
            || yytoken == Token_STATIC
            || yytoken == Token_LIST
            || yytoken == Token_LBRACE
            || yytoken == Token_STRING_CAST
            || yytoken == Token_VARIABLE
            || yytoken == Token_PRINT
            || yytoken == Token_FILE
            || yytoken == Token_NEW
            || yytoken == Token_START_HEREDOC)
        {
            StatementAst *__node_288 = 0;
            if (!parseStatement(&__node_288))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_288;

        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            InnerStatementListAst *__node_289 = 0;
            if (!parseInnerStatementList(&__node_289))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InnerStatementListKind, "innerStatementList");
                }
                return false;
            }
            (*yynode)->statements = __node_289;

            if (yytoken != Token_ENDWHILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENDWHILE, "endwhile");
                }
                return false;
            }
            yylex();

            SemicolonOrCloseTagAst *__node_290 = 0;
            if (!parseSemicolonOrCloseTag(&__node_290))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SemicolonOrCloseTagKind, "semicolonOrCloseTag");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace Php

