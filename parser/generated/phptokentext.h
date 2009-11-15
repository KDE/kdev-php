// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_TOKEN_TEXT_H_INCLUDED
#define PHP_TOKEN_TEXT_H_INCLUDED

#include "phpparser.h"

namespace Php
{

QString tokenText(int token)
{
    switch (token)
    {
    case Parser::Token_ABSTRACT:
        return "abstract";
    case Parser::Token_AND_ASSIGN:
        return "&=";
    case Parser::Token_ARRAY:
        return "array";
    case Parser::Token_ARRAY_CAST:
        return "array cast";
    case Parser::Token_AS:
        return "as";
    case Parser::Token_ASSIGN:
        return "=";
    case Parser::Token_AT:
        return "@";
    case Parser::Token_BACKTICK:
        return "`";
    case Parser::Token_BANG:
        return "!";
    case Parser::Token_BIT_AND:
        return "&";
    case Parser::Token_BIT_OR:
        return "|";
    case Parser::Token_BIT_XOR:
        return "^";
    case Parser::Token_BOOLEAN_AND:
        return "&&";
    case Parser::Token_BOOLEAN_OR:
        return "||";
    case Parser::Token_BOOL_CAST:
        return "bool cast";
    case Parser::Token_BREAK:
        return "break";
    case Parser::Token_CASE:
        return "case";
    case Parser::Token_CATCH:
        return "catch";
    case Parser::Token_CLASS:
        return "class";
    case Parser::Token_CLASS_C:
        return "__CLASS__";
    case Parser::Token_CLONE:
        return "clone";
    case Parser::Token_CLOSE_TAG:
        return "?>";
    case Parser::Token_COLON:
        return ":";
    case Parser::Token_COMMA:
        return ",";
    case Parser::Token_COMMENT:
        return "comment";
    case Parser::Token_CONCAT:
        return ".";
    case Parser::Token_CONCAT_ASSIGN:
        return ".=";
    case Parser::Token_CONST:
        return "const";
    case Parser::Token_CONSTANT_ENCAPSED_STRING:
        return "constant encapsed string";
    case Parser::Token_CONTINUE:
        return "continue";
    case Parser::Token_CURLY_OPEN:
        return "curly open";
    case Parser::Token_DEC:
        return "--";
    case Parser::Token_DECLARE:
        return "declare";
    case Parser::Token_DEFAULT:
        return "default";
    case Parser::Token_DIV:
        return "/";
    case Parser::Token_DIV_ASSIGN:
        return "/=";
    case Parser::Token_DNUMBER:
        return "double number";
    case Parser::Token_DO:
        return "do";
    case Parser::Token_DOC_COMMENT:
        return "doc comment";
    case Parser::Token_DOLLAR:
        return "$";
    case Parser::Token_DOLLAR_OPEN_CURLY_BRACES:
        return "${";
    case Parser::Token_DOUBLE_ARROW:
        return "=>";
    case Parser::Token_DOUBLE_CAST:
        return "double cast";
    case Parser::Token_DOUBLE_QUOTE:
        return "\\\"";
    case Parser::Token_ECHO:
        return "echo";
    case Parser::Token_ELSE:
        return "else";
    case Parser::Token_ELSEIF:
        return "elseif";
    case Parser::Token_EMPTY:
        return "empty";
    case Parser::Token_ENCAPSED_AND_WHITESPACE:
        return "encapsed and whitespace";
    case Parser::Token_ENDDECLARE:
        return "enddeclare";
    case Parser::Token_ENDFOR:
        return "endfor";
    case Parser::Token_ENDFOREACH:
        return "endforeach";
    case Parser::Token_ENDIF:
        return "endif";
    case Parser::Token_ENDSWITCH:
        return "endswitch";
    case Parser::Token_ENDWHILE:
        return "endwhile";
    case Parser::Token_END_HEREDOC:
        return "end heredoc";
    case Parser::Token_EOF:
        return "end of file";
    case Parser::Token_EVAL:
        return "eval";
    case Parser::Token_EXIT:
        return "exit";
    case Parser::Token_EXTENDS:
        return "extends";
    case Parser::Token_FILE:
        return "__FILE__";
    case Parser::Token_FINAL:
        return "final";
    case Parser::Token_FOR:
        return "for";
    case Parser::Token_FOREACH:
        return "foreach";
    case Parser::Token_FUNCTION:
        return "function";
    case Parser::Token_FUNC_C:
        return "__FUNCTION__";
    case Parser::Token_GLOBAL:
        return "global";
    case Parser::Token_HALT_COMPILER:
        return "halt compiler";
    case Parser::Token_IF:
        return "if";
    case Parser::Token_IMPLEMENTS:
        return "implements";
    case Parser::Token_INC:
        return "++";
    case Parser::Token_INCLUDE:
        return "include";
    case Parser::Token_INCLUDE_ONCE:
        return "include_once";
    case Parser::Token_INLINE_HTML:
        return "inline html";
    case Parser::Token_INSTANCEOF:
        return "instanceof";
    case Parser::Token_INTERFACE:
        return "interface";
    case Parser::Token_INT_CAST:
        return "int cast";
    case Parser::Token_INVALID:
        return "invalid token";
    case Parser::Token_ISSET:
        return "isset";
    case Parser::Token_IS_EQUAL:
        return "==";
    case Parser::Token_IS_GREATER:
        return ">";
    case Parser::Token_IS_GREATER_OR_EQUAL:
        return ">=";
    case Parser::Token_IS_IDENTICAL:
        return "===";
    case Parser::Token_IS_NOT_EQUAL:
        return "!=";
    case Parser::Token_IS_NOT_IDENTICAL:
        return "!==";
    case Parser::Token_IS_SMALLER:
        return "<";
    case Parser::Token_IS_SMALLER_OR_EQUAL:
        return "<=";
    case Parser::Token_LBRACE:
        return "{";
    case Parser::Token_LBRACKET:
        return "[";
    case Parser::Token_LINE:
        return "__LINE__";
    case Parser::Token_LIST:
        return "list";
    case Parser::Token_LNUMBER:
        return "long number";
    case Parser::Token_LOGICAL_AND:
        return "logical and";
    case Parser::Token_LOGICAL_OR:
        return "logical or";
    case Parser::Token_LOGICAL_XOR:
        return "logical xor";
    case Parser::Token_LPAREN:
        return "(";
    case Parser::Token_METHOD_C:
        return "__METHOD__";
    case Parser::Token_MINUS:
        return "-";
    case Parser::Token_MINUS_ASSIGN:
        return "-=";
    case Parser::Token_MOD:
        return "%";
    case Parser::Token_MOD_ASSIGN:
        return "%=";
    case Parser::Token_MUL:
        return "*";
    case Parser::Token_MUL_ASSIGN:
        return "*=";
    case Parser::Token_NEW:
        return "new";
    case Parser::Token_NUM_STRING:
        return "num string";
    case Parser::Token_OBJECT_CAST:
        return "object cast";
    case Parser::Token_OBJECT_OPERATOR:
        return "->";
    case Parser::Token_OPEN_TAG:
        return "<?";
    case Parser::Token_OPEN_TAG_WITH_ECHO:
        return "<?=";
    case Parser::Token_OR_ASSIGN:
        return "|=";
    case Parser::Token_PAAMAYIM_NEKUDOTAYIM:
        return "::";
    case Parser::Token_PLUS:
        return "+";
    case Parser::Token_PLUS_ASSIGN:
        return "+=";
    case Parser::Token_PRINT:
        return "print";
    case Parser::Token_PRIVATE:
        return "private";
    case Parser::Token_PROTECTED:
        return "protected";
    case Parser::Token_PUBLIC:
        return "public";
    case Parser::Token_QUESTION:
        return "?";
    case Parser::Token_RBRACE:
        return "}";
    case Parser::Token_RBRACKET:
        return "]";
    case Parser::Token_REQUIRE:
        return "require";
    case Parser::Token_REQUIRE_ONCE:
        return "require_once";
    case Parser::Token_RETURN:
        return "return";
    case Parser::Token_RPAREN:
        return ")";
    case Parser::Token_SEMICOLON:
        return ";";
    case Parser::Token_SL:
        return "<<";
    case Parser::Token_SL_ASSIGN:
        return "<<=";
    case Parser::Token_SR:
        return ">>";
    case Parser::Token_SR_ASSIGN:
        return ">>=";
    case Parser::Token_START_HEREDOC:
        return "start heredoc";
    case Parser::Token_STATIC:
        return "static";
    case Parser::Token_STRING:
        return "string";
    case Parser::Token_STRING_CAST:
        return "string cast";
    case Parser::Token_STRING_VARNAME:
        return "string varname";
    case Parser::Token_SWITCH:
        return "switch";
    case Parser::Token_THROW:
        return "throw";
    case Parser::Token_TILDE:
        return "~";
    case Parser::Token_TRY:
        return "try";
    case Parser::Token_UNSET:
        return "unset";
    case Parser::Token_UNSET_CAST:
        return "unset cast";
    case Parser::Token_USE:
        return "use";
    case Parser::Token_VAR:
        return "var ";
    case Parser::Token_VARIABLE:
        return "variable";
    case Parser::Token_WHILE:
        return "while";
    case Parser::Token_WHITESPACE:
        return "whitespace";
    case Parser::Token_XOR_ASSIGN:
        return "^=";
    default:
        return "unknown token";
    }
}
} // end of namespace Php

#endif

