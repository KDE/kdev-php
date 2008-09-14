// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_AST_H_INCLUDED
#define PHP_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>

#include <parserexport.h>


#include <QtCore/QString>
#include <kdebug.h>
#include <tokenstream.h>
#include "phplexer.h"

namespace KDevelop
{
class DUContext;
}


namespace Php
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
struct ClassBodyAst;
struct ClassConstantDeclarationAst;
struct ClassDeclarationStatementAst;
struct ClassExtendsAst;
struct ClassImplementsAst;
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
struct IdentifierAst;
struct InnerStatementListAst;
struct InterfaceDeclarationStatementAst;
struct LogicalAndExpressionAst;
struct LogicalOrExpressionAst;
struct LogicalXorExpressionAst;
struct MethodBodyAst;
struct MultiplicativeExpressionAst;
struct MultiplicativeExpressionRestAst;
struct NewElseSingleAst;
struct NewElseifListAst;
struct NewelseifListItemAst;
struct ObjectDimListAst;
struct ObjectPropertyAst;
struct OptionalModifiersAst;
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
struct UnaryExpressionNotPlusminusAst;
struct VarExpressionAst;
struct VarExpressionNewObjectAst;
struct VarExpressionNormalAst;
struct VariableAst;
struct VariableIdentifierAst;
struct VariableNameAst;
struct VariablePropertyAst;
struct VariableWithoutObjectsAst;
struct WhileStatementAst;


class Lexer;

enum ModifierFlags
{
    ModifierPrivate      = 1,
    ModifierPublic       = 1 << 1,
    ModifierProtected    = 1 << 2,
    ModifierStatic       = 1 << 3,
    ModifierFinal        = 1 << 4,
    ModifierAbstract     = 1 << 5
};

enum ScalarTypes
{
    ScalarTypeNumber,
    ScalarTypeString
};

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
        ClassBodyKind = 1018,
        ClassConstantDeclarationKind = 1019,
        ClassDeclarationStatementKind = 1020,
        ClassExtendsKind = 1021,
        ClassImplementsKind = 1022,
        ClassNameReferenceKind = 1023,
        ClassStatementKind = 1024,
        ClassVariableKind = 1025,
        ClassVariableDeclarationKind = 1026,
        CommonScalarKind = 1027,
        CompoundVariableKind = 1028,
        CompoundVariableWithSimpleIndirectReferenceKind = 1029,
        ConditionalExpressionKind = 1030,
        CtorArgumentsKind = 1031,
        DeclareItemKind = 1032,
        DeclareStatementKind = 1033,
        DimListItemKind = 1034,
        DimOffsetKind = 1035,
        DynamicClassNameReferenceKind = 1036,
        DynamicClassNameVariablePropertiesKind = 1037,
        DynamicClassNameVariablePropertyKind = 1038,
        ElseSingleKind = 1039,
        ElseifListKind = 1040,
        ElseifListItemKind = 1041,
        EncapsKind = 1042,
        EncapsListKind = 1043,
        EncapsVarKind = 1044,
        EncapsVarOffsetKind = 1045,
        EqualityExpressionKind = 1046,
        EqualityExpressionRestKind = 1047,
        ExprKind = 1048,
        ForExprKind = 1049,
        ForStatementKind = 1050,
        ForeachOptionalArgKind = 1051,
        ForeachStatementKind = 1052,
        ForeachVariableKind = 1053,
        FunctionCallKind = 1054,
        FunctionCallParameterListKind = 1055,
        FunctionCallParameterListElementKind = 1056,
        FunctionDeclarationStatementKind = 1057,
        GlobalVarKind = 1058,
        IdentifierKind = 1059,
        InnerStatementListKind = 1060,
        InterfaceDeclarationStatementKind = 1061,
        LogicalAndExpressionKind = 1062,
        LogicalOrExpressionKind = 1063,
        LogicalXorExpressionKind = 1064,
        MethodBodyKind = 1065,
        MultiplicativeExpressionKind = 1066,
        MultiplicativeExpressionRestKind = 1067,
        NewElseSingleKind = 1068,
        NewElseifListKind = 1069,
        NewelseifListItemKind = 1070,
        ObjectDimListKind = 1071,
        ObjectPropertyKind = 1072,
        OptionalModifiersKind = 1073,
        ParameterKind = 1074,
        ParameterListKind = 1075,
        PostprefixOperatorKind = 1076,
        PrintExpressionKind = 1077,
        RelationalExpressionKind = 1078,
        RelationalExpressionRestKind = 1079,
        ScalarKind = 1080,
        SemicolonOrCloseTagKind = 1081,
        ShiftExpressionKind = 1082,
        ShiftExpressionRestKind = 1083,
        StartKind = 1084,
        StatementKind = 1085,
        StaticArrayPairValueKind = 1086,
        StaticMemberKind = 1087,
        StaticScalarKind = 1088,
        StaticVarKind = 1089,
        SwitchCaseListKind = 1090,
        TopStatementKind = 1091,
        UnaryExpressionKind = 1092,
        UnaryExpressionNotPlusminusKind = 1093,
        VarExpressionKind = 1094,
        VarExpressionNewObjectKind = 1095,
        VarExpressionNormalKind = 1096,
        VariableKind = 1097,
        VariableIdentifierKind = 1098,
        VariableNameKind = 1099,
        VariablePropertyKind = 1100,
        VariableWithoutObjectsKind = 1101,
        WhileStatementKind = 1102,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

    KDevelop::DUContext* ducontext;

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

    ConditionalExpressionAst *expression;
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

