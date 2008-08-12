// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_H_INCLUDED
#define PHP_H_INCLUDED

#include "phpast.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>
#include "phplexer.h"

#include <parserexport.h>
namespace Php
{

class KDEVPHPPARSER_EXPORT Parser
{
public:
    typedef TokenStream::Token Token;
    TokenStream *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        return tokenStream->token(tokenStream->index() - 1 + k - 1);
    }
    inline int yylex()
    {
        return (yytoken = tokenStream->nextToken());
    }
    inline void rewind(qint64 index)
    {
        tokenStream->rewind(index);
        yylex();
    }

// token stream
    void setTokenStream(TokenStream *s)
    {
        tokenStream = s;
    }

// error handling
    void expectedSymbol(int kind, const QString& name);
    void expectedToken(int kind, qint64 token, const QString& name);

    bool mBlockErrors;
    inline bool blockErrors(bool block)
    {
        bool previous = mBlockErrors;
        mBlockErrors = block;
        return previous;
    }

// memory pool
    typedef KDevPG::MemoryPool memoryPoolType;

    KDevPG::MemoryPool *memoryPool;
    void setMemoryPool(KDevPG::MemoryPool *p)
    {
        memoryPool = p;
    }
    template <class T>
    inline T *create()
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
    }

    enum TokenType
    {
        Token_ABSTRACT = 1000,
        Token_AND_ASSIGN = 1001,
        Token_ARRAY = 1002,
        Token_ARRAY_CAST = 1003,
        Token_AS = 1004,
        Token_ASSIGN = 1005,
        Token_AT = 1006,
        Token_BACKTICK = 1007,
        Token_BANG = 1008,
        Token_BIT_AND = 1009,
        Token_BIT_OR = 1010,
        Token_BIT_XOR = 1011,
        Token_BOOLEAN_AND = 1012,
        Token_BOOLEAN_OR = 1013,
        Token_BOOL_CAST = 1014,
        Token_BREAK = 1015,
        Token_CASE = 1016,
        Token_CATCH = 1017,
        Token_CLASS = 1018,
        Token_CLASS_C = 1019,
        Token_CLONE = 1020,
        Token_CLOSE_TAG = 1021,
        Token_COLON = 1022,
        Token_COMMA = 1023,
        Token_COMMENT = 1024,
        Token_CONCAT = 1025,
        Token_CONCAT_ASSIGN = 1026,
        Token_CONST = 1027,
        Token_CONSTANT_ENCAPSED_STRING = 1028,
        Token_CONTINUE = 1029,
        Token_CURLY_OPEN = 1030,
        Token_DEC = 1031,
        Token_DECLARE = 1032,
        Token_DEFAULT = 1033,
        Token_DIV = 1034,
        Token_DIV_ASSIGN = 1035,
        Token_DNUMBER = 1036,
        Token_DO = 1037,
        Token_DOC_COMMENT = 1038,
        Token_DOLLAR = 1039,
        Token_DOLLAR_OPEN_CURLY_BRACES = 1040,
        Token_DOUBLE_ARROW = 1041,
        Token_DOUBLE_CAST = 1042,
        Token_DOUBLE_QUOTE = 1043,
        Token_ECHO = 1044,
        Token_ELSE = 1045,
        Token_ELSEIF = 1046,
        Token_EMPTY = 1047,
        Token_ENCAPSED_AND_WHITESPACE = 1048,
        Token_ENDDECLARE = 1049,
        Token_ENDFOR = 1050,
        Token_ENDFOREACH = 1051,
        Token_ENDIF = 1052,
        Token_ENDSWITCH = 1053,
        Token_ENDWHILE = 1054,
        Token_END_HEREDOC = 1055,
        Token_EOF = 1056,
        Token_EVAL = 1057,
        Token_EXIT = 1058,
        Token_EXTENDS = 1059,
        Token_FILE = 1060,
        Token_FINAL = 1061,
        Token_FOR = 1062,
        Token_FOREACH = 1063,
        Token_FUNCTION = 1064,
        Token_FUNC_C = 1065,
        Token_GLOBAL = 1066,
        Token_HALT_COMPILER = 1067,
        Token_IF = 1068,
        Token_IMPLEMENTS = 1069,
        Token_INC = 1070,
        Token_INCLUDE = 1071,
        Token_INCLUDE_ONCE = 1072,
        Token_INLINE_HTML = 1073,
        Token_INSTANCEOF = 1074,
        Token_INTERFACE = 1075,
        Token_INT_CAST = 1076,
        Token_INVALID = 1077,
        Token_ISSET = 1078,
        Token_IS_EQUAL = 1079,
        Token_IS_GREATER = 1080,
        Token_IS_GREATER_OR_EQUAL = 1081,
        Token_IS_IDENTICAL = 1082,
        Token_IS_NOT_EQUAL = 1083,
        Token_IS_NOT_IDENTICAL = 1084,
        Token_IS_SMALLER = 1085,
        Token_IS_SMALLER_OR_EQUAL = 1086,
        Token_LBRACE = 1087,
        Token_LBRACKET = 1088,
        Token_LINE = 1089,
        Token_LIST = 1090,
        Token_LNUMBER = 1091,
        Token_LOGICAL_AND = 1092,
        Token_LOGICAL_OR = 1093,
        Token_LOGICAL_XOR = 1094,
        Token_LPAREN = 1095,
        Token_METHOD_C = 1096,
        Token_MINUS = 1097,
        Token_MINUS_ASSIGN = 1098,
        Token_MOD = 1099,
        Token_MOD_ASSIGN = 1100,
        Token_MUL = 1101,
        Token_MUL_ASSIGN = 1102,
        Token_NEW = 1103,
        Token_NUM_STRING = 1104,
        Token_OBJECT_CAST = 1105,
        Token_OBJECT_OPERATOR = 1106,
        Token_OPEN_TAG = 1107,
        Token_OPEN_TAG_WITH_ECHO = 1108,
        Token_OR_ASSIGN = 1109,
        Token_PAAMAYIM_NEKUDOTAYIM = 1110,
        Token_PLUS = 1111,
        Token_PLUS_ASSIGN = 1112,
        Token_PRINT = 1113,
        Token_PRIVATE = 1114,
        Token_PROTECTED = 1115,
        Token_PUBLIC = 1116,
        Token_QUESTION = 1117,
        Token_RBRACE = 1118,
        Token_RBRACKET = 1119,
        Token_REQUIRE = 1120,
        Token_REQUIRE_ONCE = 1121,
        Token_RETURN = 1122,
        Token_RPAREN = 1123,
        Token_SEMICOLON = 1124,
        Token_SL = 1125,
        Token_SL_ASSIGN = 1126,
        Token_SR = 1127,
        Token_SR_ASSIGN = 1128,
        Token_START_HEREDOC = 1129,
        Token_STATIC = 1130,
        Token_STRING = 1131,
        Token_STRING_CAST = 1132,
        Token_STRING_VARNAME = 1133,
        Token_SWITCH = 1134,
        Token_THROW = 1135,
        Token_TILDE = 1136,
        Token_TRY = 1137,
        Token_UNSET = 1138,
        Token_UNSET_CAST = 1139,
        Token_USE = 1140,
        Token_VAR = 1141,
        Token_VARIABLE = 1142,
        Token_WHILE = 1143,
        Token_WHITESPACE = 1144,
        Token_XOR_ASSIGN = 1145,
        TokenTypeSize
    }; // TokenType

