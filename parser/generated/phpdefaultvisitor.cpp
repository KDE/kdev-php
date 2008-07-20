// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "phpdefaultvisitor.h"

namespace Php
{

void DefaultVisitor::visitAdditiveExpression(AdditiveExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<AdditiveExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAdditiveExpressionRest(AdditiveExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitArrayPairValue(ArrayPairValueAst *node)
{
    visitNode(node->expr);
    visitNode(node->exprValue);
    visitNode(node->varValue);
    visitNode(node->variable);
}

void DefaultVisitor::visitAssignmentExpression(AssignmentExpressionAst *node)
{
    visitNode(node->expression);
    visitNode(node->assignmentAxpressionEqual);
    visitNode(node->assignmentExpression);
}

void DefaultVisitor::visitAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst *)
{
}

void DefaultVisitor::visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
{
    visitNode(node->assignmentExpression);
}

void DefaultVisitor::visitAssignmentList(AssignmentListAst *node)
{
    if (node->elementSequence)
    {
        const KDevPG::ListNode<AssignmentListElementAst*> *__it = node->elementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAssignmentListElement(AssignmentListElementAst *node)
{
    visitNode(node->variable);
    visitNode(node->assignmentList);
}

void DefaultVisitor::visitBaseVariable(BaseVariableAst *node)
{
    visitNode(node->var);
    if (node->offsetItemsSequence)
    {
        const KDevPG::ListNode<DimListItemAst*> *__it = node->offsetItemsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->staticMember);
}

void DefaultVisitor::visitBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst *node)
{
    visitNode(node->functionCall);
    visitNode(node->baseVariable);
}

void DefaultVisitor::visitBitAndExpression(BitAndExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<EqualityExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBitOrExpression(BitOrExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BitXorExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBitXorExpression(BitXorExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BitAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBooleanAndExpression(BooleanAndExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BitOrExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBooleanOrExpression(BooleanOrExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BooleanAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitCaseList(CaseListAst *node)
{
    if (node->caseItemsSequence)
    {
        const KDevPG::ListNode<Case_itemAst*> *__it = node->caseItemsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitCase_item(Case_itemAst *node)
{
    visitNode(node->expr);
    visitNode(node->statements);
}

void DefaultVisitor::visitCatch_item(Catch_itemAst *node)
{
    visitNode(node->statements);
}

void DefaultVisitor::visitClassBody(ClassBodyAst *node)
{
    if (node->classStatementsSequence)
    {
        const KDevPG::ListNode<ClassStatementAst*> *__it = node->classStatementsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitClassConstantDeclaration(ClassConstantDeclarationAst *node)
{
    visitNode(node->identifier);
    visitNode(node->scalar);
}

void DefaultVisitor::visitClassDeclarationStatement(ClassDeclarationStatementAst *node)
{
    visitNode(node->className);
    visitNode(node->extends);
    visitNode(node->implements);
    visitNode(node->body);
}

void DefaultVisitor::visitClassExtends(ClassExtendsAst *node)
{
    visitNode(node->identifier);
}

void DefaultVisitor::visitClassImplements(ClassImplementsAst *node)
{
    if (node->implementsSequence)
    {
        const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitClassNameReference(ClassNameReferenceAst *node)
{
    visitNode(node->identifier);
    visitNode(node->dynamicClassNameReference);
}

void DefaultVisitor::visitClassStatement(ClassStatementAst *node)
{
    visitNode(node->consts);
    visitNode(node->variable);
    visitNode(node->modifiers);
    visitNode(node->methodName);
    visitNode(node->parameters);
    visitNode(node->methodBody);
}

void DefaultVisitor::visitClassVariable(ClassVariableAst *node)
{
    visitNode(node->variable);
    visitNode(node->value);
}

void DefaultVisitor::visitClassVariableDeclaration(ClassVariableDeclarationAst *node)
{
    if (node->varsSequence)
    {
        const KDevPG::ListNode<ClassVariableAst*> *__it = node->varsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitCommonScalar(CommonScalarAst *)
{
}

void DefaultVisitor::visitCompoundVariable(CompoundVariableAst *node)
{
    visitNode(node->variable);
    visitNode(node->expr);
}

void DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    visitNode(node->indirectVariable);
    visitNode(node->expr);
    visitNode(node->variable);
}

void DefaultVisitor::visitConditionalExpression(ConditionalExpressionAst *node)
{
    visitNode(node->expression);
    visitNode(node->ifExpression);
    visitNode(node->elseExpression);
}

void DefaultVisitor::visitCtorArguments(CtorArgumentsAst *node)
{
    visitNode(node->parameterList);
}

void DefaultVisitor::visitDeclareItem(DeclareItemAst *node)
{
    visitNode(node->scalar);
}

void DefaultVisitor::visitDeclareStatement(DeclareStatementAst *node)
{
    visitNode(node->statement);
    visitNode(node->statements);
}

void DefaultVisitor::visitDimListItem(DimListItemAst *node)
{
    visitNode(node->dimOffset);
    visitNode(node->expr);
}

void DefaultVisitor::visitDimOffset(DimOffsetAst *node)
{
    visitNode(node->expr);
}

void DefaultVisitor::visitDynamicClassNameReference(DynamicClassNameReferenceAst *node)
{
    visitNode(node->baseVariable);
    visitNode(node->objectProperty);
    visitNode(node->properties);
}

void DefaultVisitor::visitDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst *node)
{
    if (node->propertiesSequence)
    {
        const KDevPG::ListNode<DynamicClassNameVariablePropertyAst*> *__it = node->propertiesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst *node)
{
    visitNode(node->property);
}

void DefaultVisitor::visitElseSingle(ElseSingleAst *node)
{
    visitNode(node->statement);
}

void DefaultVisitor::visitElseifList(ElseifListAst *node)
{
    if (node->elseifListItemSequence)
    {
        const KDevPG::ListNode<ElseifListItemAst*> *__it = node->elseifListItemSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitElseifListItem(ElseifListItemAst *node)
{
    visitNode(node->expr);
    visitNode(node->statement);
}

void DefaultVisitor::visitEncaps(EncapsAst *node)
{
    visitNode(node->var);
}

void DefaultVisitor::visitEncapsList(EncapsListAst *node)
{
    if (node->encapsSequence)
    {
        const KDevPG::ListNode<EncapsAst*> *__it = node->encapsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEncapsVar(EncapsVarAst *node)
{
    visitNode(node->expr);
    visitNode(node->offset);
}

void DefaultVisitor::visitEncapsVarOffset(EncapsVarOffsetAst *)
{
}

void DefaultVisitor::visitEqualityExpression(EqualityExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<EqualityExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEqualityExpressionRest(EqualityExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitExpr(ExprAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitForExpr(ForExprAst *node)
{
    if (node->exprsSequence)
    {
        const KDevPG::ListNode<ExprAst*> *__it = node->exprsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitForStatement(ForStatementAst *node)
{
    visitNode(node->statement);
    visitNode(node->statements);
}

void DefaultVisitor::visitForeachOptionalArg(ForeachOptionalArgAst *node)
{
    visitNode(node->foreachVariable);
}

void DefaultVisitor::visitForeachStatement(ForeachStatementAst *node)
{
    visitNode(node->statement);
    visitNode(node->statements);
}

void DefaultVisitor::visitForeachVariable(ForeachVariableAst *node)
{
    visitNode(node->variable);
}

void DefaultVisitor::visitFunctionCall(FunctionCallAst *node)
{
    visitNode(node->stringFunctionNameOrClass);
    visitNode(node->stringParameterList);
    visitNode(node->stringFunctionName);
    visitNode(node->varFunctionName);
    visitNode(node->varParameterList);
}

void DefaultVisitor::visitFunctionCallParameterList(FunctionCallParameterListAst *node)
{
    if (node->parametersSequence)
    {
        const KDevPG::ListNode<FunctionCallParameterListElementAst*> *__it = node->parametersSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFunctionCallParameterListElement(FunctionCallParameterListElementAst *node)
{
    visitNode(node->variable);
    visitNode(node->expr);
}

void DefaultVisitor::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node)
{
    visitNode(node->functionName);
    visitNode(node->parameters);
    visitNode(node->functionBody);
}

void DefaultVisitor::visitGlobalVar(GlobalVarAst *node)
{
    visitNode(node->var);
    visitNode(node->dollarVar);
    visitNode(node->expr);
}

void DefaultVisitor::visitIdentifier(IdentifierAst *)
{
}

void DefaultVisitor::visitInnerStatementList(InnerStatementListAst *node)
{
    if (node->statementsSequence)
    {
        const KDevPG::ListNode<TopStatementAst*> *__it = node->statementsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
{
    visitNode(node->interfaceName);
    visitNode(node->extends);
    visitNode(node->body);
}

void DefaultVisitor::visitLogicalAndExpression(LogicalAndExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<PrintExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitLogicalOrExpression(LogicalOrExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<LogicalXorExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitLogicalXorExpression(LogicalXorExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<LogicalAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMethodBody(MethodBodyAst *node)
{
    visitNode(node->statements);
}

void DefaultVisitor::visitMultiplicativeExpression(MultiplicativeExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<MultiplicativeExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitNewElseSingle(NewElseSingleAst *node)
{
    visitNode(node->statements);
}

void DefaultVisitor::visitNewElseifList(NewElseifListAst *node)
{
    if (node->newElseifListItemSequence)
    {
        const KDevPG::ListNode<NewelseifListItemAst*> *__it = node->newElseifListItemSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitNewelseifListItem(NewelseifListItemAst *node)
{
    visitNode(node->expr);
    visitNode(node->statements);
}

void DefaultVisitor::visitObjectDimList(ObjectDimListAst *node)
{
    visitNode(node->variableName);
    if (node->offsetItemsSequence)
    {
        const KDevPG::ListNode<DimListItemAst*> *__it = node->offsetItemsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitObjectProperty(ObjectPropertyAst *node)
{
    visitNode(node->objectDimList);
    visitNode(node->variableWithoutObjects);
}

void DefaultVisitor::visitOptionalModifiers(OptionalModifiersAst *)
{
}

void DefaultVisitor::visitParameter(ParameterAst *node)
{
    visitNode(node->parameterType);
    visitNode(node->variable);
    visitNode(node->defaultValue);
}

void DefaultVisitor::visitParameterList(ParameterListAst *node)
{
    if (node->parametersSequence)
    {
        const KDevPG::ListNode<ParameterAst*> *__it = node->parametersSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPostprefixOperator(PostprefixOperatorAst *)
{
}

void DefaultVisitor::visitPrintExpression(PrintExpressionAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitRelationalExpression(RelationalExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<RelationalExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->instanceofType);
}

void DefaultVisitor::visitRelationalExpressionRest(RelationalExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitScalar(ScalarAst *node)
{
    visitNode(node->commonScalar);
    visitNode(node->encapsList);
}

void DefaultVisitor::visitSemicolonOrCloseTag(SemicolonOrCloseTagAst *)
{
}

void DefaultVisitor::visitShiftExpression(ShiftExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<ShiftExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitShiftExpressionRest(ShiftExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitStart(StartAst *node)
{
    visitNode(node->statements);
}

void DefaultVisitor::visitStatement(StatementAst *node)
{
    visitNode(node->statements);
    visitNode(node->ifExpr);
    visitNode(node->ifStatement);
    visitNode(node->elseifList);
    visitNode(node->elseSingle);
    visitNode(node->whileExpr);
    visitNode(node->whilteStatement);
    visitNode(node->forExpr1);
    visitNode(node->forExpr2);
    visitNode(node->forExpr3);
    visitNode(node->forStatement);
    visitNode(node->swtichExpr);
    visitNode(node->switchCaseList);
    visitNode(node->foreachVar);
    visitNode(node->foreachVarAsVar);
    visitNode(node->foreachExpr);
    visitNode(node->foreachExprAsVar);
    visitNode(node->foreachArg);
    visitNode(node->foreachStatement);
    visitNode(node->declareItem);
    if (node->catchesSequence)
    {
        const KDevPG::ListNode<Catch_itemAst*> *__it = node->catchesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->unsetVariablesSequence)
    {
        const KDevPG::ListNode<VariableAst*> *__it = node->unsetVariablesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->expr);
    visitNode(node->doStatement);
    visitNode(node->whilteExpr);
    visitNode(node->breakExpr);
    visitNode(node->continueExpr);
    visitNode(node->returnExpr);
    if (node->globalVarsSequence)
    {
        const KDevPG::ListNode<GlobalVarAst*> *__it = node->globalVarsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->staticVarsSequence)
    {
        const KDevPG::ListNode<StaticVarAst*> *__it = node->staticVarsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->echoExprsSequence)
    {
        const KDevPG::ListNode<ExprAst*> *__it = node->echoExprsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->throwExpr);
}

void DefaultVisitor::visitStaticArrayPairValue(StaticArrayPairValueAst *node)
{
    if (node->val1Sequence)
    {
        const KDevPG::ListNode<StaticScalarAst*> *__it = node->val1Sequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->val2Sequence)
    {
        const KDevPG::ListNode<StaticScalarAst*> *__it = node->val2Sequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitStaticMember(StaticMemberAst *node)
{
    visitNode(node->className);
    visitNode(node->variable);
}

void DefaultVisitor::visitStaticScalar(StaticScalarAst *node)
{
    visitNode(node->value);
    visitNode(node->plusValue);
    visitNode(node->minusValue);
    if (node->arrayValuesSequence)
    {
        const KDevPG::ListNode<StaticArrayPairValueAst*> *__it = node->arrayValuesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitStaticVar(StaticVarAst *node)
{
    visitNode(node->staticScalar);
}

void DefaultVisitor::visitSwitchCaseList(SwitchCaseListAst *node)
{
    visitNode(node->caseList);
}

void DefaultVisitor::visitTopStatement(TopStatementAst *node)
{
    visitNode(node->statement);
    visitNode(node->functionDeclaration);
    visitNode(node->classDeclaration);
    visitNode(node->interfaceDeclaration);
}

void DefaultVisitor::visitUnaryExpression(UnaryExpressionAst *node)
{
    visitNode(node->unaryExpression);
    visitNode(node->assignmentList);
    visitNode(node->expression);
    visitNode(node->unaryExpressionNotPlusminus);
}

void DefaultVisitor::visitUnaryExpressionNotPlusminus(UnaryExpressionNotPlusminusAst *node)
{
    if (node->prefixOperatorSequence)
    {
        const KDevPG::ListNode<PostprefixOperatorAst*> *__it = node->prefixOperatorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->varExpression);
    if (node->postfixOperatorSequence)
    {
        const KDevPG::ListNode<PostprefixOperatorAst*> *__it = node->postfixOperatorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVarExpression(VarExpressionAst *node)
{
    visitNode(node->variable);
    visitNode(node->newObject);
    visitNode(node->varExpressionNormal);
}

void DefaultVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    visitNode(node->className);
    visitNode(node->ctor);
}

void DefaultVisitor::visitVarExpressionNormal(VarExpressionNormalAst *node)
{
    visitNode(node->expression);
    visitNode(node->encapsList);
    visitNode(node->variable);
    visitNode(node->scalar);
    if (node->arrayValuesSequence)
    {
        const KDevPG::ListNode<ArrayPairValueAst*> *__it = node->arrayValuesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->issetVariableSequence)
    {
        const KDevPG::ListNode<VariableAst*> *__it = node->issetVariableSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->emptyVarialbe);
    visitNode(node->newObject);
    visitNode(node->cloneCar);
}

void DefaultVisitor::visitVariable(VariableAst *node)
{
    visitNode(node->var);
    if (node->variablePropertiesSequence)
    {
        const KDevPG::ListNode<VariablePropertyAst*> *__it = node->variablePropertiesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariableIdentifier(VariableIdentifierAst *)
{
}

void DefaultVisitor::visitVariableName(VariableNameAst *node)
{
    visitNode(node->name);
    visitNode(node->expr);
}

void DefaultVisitor::visitVariableProperty(VariablePropertyAst *node)
{
    visitNode(node->objectProperty);
    visitNode(node->parameterList);
}

void DefaultVisitor::visitVariableWithoutObjects(VariableWithoutObjectsAst *node)
{
    visitNode(node->variable);
    if (node->offsetItemsSequence)
    {
        const KDevPG::ListNode<DimListItemAst*> *__it = node->offsetItemsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitWhileStatement(WhileStatementAst *node)
{
    visitNode(node->statement);
    visitNode(node->statements);
}


} // end of namespace Php