struct KDEVPHPPARSER_EXPORT ClassBodyAst: public AstNode
{
    enum { KIND = ClassBodyKind };

    const KDevPG::ListNode<ClassStatementAst *> *classStatementsSequence;
};

struct KDEVPHPPARSER_EXPORT ClassConstantDeclarationAst: public AstNode
{
    enum { KIND = ClassConstantDeclarationKind };

    IdentifierAst *identifier;
    StaticScalarAst *scalar;
};

struct KDEVPHPPARSER_EXPORT ClassDeclarationStatementAst: public AstNode
{
    enum { KIND = ClassDeclarationStatementKind };

    IdentifierAst *className;
    ClassExtendsAst *extends;
    ClassImplementsAst *implements;
    ClassBodyAst *body;
};

struct KDEVPHPPARSER_EXPORT ClassExtendsAst: public AstNode
{
    enum { KIND = ClassExtendsKind };

    IdentifierAst *identifier;
};

struct KDEVPHPPARSER_EXPORT ClassImplementsAst: public AstNode
{
    enum { KIND = ClassImplementsKind };

    const KDevPG::ListNode<IdentifierAst *> *implementsSequence;
};

struct KDEVPHPPARSER_EXPORT ClassNameReferenceAst: public AstNode
{
    enum { KIND = ClassNameReferenceKind };

    IdentifierAst *identifier;
    DynamicClassNameReferenceAst *dynamicClassNameReference;
};

struct KDEVPHPPARSER_EXPORT ClassStatementAst: public AstNode
{
    enum { KIND = ClassStatementKind };

    ClassConstantDeclarationAst *consts;
    ClassVariableDeclarationAst *variable;
    OptionalModifiersAst *modifiers;
    IdentifierAst *methodName;
    ParameterListAst *parameters;
    MethodBodyAst *methodBody;
};

struct KDEVPHPPARSER_EXPORT ClassVariableAst: public AstNode
{
    enum { KIND = ClassVariableKind };

    VariableIdentifierAst *variable;
    StaticScalarAst *value;
};

struct KDEVPHPPARSER_EXPORT ClassVariableDeclarationAst: public AstNode
{
    enum { KIND = ClassVariableDeclarationKind };

    const KDevPG::ListNode<ClassVariableAst *> *varsSequence;
};

struct KDEVPHPPARSER_EXPORT CommonScalarAst: public AstNode
{
    enum { KIND = CommonScalarKind };

    ScalarTypes scalarType;
    qint64 string;
};

struct KDEVPHPPARSER_EXPORT CompoundVariableAst: public AstNode
{
    enum { KIND = CompoundVariableKind };