// user defined declarations:
public:

    /**
     * Transform the raw input into tokens.
     * When this method returns, the parser's token stream has been filled
     * and any parse*() method can be called.
     */
    void tokenize(const QString& contents, int initialState = HtmlState);

    enum ProblemType
    {
        Error,
        Warning,
        Info
    };
    void reportProblem( Parser::ProblemType type, const QString& message );
    QString tokenText(qint64 begin, qint64 end);
    void setDebug(bool debug);

    enum InitialLexerState {
        HtmlState = 0,
        DefaultState = 1
    };

private:

    enum VarExpressionState
    {
        Normal,
        OnlyVariable,
        OnlyNewObject
    };
    QString m_contents;
    bool m_debug;

    struct ParserState
    {
        VarExpressionState varExpressionState;
        bool varExpressionIsVariable;
    };
    ParserState m_state;


public:
// The copyCurrentState() and restoreState() methods are only declared
// if you are using try blocks in your grammar, and have to be
// implemented by yourself, and you also have to define a
// "struct ParserState" inside a %parserclass directive.

// This method should create a new ParserState object and return it,
// or return 0 if no state variables need to be saved.
    ParserState *copyCurrentState();

// This method is only called for ParserState objects != 0
// and should restore the parser state given as argument.
    void restoreState(ParserState *state);
    Parser()
    {
        memoryPool = 0;
        tokenStream = 0;
        yytoken = Token_EOF;
        mBlockErrors = false;

// user defined constructor code:

        m_state.varExpressionState = Normal;
        m_state.varExpressionIsVariable = false;

    }

    virtual ~Parser() {}

    bool parseAdditiveExpression(AdditiveExpressionAst **yynode);
    bool parseAdditiveExpressionRest(AdditiveExpressionRestAst **yynode);
    bool parseArrayPairValue(ArrayPairValueAst **yynode);
    bool parseAssignmentExpression(AssignmentExpressionAst **yynode);
    bool parseAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst **yynode);
    bool parseAssignmentExpressionEqual(AssignmentExpressionEqualAst **yynode);
    bool parseAssignmentList(AssignmentListAst **yynode);
    bool parseAssignmentListElement(AssignmentListElementAst **yynode);
    bool parseBaseVariable(BaseVariableAst **yynode);
    bool parseBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst **yynode);
    bool parseBitAndExpression(BitAndExpressionAst **yynode);
    bool parseBitOrExpression(BitOrExpressionAst **yynode);
    bool parseBitXorExpression(BitXorExpressionAst **yynode);
    bool parseBooleanAndExpression(BooleanAndExpressionAst **yynode);
    bool parseBooleanOrExpression(BooleanOrExpressionAst **yynode);
    bool parseCaseList(CaseListAst **yynode);
    bool parseCase_item(Case_itemAst **yynode);
    bool parseCatch_item(Catch_itemAst **yynode);
    bool parseClassBody(ClassBodyAst **yynode);
    bool parseClassConstantDeclaration(ClassConstantDeclarationAst **yynode);
    bool parseClassDeclarationStatement(ClassDeclarationStatementAst **yynode);
    bool parseClassExtends(ClassExtendsAst **yynode);
    bool parseClassImplements(ClassImplementsAst **yynode);
    bool parseClassNameReference(ClassNameReferenceAst **yynode);
    bool parseClassStatement(ClassStatementAst **yynode);
    bool parseClassVariable(ClassVariableAst **yynode);
    bool parseClassVariableDeclaration(ClassVariableDeclarationAst **yynode);
    bool parseCommonScalar(CommonScalarAst **yynode);
    bool parseCompoundVariable(CompoundVariableAst **yynode);
    bool parseCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst **yynode);
    bool parseConditionalExpression(ConditionalExpressionAst **yynode);
    bool parseCtorArguments(CtorArgumentsAst **yynode);
    bool parseDeclareItem(DeclareItemAst **yynode);
    bool parseDeclareStatement(DeclareStatementAst **yynode);
    bool parseDimListItem(DimListItemAst **yynode);
    bool parseDimOffset(DimOffsetAst **yynode);
    bool parseDynamicClassNameReference(DynamicClassNameReferenceAst **yynode);
    bool parseDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst **yynode);
    bool parseDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst **yynode);
    bool parseElseSingle(ElseSingleAst **yynode);
    bool parseElseifList(ElseifListAst **yynode);
    bool parseElseifListItem(ElseifListItemAst **yynode);
    bool parseEncaps(EncapsAst **yynode);
    bool parseEncapsList(EncapsListAst **yynode);
    bool parseEncapsVar(EncapsVarAst **yynode);
    bool parseEncapsVarOffset(EncapsVarOffsetAst **yynode);
    bool parseEqualityExpression(EqualityExpressionAst **yynode);
    bool parseEqualityExpressionRest(EqualityExpressionRestAst **yynode);
    bool parseExpr(ExprAst **yynode);
    bool parseForExpr(ForExprAst **yynode);
    bool parseForStatement(ForStatementAst **yynode);
    bool parseForeachOptionalArg(ForeachOptionalArgAst **yynode);
    bool parseForeachStatement(ForeachStatementAst **yynode);
    bool parseForeachVariable(ForeachVariableAst **yynode);
    bool parseFunctionCall(FunctionCallAst **yynode);
    bool parseFunctionCallParameterList(FunctionCallParameterListAst **yynode);
    bool parseFunctionCallParameterListElement(FunctionCallParameterListElementAst **yynode);
    bool parseFunctionDeclarationStatement(FunctionDeclarationStatementAst **yynode);
    bool parseGlobalVar(GlobalVarAst **yynode);
    bool parseIdentifier(IdentifierAst **yynode);
    bool parseInnerStatementList(InnerStatementListAst **yynode);
    bool parseInterfaceDeclarationStatement(InterfaceDeclarationStatementAst **yynode);
    bool parseLogicalAndExpression(LogicalAndExpressionAst **yynode);
    bool parseLogicalOrExpression(LogicalOrExpressionAst **yynode);
    bool parseLogicalXorExpression(LogicalXorExpressionAst **yynode);
    bool parseMethodBody(MethodBodyAst **yynode);
    bool parseMultiplicativeExpression(MultiplicativeExpressionAst **yynode);
    bool parseMultiplicativeExpressionRest(MultiplicativeExpressionRestAst **yynode);
    bool parseNewElseSingle(NewElseSingleAst **yynode);
    bool parseNewElseifList(NewElseifListAst **yynode);
    bool parseNewelseifListItem(NewelseifListItemAst **yynode);
    bool parseObjectDimList(ObjectDimListAst **yynode);
    bool parseObjectProperty(ObjectPropertyAst **yynode);
    bool parseOptionalModifiers(OptionalModifiersAst **yynode);
    bool parseParameter(ParameterAst **yynode);
    bool parseParameterList(ParameterListAst **yynode);
    bool parsePostprefixOperator(PostprefixOperatorAst **yynode);
    bool parsePrintExpression(PrintExpressionAst **yynode);
    bool parseRelationalExpression(RelationalExpressionAst **yynode);
    bool parseRelationalExpressionRest(RelationalExpressionRestAst **yynode);
    bool parseScalar(ScalarAst **yynode);
    bool parseSemicolonOrCloseTag(SemicolonOrCloseTagAst **yynode);
    bool parseShiftExpression(ShiftExpressionAst **yynode);
    bool parseShiftExpressionRest(ShiftExpressionRestAst **yynode);
    bool parseStart(StartAst **yynode);
    bool parseStatement(StatementAst **yynode);
    bool parseStaticArrayPairValue(StaticArrayPairValueAst **yynode);
    bool parseStaticMember(StaticMemberAst **yynode);
    bool parseStaticScalar(StaticScalarAst **yynode);
    bool parseStaticVar(StaticVarAst **yynode);
    bool parseSwitchCaseList(SwitchCaseListAst **yynode);
    bool parseTopStatement(TopStatementAst **yynode);
    bool parseUnaryExpression(UnaryExpressionAst **yynode);
    bool parseUnaryExpressionNotPlusminus(UnaryExpressionNotPlusminusAst **yynode);
    bool parseVarExpression(VarExpressionAst **yynode);
    bool parseVarExpressionNewObject(VarExpressionNewObjectAst **yynode);
    bool parseVarExpressionNormal(VarExpressionNormalAst **yynode);
    bool parseVariable(VariableAst **yynode);
    bool parseVariableIdentifier(VariableIdentifierAst **yynode);
    bool parseVariableName(VariableNameAst **yynode);
    bool parseVariableProperty(VariablePropertyAst **yynode);
    bool parseVariableWithoutObjects(VariableWithoutObjectsAst **yynode);
    bool parseWhileStatement(WhileStatementAst **yynode);
};

} // end of namespace Php

#endif

