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

namespace Php
{

QString tokenText(int token)
{
    if (token ==  Parser::Token_INLINE_HTML) {
        return " T_INLINE_HTML" ;
    } else if (token ==  Parser::Token_OPEN_TAG) {
        return " T_OPEN_TAG" ;
    } else if (token ==  Parser::Token_CLOSE_TAG) {
        return " T_CLOSE_TAG" ;
    } else if (token ==  Parser::Token_ECHO) {
        return " T_ECHO" ;
    } else if (token ==  Parser::Token_WHITESPACE) {
        return " T_WHITESPACE" ;
    } else if (token ==  Parser::Token_CONSTANT_ENCAPSED_STRING) {
        return " T_CONSTANT_ENCAPSED_STRING" ;
    } else if (token ==  Parser::Token_SEMICOLON) {
        return " ;" ;
    } else if (token ==  Parser::Token_VARIABLE) {
        return " T_VARIABLE" ;
    } else if (token ==  Parser::Token_DOUBLE_QUOTE) {
        return " \"" ;
    } else if (token ==  Parser::Token_ENCAPSED_AND_WHITESPACE) {
        return " T_ENCAPSED_AND_WHITESPACE" ;
    } else if (token ==  Parser::Token_OBJECT_OPERATOR) {
        return " T_OBJECT_OPERATOR" ;
    } else if (token ==  Parser::Token_LBRACKET) {
        return " [" ;
    } else if (token ==  Parser::Token_RBRACKET) {
        return " ]" ;
    } else if (token ==  Parser::Token_NUM_STRING) {
        return " T_NUM_STRING" ;
    } else if (token ==  Parser::Token_STRING) {
        return " T_STRING" ;
    } else if (token ==  Parser::Token_ASSIGN) {
        return " =" ;
    } else if (token ==  Parser::Token_DNUMBER) {
        return " T_DNUMBER" ;
    } else if (token ==  Parser::Token_LNUMBER) {
        return " T_LNUMBER" ;
    } else if (token ==  Parser::Token_PLUS) {
        return " +" ;
    } else if (token ==  Parser::Token_MINUS) {
        return " -" ;
    } else if (token ==  Parser::Token_CONCAT) {
        return " ." ;
    } else if (token ==  Parser::Token_INC) {
        return " T_INC" ;
    } else if (token ==  Parser::Token_DEC) {
        return " T_DEC" ;
    } else if (token ==  Parser::Token_IS_EQUAL) {
        return " T_IS_EQUAL" ;
    } else if (token ==  Parser::Token_IS_NOT_EQUAL) {
        return " T_IS_NOT_EQUAL" ;
    } else if (token ==  Parser::Token_IS_IDENTICAL) {
        return " T_IS_IDENTICAL" ;
    } else if (token ==  Parser::Token_IS_NOT_IDENTICAL) {
        return " T_IS_NOT_IDENTICAL" ;
    } else if (token ==  Parser::Token_IS_SMALLER) {
        return " <" ;
    } else if (token ==  Parser::Token_IS_GREATER) {
        return " >" ;
    } else if (token ==  Parser::Token_IS_SMALLER_OR_EQUAL) {
        return " T_IS_SMALLER_OR_EQUAL" ;
    } else if (token ==  Parser::Token_IS_GREATER_OR_EQUAL) {
        return " T_IS_GREATER_OR_EQUAL" ;
    } else if (token ==  Parser::Token_BOOLEAN_OR) {
        return " T_BOOLEAN_OR" ;
    } else if (token ==  Parser::Token_BOOLEAN_AND) {
        return " T_BOOLEAN_AND" ;
    } else if (token ==  Parser::Token_PLUS_ASSIGN) {
        return " T_PLUS_EQUAL" ;
    } else if (token ==  Parser::Token_MINUS_ASSIGN) {
        return " T_MINUS_EQUAL" ;
    } else if (token ==  Parser::Token_MUL_ASSIGN) {
        return " T_MUL_EQUAL" ;
    } else if (token ==  Parser::Token_DIV_ASSIGN) {
        return " T_DIV_EQUAL" ;
    } else if (token ==  Parser::Token_CONCAT_ASSIGN) {
        return " T_CONCAT_EQUAL" ;
    } else if (token ==  Parser::Token_MOD_ASSIGN) {
        return " T_MOD_EQUAL" ;
    } else if (token ==  Parser::Token_AND_ASSIGN) {
        return " T_AND_EQUAL" ;
    } else if (token ==  Parser::Token_OR_ASSIGN) {
        return " T_OR_EQUAL" ;
    } else if (token ==  Parser::Token_XOR_ASSIGN) {
        return " T_XOR_EQUAL" ;
    } else if (token ==  Parser::Token_SL_ASSIGN) {
        return " T_SL_EQUAL" ;
    } else if (token ==  Parser::Token_SR_ASSIGN) {
        return " T_SR_EQUAL" ;
    } else if (token ==  Parser::Token_BANG) {
        return " !" ;
    } else if (token ==  Parser::Token_QUESTION) {
        return " ?" ;
    } else if (token ==  Parser::Token_COLON) {
        return " :" ;
    } else if (token ==  Parser::Token_BIT_AND) {
        return " &" ;
    } else if (token ==  Parser::Token_BIT_OR) {
        return " |" ;
    } else if (token ==  Parser::Token_BIT_XOR) {
        return " ^" ;
    } else if (token ==  Parser::Token_SL) {
        return " T_SL" ;
    } else if (token ==  Parser::Token_SR) {
        return " T_SR" ;
    } else if (token ==  Parser::Token_MUL) {
        return " *" ;
    } else if (token ==  Parser::Token_DIV) {
        return " /" ;
    } else if (token ==  Parser::Token_MOD) {
        return " %" ;
    } else if (token ==  Parser::Token_TILDE) {
        return " ~" ;
    } else if (token ==  Parser::Token_LPAREN) {
        return " (" ;
    } else if (token ==  Parser::Token_RPAREN) {
        return " )" ;
    } else if (token ==  Parser::Token_LBRACE) {
        return " {" ;
    } else if (token ==  Parser::Token_RBRACE) {
        return " }" ;
    } else if (token ==  Parser::Token_COMMA) {
        return " ," ;
    } else if (token ==  Parser::Token_AT) {
        return " @" ;
    } else if (token ==  Parser::Token_INCLUDE) {
        return " T_INCLUDE" ;
    } else if (token ==  Parser::Token_INCLUDE_ONCE) {
        return " T_INCLUDE_ONCE" ;
    } else if (token ==  Parser::Token_EVAL) {
        return " T_EVAL" ;
    } else if (token ==  Parser::Token_REQUIRE) {
        return " T_REQUIRE" ;
    } else if (token ==  Parser::Token_REQUIRE_ONCE) {
        return " T_REQUIRE_ONCE" ;
    } else if (token ==  Parser::Token_PRINT) {
        return " T_PRINT" ;
    } else if (token ==  Parser::Token_ABSTRACT) {
        return " T_ABSTRACT" ;
    } else if (token ==  Parser::Token_BREAK) {
        return " T_BREAK" ;
    } else if (token ==  Parser::Token_CASE) {
        return " T_CASE" ;
    } else if (token ==  Parser::Token_CATCH) {
        return " T_CATCH" ;
    } else if (token ==  Parser::Token_CLASS) {
        return " T_CLASS" ;
    } else if (token ==  Parser::Token_CONST) {
        return " T_CONST" ;
    } else if (token ==  Parser::Token_CONTINUE) {
        return " T_CONTINUE" ;
    } else if (token ==  Parser::Token_DEFAULT) {
        return " T_DEFAULT" ;
    } else if (token ==  Parser::Token_DO) {
        return " T_DO" ;
    } else if (token ==  Parser::Token_ELSE) {
        return " T_ELSE" ;
    } else if (token ==  Parser::Token_EXTENDS) {
        return " T_EXTENDS" ;
    } else if (token ==  Parser::Token_FINAL) {
        return " T_FINAL" ;
    } else if (token ==  Parser::Token_FOR) {
        return " T_FOR" ;
    } else if (token ==  Parser::Token_IF) {
        return " T_IF" ;
    } else if (token ==  Parser::Token_IMPLEMENTS) {
        return " T_IMPLEMENTS" ;
    } else if (token ==  Parser::Token_INSTANCEOF) {
        return " T_INSTANCEOF" ;
    } else if (token ==  Parser::Token_INTERFACE) {
        return " T_INTERFACE" ;
    } else if (token ==  Parser::Token_NEW) {
        return " T_NEW" ;
    } else if (token ==  Parser::Token_PRIVATE) {
        return " T_PRIVATE" ;
    } else if (token ==  Parser::Token_PROTECTED) {
        return " T_PROTECTED" ;
    } else if (token ==  Parser::Token_PUBLIC) {
        return " T_PUBLIC" ;
    } else if (token ==  Parser::Token_RETURN) {
        return " T_RETURN" ;
    } else if (token ==  Parser::Token_STATIC) {
        return " T_STATIC" ;
    } else if (token ==  Parser::Token_SWITCH) {
        return " T_SWITCH" ;
    } else if (token ==  Parser::Token_THROW) {
        return " T_THROW" ;
    } else if (token ==  Parser::Token_TRY) {
        return " T_TRY" ;
    } else if (token ==  Parser::Token_WHILE) {
        return " T_WHILE" ;
    } else if (token ==  Parser::Token_INT_CAST) {
        return " T_INT_CAST" ;
    } else if (token ==  Parser::Token_DOUBLE_CAST) {
        return " T_DOUBLE_CAST" ;
    } else if (token ==  Parser::Token_STRING_CAST) {
        return " T_STRING_CAST" ;
    } else if (token ==  Parser::Token_ARRAY_CAST) {
        return " T_ARRAY_CAST" ;
    } else if (token ==  Parser::Token_OBJECT_CAST) {
        return " T_OBJECT_CAST" ;
    } else if (token ==  Parser::Token_BOOL_CAST) {
        return " T_BOOL_CAST" ;
    } else if (token ==  Parser::Token_UNSET_CAST) {
        return " T_UNSET_CAST" ;
    } else if (token ==  Parser::Token_CLONE) {
        return " T_CLONE" ;
    } else if (token ==  Parser::Token_EXIT) {
        return " T_EXIT" ;
    } else if (token ==  Parser::Token_ELSEIF) {
        return " T_ELSEIF" ;
    } else if (token ==  Parser::Token_ENDIF) {
        return " T_ENDIF" ;
    } else if (token ==  Parser::Token_ENDWHILE) {
        return " T_ENDWHILE" ;
    } else if (token ==  Parser::Token_ENDFOR) {
        return " T_ENDFOR" ;
    } else if (token ==  Parser::Token_FOREACH) {
        return " T_FOREACH" ;
    } else if (token ==  Parser::Token_ENDFOREACH) {
        return " T_ENDFOREACH" ;
    } else if (token ==  Parser::Token_DECLARE) {
        return " T_DECLARE" ;
    } else if (token ==  Parser::Token_ENDDECLARE) {
        return " T_ENDDECLARE" ;
    } else if (token ==  Parser::Token_AS) {
        return " T_AS" ;
    } else if (token ==  Parser::Token_ENDSWITCH) {
        return " T_ENDSWITCH" ;
    } else if (token ==  Parser::Token_FUNCTION) {
        return " T_FUNCTION" ;
    } else if (token ==  Parser::Token_USE) {
        return " T_USE" ;
    } else if (token ==  Parser::Token_GLOBAL) {
        return " T_GLOBAL" ;
    } else if (token ==  Parser::Token_VAR) {
        return " T_VAR" ;
    } else if (token ==  Parser::Token_UNSET) {
        return " T_UNSET" ;
    } else if (token ==  Parser::Token_ISSET) {
        return " T_ISSET" ;
    } else if (token ==  Parser::Token_ISSET) {
        return " T_ISSET" ;
    } else if (token ==  Parser::Token_EMPTY) {
        return " T_EMPTY" ;
    } else if (token ==  Parser::Token_HALT_COMPILER) {
        return " T_HALT_COMPILER" ;
    } else if (token ==  Parser::Token_DOUBLE_ARROW) {
        return " T_DOUBLE_ARROW" ;
    } else if (token ==  Parser::Token_LIST) {
        return " T_LIST" ;
    } else if (token ==  Parser::Token_ARRAY) {
        return " T_ARRAY" ;
    } else if (token ==  Parser::Token_CLASS_C) {
        return " T_CLASS_C" ;
    } else if (token ==  Parser::Token_METHOD_C) {
        return " T_METHOD_C" ;
    } else if (token ==  Parser::Token_FUNC_C) {
        return " T_FUNC_C" ;
    } else if (token ==  Parser::Token_LINE) {
        return " T_LINE" ;
    } else if (token ==  Parser::Token_FILE) {
        return " T_FILE" ;
    } else if (token ==  Parser::Token_COMMENT) {
        return " T_COMMENT" ;
    } else if (token ==  Parser::Token_DOC_COMMENT) {
        return " T_DOC_COMMENT" ;
    } else if (token ==  Parser::Token_PAAMAYIM_NEKUDOTAYIM) {
        return " T_DOUBLE_COLON" ;
    } else if (token ==  Parser::Token_OPEN_TAG_WITH_ECHO) {
        return " T_OPEN_TAG_WITH_ECHO" ;
    } else if (token ==  Parser::Token_CURLY_OPEN) {
        return " T_CURLY_OPEN" ;
    } else if (token ==  Parser::Token_STRING_VARNAME) {
        return " T_STRING_VARNAME" ;
    } else if (token ==  Parser::Token_DOLLAR_OPEN_CURLY_BRACES) {
        return " T_DOLLAR_OPEN_CURLY_BRACES" ;
    } else if (token ==  Parser::Token_DOLLAR) {
        return " $" ;
    } else if (token ==  Parser::Token_LOGICAL_XOR) {
        return " T_LOGICAL_XOR" ;
    } else if (token ==  Parser::Token_LOGICAL_AND) {
        return " T_LOGICAL_AND" ;
    } else if (token ==  Parser::Token_LOGICAL_OR) {
        return " T_LOGICAL_OR" ;
    } else if (token ==  Parser::Token_START_HEREDOC) {
        return " T_START_HEREDOC" ;
    } else if (token ==  Parser::Token_END_HEREDOC) {
        return " T_END_HEREDOC" ;
    } else if (token ==  Parser::Token_BACKTICK) {
        return " `" ;
    } else if (token ==  0) {
        return " end of file" ;
    } else {
        return " unknown token";
    }
}

}
