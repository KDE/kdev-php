/*
 * KDevelop Php Code Completion Support
 *
 * Copyright 2007-2008 David Nolden <david.nolden.kdevelop@art-master.de>
 * Copyright 2008 Hamish Rodda <rodda@kde.org>
 * Copyright 2008 Niko Sams <niko.sams@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "items.h"

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <ktexteditor/range.h>
#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <language/codecompletion/codecompletionmodel.h>
#include <language/duchain/declaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/structuretype.h>

#include "completion/helpers.h"

using namespace KDevelop;

namespace Php {
  
void NormalDeclarationCompletionItem::execute(KTextEditor::Document* document, const KTextEditor::Range& word) {
  bool spaceBeforeParen = false; ///@todo Take this from some astyle config or something
  bool spaceBetweenParens = true;
  bool spaceBetweenEmptyParens = false;
  
  if( completionContext && completionContext->depth() != 0 )
    return; //Do not replace any text when it is an argument-hint

  QString newText;

  {
    KDevelop::DUChainReadLocker lock(KDevelop::DUChain::lock());
    if(m_declaration) {
      newText = m_declaration->identifier().toString();
    } else {
      kDebug() << "Declaration disappeared";
      return;
    }
  }

  document->replaceText(word, newText);

  if( m_declaration && dynamic_cast<AbstractFunctionDeclaration*>(m_declaration.data()) ) { //Do some intelligent stuff for functions with the parens:
    KDevelop::DUChainReadLocker lock(KDevelop::DUChain::lock());
    bool haveArguments = false;
    if( m_declaration && m_declaration->type<FunctionType>() && m_declaration->type<FunctionType>()->arguments().count() )
      haveArguments = true;
    //Need to have a paren behind
    QString suffix = document->text( KTextEditor::Range( word.end(), word.end() + KTextEditor::Cursor(1, 0) ) );
    if( suffix.trimmed().startsWith("(") ) {
      //Move the cursor behind the opening paren
      if( document->activeView() )
        document->activeView()->setCursorPosition( word.end() + KTextEditor::Cursor( 0, suffix.indexOf('(')+1 ) );
    }else{
      //We need to insert an opening paren
      QString openingParen;
      if( spaceBeforeParen )
        openingParen = " (";
      else
        openingParen = "(";

      if( spaceBetweenParens && (haveArguments || spaceBetweenEmptyParens) )
        openingParen += " ";

      QString closingParen;
      if( spaceBetweenParens && (haveArguments) ) {
        closingParen = " )";
      } else
        closingParen = ")";

      KTextEditor::Cursor jumpPos = word.end() + KTextEditor::Cursor( 0, openingParen.length() );

      //If no arguments, move the cursor behind the closing paren
      if( !haveArguments )
        jumpPos += KTextEditor::Cursor( 0, closingParen.length() );
      
      lock.unlock();
      document->insertText( word.end(), openingParen + closingParen );
      if( document->activeView() )
        document->activeView()->setCursorPosition( jumpPos );
    }
  }
}

const bool indentByDepth = false;

//The name to be viewed in the name column
QString nameForDeclaration(Declaration* dec) {
  if (dec->identifier().toString().isEmpty())
    return "<unknown>";
  else
    return dec->identifier().toString();
}

QVariant NormalDeclarationCompletionItem::data(const QModelIndex& index, int role, const KDevelop::CodeCompletionModel* model) const {
  DUChainReadLocker lock(DUChain::lock(), 500);
  if(!lock.locked()) {
    kDebug(9007) << "Failed to lock the du-chain in time";
    return QVariant();
  }

  static CompletionTreeItemPointer currentMatchContext;

  
  //Stuff that does not require a declaration:
  switch (role) {
    case CodeCompletionModel::SetMatchContext:
      currentMatchContext = CompletionTreeItemPointer(const_cast<NormalDeclarationCompletionItem*>(this));
      return QVariant(1);
  };

  if(!m_declaration) {
    if(role == Qt::DisplayRole && index.column() == CodeCompletionModel::Name)
      return alternativeText;
    return QVariant();
  }
  
  Declaration* dec = const_cast<Declaration*>( m_declaration.data() );

  switch (role) {
    case CodeCompletionModel::BestMatchesCount:
      return QVariant(5);
    break;
    case CodeCompletionModel::MatchQuality:
    {
      if( currentMatchContext && currentMatchContext->asItem()) {
        const NormalDeclarationCompletionItem& contextItem(*currentMatchContext->asItem<NormalDeclarationCompletionItem>());
#if 0
        if( contextItem.asItem() && contextItem.declaration && contextItem.completionContext && contextItem.completionContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess && contextItem.listOffset < contextItem.completionContext->functions().count() )
        {
          CodeCompletionContext::Function f( contextItem.completionContext->functions()[contextItem.listOffset] );

          if( f.function.isValid() && f.function.isViable() && f.function.declaration() && f.function.declaration()->type<CppFunctionType>() && f.function.declaration()->type<CppFunctionType>()->arguments().count() > f.matchedArguments ) {
            TypeConversion conv(model->currentTopContext().data());

            ///@todo fill the lvalue-ness correctly
            int quality = ( conv.implicitConversion( effectiveType(dec), f.function.declaration()->type<CppFunctionType>()->arguments()[f.matchedArguments], true )  * 10 ) / MaximumConversionResult;
            return QVariant(quality);
          }else{
            //kDebug(9007) << "MatchQuality requested with invalid match-context";
          }
        } else {
          //kDebug(9007) << "MatchQuality requested with invalid match-context";
        }
#endif
      }
    }
    return QVariant();
#if 0
    case CodeCompletionModel::ItemSelected:
       return QVariant(NavigationWidget::shortDescription(dec));
#endif
    case CodeCompletionModel::IsExpandable:
      return QVariant(false /* true*/);
