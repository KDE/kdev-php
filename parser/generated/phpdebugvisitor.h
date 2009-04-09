// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef PHP_DEBUG_VISITOR_H_INCLUDED
#define PHP_DEBUG_VISITOR_H_INCLUDED

#include "phpdefaultvisitor.h"

#include <parserexport.h>
#include <kdev-pg-token-stream.h>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

namespace Php
{

class KDEVPHPPARSER_EXPORT DebugVisitor: public DefaultVisitor
{
public:
    DebugVisitor(TokenStream *str, const QString& content = QString())
            : m_str(str), m_indent(0), m_content(content) {}
    virtual void visitAdditiveExpression(AdditiveExpressionAst *node)
    {
        if (!m_indent) printToken(node, "additiveExpression");
        if (node->expression) printToken(node->expression, "multiplicativeExpression", "expression");
        if (node->additionalExpressionSequence)
        {
            const KDevPG::ListNode<AdditiveExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "additiveExpressionRest", "additionalExpression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitAdditiveExpression(node);
        m_indent--;
    }

    virtual void visitAdditiveExpressionRest(AdditiveExpressionRestAst *node)
    {
        if (!m_indent) printToken(node, "additiveExpressionRest");
        if (node->expression) printToken(node->expression, "multiplicativeExpression", "expression");
        m_indent++;
        DefaultVisitor::visitAdditiveExpressionRest(node);
        m_indent--;
    }

    virtual void visitArrayPairValue(ArrayPairValueAst *node)
    {
        if (!m_indent) printToken(node, "arrayPairValue");
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->exprValue) printToken(node->exprValue, "expr", "exprValue");
        if (node->varValue) printToken(node->varValue, "variable", "varValue");
        if (node->variable) printToken(node->variable, "variable", "variable");
        m_indent++;
        DefaultVisitor::visitArrayPairValue(node);
        m_indent--;
    }

    virtual void visitAssignmentExpression(AssignmentExpressionAst *node)
    {
        if (!m_indent) printToken(node, "assignmentExpression");
        if (node->expression) printToken(node->expression, "conditionalExpression", "expression");
        if (node->assignmentExpressionEqual) printToken(node->assignmentExpressionEqual, "assignmentExpressionEqual", "assignmentExpressionEqual");
        if (node->assignmentExpression) printToken(node->assignmentExpression, "assignmentExpression", "assignmentExpression");
        m_indent++;
        DefaultVisitor::visitAssignmentExpression(node);
        m_indent--;
    }

    virtual void visitAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst *node)
    {
        if (!m_indent) printToken(node, "assignmentExpressionCheckIfVariable");
        m_indent++;
        DefaultVisitor::visitAssignmentExpressionCheckIfVariable(node);
        m_indent--;
    }

    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
    {
        if (!m_indent) printToken(node, "assignmentExpressionEqual");
        if (node->assignmentExpression) printToken(node->assignmentExpression, "assignmentExpression", "assignmentExpression");
        m_indent++;
        DefaultVisitor::visitAssignmentExpressionEqual(node);
        m_indent--;
    }

