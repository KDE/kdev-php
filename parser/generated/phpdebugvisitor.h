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
    DebugVisitor(KDevPG::TokenStream *str, const QString& content = QString())
            : m_str(str), m_indent(0), m_content(content) {}
    virtual void visitAdditiveExpression(AdditiveExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "additiveExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAdditiveExpression(node);
        m_indent--;
    }

    virtual void visitAdditiveExpressionRest(AdditiveExpressionRestAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "additiveExpressionRest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAdditiveExpressionRest(node);
        m_indent--;
    }

    virtual void visitArrayPairValue(ArrayPairValueAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "arrayPairValue[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitArrayPairValue(node);
        m_indent--;
    }

    virtual void visitAssignmentExpression(AssignmentExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "assignmentExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAssignmentExpression(node);
        m_indent--;
    }

    virtual void visitAssignmentExpressionCheckIfVariable(AssignmentExpressionCheckIfVariableAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "assignmentExpressionCheckIfVariable[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAssignmentExpressionCheckIfVariable(node);
        m_indent--;
    }

    virtual void visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "assignmentExpressionEqual[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAssignmentExpressionEqual(node);
        m_indent--;
    }

    virtual void visitAssignmentList(AssignmentListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "assignmentList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAssignmentList(node);
        m_indent--;
    }

    virtual void visitAssignmentListElement(AssignmentListElementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "assignmentListElement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitAssignmentListElement(node);
        m_indent--;
    }

    virtual void visitBaseVariable(BaseVariableAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "baseVariable[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBaseVariable(node);
        m_indent--;
    }

    virtual void visitBaseVariableWithFunctionCalls(BaseVariableWithFunctionCallsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "baseVariableWithFunctionCalls[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBaseVariableWithFunctionCalls(node);
        m_indent--;
    }

    virtual void visitBitAndExpression(BitAndExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "bitAndExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBitAndExpression(node);
        m_indent--;
    }

    virtual void visitBitOrExpression(BitOrExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "bitOrExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBitOrExpression(node);
        m_indent--;
    }

    virtual void visitBitXorExpression(BitXorExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "bitXorExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBitXorExpression(node);
        m_indent--;
    }

    virtual void visitBooleanAndExpression(BooleanAndExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "booleanAndExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBooleanAndExpression(node);
        m_indent--;
    }

    virtual void visitBooleanOrExpression(BooleanOrExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "booleanOrExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitBooleanOrExpression(node);
        m_indent--;
    }

    virtual void visitCaseList(CaseListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "caseList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCaseList(node);
        m_indent--;
    }

    virtual void visitCase_item(Case_itemAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "case_item[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCase_item(node);
        m_indent--;
    }

    virtual void visitCatch_item(Catch_itemAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "catch_item[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCatch_item(node);
        m_indent--;
    }

    virtual void visitClassConstantDeclaration(ClassConstantDeclarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "classConstantDeclaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitClassConstantDeclaration(node);
        m_indent--;
    }

    virtual void visitClassDeclarationStatement(ClassDeclarationStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "classDeclarationStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitClassDeclarationStatement(node);
        m_indent--;
    }

    virtual void visitClassNameReference(ClassNameReferenceAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "classNameReference[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitClassNameReference(node);
        m_indent--;
    }

    virtual void visitClassStatement(ClassStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "classStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitClassStatement(node);
        m_indent--;
    }

    virtual void visitClassVariable(ClassVariableAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "classVariable[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitClassVariable(node);
        m_indent--;
    }

    virtual void visitClassVariableDeclaration(ClassVariableDeclarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "classVariableDeclaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitClassVariableDeclaration(node);
        m_indent--;
    }

    virtual void visitCommonScalar(CommonScalarAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "commonScalar[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCommonScalar(node);
        m_indent--;
    }

    virtual void visitCompoundVariable(CompoundVariableAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "compoundVariable[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCompoundVariable(node);
        m_indent--;
    }

    virtual void visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "compoundVariableWithSimpleIndirectReference[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
        m_indent--;
    }

    virtual void visitConditionalExpression(ConditionalExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "conditionalExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitConditionalExpression(node);
        m_indent--;
    }

    virtual void visitCtorArguments(CtorArgumentsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "ctorArguments[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitCtorArguments(node);
        m_indent--;
    }

    virtual void visitDeclareItem(DeclareItemAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "declareItem[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDeclareItem(node);
        m_indent--;
    }

    virtual void visitDeclareStatement(DeclareStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "declareStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDeclareStatement(node);
        m_indent--;
    }

    virtual void visitDimListItem(DimListItemAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "dimListItem[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDimListItem(node);
        m_indent--;
    }

    virtual void visitDimOffset(DimOffsetAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "dimOffset[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDimOffset(node);
        m_indent--;
    }

    virtual void visitDynamicClassNameReference(DynamicClassNameReferenceAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "dynamicClassNameReference[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDynamicClassNameReference(node);
        m_indent--;
    }

    virtual void visitDynamicClassNameVariableProperties(DynamicClassNameVariablePropertiesAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "dynamicClassNameVariableProperties[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDynamicClassNameVariableProperties(node);
        m_indent--;
    }

    virtual void visitDynamicClassNameVariableProperty(DynamicClassNameVariablePropertyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "dynamicClassNameVariableProperty[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitDynamicClassNameVariableProperty(node);
        m_indent--;
    }

    virtual void visitElseSingle(ElseSingleAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "elseSingle[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitElseSingle(node);
        m_indent--;
    }

    virtual void visitElseifList(ElseifListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "elseifList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitElseifList(node);
        m_indent--;
    }

    virtual void visitElseifListItem(ElseifListItemAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "elseifListItem[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitElseifListItem(node);
        m_indent--;
    }

    virtual void visitEncaps(EncapsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "encaps[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitEncaps(node);
        m_indent--;
    }

    virtual void visitEncapsList(EncapsListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "encapsList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitEncapsList(node);
        m_indent--;
    }

    virtual void visitEncapsVar(EncapsVarAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "encapsVar[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitEncapsVar(node);
        m_indent--;
    }

    virtual void visitEncapsVarOffset(EncapsVarOffsetAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "encapsVarOffset[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitEncapsVarOffset(node);
        m_indent--;
    }

    virtual void visitEqualityExpression(EqualityExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "equalityExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitEqualityExpression(node);
        m_indent--;
    }

    virtual void visitEqualityExpressionRest(EqualityExpressionRestAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "equalityExpressionRest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitEqualityExpressionRest(node);
        m_indent--;
    }

    virtual void visitExpr(ExprAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "expr[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitExpr(node);
        m_indent--;
    }

    virtual void visitForExpr(ForExprAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "forExpr[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitForExpr(node);
        m_indent--;
    }

    virtual void visitForStatement(ForStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "forStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitForStatement(node);
        m_indent--;
    }

    virtual void visitForeachOptionalArg(ForeachOptionalArgAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "foreachOptionalArg[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitForeachOptionalArg(node);
        m_indent--;
    }

    virtual void visitForeachStatement(ForeachStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "foreachStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitForeachStatement(node);
        m_indent--;
    }

    virtual void visitForeachVariable(ForeachVariableAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "foreachVariable[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitForeachVariable(node);
        m_indent--;
    }

    virtual void visitFunctionCall(FunctionCallAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "functionCall[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitFunctionCall(node);
        m_indent--;
    }

    virtual void visitFunctionCallParameterList(FunctionCallParameterListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "functionCallParameterList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitFunctionCallParameterList(node);
        m_indent--;
    }

    virtual void visitFunctionCallParameterListElement(FunctionCallParameterListElementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "functionCallParameterListElement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitFunctionCallParameterListElement(node);
        m_indent--;
    }

    virtual void visitFunctionDeclarationStatement(FunctionDeclarationStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "functionDeclarationStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitFunctionDeclarationStatement(node);
        m_indent--;
    }

    virtual void visitGlobalVar(GlobalVarAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "globalVar[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitGlobalVar(node);
        m_indent--;
    }

    virtual void visitIdentifier(IdentifierAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "identifier[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitIdentifier(node);
        m_indent--;
    }

    virtual void visitInnerStatementList(InnerStatementListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "innerStatementList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitInnerStatementList(node);
        m_indent--;
    }

    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "logicalAndExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitLogicalAndExpression(node);
        m_indent--;
    }

    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "logicalOrExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitLogicalOrExpression(node);
        m_indent--;
    }

    virtual void visitLogicalXorExpression(LogicalXorExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "logicalXorExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitLogicalXorExpression(node);
        m_indent--;
    }

    virtual void visitMethodBody(MethodBodyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "methodBody[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitMethodBody(node);
        m_indent--;
    }

    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "multiplicativeExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitMultiplicativeExpression(node);
        m_indent--;
    }

    virtual void visitMultiplicativeExpression_rest(MultiplicativeExpression_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "multiplicativeExpression_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitMultiplicativeExpression_rest(node);
        m_indent--;
    }

    virtual void visitNewElseSingle(NewElseSingleAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "newElseSingle[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitNewElseSingle(node);
        m_indent--;
    }

    virtual void visitNewElseifList(NewElseifListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "newElseifList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitNewElseifList(node);
        m_indent--;
    }

    virtual void visitNewelseifListItem(NewelseifListItemAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "newelseifListItem[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitNewelseifListItem(node);
        m_indent--;
    }

    virtual void visitObjectDimList(ObjectDimListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "objectDimList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitObjectDimList(node);
        m_indent--;
    }

    virtual void visitObjectProperty(ObjectPropertyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "objectProperty[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitObjectProperty(node);
        m_indent--;
    }

    virtual void visitOptionalModifiers(OptionalModifiersAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "optionalModifiers[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitOptionalModifiers(node);
        m_indent--;
    }

    virtual void visitParameter(ParameterAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "parameter[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitParameter(node);
        m_indent--;
    }

    virtual void visitParameterList(ParameterListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "parameterList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitParameterList(node);
        m_indent--;
    }

    virtual void visitPostprefixOperator(PostprefixOperatorAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "postprefixOperator[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitPostprefixOperator(node);
        m_indent--;
    }

    virtual void visitPrintExpression(PrintExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "printExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitPrintExpression(node);
        m_indent--;
    }

    virtual void visitRelationalExpression(RelationalExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "relationalExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitRelationalExpression(node);
        m_indent--;
    }

    virtual void visitRelationalExpressionRest(RelationalExpressionRestAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "relationalExpressionRest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitRelationalExpressionRest(node);
        m_indent--;
    }

    virtual void visitScalar(ScalarAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "scalar[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitScalar(node);
        m_indent--;
    }

    virtual void visitSemicolonOrCloseTag(SemicolonOrCloseTagAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "semicolonOrCloseTag[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitSemicolonOrCloseTag(node);
        m_indent--;
    }

    virtual void visitShiftExpression(ShiftExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "shiftExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitShiftExpression(node);
        m_indent--;
    }

    virtual void visitShiftExpressionRest(ShiftExpressionRestAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "shiftExpressionRest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitShiftExpressionRest(node);
        m_indent--;
    }

    virtual void visitStart(StartAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "start[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitStart(node);
        m_indent--;
    }

    virtual void visitStatement(StatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitStatement(node);
        m_indent--;
    }

    virtual void visitStaticArrayPairValue(StaticArrayPairValueAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "staticArrayPairValue[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitStaticArrayPairValue(node);
        m_indent--;
    }

    virtual void visitStaticMember(StaticMemberAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "staticMember[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitStaticMember(node);
        m_indent--;
    }

    virtual void visitStaticScalar(StaticScalarAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "staticScalar[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitStaticScalar(node);
        m_indent--;
    }

    virtual void visitStaticVar(StaticVarAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "staticVar[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitStaticVar(node);
        m_indent--;
    }

    virtual void visitSwitchCaseList(SwitchCaseListAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "switchCaseList[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitSwitchCaseList(node);
        m_indent--;
    }

    virtual void visitTopStatement(TopStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "topStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitTopStatement(node);
        m_indent--;
    }

    virtual void visitUnaryExpression(UnaryExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "unaryExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitUnaryExpression(node);
        m_indent--;
    }

    virtual void visitUnaryExpression_not_plusminus(UnaryExpression_not_plusminusAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "unaryExpression_not_plusminus[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitUnaryExpression_not_plusminus(node);
        m_indent--;
    }

    virtual void visitVarExpression(VarExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "varExpression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVarExpression(node);
        m_indent--;
    }

    virtual void visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "varExpressionNewObject[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVarExpressionNewObject(node);
        m_indent--;
    }

    virtual void visitVarExpressionNormal(VarExpressionNormalAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "varExpressionNormal[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVarExpressionNormal(node);
        m_indent--;
    }

    virtual void visitVariable(VariableAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "variable[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVariable(node);
        m_indent--;
    }

    virtual void visitVariableName(VariableNameAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "variableName[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVariableName(node);
        m_indent--;
    }

    virtual void visitVariableProperty(VariablePropertyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "variableProperty[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVariableProperty(node);
        m_indent--;
    }

    virtual void visitVariableWithoutObjects(VariableWithoutObjectsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "variableWithoutObjects[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitVariableWithoutObjects(node);
        m_indent--;
    }

    virtual void visitWhileStatement(WhileStatementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        QString tokenString;
        if (!m_content.isEmpty())
        {
            KDevPG::TokenStream::Token startToken = m_str->token(node->startToken);
            KDevPG::TokenStream::Token endToken = m_str->token(node->endToken);
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
        qDebug() << QString().fill(' ', m_indent) << "whileStatement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "] " << tokenString;
        m_indent++;
        DefaultVisitor::visitWhileStatement(node);
        m_indent--;
    }

private:
    KDevPG::TokenStream *m_str;
    int m_indent;
    QString m_content;
};

} // end of namespace Php

#endif

