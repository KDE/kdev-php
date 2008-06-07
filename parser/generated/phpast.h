// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_AST_H_INCLUDED
#define PHP_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>

#include <parserexport.h>


#include <QtCore/QString>
#include <kdebug.h>

namespace PhpParser
{
class Lexer;
enum NumericType
{
    LongNumber,
    DoubleNumber,
};
}

namespace PhpParser
{

struct AdditiveExpressionAst;
struct AdditiveExpressionRestAst;
struct ArrayPairValueAst;
struct AssignmentExpressionAst;
struct AssignmentExpressionCheckIfVariableAst;
struct AssignmentExpressionEqualAst;
struct AssignmentListAst;
struct AssignmentListElementAst;
struct BaseVariableAst;
struct BaseVariableWithFunctionCallsAst;
struct BitAndExpressionAst;
struct BitOrExpressionAst;
struct BitXorExpressionAst;
struct BooleanAndExpressionAst;
struct BooleanOrExpressionAst;
struct CaseListAst;
struct Case_itemAst;
struct Catch_itemAst;
struct ClassConstantDeclarationAst;
struct ClassDeclarationStatementAst;
struct ClassNameReferenceAst;
struct ClassStatementAst;
struct ClassVariableAst;
struct ClassVariableDeclarationAst;
struct CommonScalarAst;
struct CompoundVariableAst;
struct CompoundVariableWithSimpleIndirectReferenceAst;
struct ConditionalExpressionAst;
struct CtorArgumentsAst;
struct DeclareItemAst;
struct DeclareStatementAst;
struct DimListItemAst;
struct DimOffsetAst;
struct DynamicClassNameReferenceAst;
struct DynamicClassNameVariablePropertiesAst;
struct DynamicClassNameVariablePropertyAst;
struct ElseSingleAst;
struct ElseifListAst;
struct ElseifListItemAst;
struct EncapsAst;
struct EncapsListAst;
struct EncapsVarAst;
struct EncapsVarOffsetAst;
struct EqualityExpressionAst;
struct EqualityExpressionRestAst;
struct ExprAst;
struct ForExprAst;
struct ForStatementAst;
struct ForeachOptionalArgAst;
struct ForeachStatementAst;
struct ForeachVariableAst;
struct FunctionCallAst;
struct FunctionCallParameterListAst;
struct FunctionCallParameterListElementAst;
struct FunctionDeclarationStatementAst;
struct GlobalVarAst;
struct InnerStatementListAst;
struct LogicalAndExpressionAst;
struct LogicalOrExpressionAst;
struct LogicalXorExpressionAst;
struct MemberModifierAst;
struct MethodBodyAst;
struct MultiplicativeExpressionAst;
struct MultiplicativeExpression_restAst;
struct NewElseSingleAst;
struct NewElseifListAst;
struct NewelseifListItemAst;
struct ObjectDimListAst;
struct ObjectPropertyAst;
struct ParameterAst;
struct ParameterListAst;
struct PostprefixOperatorAst;
struct PrintExpressionAst;
struct RelationalExpressionAst;
struct RelationalExpressionRestAst;
struct ScalarAst;
struct SemicolonOrCloseTagAst;
struct ShiftExpressionAst;
struct ShiftExpressionRestAst;
struct StartAst;
struct StatementAst;
struct StaticArrayPairValueAst;
struct StaticMemberAst;
struct StaticScalarAst;
struct StaticVarAst;
struct SwitchCaseListAst;
struct TopStatementAst;
struct UnaryExpressionAst;
struct UnaryExpression_not_plusminusAst;
struct VarExpressionAst;
struct VarExpressionNewObjectAst;
struct VarExpressionNormalAst;
struct VariableAst;
struct VariableNameAst;
struct VariablePropertyAst;
struct VariableWithoutObjectsAst;
struct WhileStatementAst;


struct KDEVPHPPARSER_EXPORT AstNode
{
    enum AstNodeKind
    {
        AdditiveExpressionKind = 1000,
        AdditiveExpressionRestKind = 1001,
        ArrayPairValueKind = 1002,
        AssignmentExpressionKind = 1003,
        AssignmentExpressionCheckIfVariableKind = 1004,
        AssignmentExpressionEqualKind = 1005,
        AssignmentListKind = 1006,
        AssignmentListElementKind = 1007,
        BaseVariableKind = 1008,
        BaseVariableWithFunctionCallsKind = 1009,
        BitAndExpressionKind = 1010,
        BitOrExpressionKind = 1011,
        BitXorExpressionKind = 1012,
        BooleanAndExpressionKind = 1013,
        BooleanOrExpressionKind = 1014,
        CaseListKind = 1015,
        Case_itemKind = 1016,
        Catch_itemKind = 1017,
        ClassConstantDeclarationKind = 1018,
        ClassDeclarationStatementKind = 1019,
        ClassNameReferenceKind = 1020,
        ClassStatementKind = 1021,
        ClassVariableKind = 1022,
        ClassVariableDeclarationKind = 1023,
        CommonScalarKind = 1024,
        CompoundVariableKind = 1025,
        CompoundVariableWithSimpleIndirectReferenceKind = 1026,
        ConditionalExpressionKind = 1027,
        CtorArgumentsKind = 1028,
        DeclareItemKind = 1029,
        DeclareStatementKind = 1030,
        DimListItemKind = 1031,
        DimOffsetKind = 1032,
        DynamicClassNameReferenceKind = 1033,
        DynamicClassNameVariablePropertiesKind = 1034,
        DynamicClassNameVariablePropertyKind = 1035,
        ElseSingleKind = 1036,
        ElseifListKind = 1037,
        ElseifListItemKind = 1038,
        EncapsKind = 1039,
        EncapsListKind = 1040,
        EncapsVarKind = 1041,
        EncapsVarOffsetKind = 1042,
        EqualityExpressionKind = 1043,
        EqualityExpressionRestKind = 1044,
        ExprKind = 1045,
        ForExprKind = 1046,
        ForStatementKind = 1047,
        ForeachOptionalArgKind = 1048,
        ForeachStatementKind = 1049,
        ForeachVariableKind = 1050,
        FunctionCallKind = 1051,
        FunctionCallParameterListKind = 1052,
        FunctionCallParameterListElementKind = 1053,
        FunctionDeclarationStatementKind = 1054,
        GlobalVarKind = 1055,
        InnerStatementListKind = 1056,
        LogicalAndExpressionKind = 1057,
        LogicalOrExpressionKind = 1058,
        LogicalXorExpressionKind = 1059,
        MemberModifierKind = 1060,
        MethodBodyKind = 1061,
        MultiplicativeExpressionKind = 1062,
        MultiplicativeExpression_restKind = 1063,
        NewElseSingleKind = 1064,
        NewElseifListKind = 1065,
        NewelseifListItemKind = 1066,
        ObjectDimListKind = 1067,
        ObjectPropertyKind = 1068,
        ParameterKind = 1069,
        ParameterListKind = 1070,
        PostprefixOperatorKind = 1071,
        PrintExpressionKind = 1072,
        RelationalExpressionKind = 1073,
        RelationalExpressionRestKind = 1074,
        ScalarKind = 1075,
        SemicolonOrCloseTagKind = 1076,
        ShiftExpressionKind = 1077,
        ShiftExpressionRestKind = 1078,
        StartKind = 1079,
        StatementKind = 1080,
        StaticArrayPairValueKind = 1081,
        StaticMemberKind = 1082,
        StaticScalarKind = 1083,
        StaticVarKind = 1084,
        SwitchCaseListKind = 1085,
        TopStatementKind = 1086,
        UnaryExpressionKind = 1087,
        UnaryExpression_not_plusminusKind = 1088,
        VarExpressionKind = 1089,
        VarExpressionNewObjectKind = 1090,
        VarExpressionNormalKind = 1091,
        VariableKind = 1092,
        VariableNameKind = 1093,
        VariablePropertyKind = 1094,
        VariableWithoutObjectsKind = 1095,
        WhileStatementKind = 1096,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

};

struct KDEVPHPPARSER_EXPORT AdditiveExpressionAst: public AstNode
{
    enum { KIND = AdditiveExpressionKind };