    virtual void visitAssignmentList(AssignmentListAst *node)
    {
        if (!m_indent) printToken(node, "assignmentList");
        if (node->elementSequence)
        {
            const KDevPG::ListNode<AssignmentListElementAst*> *__it = node->elementSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "assignmentListElement", "element[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitAssignmentList(node);
        m_indent--;
    }

    virtual void visitAssignmentListElement(AssignmentListElementAst *node)
    {
        if (!m_indent) printToken(node, "assignmentListElement");
        if (node->variable) printToken(node->variable, "variable", "variable");
        if (node->assignmentList) printToken(node->assignmentList, "assignmentList", "assignmentList");
        m_indent++;
        DefaultVisitor::visitAssignmentListElement(node);
        m_indent--;
    }

    virtual void visitBaseVariable(BaseVariableAst *node)
    {
        if (!m_indent) printToken(node, "baseVariable");
        if (node->var) printToken(node->var, "compoundVariableWithSimpleIndirectReference", "var");
        if (node->offsetItemsSequence)
        {
            const KDevPG::ListNode<DimListItemAst*> *__it = node->offsetItemsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "dimListItem", "offsetItems[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->staticMember) printToken(node->staticMember, "staticMember", "staticMember");
        m_indent++;
        DefaultVisitor::visitBaseVariable(node);
        m_indent--;
    }

    virtual void visitBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst *node)
    {
        if (!m_indent) printToken(node, "baseVariableWithFunctionCalls");
        if (node->functionCall) printToken(node->functionCall, "functionCall", "functionCall");
        if (node->baseVariable) printToken(node->baseVariable, "baseVariable", "baseVariable");
        m_indent++;
        DefaultVisitor::visitBaseVariableWithFunctionCalls(node);
        m_indent--;
    }

    virtual void visitBitAndExpression(BitAndExpressionAst *node)
    {
        if (!m_indent) printToken(node, "bitAndExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<EqualityExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "equalityExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitBitAndExpression(node);
        m_indent--;
    }

    virtual void visitBitOrExpression(BitOrExpressionAst *node)
    {
        if (!m_indent) printToken(node, "bitOrExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<BitXorExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "bitXorExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitBitOrExpression(node);
        m_indent--;
    }

    virtual void visitBitXorExpression(BitXorExpressionAst *node)
    {
        if (!m_indent) printToken(node, "bitXorExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<BitAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "bitAndExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitBitXorExpression(node);
        m_indent--;
    }

    virtual void visitBooleanAndExpression(BooleanAndExpressionAst *node)
    {
        if (!m_indent) printToken(node, "booleanAndExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<BitOrExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "bitOrExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitBooleanAndExpression(node);
        m_indent--;
    }

    virtual void visitBooleanOrExpression(BooleanOrExpressionAst *node)
    {
        if (!m_indent) printToken(node, "booleanOrExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<BooleanAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "booleanAndExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitBooleanOrExpression(node);
        m_indent--;
    }

    virtual void visitCaseList(CaseListAst *node)
    {
        if (!m_indent) printToken(node, "caseList");
        if (node->caseItemsSequence)
        {
            const KDevPG::ListNode<Case_itemAst*> *__it = node->caseItemsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "case_item", "caseItems[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitCaseList(node);
        m_indent--;
    }

    virtual void visitCase_item(Case_itemAst *node)
    {
        if (!m_indent) printToken(node, "case_item");
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitCase_item(node);
        m_indent--;
    }

    virtual void visitCatchItem(CatchItemAst *node)
    {
        if (!m_indent) printToken(node, "catchItem");
        if (node->catchClass) printToken(node->catchClass, "identifier", "catchClass");
        if (node->var) printToken(node->var, "variableIdentifier", "var");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitCatchItem(node);
        m_indent--;
    }

    virtual void visitClassBody(ClassBodyAst *node)
    {
        if (!m_indent) printToken(node, "classBody");
        if (node->classStatementsSequence)
        {
            const KDevPG::ListNode<ClassStatementAst*> *__it = node->classStatementsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "classStatement", "classStatements[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitClassBody(node);
        m_indent--;
    }

    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *node)
    {
        if (!m_indent) printToken(node, "classConstantDeclaration");
        if (node->identifier) printToken(node->identifier, "identifier", "identifier");
        if (node->scalar) printToken(node->scalar, "staticScalar", "scalar");
        m_indent++;
        DefaultVisitor::visitClassConstantDeclaration(node);
        m_indent--;
    }

    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node)
    {
        if (!m_indent) printToken(node, "classDeclarationStatement");
        if (node->modifier) printToken(node->modifier, "optionalClassModifier", "modifier");
        if (node->className) printToken(node->className, "identifier", "className");
        if (node->extends) printToken(node->extends, "classExtends", "extends");
        if (node->implements) printToken(node->implements, "classImplements", "implements");
        if (node->body) printToken(node->body, "classBody", "body");
        m_indent++;
        DefaultVisitor::visitClassDeclarationStatement(node);
        m_indent--;
    }

    virtual void visitClassExtends(ClassExtendsAst *node)
    {
        if (!m_indent) printToken(node, "classExtends");
        if (node->identifier) printToken(node->identifier, "identifier", "identifier");
        m_indent++;
        DefaultVisitor::visitClassExtends(node);
        m_indent--;
    }

    virtual void visitClassImplements(ClassImplementsAst *node)
    {
        if (!m_indent) printToken(node, "classImplements");
        if (node->implementsSequence)
        {
            const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "identifier", "implements[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitClassImplements(node);
        m_indent--;
    }

    virtual void visitClassNameReference(ClassNameReferenceAst *node)
    {
        if (!m_indent) printToken(node, "classNameReference");
        if (node->identifier) printToken(node->identifier, "identifier", "identifier");
        if (node->dynamicClassNameReference) printToken(node->dynamicClassNameReference, "dynamicClassNameReference", "dynamicClassNameReference");
        m_indent++;
        DefaultVisitor::visitClassNameReference(node);
        m_indent--;
    }

    virtual void visitClassStatement(ClassStatementAst *node)
    {
        if (!m_indent) printToken(node, "classStatement");
        if (node->consts) printToken(node->consts, "classConstantDeclaration", "consts");
        if (node->variable) printToken(node->variable, "classVariableDeclaration", "variable");
        if (node->modifiers) printToken(node->modifiers, "optionalModifiers", "modifiers");
        if (node->methodName) printToken(node->methodName, "identifier", "methodName");
        if (node->parameters) printToken(node->parameters, "parameterList", "parameters");
        if (node->methodBody) printToken(node->methodBody, "methodBody", "methodBody");
        m_indent++;
        DefaultVisitor::visitClassStatement(node);
        m_indent--;
    }

    virtual void visitClassVariable(ClassVariableAst *node)
    {
        if (!m_indent) printToken(node, "classVariable");
        if (node->variable) printToken(node->variable, "variableIdentifier", "variable");
        if (node->value) printToken(node->value, "staticScalar", "value");
        m_indent++;
        DefaultVisitor::visitClassVariable(node);
        m_indent--;
    }

    virtual void visitClassVariableDeclaration(ClassVariableDeclarationAst *node)
    {
        if (!m_indent) printToken(node, "classVariableDeclaration");
        if (node->varsSequence)
        {
            const KDevPG::ListNode<ClassVariableAst*> *__it = node->varsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "classVariable", "vars[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitClassVariableDeclaration(node);
        m_indent--;
    }

    virtual void visitCommonScalar(CommonScalarAst *node)
    {
        if (!m_indent) printToken(node, "commonScalar");
        m_indent++;
        DefaultVisitor::visitCommonScalar(node);
        m_indent--;
    }

    virtual void visitCompoundVariable(CompoundVariableAst *node)
    {
        if (!m_indent) printToken(node, "compoundVariable");
        if (node->variable) printToken(node->variable, "variableIdentifier", "variable");
        if (node->expr) printToken(node->expr, "expr", "expr");
        m_indent++;
        DefaultVisitor::visitCompoundVariable(node);
        m_indent--;
    }

    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
    {
        if (!m_indent) printToken(node, "compoundVariableWithSimpleIndirectReference");
        if (node->indirectVariable) printToken(node->indirectVariable, "variableIdentifier", "indirectVariable");
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->variable) printToken(node->variable, "variableIdentifier", "variable");
        m_indent++;
        DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
        m_indent--;
    }

    virtual void visitConditionalExpression(ConditionalExpressionAst *node)
    {
        if (!m_indent) printToken(node, "conditionalExpression");
        if (node->expression) printToken(node->expression, "booleanOrExpression", "expression");
        if (node->ifExpression) printToken(node->ifExpression, "expr", "ifExpression");
        if (node->elseExpression) printToken(node->elseExpression, "conditionalExpression", "elseExpression");
        m_indent++;
        DefaultVisitor::visitConditionalExpression(node);
        m_indent--;
    }

    virtual void visitConstantOrClassConst(ConstantOrClassConstAst *node)
    {
        if (!m_indent) printToken(node, "constantOrClassConst");
        if (node->className) printToken(node->className, "identifier", "className");
        if (node->constant) printToken(node->constant, "identifier", "constant");
        m_indent++;
        DefaultVisitor::visitConstantOrClassConst(node);
        m_indent--;
    }

    virtual void visitCtorArguments(CtorArgumentsAst *node)
    {
        if (!m_indent) printToken(node, "ctorArguments");
        if (node->parameterList) printToken(node->parameterList, "functionCallParameterList", "parameterList");
        m_indent++;
        DefaultVisitor::visitCtorArguments(node);
        m_indent--;
    }

    virtual void visitDeclareItem(DeclareItemAst *node)
    {
        if (!m_indent) printToken(node, "declareItem");
        if (node->scalar) printToken(node->scalar, "staticScalar", "scalar");
        m_indent++;
        DefaultVisitor::visitDeclareItem(node);
        m_indent--;
    }

    virtual void visitDeclareStatement(DeclareStatementAst *node)
    {
        if (!m_indent) printToken(node, "declareStatement");
        if (node->statement) printToken(node->statement, "statement", "statement");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitDeclareStatement(node);
        m_indent--;
    }

    virtual void visitDimListItem(DimListItemAst *node)
    {
        if (!m_indent) printToken(node, "dimListItem");
        if (node->dimOffset) printToken(node->dimOffset, "dimOffset", "dimOffset");
        if (node->expr) printToken(node->expr, "expr", "expr");
        m_indent++;
        DefaultVisitor::visitDimListItem(node);
        m_indent--;
    }

    virtual void visitDimOffset(DimOffsetAst *node)
    {
        if (!m_indent) printToken(node, "dimOffset");
        if (node->expr) printToken(node->expr, "expr", "expr");
        m_indent++;
        DefaultVisitor::visitDimOffset(node);
        m_indent--;
    }

    virtual void visitDynamicClassNameReference(DynamicClassNameReferenceAst *node)
    {
        if (!m_indent) printToken(node, "dynamicClassNameReference");
        if (node->baseVariable) printToken(node->baseVariable, "baseVariable", "baseVariable");
        if (node->objectProperty) printToken(node->objectProperty, "objectProperty", "objectProperty");
        if (node->properties) printToken(node->properties, "dynamicClassNameVariableProperties", "properties");
        m_indent++;
        DefaultVisitor::visitDynamicClassNameReference(node);
        m_indent--;
    }

    virtual void visitDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst *node)
    {
        if (!m_indent) printToken(node, "dynamicClassNameVariableProperties");
        if (node->propertiesSequence)
        {
            const KDevPG::ListNode<DynamicClassNameVariablePropertyAst*> *__it = node->propertiesSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "dynamicClassNameVariableProperty", "properties[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitDynamicClassNameVariableProperties(node);
        m_indent--;
    }

    virtual void visitDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst *node)
    {
        if (!m_indent) printToken(node, "dynamicClassNameVariableProperty");
        if (node->property) printToken(node->property, "objectProperty", "property");
        m_indent++;
        DefaultVisitor::visitDynamicClassNameVariableProperty(node);
        m_indent--;
    }

    virtual void visitElseSingle(ElseSingleAst *node)
    {
        if (!m_indent) printToken(node, "elseSingle");
        if (node->statement) printToken(node->statement, "statement", "statement");
        m_indent++;
        DefaultVisitor::visitElseSingle(node);
        m_indent--;
    }

    virtual void visitElseifList(ElseifListAst *node)
    {
        if (!m_indent) printToken(node, "elseifList");
        if (node->elseifListItemSequence)
        {
            const KDevPG::ListNode<ElseifListItemAst*> *__it = node->elseifListItemSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "elseifListItem", "elseifListItem[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitElseifList(node);
        m_indent--;
    }

    virtual void visitElseifListItem(ElseifListItemAst *node)
    {
        if (!m_indent) printToken(node, "elseifListItem");
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->statement) printToken(node->statement, "statement", "statement");
        m_indent++;
        DefaultVisitor::visitElseifListItem(node);
        m_indent--;
    }

    virtual void visitEncaps(EncapsAst *node)
    {
        if (!m_indent) printToken(node, "encaps");
        if (node->var) printToken(node->var, "encapsVar", "var");
        m_indent++;
        DefaultVisitor::visitEncaps(node);
        m_indent--;
    }

    virtual void visitEncapsList(EncapsListAst *node)
    {
        if (!m_indent) printToken(node, "encapsList");
        if (node->encapsSequence)
        {
            const KDevPG::ListNode<EncapsAst*> *__it = node->encapsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "encaps", "encaps[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitEncapsList(node);
        m_indent--;
    }

    virtual void visitEncapsVar(EncapsVarAst *node)
    {
        if (!m_indent) printToken(node, "encapsVar");
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->variable) printToken(node->variable, "variableIdentifier", "variable");
        if (node->propertyIdentifier) printToken(node->propertyIdentifier, "identifier", "propertyIdentifier");
        if (node->offset) printToken(node->offset, "encapsVarOffset", "offset");
        m_indent++;
        DefaultVisitor::visitEncapsVar(node);
        m_indent--;
    }

    virtual void visitEncapsVarOffset(EncapsVarOffsetAst *node)
    {
        if (!m_indent) printToken(node, "encapsVarOffset");
        m_indent++;
        DefaultVisitor::visitEncapsVarOffset(node);
        m_indent--;
    }

    virtual void visitEqualityExpression(EqualityExpressionAst *node)
    {
        if (!m_indent) printToken(node, "equalityExpression");
        if (node->expression) printToken(node->expression, "relationalExpression", "expression");
        if (node->additionalExpressionSequence)
        {
            const KDevPG::ListNode<EqualityExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "equalityExpressionRest", "additionalExpression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitEqualityExpression(node);
        m_indent--;
    }

    virtual void visitEqualityExpressionRest(EqualityExpressionRestAst *node)
    {
        if (!m_indent) printToken(node, "equalityExpressionRest");
        if (node->expression) printToken(node->expression, "relationalExpression", "expression");
        m_indent++;
        DefaultVisitor::visitEqualityExpressionRest(node);
        m_indent--;
    }

    virtual void visitExpr(ExprAst *node)
    {
        if (!m_indent) printToken(node, "expr");
        if (node->expression) printToken(node->expression, "logicalOrExpression", "expression");
        m_indent++;
        DefaultVisitor::visitExpr(node);
        m_indent--;
    }

    virtual void visitForExpr(ForExprAst *node)
    {
        if (!m_indent) printToken(node, "forExpr");
        if (node->exprsSequence)
        {
            const KDevPG::ListNode<ExprAst*> *__it = node->exprsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "expr", "exprs[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitForExpr(node);
        m_indent--;
    }

    virtual void visitForStatement(ForStatementAst *node)
    {
        if (!m_indent) printToken(node, "forStatement");
        if (node->statement) printToken(node->statement, "statement", "statement");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitForStatement(node);
        m_indent--;
    }

    virtual void visitForeachStatement(ForeachStatementAst *node)
    {
        if (!m_indent) printToken(node, "foreachStatement");
        if (node->statement) printToken(node->statement, "statement", "statement");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitForeachStatement(node);
        m_indent--;
    }

    virtual void visitForeachVariable(ForeachVariableAst *node)
    {
        if (!m_indent) printToken(node, "foreachVariable");
        if (node->variable) printToken(node->variable, "variableIdentifier", "variable");
        m_indent++;
        DefaultVisitor::visitForeachVariable(node);
        m_indent--;
    }

    virtual void visitFunctionCall(FunctionCallAst *node)
    {
        if (!m_indent) printToken(node, "functionCall");
        if (node->stringFunctionNameOrClass) printToken(node->stringFunctionNameOrClass, "identifier", "stringFunctionNameOrClass");
        if (node->stringParameterList) printToken(node->stringParameterList, "functionCallParameterList", "stringParameterList");
        if (node->stringFunctionName) printToken(node->stringFunctionName, "identifier", "stringFunctionName");
        if (node->varFunctionName) printToken(node->varFunctionName, "variableWithoutObjects", "varFunctionName");
        if (node->varParameterList) printToken(node->varParameterList, "functionCallParameterList", "varParameterList");
        m_indent++;
        DefaultVisitor::visitFunctionCall(node);
        m_indent--;
    }

    virtual void visitFunctionCallParameterList(FunctionCallParameterListAst *node)
    {
        if (!m_indent) printToken(node, "functionCallParameterList");
        if (node->parametersSequence)
        {
            const KDevPG::ListNode<FunctionCallParameterListElementAst*> *__it = node->parametersSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "functionCallParameterListElement", "parameters[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitFunctionCallParameterList(node);
        m_indent--;
    }

    virtual void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst *node)
    {
        if (!m_indent) printToken(node, "functionCallParameterListElement");
        if (node->variable) printToken(node->variable, "variable", "variable");
        if (node->expr) printToken(node->expr, "expr", "expr");
        m_indent++;
        DefaultVisitor::visitFunctionCallParameterListElement(node);
        m_indent--;
    }

    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node)
    {
        if (!m_indent) printToken(node, "functionDeclarationStatement");
        if (node->functionName) printToken(node->functionName, "identifier", "functionName");
        if (node->parameters) printToken(node->parameters, "parameterList", "parameters");
        if (node->functionBody) printToken(node->functionBody, "innerStatementList", "functionBody");
        m_indent++;
        DefaultVisitor::visitFunctionDeclarationStatement(node);
        m_indent--;
    }

    virtual void visitGlobalVar(GlobalVarAst *node)
    {
        if (!m_indent) printToken(node, "globalVar");
        if (node->var) printToken(node->var, "variableIdentifier", "var");
        if (node->dollarVar) printToken(node->dollarVar, "variable", "dollarVar");
        if (node->expr) printToken(node->expr, "expr", "expr");
        m_indent++;
        DefaultVisitor::visitGlobalVar(node);
        m_indent--;
    }

    virtual void visitIdentifier(IdentifierAst *node)
    {
        if (!m_indent) printToken(node, "identifier");
        m_indent++;
        DefaultVisitor::visitIdentifier(node);
        m_indent--;
    }

    virtual void visitInnerStatementList(InnerStatementListAst *node)
    {
        if (!m_indent) printToken(node, "innerStatementList");
        if (node->statementsSequence)
        {
            const KDevPG::ListNode<TopStatementAst*> *__it = node->statementsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "topStatement", "statements[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitInnerStatementList(node);
        m_indent--;
    }

    virtual void visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
    {
        if (!m_indent) printToken(node, "interfaceDeclarationStatement");
        if (node->interfaceName) printToken(node->interfaceName, "identifier", "interfaceName");
        if (node->extends) printToken(node->extends, "classImplements", "extends");
        if (node->body) printToken(node->body, "classBody", "body");
        m_indent++;
        DefaultVisitor::visitInterfaceDeclarationStatement(node);
        m_indent--;
    }

    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *node)
    {
        if (!m_indent) printToken(node, "logicalAndExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<PrintExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "printExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitLogicalAndExpression(node);
        m_indent--;
    }

    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *node)
    {
        if (!m_indent) printToken(node, "logicalOrExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<LogicalXorExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "logicalXorExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitLogicalOrExpression(node);
        m_indent--;
    }

    virtual void visitLogicalXorExpression(LogicalXorExpressionAst *node)
    {
        if (!m_indent) printToken(node, "logicalXorExpression");
        if (node->expressionSequence)
        {
            const KDevPG::ListNode<LogicalAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "logicalAndExpression", "expression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitLogicalXorExpression(node);
        m_indent--;
    }

    virtual void visitMethodBody(MethodBodyAst *node)
    {
        if (!m_indent) printToken(node, "methodBody");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitMethodBody(node);
        m_indent--;
    }

    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *node)
    {
        if (!m_indent) printToken(node, "multiplicativeExpression");
        if (node->expression) printToken(node->expression, "unaryExpression", "expression");
        if (node->additionalExpressionSequence)
        {
            const KDevPG::ListNode<MultiplicativeExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "multiplicativeExpressionRest", "additionalExpression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitMultiplicativeExpression(node);
        m_indent--;
    }

    virtual void visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst *node)
    {
        if (!m_indent) printToken(node, "multiplicativeExpressionRest");
        if (node->expression) printToken(node->expression, "unaryExpression", "expression");
        m_indent++;
        DefaultVisitor::visitMultiplicativeExpressionRest(node);
        m_indent--;
    }

    virtual void visitNewElseSingle(NewElseSingleAst *node)
    {
        if (!m_indent) printToken(node, "newElseSingle");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitNewElseSingle(node);
        m_indent--;
    }

    virtual void visitNewElseifList(NewElseifListAst *node)
    {
        if (!m_indent) printToken(node, "newElseifList");
        if (node->newElseifListItemSequence)
        {
            const KDevPG::ListNode<NewelseifListItemAst*> *__it = node->newElseifListItemSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "newelseifListItem", "newElseifListItem[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitNewElseifList(node);
        m_indent--;
    }

    virtual void visitNewelseifListItem(NewelseifListItemAst *node)
    {
        if (!m_indent) printToken(node, "newelseifListItem");
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitNewelseifListItem(node);
        m_indent--;
    }

    virtual void visitObjectDimList(ObjectDimListAst *node)
    {
        if (!m_indent) printToken(node, "objectDimList");
        if (node->variableName) printToken(node->variableName, "variableName", "variableName");
        if (node->offsetItemsSequence)
        {
            const KDevPG::ListNode<DimListItemAst*> *__it = node->offsetItemsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "dimListItem", "offsetItems[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitObjectDimList(node);
        m_indent--;
    }

    virtual void visitObjectProperty(ObjectPropertyAst *node)
    {
        if (!m_indent) printToken(node, "objectProperty");
        if (node->objectDimList) printToken(node->objectDimList, "objectDimList", "objectDimList");
        if (node->variableWithoutObjects) printToken(node->variableWithoutObjects, "variableWithoutObjects", "variableWithoutObjects");
        m_indent++;
        DefaultVisitor::visitObjectProperty(node);
        m_indent--;
    }

    virtual void visitOptionalClassModifier(OptionalClassModifierAst *node)
    {
        if (!m_indent) printToken(node, "optionalClassModifier");
        m_indent++;
        DefaultVisitor::visitOptionalClassModifier(node);
        m_indent--;
    }

    virtual void visitOptionalModifiers(OptionalModifiersAst *node)
    {
        if (!m_indent) printToken(node, "optionalModifiers");
        m_indent++;
        DefaultVisitor::visitOptionalModifiers(node);
        m_indent--;
    }

    virtual void visitParameter(ParameterAst *node)
    {
        if (!m_indent) printToken(node, "parameter");
        if (node->parameterType) printToken(node->parameterType, "identifier", "parameterType");
        if (node->variable) printToken(node->variable, "variableIdentifier", "variable");
        if (node->defaultValue) printToken(node->defaultValue, "staticScalar", "defaultValue");
        m_indent++;
        DefaultVisitor::visitParameter(node);
        m_indent--;
    }

    virtual void visitParameterList(ParameterListAst *node)
    {
        if (!m_indent) printToken(node, "parameterList");
        if (node->parametersSequence)
        {
            const KDevPG::ListNode<ParameterAst*> *__it = node->parametersSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "parameter", "parameters[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitParameterList(node);
        m_indent--;
    }

    virtual void visitPostprefixOperator(PostprefixOperatorAst *node)
    {
        if (!m_indent) printToken(node, "postprefixOperator");
        m_indent++;
        DefaultVisitor::visitPostprefixOperator(node);
        m_indent--;
    }

    virtual void visitPrintExpression(PrintExpressionAst *node)
    {
        if (!m_indent) printToken(node, "printExpression");
        if (node->expression) printToken(node->expression, "assignmentExpression", "expression");
        m_indent++;
        DefaultVisitor::visitPrintExpression(node);
        m_indent--;
    }

    virtual void visitRelationalExpression(RelationalExpressionAst *node)
    {
        if (!m_indent) printToken(node, "relationalExpression");
        if (node->expression) printToken(node->expression, "shiftExpression", "expression");
        if (node->additionalExpressionSequence)
        {
            const KDevPG::ListNode<RelationalExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "relationalExpressionRest", "additionalExpression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->instanceofType) printToken(node->instanceofType, "classNameReference", "instanceofType");
        m_indent++;
        DefaultVisitor::visitRelationalExpression(node);
        m_indent--;
    }

    virtual void visitRelationalExpressionRest(RelationalExpressionRestAst *node)
    {
        if (!m_indent) printToken(node, "relationalExpressionRest");
        if (node->expression) printToken(node->expression, "shiftExpression", "expression");
        m_indent++;
        DefaultVisitor::visitRelationalExpressionRest(node);
        m_indent--;
    }

    virtual void visitScalar(ScalarAst *node)
    {
        if (!m_indent) printToken(node, "scalar");
        if (node->commonScalar) printToken(node->commonScalar, "commonScalar", "commonScalar");
        if (node->constantOrClassConst) printToken(node->constantOrClassConst, "constantOrClassConst", "constantOrClassConst");
        if (node->encapsList) printToken(node->encapsList, "encapsList", "encapsList");
        m_indent++;
        DefaultVisitor::visitScalar(node);
        m_indent--;
    }

    virtual void visitSemicolonOrCloseTag(SemicolonOrCloseTagAst *node)
    {
        if (!m_indent) printToken(node, "semicolonOrCloseTag");
        m_indent++;
        DefaultVisitor::visitSemicolonOrCloseTag(node);
        m_indent--;
    }

    virtual void visitShiftExpression(ShiftExpressionAst *node)
    {
        if (!m_indent) printToken(node, "shiftExpression");
        if (node->expression) printToken(node->expression, "additiveExpression", "expression");
        if (node->additionalExpressionSequence)
        {
            const KDevPG::ListNode<ShiftExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "shiftExpressionRest", "additionalExpression[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitShiftExpression(node);
        m_indent--;
    }

    virtual void visitShiftExpressionRest(ShiftExpressionRestAst *node)
    {
        if (!m_indent) printToken(node, "shiftExpressionRest");
        if (node->expression) printToken(node->expression, "additiveExpression", "expression");
        m_indent++;
        DefaultVisitor::visitShiftExpressionRest(node);
        m_indent--;
    }

    virtual void visitStart(StartAst *node)
    {
        if (!m_indent) printToken(node, "start");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitStart(node);
        m_indent--;
    }

    virtual void visitStatement(StatementAst *node)
    {
        if (!m_indent) printToken(node, "statement");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        if (node->ifExpr) printToken(node->ifExpr, "expr", "ifExpr");
        if (node->ifStatement) printToken(node->ifStatement, "statement", "ifStatement");
        if (node->elseifList) printToken(node->elseifList, "elseifList", "elseifList");
        if (node->elseSingle) printToken(node->elseSingle, "elseSingle", "elseSingle");
        if (node->whileExpr) printToken(node->whileExpr, "expr", "whileExpr");
        if (node->whilteStatement) printToken(node->whilteStatement, "whileStatement", "whilteStatement");
        if (node->forExpr1) printToken(node->forExpr1, "forExpr", "forExpr1");
        if (node->forExpr2) printToken(node->forExpr2, "forExpr", "forExpr2");
        if (node->forExpr3) printToken(node->forExpr3, "forExpr", "forExpr3");
        if (node->forStatement) printToken(node->forStatement, "forStatement", "forStatement");
        if (node->swtichExpr) printToken(node->swtichExpr, "expr", "swtichExpr");
        if (node->switchCaseList) printToken(node->switchCaseList, "switchCaseList", "switchCaseList");
        if (node->foreachVar) printToken(node->foreachVar, "variable", "foreachVar");
        if (node->foreachVarAsVar) printToken(node->foreachVarAsVar, "foreachVariable", "foreachVarAsVar");
        if (node->foreachExpr) printToken(node->foreachExpr, "expr", "foreachExpr");
        if (node->foreachExprAsVar) printToken(node->foreachExprAsVar, "variableIdentifier", "foreachExprAsVar");
        if (node->foreachVariable) printToken(node->foreachVariable, "foreachVariable", "foreachVariable");
        if (node->foreachStatement) printToken(node->foreachStatement, "foreachStatement", "foreachStatement");
        if (node->declareItem) printToken(node->declareItem, "declareItem", "declareItem");
        if (node->catchesSequence)
        {
            const KDevPG::ListNode<CatchItemAst*> *__it = node->catchesSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "catchItem", "catches[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->unsetVariablesSequence)
        {
            const KDevPG::ListNode<VariableAst*> *__it = node->unsetVariablesSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "variable", "unsetVariables[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->expr) printToken(node->expr, "expr", "expr");
        if (node->doStatement) printToken(node->doStatement, "statement", "doStatement");
        if (node->whilteExpr) printToken(node->whilteExpr, "expr", "whilteExpr");
        if (node->breakExpr) printToken(node->breakExpr, "expr", "breakExpr");
        if (node->continueExpr) printToken(node->continueExpr, "expr", "continueExpr");
        if (node->returnExpr) printToken(node->returnExpr, "expr", "returnExpr");
        if (node->globalVarsSequence)
        {
            const KDevPG::ListNode<GlobalVarAst*> *__it = node->globalVarsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "globalVar", "globalVars[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->staticVarsSequence)
        {
            const KDevPG::ListNode<StaticVarAst*> *__it = node->staticVarsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "staticVar", "staticVars[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->echoExprsSequence)
        {
            const KDevPG::ListNode<ExprAst*> *__it = node->echoExprsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "expr", "echoExprs[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->throwExpr) printToken(node->throwExpr, "expr", "throwExpr");
        m_indent++;
        DefaultVisitor::visitStatement(node);
        m_indent--;
    }

    virtual void visitStaticArrayPairValue(StaticArrayPairValueAst *node)
    {
        if (!m_indent) printToken(node, "staticArrayPairValue");
        if (node->val1Sequence)
        {
            const KDevPG::ListNode<StaticScalarAst*> *__it = node->val1Sequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "staticScalar", "val1[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->val2Sequence)
        {
            const KDevPG::ListNode<StaticScalarAst*> *__it = node->val2Sequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "staticScalar", "val2[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitStaticArrayPairValue(node);
        m_indent--;
    }

    virtual void visitStaticMember(StaticMemberAst *node)
    {
        if (!m_indent) printToken(node, "staticMember");
        if (node->className) printToken(node->className, "identifier", "className");
        if (node->variable) printToken(node->variable, "variableWithoutObjects", "variable");
        m_indent++;
        DefaultVisitor::visitStaticMember(node);
        m_indent--;
    }

    virtual void visitStaticScalar(StaticScalarAst *node)
    {
        if (!m_indent) printToken(node, "staticScalar");
        if (node->value) printToken(node->value, "commonScalar", "value");
        if (node->constantOrClassConst) printToken(node->constantOrClassConst, "constantOrClassConst", "constantOrClassConst");
        if (node->plusValue) printToken(node->plusValue, "staticScalar", "plusValue");
        if (node->minusValue) printToken(node->minusValue, "staticScalar", "minusValue");
        if (node->arrayValuesSequence)
        {
            const KDevPG::ListNode<StaticArrayPairValueAst*> *__it = node->arrayValuesSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "staticArrayPairValue", "arrayValues[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitStaticScalar(node);
        m_indent--;
    }

    virtual void visitStaticVar(StaticVarAst *node)
    {
        if (!m_indent) printToken(node, "staticVar");
        if (node->var) printToken(node->var, "variableIdentifier", "var");
        if (node->value) printToken(node->value, "staticScalar", "value");
        m_indent++;
        DefaultVisitor::visitStaticVar(node);
        m_indent--;
    }

    virtual void visitSwitchCaseList(SwitchCaseListAst *node)
    {
        if (!m_indent) printToken(node, "switchCaseList");
        if (node->caseList) printToken(node->caseList, "caseList", "caseList");
        m_indent++;
        DefaultVisitor::visitSwitchCaseList(node);
        m_indent--;
    }

    virtual void visitTopStatement(TopStatementAst *node)
    {
        if (!m_indent) printToken(node, "topStatement");
        if (node->statement) printToken(node->statement, "statement", "statement");
        if (node->functionDeclaration) printToken(node->functionDeclaration, "functionDeclarationStatement", "functionDeclaration");
        if (node->classDeclaration) printToken(node->classDeclaration, "classDeclarationStatement", "classDeclaration");
        if (node->interfaceDeclaration) printToken(node->interfaceDeclaration, "interfaceDeclarationStatement", "interfaceDeclaration");
        m_indent++;
        DefaultVisitor::visitTopStatement(node);
        m_indent--;
    }

    virtual void visitUnaryExpression(UnaryExpressionAst *node)
    {
        if (!m_indent) printToken(node, "unaryExpression");
        if (node->unaryExpression) printToken(node->unaryExpression, "unaryExpression", "unaryExpression");
        if (node->assignmentList) printToken(node->assignmentList, "assignmentList", "assignmentList");
        if (node->expression) printToken(node->expression, "expr", "expression");
        if (node->includeExpression) printToken(node->includeExpression, "unaryExpression", "includeExpression");
        if (node->unaryExpressionNotPlusminus) printToken(node->unaryExpressionNotPlusminus, "unaryExpressionNotPlusminus", "unaryExpressionNotPlusminus");
        m_indent++;
        DefaultVisitor::visitUnaryExpression(node);
        m_indent--;
    }

    virtual void visitUnaryExpressionNotPlusminus(UnaryExpressionNotPlusminusAst *node)
    {
        if (!m_indent) printToken(node, "unaryExpressionNotPlusminus");
        if (node->prefixOperatorSequence)
        {
            const KDevPG::ListNode<PostprefixOperatorAst*> *__it = node->prefixOperatorSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "postprefixOperator", "prefixOperator[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->varExpression) printToken(node->varExpression, "varExpression", "varExpression");
        if (node->postfixOperatorSequence)
        {
            const KDevPG::ListNode<PostprefixOperatorAst*> *__it = node->postfixOperatorSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "postprefixOperator", "postfixOperator[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitUnaryExpressionNotPlusminus(node);
        m_indent--;
    }

    virtual void visitVarExpression(VarExpressionAst *node)
    {
        if (!m_indent) printToken(node, "varExpression");
        if (node->variable) printToken(node->variable, "variable", "variable");
        if (node->newObject) printToken(node->newObject, "varExpressionNewObject", "newObject");
        if (node->varExpressionNormal) printToken(node->varExpressionNormal, "varExpressionNormal", "varExpressionNormal");
        m_indent++;
        DefaultVisitor::visitVarExpression(node);
        m_indent--;
    }

    virtual void visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
    {
        if (!m_indent) printToken(node, "varExpressionNewObject");
        if (node->className) printToken(node->className, "classNameReference", "className");
        if (node->ctor) printToken(node->ctor, "ctorArguments", "ctor");
        m_indent++;
        DefaultVisitor::visitVarExpressionNewObject(node);
        m_indent--;
    }

    virtual void visitVarExpressionNormal(VarExpressionNormalAst *node)
    {
        if (!m_indent) printToken(node, "varExpressionNormal");
        if (node->expression) printToken(node->expression, "expr", "expression");
        if (node->encapsList) printToken(node->encapsList, "encapsList", "encapsList");
        if (node->variable) printToken(node->variable, "variable", "variable");
        if (node->scalar) printToken(node->scalar, "scalar", "scalar");
        if (node->arrayValuesSequence)
        {
            const KDevPG::ListNode<ArrayPairValueAst*> *__it = node->arrayValuesSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "arrayPairValue", "arrayValues[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->issetVariableSequence)
        {
            const KDevPG::ListNode<VariableAst*> *__it = node->issetVariableSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "variable", "issetVariable[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        if (node->emptyVarialbe) printToken(node->emptyVarialbe, "variable", "emptyVarialbe");
        if (node->newObject) printToken(node->newObject, "varExpressionNewObject", "newObject");
        if (node->cloneCar) printToken(node->cloneCar, "varExpressionNormal", "cloneCar");
        m_indent++;
        DefaultVisitor::visitVarExpressionNormal(node);
        m_indent--;
    }

    virtual void visitVariable(VariableAst *node)
    {
        if (!m_indent) printToken(node, "variable");
        if (node->var) printToken(node->var, "baseVariableWithFunctionCalls", "var");
        if (node->variablePropertiesSequence)
        {
            const KDevPG::ListNode<VariablePropertyAst*> *__it = node->variablePropertiesSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "variableProperty", "variableProperties[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitVariable(node);
        m_indent--;
    }

    virtual void visitVariableIdentifier(VariableIdentifierAst *node)
    {
        if (!m_indent) printToken(node, "variableIdentifier");
        m_indent++;
        DefaultVisitor::visitVariableIdentifier(node);
        m_indent--;
    }

    virtual void visitVariableName(VariableNameAst *node)
    {
        if (!m_indent) printToken(node, "variableName");
        if (node->name) printToken(node->name, "identifier", "name");
        if (node->expr) printToken(node->expr, "expr", "expr");
        m_indent++;
        DefaultVisitor::visitVariableName(node);
        m_indent--;
    }

    virtual void visitVariableProperty(VariablePropertyAst *node)
    {
        if (!m_indent) printToken(node, "variableProperty");
        if (node->objectProperty) printToken(node->objectProperty, "objectProperty", "objectProperty");
        if (node->parameterList) printToken(node->parameterList, "functionCallParameterList", "parameterList");
        m_indent++;
        DefaultVisitor::visitVariableProperty(node);
        m_indent--;
    }

    virtual void visitVariableWithoutObjects(VariableWithoutObjectsAst *node)
    {
        if (!m_indent) printToken(node, "variableWithoutObjects");
        if (node->variable) printToken(node->variable, "compoundVariableWithSimpleIndirectReference", "variable");
        if (node->offsetItemsSequence)
        {
            const KDevPG::ListNode<DimListItemAst*> *__it = node->offsetItemsSequence->front(), *__end = __it;
            do
            {
                printToken(__it->element, "dimListItem", "offsetItems[]");
                __it = __it->next;
            }
            while (__it != __end);
        }
        m_indent++;
        DefaultVisitor::visitVariableWithoutObjects(node);
        m_indent--;
    }

    virtual void visitWhileStatement(WhileStatementAst *node)
    {
        if (!m_indent) printToken(node, "whileStatement");
        if (node->statement) printToken(node->statement, "statement", "statement");
        if (node->statements) printToken(node->statements, "innerStatementList", "statements");
        m_indent++;
        DefaultVisitor::visitWhileStatement(node);
        m_indent--;
    }

private:
    void printToken(AstNode *node, const QString &mType, const QString &mName = QString())
    {
        QString tokenString;
        if (!m_content.isEmpty())
        {
            TokenStream::Token startToken = m_str->token(node->startToken);
            TokenStream::Token endToken = m_str->token(node->endToken);
            int begin = startToken.begin;
            int end = endToken.end;
            if (end-begin > 30)
            {
                tokenString = m_content.mid(begin, 10);
                tokenString += " ...";
                tokenString += QString("%1 more").arg(end-begin-20);
                tokenString += "... ";
                tokenString += m_content.mid(end-10, 10);
            }
            else
            {
                tokenString = m_content.mid(begin, end-begin+1);
            }
            tokenString = tokenString.replace('\n', "\\n");
            tokenString = tokenString.replace('\r', "\\r");
        }
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) + mName + (!mName.isEmpty() ? "->" : "") + mType + "[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
    }
    TokenStream *m_str;
    int m_indent;
    QString m_content;
};

} // end of namespace Php

#endif

