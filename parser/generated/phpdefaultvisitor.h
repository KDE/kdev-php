// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_DEFAULT_VISITOR_H_INCLUDED
#define PHP_DEFAULT_VISITOR_H_INCLUDED

#include "phpvisitor.h"

#include <parserexport.h>
namespace Php
{

class KDEVPHPPARSER_EXPORT DefaultVisitor: public Visitor
{
public:
    virtual void visitAdditiveExpression(AdditiveExpressionAst *node);
    virtual void visitAdditiveExpressionRest(AdditiveExpressionRestAst *node);
    virtual void visitArrayPairValue(ArrayPairValueAst *node);
    virtual void visitAssignmentExpression(AssignmentExpressionAst *node);
    virtual void visitAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst *node);
    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node);
    virtual void visitAssignmentList(AssignmentListAst *node);
    virtual void visitAssignmentListElement(AssignmentListElementAst *node);
    virtual void visitBaseVariable(BaseVariableAst *node);
    virtual void visitBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst *node);
    virtual void visitBitAndExpression(BitAndExpressionAst *node);
    virtual void visitBitOrExpression(BitOrExpressionAst *node);
    virtual void visitBitXorExpression(BitXorExpressionAst *node);
    virtual void visitBooleanAndExpression(BooleanAndExpressionAst *node);
    virtual void visitBooleanOrExpression(BooleanOrExpressionAst *node);
    virtual void visitCaseList(CaseListAst *node);
    virtual void visitCase_item(Case_itemAst *node);
    virtual void visitCatch_item(Catch_itemAst *node);
    virtual void visitClassBody(ClassBodyAst *node);
    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *node);
    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node);
    virtual void visitClassExtends(ClassExtendsAst *node);
    virtual void visitClassImplements(ClassImplementsAst *node);
    virtual void visitClassNameReference(ClassNameReferenceAst *node);
    virtual void visitClassStatement(ClassStatementAst *node);
    virtual void visitClassVariable(ClassVariableAst *node);
    virtual void visitClassVariableDeclaration(ClassVariableDeclarationAst *node);
    virtual void visitCommonScalar(CommonScalarAst *node);
    virtual void visitCompoundVariable(CompoundVariableAst *node);
    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node);
    virtual void visitConditionalExpression(ConditionalExpressionAst *node);
    virtual void visitCtorArguments(CtorArgumentsAst *node);
    virtual void visitDeclareItem(DeclareItemAst *node);
    virtual void visitDeclareStatement(DeclareStatementAst *node);
    virtual void visitDimListItem(DimListItemAst *node);
    virtual void visitDimOffset(DimOffsetAst *node);
    virtual void visitDynamicClassNameReference(DynamicClassNameReferenceAst *node);
    virtual void visitDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst *node);
    virtual void visitDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst *node);
    virtual void visitElseSingle(ElseSingleAst *node);
    virtual void visitElseifList(ElseifListAst *node);
    virtual void visitElseifListItem(ElseifListItemAst *node);
    virtual void visitEncaps(EncapsAst *node);
    virtual void visitEncapsList(EncapsListAst *node);
    virtual void visitEncapsVar(EncapsVarAst *node);
    virtual void visitEncapsVarOffset(EncapsVarOffsetAst *node);
    virtual void visitEqualityExpression(EqualityExpressionAst *node);
    virtual void visitEqualityExpressionRest(EqualityExpressionRestAst *node);
    virtual void visitExpr(ExprAst *node);
    virtual void visitForExpr(ForExprAst *node);
    virtual void visitForStatement(ForStatementAst *node);
    virtual void visitForeachOptionalArg(ForeachOptionalArgAst *node);
    virtual void visitForeachStatement(ForeachStatementAst *node);
    virtual void visitForeachVariable(ForeachVariableAst *node);
    virtual void visitFunctionCall(FunctionCallAst *node);
    virtual void visitFunctionCallParameterList(FunctionCallParameterListAst *node);
    virtual void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst *node);
    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node);
    virtual void visitGlobalVar(GlobalVarAst *node);
    virtual void visitIdentifier(IdentifierAst *node);
    virtual void visitInnerStatementList(InnerStatementListAst *node);
    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node);
    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *node);
    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *node);
    virtual void visitLogicalXorExpression(LogicalXorExpressionAst *node);
    virtual void visitMethodBody(MethodBodyAst *node);
    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *node);
    virtual void visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst *node);
    virtual void visitNewElseSingle(NewElseSingleAst *node);
    virtual void visitNewElseifList(NewElseifListAst *node);
    virtual void visitNewelseifListItem(NewelseifListItemAst *node);
    virtual void visitObjectDimList(ObjectDimListAst *node);
    virtual void visitObjectProperty(ObjectPropertyAst *node);
    virtual void visitOptionalModifiers(OptionalModifiersAst *node);
    virtual void visitParameter(ParameterAst *node);
    virtual void visitParameterList(ParameterListAst *node);
    virtual void visitPostprefixOperator(PostprefixOperatorAst *node);
    virtual void visitPrintExpression(PrintExpressionAst *node);
    virtual void visitRelationalExpression(RelationalExpressionAst *node);
    virtual void visitRelationalExpressionRest(RelationalExpressionRestAst *node);
    virtual void visitScalar(ScalarAst *node);
    virtual void visitSemicolonOrCloseTag(SemicolonOrCloseTagAst *node);
    virtual void visitShiftExpression(ShiftExpressionAst *node);
    virtual void visitShiftExpressionRest(ShiftExpressionRestAst *node);
    virtual void visitStart(StartAst *node);
    virtual void visitStatement(StatementAst *node);
    virtual void visitStaticArrayPairValue(StaticArrayPairValueAst *node);
    virtual void visitStaticMember(StaticMemberAst *node);
    virtual void visitStaticScalar(StaticScalarAst *node);
    virtual void visitStaticVar(StaticVarAst *node);
    virtual void visitSwitchCaseList(SwitchCaseListAst *node);
    virtual void visitTopStatement(TopStatementAst *node);
    virtual void visitUnaryExpression(UnaryExpressionAst *node);
    virtual void visitUnaryExpressionNotPlusminus(UnaryExpressionNotPlusminusAst *node);
    virtual void visitVarExpression(VarExpressionAst *node);
    virtual void visitVarExpressionNewObject(VarExpressionNewObjectAst *node);
    virtual void visitVarExpressionNormal(VarExpressionNormalAst *node);
    virtual void visitVariable(VariableAst *node);
    virtual void visitVariableIdentifier(VariableIdentifierAst *node);
    virtual void visitVariableName(VariableNameAst *node);
    virtual void visitVariableProperty(VariablePropertyAst *node);
    virtual void visitVariableWithoutObjects(VariableWithoutObjectsAst *node);
    virtual void visitWhileStatement(WhileStatementAst *node);
};

} // end of namespace Php

#endif

