// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_VISITOR_H_INCLUDED
#define PHP_VISITOR_H_INCLUDED

#include "phpast.h"

#include <parserexport.h>
namespace Php
{

class KDEVPHPPARSER_EXPORT Visitor
{
    typedef void (Visitor::*ParserFuncType)(AstNode *);
    static ParserFuncType sParserTable[];

public:
    virtual ~Visitor() {}
    virtual void visitNode(AstNode *node)
    {
        if (node) (this->*sParserTable[node->kind - 1000])(node);
    }
    virtual void visitAdditiveExpression(AdditiveExpressionAst *) {}
    virtual void visitAdditiveExpressionRest(AdditiveExpressionRestAst *) {}
    virtual void visitArrayPairValue(ArrayPairValueAst *) {}
    virtual void visitAssignmentExpression(AssignmentExpressionAst *) {}
    virtual void visitAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst *) {}
    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *) {}
    virtual void visitAssignmentList(AssignmentListAst *) {}
    virtual void visitAssignmentListElement(AssignmentListElementAst *) {}
    virtual void visitBaseVariable(BaseVariableAst *) {}
    virtual void visitBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst *) {}
    virtual void visitBitAndExpression(BitAndExpressionAst *) {}
    virtual void visitBitOrExpression(BitOrExpressionAst *) {}
    virtual void visitBitXorExpression(BitXorExpressionAst *) {}
    virtual void visitBooleanAndExpression(BooleanAndExpressionAst *) {}
    virtual void visitBooleanOrExpression(BooleanOrExpressionAst *) {}
    virtual void visitCaseList(CaseListAst *) {}
    virtual void visitCase_item(Case_itemAst *) {}
    virtual void visitCatch_item(Catch_itemAst *) {}
    virtual void visitClassBody(ClassBodyAst *) {}
    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *) {}
    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *) {}
    virtual void visitClassExtends(ClassExtendsAst *) {}
    virtual void visitClassImplements(ClassImplementsAst *) {}
    virtual void visitClassNameReference(ClassNameReferenceAst *) {}
    virtual void visitClassStatement(ClassStatementAst *) {}
    virtual void visitClassVariable(ClassVariableAst *) {}
    virtual void visitClassVariableDeclaration(ClassVariableDeclarationAst *) {}
    virtual void visitCommonScalar(CommonScalarAst *) {}
    virtual void visitCompoundVariable(CompoundVariableAst *) {}
    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *) {}
    virtual void visitConditionalExpression(ConditionalExpressionAst *) {}
    virtual void visitConstantOrClassConst(ConstantOrClassConstAst *) {}
    virtual void visitCtorArguments(CtorArgumentsAst *) {}
    virtual void visitDeclareItem(DeclareItemAst *) {}
    virtual void visitDeclareStatement(DeclareStatementAst *) {}
    virtual void visitDimListItem(DimListItemAst *) {}
    virtual void visitDimOffset(DimOffsetAst *) {}
    virtual void visitDynamicClassNameReference(DynamicClassNameReferenceAst *) {}
    virtual void visitDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst *) {}
    virtual void visitDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst *) {}
    virtual void visitElseSingle(ElseSingleAst *) {}
    virtual void visitElseifList(ElseifListAst *) {}
    virtual void visitElseifListItem(ElseifListItemAst *) {}
    virtual void visitEncaps(EncapsAst *) {}
    virtual void visitEncapsList(EncapsListAst *) {}
    virtual void visitEncapsVar(EncapsVarAst *) {}
    virtual void visitEncapsVarOffset(EncapsVarOffsetAst *) {}
    virtual void visitEqualityExpression(EqualityExpressionAst *) {}
    virtual void visitEqualityExpressionRest(EqualityExpressionRestAst *) {}
    virtual void visitExpr(ExprAst *) {}
    virtual void visitForExpr(ForExprAst *) {}
    virtual void visitForStatement(ForStatementAst *) {}
    virtual void visitForeachStatement(ForeachStatementAst *) {}
    virtual void visitForeachVariable(ForeachVariableAst *) {}
    virtual void visitFunctionCall(FunctionCallAst *) {}
    virtual void visitFunctionCallParameterList(FunctionCallParameterListAst *) {}
    virtual void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst *) {}
    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *) {}
    virtual void visitGlobalVar(GlobalVarAst *) {}
    virtual void visitIdentifier(IdentifierAst *) {}
    virtual void visitInnerStatementList(InnerStatementListAst *) {}
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *) {}
    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *) {}
    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *) {}
    virtual void visitLogicalXorExpression(LogicalXorExpressionAst *) {}
    virtual void visitMethodBody(MethodBodyAst *) {}
    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *) {}
    virtual void visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst *) {}
    virtual void visitNewElseSingle(NewElseSingleAst *) {}
    virtual void visitNewElseifList(NewElseifListAst *) {}
    virtual void visitNewelseifListItem(NewelseifListItemAst *) {}
    virtual void visitObjectDimList(ObjectDimListAst *) {}
    virtual void visitObjectProperty(ObjectPropertyAst *) {}
    virtual void visitOptionalClassModifier(OptionalClassModifierAst *) {}
    virtual void visitOptionalModifiers(OptionalModifiersAst *) {}
    virtual void visitParameter(ParameterAst *) {}
    virtual void visitParameterList(ParameterListAst *) {}
    virtual void visitPostprefixOperator(PostprefixOperatorAst *) {}
    virtual void visitPrintExpression(PrintExpressionAst *) {}
    virtual void visitRelationalExpression(RelationalExpressionAst *) {}
    virtual void visitRelationalExpressionRest(RelationalExpressionRestAst *) {}
    virtual void visitScalar(ScalarAst *) {}
    virtual void visitSemicolonOrCloseTag(SemicolonOrCloseTagAst *) {}
    virtual void visitShiftExpression(ShiftExpressionAst *) {}
    virtual void visitShiftExpressionRest(ShiftExpressionRestAst *) {}
    virtual void visitStart(StartAst *) {}
    virtual void visitStatement(StatementAst *) {}
    virtual void visitStaticArrayPairValue(StaticArrayPairValueAst *) {}
    virtual void visitStaticMember(StaticMemberAst *) {}
    virtual void visitStaticScalar(StaticScalarAst *) {}
    virtual void visitStaticVar(StaticVarAst *) {}
    virtual void visitSwitchCaseList(SwitchCaseListAst *) {}
    virtual void visitTopStatement(TopStatementAst *) {}
    virtual void visitUnaryExpression(UnaryExpressionAst *) {}
    virtual void visitUnaryExpressionNotPlusminus(UnaryExpressionNotPlusminusAst *) {}
    virtual void visitVarExpression(VarExpressionAst *) {}
    virtual void visitVarExpressionNewObject(VarExpressionNewObjectAst *) {}
    virtual void visitVarExpressionNormal(VarExpressionNormalAst *) {}
    virtual void visitVariable(VariableAst *) {}
    virtual void visitVariableIdentifier(VariableIdentifierAst *) {}
    virtual void visitVariableName(VariableNameAst *) {}
    virtual void visitVariableProperty(VariablePropertyAst *) {}
    virtual void visitVariableWithoutObjects(VariableWithoutObjectsAst *) {}
    virtual void visitWhileStatement(WhileStatementAst *) {}
};

} // end of namespace Php

#endif

