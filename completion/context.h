/*
   Copyright 2007 David Nolden <david.nolden.kdevelop@art-master.de>
   Copyright 2008 Hamish Rodda <rodda@kde.org>
   Copyright 2008 Niko Sams <niko.sams@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef PHPCODECOMPLETIONCONTEXT_H
#define PHPCODECOMPLETIONCONTEXT_H

#include <ksharedptr.h>

#include <language/codecompletion/codecompletioncontext.h>
#include <language/duchain/types/abstracttype.h>

#include "phpcompletionexport.h"
#include "item.h"
#include "expressionevaluationresult.h"

namespace KTextEditor
{
class View;
class Cursor;
}

namespace KDevelop
{
class DUContext;
class ClassDeclaration;

class CompletionTreeItem;
typedef KSharedPtr<CompletionTreeItem> CompletionTreeItemPointer;

class SimpleCursor;
}

namespace Php
{
/**
 * This class is responsible for finding out what kind of completion is needed, what expression should be evaluated for the container-class of the completion, what conversion will be applied to the result of the completion, etc.
 * */
class KDEVPHPCOMPLETION_EXPORT CodeCompletionContext : public KDevelop::CodeCompletionContext
{
public:
    typedef KSharedPtr<CodeCompletionContext> Ptr;

    /**
     * @param firstContext should be true for a context that has no parent. Such a context will never be a function-call context.
     * @param text the text to analyze. It usually is the text in the range starting at the beginning of the context, and ending at the position where completion should start
     * @warning The du-chain must be unlocked when this is called
     * */
    CodeCompletionContext(KDevelop::DUContextPointer context, const QString& text, const QString& followingText, const KDevelop::SimpleCursor& position, int depth = 0);
    ~CodeCompletionContext();

    ///Computes the full set of completion items, using the information retrieved earlier.
    ///Should only be called on the first context, parent contexts are included in the computations.
    ///@param Abort is checked regularly, and if it is false, the computation is aborted.
    virtual QList<KDevelop::CompletionTreeItemPointer> completionItems(bool& abort, bool fullCompletion = true);

    bool isValidPosition() const;

    enum MemberAccessOperation {
        NoMemberAccess,  ///With NoMemberAccess, a global completion should be done
        MemberAccess,      ///klass->
        FunctionCallAccess,  ///"function(". Will never appear as initial access-operation, but as parentContext() access-operation.
        StaticMemberAccess, ///klass::
        NewClassChoose, /// after the "new" keyword any non-abstract classes (not interfaces) should be shown
        ClassExtendsChoose, /// after "class XYZ extends" any non-final classes should be shown
        InterfaceChoose, /// after the "implements" keyword or after "interface XYZ extends" any interfaces should be shown
        InstanceOfChoose, /// after the "instanceof" operator, any class-type should be shown
        ExceptionChoose, /// after keywords "catch" and "throw new" only classes which extend Exception should be shown
        ExceptionInstanceChoose, /// after the "throw" keyword instancec of the exception class should be shown
        ClassMemberChoose, /// in class context show list of overloadable or implementable methods
        /// and typical keywords for classes, i.e. access modifiers, static etc.
        FileChoose /// autocompletion for files
    };

    ///@return the used access-operation
    MemberAccessOperation memberAccessOperation() const;

    ExpressionEvaluationResult memberAccessContainer() const;

    /**
     * Returns the internal context of memberAccessContainer, if any.
     *
     * When memberAccessOperation is StaticMemberChoose, this returns all
     * fitting namespace-contexts.
     * */
    QList<KDevelop::DUContext*> memberAccessContainers() const;

    /**
     * When memberAccessOperation is FunctionCallAccess,
     * this returns all functions available for matching, together with the argument-number that should be matched.
     * */
    const QList<KDevelop::AbstractFunctionDeclaration*>& functions() const;

    virtual CodeCompletionContext* parentContext();

    /**
     * Returns the code for the CodeCompletionContext.
     */
    const QString& code() const;

protected:
    virtual QList<QSet<KDevelop::IndexedString> > completionFiles();
    inline bool isValidCompletionItem(KDevelop::Declaration* dec);

private:
    MemberAccessOperation m_memberAccessOperation;
    ExpressionEvaluationResult m_expressionResult;
    QString m_expression;
    bool m_parentAccess;
    /**
     * a list of indizes of identifiers which must not be added as completion items
     * examples:
     * class test implements foo, ...
     * => identifiers test and foo must not be proposed for completion
     **/
    QList<uint> m_forbiddenIdentifiers;

    void forbidIdentifier(const QString &identifier);
    void forbidIdentifier(KDevelop::ClassDeclaration* identifier);
};
}

#endif