    VariableIdentifierAst *variable;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT CompoundVariableWithSimpleIndirectReferenceAst: public AstNode
{
    enum { KIND = CompoundVariableWithSimpleIndirectReferenceKind };

    VariableIdentifierAst *indirectVariable;
    ExprAst *expr;
    VariableIdentifierAst *variable;
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

    IdentifierAst *stringFunctionNameOrClass;
    FunctionCallParameterListAst *stringParameterList;
    IdentifierAst *stringFunctionName;
    VariableWithoutObjectsAst *varFunctionName;
    FunctionCallParameterListAst *varParameterList;
};

struct KDEVPHPPARSER_EXPORT FunctionCallParameterListAst: public AstNode
{
    enum { KIND = FunctionCallParameterListKind };

    const KDevPG::ListNode<FunctionCallParameterListElementAst *> *parametersSequence;
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

    IdentifierAst *functionName;
    ParameterListAst *parameters;
    InnerStatementListAst *functionBody;
};

struct KDEVPHPPARSER_EXPORT GlobalVarAst: public AstNode
{
    enum { KIND = GlobalVarKind };

    VariableIdentifierAst *var;
    VariableAst *dollarVar;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT IdentifierAst: public AstNode
{
    enum { KIND = IdentifierKind };

    qint64 string;
};

struct KDEVPHPPARSER_EXPORT InnerStatementListAst: public AstNode
{
    enum { KIND = InnerStatementListKind };

    const KDevPG::ListNode<TopStatementAst *> *statementsSequence;
};

struct KDEVPHPPARSER_EXPORT InterfaceDeclarationStatementAst: public AstNode
{
    enum { KIND = InterfaceDeclarationStatementKind };

    IdentifierAst *interfaceName;
    ClassImplementsAst *extends;
    ClassBodyAst *body;
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

struct KDEVPHPPARSER_EXPORT MethodBodyAst: public AstNode
{
    enum { KIND = MethodBodyKind };

    InnerStatementListAst *statements;
};

struct KDEVPHPPARSER_EXPORT MultiplicativeExpressionAst: public AstNode
{
    enum { KIND = MultiplicativeExpressionKind };

    UnaryExpressionAst *expression;
    const KDevPG::ListNode<MultiplicativeExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVPHPPARSER_EXPORT MultiplicativeExpressionRestAst: public AstNode
{
    enum { KIND = MultiplicativeExpressionRestKind };

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

struct KDEVPHPPARSER_EXPORT OptionalModifiersAst: public AstNode
{
    enum { KIND = OptionalModifiersKind };

    unsigned int modifiers;
};

struct KDEVPHPPARSER_EXPORT ParameterAst: public AstNode
{
    enum { KIND = ParameterKind };

    IdentifierAst *parameterType;
    qint64 arrayType;
    VariableIdentifierAst *variable;
    StaticScalarAst *defaultValue;
};

struct KDEVPHPPARSER_EXPORT ParameterListAst: public AstNode
{
    enum { KIND = ParameterListKind };

    const KDevPG::ListNode<ParameterAst *> *parametersSequence;
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
    IdentifierAst *className;
    IdentifierAst *constant;
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

    IdentifierAst *className;
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
    InterfaceDeclarationStatementAst *interfaceDeclaration;
};

struct KDEVPHPPARSER_EXPORT UnaryExpressionAst: public AstNode
{
    enum { KIND = UnaryExpressionKind };

    UnaryExpressionAst *unaryExpression;
    AssignmentListAst *assignmentList;
    ExprAst *expression;
    UnaryExpressionNotPlusminusAst *unaryExpressionNotPlusminus;
};

struct KDEVPHPPARSER_EXPORT UnaryExpressionNotPlusminusAst: public AstNode
{
    enum { KIND = UnaryExpressionNotPlusminusKind };

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

struct KDEVPHPPARSER_EXPORT VariableIdentifierAst: public AstNode
{
    enum { KIND = VariableIdentifierKind };

    qint64 variable;
};

struct KDEVPHPPARSER_EXPORT VariableNameAst: public AstNode
{
    enum { KIND = VariableNameKind };

    IdentifierAst *name;
    ExprAst *expr;
};

struct KDEVPHPPARSER_EXPORT VariablePropertyAst: public AstNode
{
    enum { KIND = VariablePropertyKind };

    ObjectPropertyAst *objectProperty;
    qint64 isFunctionCall;
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



} // end of namespace Php

#endif