#if 0
    case CodeCompletionModel::ExpandingWidget: {
      NavigationWidget* nav = new NavigationWidget(DeclarationPointer(dec), model->currentTopContext());
      model->addNavigationWidget(this, nav);

      QVariant v;
      v.setValue<QWidget*>((QWidget*)nav);
      return v;
    }
#endif
    case Qt::DisplayRole:

      switch (index.column()) {
        case CodeCompletionModel::Prefix:
        {
          int depth = m_inheritanceDepth;
          if( depth >= 1000 )
            depth-=1000;
          QString indentation;
          if(indentByDepth)
            indentation = QString(depth, ' ');

          if( dec->isTypeAlias() )
            indentation += "typedef ";

          if( dec->kind() == Declaration::Type && !dec->type<FunctionType>() && !dec->isTypeAlias() ) {
            if (StructureType::Ptr classType =  dec->type<StructureType>())
              switch (classType->classType()) {
                case StructureType::Class:
                  return indentation + "class";
                case StructureType::Interface:
                  return indentation + "interface";
              }
            return QVariant();
          }

          if (dec->abstractType()) {
            if (FunctionType::Ptr functionType = dec->type<FunctionType>()) {
              ClassFunctionDeclaration* funDecl = dynamic_cast<ClassFunctionDeclaration*>(dec);

              if (functionType->returnType())
                return indentation + functionType->returnType()->toString();
              else if(funDecl && funDecl->isConstructor() )
                return indentation + "<constructor>";
              else if(funDecl && funDecl->isDestructor() )
                return indentation + "<destructor>";
              else
                return indentation + "<incomplete type>";

            } else {
              QString ret = indentation;
//               if(dec->type<EnumeratorType>())
//                 ret += "enumerator ";
              return  ret + dec->abstractType()->toString();
            }
          } else {
            return indentation + "<incomplete type>";
          }
        }

        case CodeCompletionModel::Scope: {
          //The scopes are not needed
          return QVariant();
/*          QualifiedIdentifier id = dec->qualifiedIdentifier();
          if (id.isEmpty())
            return QVariant();
          id.pop();
          if (id.isEmpty())
            return QVariant();
          return id.toString() + "::";*/
        }

        case CodeCompletionModel::Name:
          return nameForDeclaration(dec);

        case CodeCompletionModel::Arguments:
          if (FunctionType::Ptr functionType = dec->type<FunctionType>()) {
            QString ret;
            createArgumentList(*this, ret, 0);
            return ret;
          }
        break;
        case CodeCompletionModel::Postfix:
          if (FunctionType::Ptr functionType = dec->type<FunctionType>()) {
//             return functionType->cvString();
          }
          break;
      }
      break;
    case CodeCompletionModel::HighlightingMethod:
    if( index.column() == CodeCompletionModel::Arguments ) {
      if( completionContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess ) {
        return QVariant(CodeCompletionModel::CustomHighlighting);
      }else{
        return QVariant();
      }
      break;
    } else if(index.column() == CodeCompletionModel::Name) {
      return QVariant(CodeCompletionModel::CustomHighlighting);
    }

    break;

    case CodeCompletionModel::CustomHighlight:
    if( index.column() == CodeCompletionModel::Arguments && completionContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess ) {
      QString ret;
      QList<QVariant> highlight;
      createArgumentList(*this, ret, &highlight);
      return QVariant(highlight);
    }
    if( index.column() == CodeCompletionModel::Name ) {
      //Bold
      QTextCharFormat boldFormat;
      boldFormat.setFontWeight(QFont::Bold);

      QList<QVariant> ret;
      ret << 0;
      ret << nameForDeclaration(dec).length();
      ret << QVariant(boldFormat);
      
      return QVariant(ret);
    }
    break;
    case Qt::DecorationRole:
    case CodeCompletionModel::CompletionRole: {
      CodeCompletionModel::CompletionProperties p = DUChainUtils::completionProperties(dec);

      if (dec->abstractType()) {
#if 0
        if (CppCVType* cv = dynamic_cast<CppCVType*>(dec->abstractType().data())) {
          if (cv->isConstant())
            p |= CodeCompletionModel::Const;
          if (cv->isVolatile())
            ;//TODO
          }
#endif

        switch (dec->abstractType()->whichType()) {
          case AbstractType::TypeIntegral:
//             if (dec->type<EnumerationType>()) {
//               // Remove variable bit set in DUChainUtils
//               p &= ~CodeCompletionModel::Variable;
//               p |= CodeCompletionModel::Enum;
//             }
            break;
          case AbstractType::TypeStructure:
            if (StructureType::Ptr classType =  dec->type<StructureType>())
              switch (classType->classType()) {
                case StructureType::Class:
                  p |= CodeCompletionModel::Class;
                  break;
                case StructureType::Interface:
                  // FIXME remove
                  p |= CodeCompletionModel::Class;
                  // Remove class bit set in DUChainUtils
                  // TODO add Interface to KTextEditor
                  //p &= ~CodeCompletionModel::Class;
                  //p |= CodeCompletionModel::Interface;
                  break;
              }
            break;
        }
      }

      if( role == CodeCompletionModel::CompletionRole ) {
        return (int)p;

      } else {
        if( index.column() == CodeCompletionModel::Icon ) {
          lock.unlock();
          return DUChainUtils::iconForProperties(p);
        }
        break;

      }
    }

    case CodeCompletionModel::ScopeIndex:
      return static_cast<int>(reinterpret_cast<long>(dec->context()));
  }

  return QVariant();
}

int NormalDeclarationCompletionItem::inheritanceDepth() const
{
  return m_inheritanceDepth;
}

int NormalDeclarationCompletionItem::argumentHintDepth() const
{
  if( completionContext && completionContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess )
      return completionContext->depth();
    else
      return 0;
}

DeclarationPointer NormalDeclarationCompletionItem::declaration() const
{
    return m_declaration;
}

}