    MultiplicativeExpressionAst *expression;
    const KDevPG::ListNode<AdditiveExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVPHPPARSER_EXPORT AdditiveExpressionRestAst: public AstNode
{
    enum { KIND = AdditiveExpressionRestKind };

    MultiplicativeExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT ArrayPairValueAst: public AstNode
{
    enum { KIND = ArrayPairValueKind };

    ExprAst *expr;
    ExprAst *exprValue;
    VariableAst *varValue;
    VariableAst *variable;
};

struct KDEVPHPPARSER_EXPORT AssignmentExpressionAst: public AstNode
{
    enum { KIND = AssignmentExpressionKind };

    ConditionalExpressionAst *conditionalExpression;
    AssignmentExpressionEqualAst *assignmentAxpressionEqual;
    AssignmentExpressionAst *assignmentExpression;
};

struct KDEVPHPPARSER_EXPORT AssignmentExpressionCheckIfVariableAst: public AstNode
{
    enum { KIND = AssignmentExpressionCheckIfVariableKind };

};

struct KDEVPHPPARSER_EXPORT AssignmentExpressionEqualAst: public AstNode
{
    enum { KIND = AssignmentExpressionEqualKind };

    AssignmentExpressionAst *assignmentExpression;
};

struct KDEVPHPPARSER_EXPORT AssignmentListAst: public AstNode
{
    enum { KIND = AssignmentListKind };

    const KDevPG::ListNode<AssignmentListElementAst *> *elementSequence;
};

struct KDEVPHPPARSER_EXPORT AssignmentListElementAst: public AstNode
{
    enum { KIND = AssignmentListElementKind };

    VariableAst *variable;
    AssignmentListAst *assignmentList;
};

struct KDEVPHPPARSER_EXPORT BaseVariableAst: public AstNode
{
    enum { KIND = BaseVariableKind };

    CompoundVariableWithSimpleIndirectReferenceAst *var;
    const KDevPG::ListNode<DimListItemAst *> *offsetItemsSequence;
    StaticMemberAst *staticMember;
};

struct KDEVPHPPARSER_EXPORT BaseVariableWithFunctionCallsAst: public AstNode
{
    enum { KIND = BaseVariableWithFunctionCallsKind };

    FunctionCallAst *functionCall;
    BaseVariableAst *baseVariable;
};

struct KDEVPHPPARSER_EXPORT BitAndExpressionAst: public AstNode
{
    enum { KIND = BitAndExpressionKind };

    const KDevPG::ListNode<EqualityExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT BitOrExpressionAst: public AstNode
{
    enum { KIND = BitOrExpressionKind };

    const KDevPG::ListNode<BitXorExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT BitXorExpressionAst: public AstNode
{
    enum { KIND = BitXorExpressionKind };

    const KDevPG::ListNode<BitAndExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT BooleanAndExpressionAst: public AstNode
{
    enum { KIND = BooleanAndExpressionKind };

    const KDevPG::ListNode<BitOrExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT BooleanOrExpressionAst: public AstNode
{
    enum { KIND = BooleanOrExpressionKind };

    const KDevPG::ListNode<BooleanAndExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT CaseListAst: public AstNode
{
    enum { KIND = CaseListKind };

    const KDevPG::ListNode<Case_itemAst *> *caseItemsSequence;
};

struct KDEVPHPPARSER_EXPORT Case_itemAst: public AstNode
{
    enum { KIND = Case_itemKind };

    ExprAst *expr;
    InnerStatementListAst *statements;
    qint64 def;
};

struct KDEVPHPPARSER_EXPORT Catch_itemAst: public AstNode
{
    enum { KIND = Catch_itemKind };

    qint64 catchClass;
    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT ClassConstantDeclarationAst: public AstNode
{
    enum { KIND = ClassConstantDeclarationKind };

    StaticScalarAst *scalar;
};

struct KDEVPHPPARSER_EXPORT ClassDeclarationStatementAst: public AstNode
{
    enum { KIND = ClassDeclarationStatementKind };

    qint64 classType;
    qint64 name;
    qint64 extends;
    const KDevPG::ListNode<qint64 > *implmentsSequence;
    const KDevPG::ListNode<ClassStatementAst *> *statementsSequence;
};

struct KDEVPHPPARSER_EXPORT ClassNameReferenceAst: public AstNode
{
    enum { KIND = ClassNameReferenceKind };

    DynamicClassNameReferenceAst *dynamicClassNameReference;
};

struct KDEVPHPPARSER_EXPORT ClassStatementAst: public AstNode
{
    enum { KIND = ClassStatementKind };

    ClassConstantDeclarationAst *consts;
    MemberModifierAst *modifiers;
    ParameterListAst *params;
    MethodBodyAst *body;
};

struct KDEVPHPPARSER_EXPORT ClassVariableAst: public AstNode
{
    enum { KIND = ClassVariableKind };

    qint64 var;
    StaticScalarAst *value;
};

struct KDEVPHPPARSER_EXPORT ClassVariableDeclarationAst: public AstNode
{
    enum { KIND = ClassVariableDeclarationKind };

    ClassVariableAst *vars;
};

struct KDEVPHPPARSER_EXPORT CommonScalarAst: public AstNode
{
    enum { KIND = CommonScalarKind };

    PhpParser::NumericType numType;
};

struct KDEVPHPPARSER_EXPORT CompoundVariableAst: public AstNode
{
    enum { KIND = CompoundVariableKind };

    qint64 variable;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT CompoundVariableWithSimpleIndirectReferenceAst: public AstNode
{
    enum { KIND = CompoundVariableWithSimpleIndirectReferenceKind };

    qint64 var;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT ConditionalExpressionAst: public AstNode
{
    enum { KIND = ConditionalExpressionKind };

    BooleanOrExpressionAst *expression;
    ExprAst *ifExpression;
    ConditionalExpressionAst *elseExpression;
};

struct KDEVPHPPARSER_EXPORT CtorArgumentsAst: public AstNode
{
    enum { KIND = CtorArgumentsKind };

    FunctionCallParameterListAst *parameterList;
};

struct KDEVPHPPARSER_EXPORT DeclareItemAst: public AstNode
{
    enum { KIND = DeclareItemKind };

    StaticScalarAst *scalar;
};

struct KDEVPHPPARSER_EXPORT DeclareStatementAst: public AstNode
{
    enum { KIND = DeclareStatementKind };

    StatementAst *statement;
    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT DimListItemAst: public AstNode
{
    enum { KIND = DimListItemKind };

    DimOffsetAst *dimOffset;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT DimOffsetAst: public AstNode
{
    enum { KIND = DimOffsetKind };

    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT DynamicClassNameReferenceAst: public AstNode
{
    enum { KIND = DynamicClassNameReferenceKind };

    BaseVariableAst *baseVariable;
    ObjectPropertyAst *objectProperty;
    DynamicClassNameVariablePropertiesAst *properties;
};

struct KDEVPHPPARSER_EXPORT DynamicClassNameVariablePropertiesAst: public AstNode
{
    enum { KIND = DynamicClassNameVariablePropertiesKind };

    const KDevPG::ListNode<DynamicClassNameVariablePropertyAst *> *propertiesSequence;
};

struct KDEVPHPPARSER_EXPORT DynamicClassNameVariablePropertyAst: public AstNode
{
    enum { KIND = DynamicClassNameVariablePropertyKind };

    ObjectPropertyAst *property;
};

struct KDEVPHPPARSER_EXPORT ElseSingleAst: public AstNode
{
    enum { KIND = ElseSingleKind };

    StatementAst *statement;
};

struct KDEVPHPPARSER_EXPORT ElseifListAst: public AstNode
{
    enum { KIND = ElseifListKind };

    const KDevPG::ListNode<ElseifListItemAst *> *elseifListItemSequence;
};

struct KDEVPHPPARSER_EXPORT ElseifListItemAst: public AstNode
{
    enum { KIND = ElseifListItemKind };

    ExprAst *expr;
    StatementAst *statement;
};

struct KDEVPHPPARSER_EXPORT EncapsAst: public AstNode
{
    enum { KIND = EncapsKind };

    EncapsVarAst *var;
    qint64 value;
};

struct KDEVPHPPARSER_EXPORT EncapsListAst: public AstNode
{
    enum { KIND = EncapsListKind };

    const KDevPG::ListNode<EncapsAst *> *encapsSequence;
};

struct KDEVPHPPARSER_EXPORT EncapsVarAst: public AstNode
{
    enum { KIND = EncapsVarKind };

    ExprAst *expr;
    EncapsVarOffsetAst *offset;
};

struct KDEVPHPPARSER_EXPORT EncapsVarOffsetAst: public AstNode
{
    enum { KIND = EncapsVarOffsetKind };

};

struct KDEVPHPPARSER_EXPORT EqualityExpressionAst: public AstNode
{
    enum { KIND = EqualityExpressionKind };

    RelationalExpressionAst *expression;
    const KDevPG::ListNode<EqualityExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVPHPPARSER_EXPORT EqualityExpressionRestAst: public AstNode
{
    enum { KIND = EqualityExpressionRestKind };

    RelationalExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT ExprAst: public AstNode
{
    enum { KIND = ExprKind };

    LogicalOrExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT ForExprAst: public AstNode
{
    enum { KIND = ForExprKind };

    const KDevPG::ListNode<ExprAst *> *exprsSequence;
};

struct KDEVPHPPARSER_EXPORT ForStatementAst: public AstNode
{
    enum { KIND = ForStatementKind };

    StatementAst *statement;
    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT ForeachOptionalArgAst: public AstNode
{
    enum { KIND = ForeachOptionalArgKind };

    ForeachVariableAst *foreachVariable;
};

struct KDEVPHPPARSER_EXPORT ForeachStatementAst: public AstNode
{
    enum { KIND = ForeachStatementKind };

    StatementAst *statement;
    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT ForeachVariableAst: public AstNode
{
    enum { KIND = ForeachVariableKind };

    VariableAst *variable;
};

struct KDEVPHPPARSER_EXPORT FunctionCallAst: public AstNode
{
    enum { KIND = FunctionCallKind };

    qint64 stringFunctionNameOrClass;
    FunctionCallParameterListAst *stringParameterList;
    qint64 stringFunctionName;
    VariableWithoutObjectsAst *varFunctionName;
    FunctionCallParameterListAst *varParameterList;
};

struct KDEVPHPPARSER_EXPORT FunctionCallParameterListAst: public AstNode
{
    enum { KIND = FunctionCallParameterListKind };

    FunctionCallParameterListElementAst *parameter;
};

struct KDEVPHPPARSER_EXPORT FunctionCallParameterListElementAst: public AstNode
{
    enum { KIND = FunctionCallParameterListElementKind };

    VariableAst *variable;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT FunctionDeclarationStatementAst: public AstNode
{
    enum { KIND = FunctionDeclarationStatementKind };

    ParameterListAst *params;
    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT GlobalVarAst: public AstNode
{
    enum { KIND = GlobalVarKind };

    qint64 var;
    VariableAst *dollarVar;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT InnerStatementListAst: public AstNode
{
    enum { KIND = InnerStatementListKind };

    const KDevPG::ListNode<TopStatementAst *> *statementsSequence;
};

struct KDEVPHPPARSER_EXPORT LogicalAndExpressionAst: public AstNode
{
    enum { KIND = LogicalAndExpressionKind };

    const KDevPG::ListNode<PrintExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT LogicalOrExpressionAst: public AstNode
{
    enum { KIND = LogicalOrExpressionKind };

    const KDevPG::ListNode<LogicalXorExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT LogicalXorExpressionAst: public AstNode
{
    enum { KIND = LogicalXorExpressionKind };

    const KDevPG::ListNode<LogicalAndExpressionAst *> *expressionSequence;
};

struct KDEVPHPPARSER_EXPORT MemberModifierAst: public AstNode
{
    enum { KIND = MemberModifierKind };

};

struct KDEVPHPPARSER_EXPORT MethodBodyAst: public AstNode
{
    enum { KIND = MethodBodyKind };

    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT MultiplicativeExpressionAst: public AstNode
{
    enum { KIND = MultiplicativeExpressionKind };

    UnaryExpressionAst *expression;
    const KDevPG::ListNode<MultiplicativeExpression_restAst *> *additionalExpressionSequence;
};

struct KDEVPHPPARSER_EXPORT MultiplicativeExpression_restAst: public AstNode
{
    enum { KIND = MultiplicativeExpression_restKind };

    UnaryExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT NewElseSingleAst: public AstNode
{
    enum { KIND = NewElseSingleKind };

    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT NewElseifListAst: public AstNode
{
    enum { KIND = NewElseifListKind };

    const KDevPG::ListNode<NewelseifListItemAst *> *newElseifListItemSequence;
};

struct KDEVPHPPARSER_EXPORT NewelseifListItemAst: public AstNode
{
    enum { KIND = NewelseifListItemKind };

    ExprAst *expr;
    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT ObjectDimListAst: public AstNode
{
    enum { KIND = ObjectDimListKind };

    VariableNameAst *variableName;
    const KDevPG::ListNode<DimListItemAst *> *offsetItemsSequence;
};

struct KDEVPHPPARSER_EXPORT ObjectPropertyAst: public AstNode
{
    enum { KIND = ObjectPropertyKind };

    ObjectDimListAst *objectDimList;
    VariableWithoutObjectsAst *variableWithoutObjects;
};

struct KDEVPHPPARSER_EXPORT ParameterAst: public AstNode
{
    enum { KIND = ParameterKind };

    StaticScalarAst *defaultValue;
};

struct KDEVPHPPARSER_EXPORT ParameterListAst: public AstNode
{
    enum { KIND = ParameterListKind };

    const KDevPG::ListNode<ParameterAst *> *paramsSequence;
};

struct KDEVPHPPARSER_EXPORT PostprefixOperatorAst: public AstNode
{
    enum { KIND = PostprefixOperatorKind };

    qint64 op;
};

struct KDEVPHPPARSER_EXPORT PrintExpressionAst: public AstNode
{
    enum { KIND = PrintExpressionKind };

    qint64 print;
    AssignmentExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT RelationalExpressionAst: public AstNode
{
    enum { KIND = RelationalExpressionKind };

    ShiftExpressionAst *expression;
    const KDevPG::ListNode<RelationalExpressionRestAst *> *additionalExpressionSequence;
    ClassNameReferenceAst *instanceofType;
};

struct KDEVPHPPARSER_EXPORT RelationalExpressionRestAst: public AstNode
{
    enum { KIND = RelationalExpressionRestKind };

    ShiftExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT ScalarAst: public AstNode
{
    enum { KIND = ScalarKind };

    CommonScalarAst *commonScalar;
    qint64 string;
    qint64 constname;
    qint64 varname;
    EncapsListAst *encapsList;
};

struct KDEVPHPPARSER_EXPORT SemicolonOrCloseTagAst: public AstNode
{
    enum { KIND = SemicolonOrCloseTagKind };

};

struct KDEVPHPPARSER_EXPORT ShiftExpressionAst: public AstNode
{
    enum { KIND = ShiftExpressionKind };

    AdditiveExpressionAst *expression;
    const KDevPG::ListNode<ShiftExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVPHPPARSER_EXPORT ShiftExpressionRestAst: public AstNode
{
    enum { KIND = ShiftExpressionRestKind };

    AdditiveExpressionAst *expression;
};

struct KDEVPHPPARSER_EXPORT StartAst: public AstNode
{
    enum { KIND = StartKind };

    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT StatementAst: public AstNode
{
    enum { KIND = StatementKind };

    InnerStatementListAst *statements;
    ExprAst *ifExpr;
    StatementAst *ifStatement;
    ElseifListAst *elseifList;
    ElseSingleAst *elseSingle;
    ExprAst *whileExpr;
    WhileStatementAst *whilteStatement;
    ForExprAst *forExpr1;
    ForExprAst *forExpr2;
    ForExprAst *forExpr3;
    ForStatementAst *forStatement;
    ExprAst *swtichExpr;
    SwitchCaseListAst *switchCaseList;
    VariableAst *foreachVar;
    ForeachVariableAst *foreachVarAsVar;
    ExprAst *foreachExpr;
    VariableAst *foreachExprAsVar;
    ForeachOptionalArgAst *foreachArg;
    ForeachStatementAst *foreachStatement;
    DeclareItemAst *declareItem;
    const KDevPG::ListNode<Catch_itemAst *> *catchesSequence;
    const KDevPG::ListNode<VariableAst *> *unsetVariablesSequence;
    ExprAst *expr;
    StatementAst *doStatement;
    ExprAst *whilteExpr;
    ExprAst *breakExpr;
    ExprAst *continueExpr;
    ExprAst *returnExpr;
    const KDevPG::ListNode<GlobalVarAst *> *globalVarsSequence;
    const KDevPG::ListNode<StaticVarAst *> *staticVarsSequence;
    const KDevPG::ListNode<ExprAst *> *echoExprsSequence;
    ExprAst *throwExpr;
};

struct KDEVPHPPARSER_EXPORT StaticArrayPairValueAst: public AstNode
{
    enum { KIND = StaticArrayPairValueKind };

    const KDevPG::ListNode<StaticScalarAst *> *val1Sequence;
    const KDevPG::ListNode<StaticScalarAst *> *val2Sequence;
};

struct KDEVPHPPARSER_EXPORT StaticMemberAst: public AstNode
{
    enum { KIND = StaticMemberKind };

    qint64 className;
    VariableWithoutObjectsAst *variable;
};

struct KDEVPHPPARSER_EXPORT StaticScalarAst: public AstNode
{
    enum { KIND = StaticScalarKind };

    CommonScalarAst *value;
    StaticScalarAst *plusValue;
    StaticScalarAst *minusValue;
    const KDevPG::ListNode<StaticArrayPairValueAst *> *arrayValuesSequence;
};

struct KDEVPHPPARSER_EXPORT StaticVarAst: public AstNode
{
    enum { KIND = StaticVarKind };

    StaticScalarAst *staticScalar;
};

struct KDEVPHPPARSER_EXPORT SwitchCaseListAst: public AstNode
{
    enum { KIND = SwitchCaseListKind };

    CaseListAst *caseList;
};

struct KDEVPHPPARSER_EXPORT TopStatementAst: public AstNode
{
    enum { KIND = TopStatementKind };

    StatementAst *statement;
    FunctionDeclarationStatementAst *functionDeclaration;
    ClassDeclarationStatementAst *classDeclaration;
};

struct KDEVPHPPARSER_EXPORT UnaryExpressionAst: public AstNode
{
    enum { KIND = UnaryExpressionKind };

    UnaryExpressionAst *unaryExpression;
    AssignmentListAst *assignmentList;
    ExprAst *expression;
    UnaryExpression_not_plusminusAst *unaryExpressionNotPlusminus;
};

struct KDEVPHPPARSER_EXPORT UnaryExpression_not_plusminusAst: public AstNode
{
    enum { KIND = UnaryExpression_not_plusminusKind };

    const KDevPG::ListNode<PostprefixOperatorAst *> *prefixOperatorSequence;
    VarExpressionAst *varExpression;
    const KDevPG::ListNode<PostprefixOperatorAst *> *postfixOperatorSequence;
};

struct KDEVPHPPARSER_EXPORT VarExpressionAst: public AstNode
{
    enum { KIND = VarExpressionKind };

    VariableAst *variable;
    VarExpressionNewObjectAst *newObject;
    VarExpressionNormalAst *varExpressionNormal;
};

struct KDEVPHPPARSER_EXPORT VarExpressionNewObjectAst: public AstNode
{
    enum { KIND = VarExpressionNewObjectKind };

    ClassNameReferenceAst *className;
    CtorArgumentsAst *ctor;
};

struct KDEVPHPPARSER_EXPORT VarExpressionNormalAst: public AstNode
{
    enum { KIND = VarExpressionNormalKind };

    ExprAst *expression;
    EncapsListAst *encapsList;
    VariableAst *variable;
    ScalarAst *scalar;
    const KDevPG::ListNode<ArrayPairValueAst *> *arrayValuesSequence;
    const KDevPG::ListNode<VariableAst *> *issetVariableSequence;
    VariableAst *emptyVarialbe;
    VarExpressionNewObjectAst *newObject;
    VarExpressionNormalAst *cloneCar;
};

struct KDEVPHPPARSER_EXPORT VariableAst: public AstNode
{
    enum { KIND = VariableKind };

    BaseVariableWithFunctionCallsAst *var;
    const KDevPG::ListNode<VariablePropertyAst *> *variablePropertiesSequence;
};

struct KDEVPHPPARSER_EXPORT VariableNameAst: public AstNode
{
    enum { KIND = VariableNameKind };

    qint64 name;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT VariablePropertyAst: public AstNode
{
    enum { KIND = VariablePropertyKind };

    ObjectPropertyAst *objectProperty;
    FunctionCallParameterListAst *parameterList;
};

struct KDEVPHPPARSER_EXPORT VariableWithoutObjectsAst: public AstNode
{
    enum { KIND = VariableWithoutObjectsKind };

    CompoundVariableWithSimpleIndirectReferenceAst *variable;
    const KDevPG::ListNode<DimListItemAst *> *offsetItemsSequence;
};

struct KDEVPHPPARSER_EXPORT WhileStatementAst: public AstNode
{
    enum { KIND = WhileStatementKind };

    StatementAst *statement;
    InnerStatementListAst *statements;
};



} // end of namespace PhpParser

#endif

