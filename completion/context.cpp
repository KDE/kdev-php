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

#include "context.h"

#include "duchain/expressionparser.h"
#include "completion/helpers.h"

#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <klocalizedstring.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/stringhelpers.h>
#include <language/duchain/types/identifiedtype.h>
#include <language/interfaces/iproblem.h>
#include <util/pushvalue.h>
#include <language/duchain/codemodel.h>

#include <interfaces/icore.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iproject.h>
#include <project/projectmodel.h>

#define LOCKDUCHAIN     DUChainReadLocker lock(DUChain::lock())

#define ifDebug(x) x

using namespace KDevelop;

namespace Php {


///@todo move these together with those from expressionvisitor into an own file, or make them unnecessary
QList<DeclarationPointer> convert( const QList<Declaration*>& list ) {
  QList<DeclarationPointer> ret;
  foreach( Declaration* decl, list )
    ret << DeclarationPointer(decl);
  return ret;
}

QList<Declaration*> convert( const QList<DeclarationPointer>& list ) {
  QList<Declaration*> ret;
  foreach( DeclarationPointer decl, list )
    if( decl )
      ret << decl.data();
  return ret;
}

///Extracts the last line from the given string
QString extractLastLine(const QString& str) {
  int prevLineEnd = str.lastIndexOf('\n');
  if(prevLineEnd != -1)
    return str.mid(prevLineEnd+1);
  else
    return str;
}

int completionRecursionDepth = 0;

CodeCompletionContext::CodeCompletionContext(DUContextPointer context, const QString& text, int depth)
  : KDevelop::CodeCompletionContext(context, text, depth)
  , m_memberAccessOperation(NoMemberAccess)
{

  m_valid = isValidPosition();
  if( !m_valid ) {
    log( "position not valid for code-completion" );
    return;
  }

  ifDebug( log( "non-processed text: " + m_text ); )

  m_text = clearComments( m_text );
  m_text = clearStrings( m_text );
  m_text = stripFinalWhitespace( m_text );

  ifDebug( log( "processed text: " + m_text ); )

  ///@todo template-parameters

  ///First: find out what kind of completion we are dealing with

  if (m_text.endsWith( ';' ) || m_text.endsWith('}') || m_text.endsWith('{') || m_text.endsWith(')') ) {
    ///We're at the beginning of a new statement. General completion is valid.
    return;
  }

  if( m_text.endsWith("->") ) {
    m_memberAccessOperation = MemberAccess;
    m_text = m_text.left( m_text.length()-2 );
    ifDebug( log( "MemberAccess"); )
  }

  if( m_text.endsWith("::") ) {
    m_memberAccessOperation = StaticMemberChoose; //We need to decide later whether it is a MemberChoose
    m_text = m_text.left( m_text.length()-2 );
    ifDebug( log( "StaticMemberChoose"); )
  }

  if( m_text.endsWith('(') ) {

    if( depth == 0 ) {
      //The first context should never be a function-call context, so make this a NoMemberAccess context and the parent a function-call context.
      m_parentContext = new CodeCompletionContext( m_duContext, m_text, depth+1 );
      ifDebug( log( "NoMemberAccess (created parentContext)"); )
      return;
    }
    m_memberAccessOperation = FunctionCallAccess;
    ifDebug( log( "FunctionCallAccess"); )
    m_text = m_text.left( m_text.length()-1 );

  }

  ///Now find out where the expression starts

  /**
   * Possible cases:
   * a = exp; - partially handled
   * ...
   * return exp;
   * emit exp;
   * throw exp;
   * new Class;
   * a=function(exp
   * a = exp(
   * ClassType instance(
   *
   * What else?
   *
   * When the left and right part are only separated by a whitespace,
   * expressionAt returns both sides
   * */
    m_expression = m_text.trimmed();
    
  int start_expr = expressionAt( m_text, m_text.length() );

  m_expression = m_text.mid(start_expr).trimmed();

  if(m_expression == "else")
    m_expression = QString();

  QString expressionPrefix = stripFinalWhitespace( m_text.left(start_expr) );
  ifDebug( log( "expressionPrefix: " + expressionPrefix ); )

  ///Handle recursive contexts(Example: "ret = function1(param1, function2(" )
  if( expressionPrefix.endsWith('(') || expressionPrefix.endsWith(',') ) {
    log( QString("Recursive function-call: Searching parent-context in \"%1\"").arg(expressionPrefix) );
    //Our expression is within a function-call. We need to find out the possible argument-types we need to match, and show an argument-hint.

    //Find out which argument-number this expression is, and compute the beginning of the parent function-call(parentContextLast)
    QStringList otherArguments;
    int parentContextEnd = expressionPrefix.length();
    
    skipFunctionArguments( expressionPrefix, otherArguments, parentContextEnd );

    QString parentContextText = expressionPrefix.left(parentContextEnd);

    log( QString("This argument-number: %1 Building parent-context from \"%2\"").arg(otherArguments.size()).arg(parentContextText) );
    m_parentContext = new CodeCompletionContext( m_duContext, parentContextText, depth+1 );
  }

  ///Now care about m_expression. It may still contain keywords like "new "
  bool isEmit = false, isReturn = false, isThrow = false;

  QString expr = m_expression.trimmed();

  if( expr.startsWith("emit") )  {
    isEmit = true; //When isEmit is true, we should filter the result so only signals are left
    expr = expr.right( expr.length() - 4 );
  }
  if( expr.startsWith("return") )  {
    isReturn = true; //When isReturn is true, we should match the result against the return-type of the current context-function
    expr = expr.right( expr.length() - 6 );
  }
  if( expr.startsWith("throw") )  {
    isThrow = true;
    expr = expr.right( expr.length() - 5 );
  }

  ifDebug( kDebug() << "expression: " << expr; )

    if (m_memberAccessOperation == StaticMemberChoose) {
        QualifiedIdentifier id(expr);
        LOCKDUCHAIN;
        m_expressionResult.setDeclarations(m_duContext->findDeclarations(id));
        if (m_expressionResult.type()) {
            ifDebug( kDebug() << "expression type: " << m_expressionResult.type()->toString(); )
        } else {
            log( QString("expression \"%1\" could not be evaluated").arg(expr) );
            m_valid = false;
            return;
        }
    } else {

        ExpressionParser expressionParser(false);
    
        if( !expr.trimmed().isEmpty() ) {
            m_expressionResult = expressionParser.evaluateType( expr.toUtf8(), m_duContext );
            if (m_expressionResult.type()) {
                LOCKDUCHAIN;
                ifDebug( kDebug() << "expression type: " << m_expressionResult.type()->toString(); )
            } else {
                log( QString("expression \"%1\" could not be evaluated").arg(expr) );
                m_valid = false;
                return;
            }
        }
    }

  switch( m_memberAccessOperation ) {

    case NoMemberAccess:
    {
      if( !expr.trimmed().isEmpty() ) {
        //This should never happen, because the position-cursor should be chosen at the beginning of a possible completion-context(not in the middle of a string)
        log( QString("Cannot complete \"%1\" because there is an expression without an access-operation" ).arg(expr) );
        m_valid  = false;
      } else {
        //Do nothing. We do not have a completion-container, which means that a global completion should be done.
      }
    }
    break;
    case MemberChoose:
    case StaticMemberChoose:
    {
      ///@todo Check whether it is a MemberChoose
    }
    case MemberAccess:
    case FunctionCallAccess:
    {
      //The result of the expression is stored in m_expressionResult, so we're fine
      break;
    }
  }

}

CodeCompletionContext::~CodeCompletionContext() {
}

bool CodeCompletionContext::isValidPosition() const {
  if( m_text.isEmpty() )
    return true;
  //If we are in a string or comment, we should not complete anything
/*  QString markedText = Utils::clearComments(m_text, '$');
  markedText = Utils::clearStrings(markedText,'$');

  if( markedText[markedText.length()-1] == '$' ) {
    //We are within a comment or string
    kDebug() << "code-completion position is invalid, marked text: \n\"" << markedText << "\"\n unmarked text:\n" << m_text << "\n";
    return false;
  }*/
  return true;
}

CodeCompletionContext::MemberAccessOperation CodeCompletionContext::memberAccessOperation() const {
  return m_memberAccessOperation;
}

ExpressionEvaluationResult CodeCompletionContext::memberAccessContainer() const {
  return m_expressionResult;
}

CodeCompletionContext* CodeCompletionContext::parentContext() {
  return static_cast<CodeCompletionContext*>(KDevelop::CodeCompletionContext::parentContext());
}

QList<DUContext*> CodeCompletionContext::memberAccessContainers() const
{
    QList<DUContext*> ret;
    foreach (DeclarationId declarationId, m_expressionResult.allDeclarationIds()) {
        AbstractType::Ptr expressionTarget = m_expressionResult.type();
        const IdentifiedType* idType = dynamic_cast<const IdentifiedType*>(expressionTarget.unsafeData());
        Declaration* declaration = 0;
        if (idType) {
            declaration = idType->declaration(m_duContext->topContext());
        }
        DUContext* ctx = 0;
        if (declaration) {
            ctx = declaration->logicalInternalContext(m_duContext->topContext());
        }
        if (ctx) {
            ret << ctx;
        } else if (declaration) {
            //Print some debug-output
            kDebug() << "Could not get internal context from" << declaration->toString();
        } else {
            //Print some debug-output
            kDebug() << "Could not get declaration";
        }
    }
    return ret;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::completionItems(const KDevelop::SimpleCursor& position, bool& abort)
{
  LOCKDUCHAIN;
  
  QList<CompletionTreeItemPointer> items;
  
  if (!m_duContext)
    return items;
  
  typedef QPair<Declaration*, int> DeclarationDepthPair;

  if(!m_storedItems.isEmpty()) {
    items = m_storedItems;
  
  } else {

    if ( m_expressionResult.type() ) {
      QList<DUContext*> containers = memberAccessContainers();
      kDebug() << "containers: " << containers.count();
      if( !containers.isEmpty() ) {
        foreach(DUContext* ctx, containers) {
          if (abort)
            return items;

          foreach( const DeclarationDepthPair& decl, ctx->allDeclarations(ctx->range().end, m_duContext->topContext(), false ) ) {
              //If we have StaticMemberChoose, which means A::Bla, show only static members, except if we're within a class that derives from the container
              if(memberAccessOperation() != StaticMemberChoose) {
//                 if(decl.first->kind() != Declaration::Instance)
//                   continue; //needed for functions: todo make this more intelligent
                ClassMemberDeclaration* classMember = dynamic_cast<ClassMemberDeclaration*>(decl.first);
                if(classMember && classMember->isStatic())
                  continue; //Skip static class members when not doing static access
              } else {
//                 if (dynamic_cast<ClassMemberFunctionDeclaration*>(decl.first)
//                     && decl.first->internalContext()
//                     && m_duContext->parentContextOf(decl.first->internalContext())
//                 ) {
//                 }
                ClassMemberDeclaration* classMember = dynamic_cast<ClassMemberDeclaration*>(decl.first);
                if(!classMember || !classMember->isStatic())
                  continue; //Skip static class members when not doing static access
              }
              
              if(!decl.first->identifier().isEmpty())
                items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem( DeclarationPointer(decl.first), CodeCompletionContext::Ptr(this), decl.second ) );
            }
        }
      } else {
        kDebug() << "setContext: no container-type";
      }

 
    } else {

      //Show all visible declarations
      QList<DeclarationDepthPair> decls = m_duContext->allDeclarations(m_duContext->type() == DUContext::Class ? m_duContext->range().end : position, m_duContext->topContext());
      foreach( const DeclarationDepthPair& decl, decls ) {
        if (abort)
          return items;
        items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem(DeclarationPointer(decl.first), CodeCompletionContext::Ptr(this), decl.second ) );
      }
      uint count = 0;
      const CodeModelItem* foundItems = 0;
      foreach (QSet<IndexedString> urlSets, completionFiles()) {
        foreach (IndexedString url, urlSets) {
            CodeModel::self().items(url, count, foundItems);
            for (uint i=0; i < count; ++i) {
                if (foundItems[i].kind == CodeModelItem::Class) {
                    foreach(TopDUContext* top, DUChain::self()->chainsForDocument(url)) {
                        if (m_duContext->imports(top)) continue;
                        QList<Declaration*> decls = top->findDeclarations(foundItems[i].id);
                        foreach (Declaration* decl, decls) {
                            if (abort) return items;
                            items << CompletionTreeItemPointer(new NormalDeclarationCompletionItem(DeclarationPointer(decl), CodeCompletionContext::Ptr(this)));
                        }
                    }
                }
            }
        }
      }
      

      kDebug() << "setContext: using all declarations visible:" << decls.size();
    }
  }

  ///Find all recursive function-calls that should be shown as call-tips
  CodeCompletionContext::Ptr parentContext(this);
  do {
    if (abort)
      return items;

    parentContext = parentContext->parentContext();
    if( parentContext ) {
      if( parentContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess ) {
        if (!parentContext->memberAccessContainer().allDeclarationIds().isEmpty()) {
            Declaration* decl = parentContext->memberAccessContainer().allDeclarationIds().first().getDeclaration(m_duContext->topContext());
            items << CompletionTreeItemPointer(new NormalDeclarationCompletionItem(DeclarationPointer(decl), parentContext));
        }
      } else {
        kDebug() << "parent-context has non function-call access type";
      }
    }
  } while( parentContext );

  return items;
}

QList<QSet<IndexedString> > CodeCompletionContext::completionFiles()
{
    QList<QSet<IndexedString> > ret;
    if (ICore::self()) {
        foreach (IProject* project, ICore::self()->projectController()->projects()) {
            ret << project->fileSet();
        }
    }
    return ret;
}

}
