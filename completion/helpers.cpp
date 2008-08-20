/*
 * KDevelop Php Code Completion Support
 *
 * Copyright 2007-2008 David Nolden <david.nolden.kdevelop@art-master.de>
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

#include "completion/helpers.h"
#include "completion/items.h"
#include <QList>
#include <QVariant>
#include <language/duchain/declaration.h>
#include <language/duchain/abstractfunctiondeclaration.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/types/functiontype.h>
#include <QTextFormat>
#include <QStringList>

using namespace KDevelop;
namespace Php {

KDevelop::DUContext* getArgumentContext(KDevelop::Declaration* decl) {
  DUContext* internal = decl->internalContext();
  if( !internal )
    return 0;
  if( internal->type() == DUContext::Function )
    return internal;
  foreach( DUContext::Import ctx, internal->importedParentContexts() ) {
    if( ctx.context() )
      if( ctx.context()->type() == DUContext::Function )
        return ctx.context();
  }
  return 0;
}

void createArgumentList(const NormalDeclarationCompletionItem& item, QString& ret, QList<QVariant>* highlighting )
{
  ///@todo also highlight the matches of the previous arguments, they are given by ViableFunction
  Declaration* dec(item.declaration().data());

  int textFormatStart = 0;
  QTextFormat normalFormat(QTextFormat::CharFormat);
  QTextFormat highlightFormat; //highlightFormat is invalid, so kate uses the match-quality dependent color.

  AbstractFunctionDeclaration* decl = dynamic_cast<AbstractFunctionDeclaration*>(dec);
  FunctionType::Ptr functionType = dec->type<FunctionType>();

  if (functionType && decl) {

    QVector<Declaration*> parameters;
    if (getArgumentContext(dec))
      parameters = getArgumentContext(dec)->localDeclarations();

    uint defaultParamNum = 0;

    int firstDefaultParam = parameters.count() - decl->defaultParametersSize();

    ret = "(";
    bool first = true;
    int num = 0;

    foreach (Declaration* dec, parameters) {
      if (first)
        first = false;
      else
        ret += ", ";

      bool doHighlight = false;
      QTextFormat doFormat = normalFormat;

//       if( num < f.matchedArguments )
//       {
        doHighlight = true;
        doFormat = QTextFormat( QTextFormat::CharFormat );

//         if( parameterConversion != conversions.end() ) {
//           //Interpolate the color
//           quint64 badMatchColor = 0xff7777ff; //Full blue
//           quint64 goodMatchColor = 0xff77ff77; //Full green
// 
//           uint totalColor = (badMatchColor*(Cpp::MaximumConversionResult-(*parameterConversion).rank) + goodMatchColor*(*parameterConversion).rank)/Cpp::MaximumConversionResult;
// 
//           doFormat.setBackground( QBrush(totalColor) );
// 
//           ++parameterConversion;
//         }
//       }

      if( doHighlight )
      {
        if( highlighting && ret.length() != textFormatStart )
        {
          //Add a default-highlighting for the passed text
          *highlighting <<  QVariant(textFormatStart);
          *highlighting << QVariant(ret.length() - textFormatStart);
          *highlighting << QVariant(normalFormat);
          textFormatStart = ret.length();
        }
      }

      if (num < functionType->arguments().count())
        ret += functionType->arguments().at(num)->toString() + " ";

      ret += "$" + dec->identifier().toString();

      if( doHighlight  )
      {
        if( highlighting && ret.length() != textFormatStart )
        {
          *highlighting <<  QVariant(textFormatStart);
          *highlighting << QVariant(ret.length() - textFormatStart);
          *highlighting << doFormat;
          textFormatStart = ret.length();
        }
      }


      if( num >= firstDefaultParam ) {
        ret += " = " + decl->defaultParameters()[defaultParamNum].str();
        ++defaultParamNum;
      }

      ++num;
    }
    ret += ')';

    if( highlighting && ret.length() != textFormatStart ) {
      *highlighting <<  QVariant(textFormatStart);
      *highlighting << QVariant(ret.length());
      *highlighting << normalFormat;
      textFormatStart = ret.length();
    }
    return;
  }
}


enum { T_ACCESS, T_PAREN, T_BRACKET, T_IDE, T_UNKNOWN, T_TEMP };
/**
 * Copied from kdevelop-3.4, should be redone
 * @param index should be the index BEHIND the expression
 * */
int expressionAt( const QString& text, int index ) {

  /* C++ style comments present issues with finding the expr so I'm
    matching for them and replacing them with empty C style comments
    of the same length for purposes of finding the expr. */

  if( index == 0 )
    return 0;

  int last = T_UNKNOWN;
  int start = index;
  --index;

  while ( index > 0 ) {

    while ( index > 0 && text[ index ].isSpace() ) {
      --index;
    }

    QChar ch = text[ index ];
    QString ch2 = text.mid( index - 1, 2 );

    if ( ( last != T_IDE ) && ( ch.isLetterOrNumber() || ch == '_' || ch == '$') ) {
      while ( index > 0 && ( text[ index ].isLetterOrNumber() || text[ index ] == '_'  || text[ index ] == '$') ) {
        --index;
      }
      last = T_IDE;
    } else if ( last != T_IDE && ch == ')' ) {
      int count = 0;
      while ( index > 0 ) {
        QChar ch = text[ index ];
        if ( ch == '(' ) {
          ++count;
        } else if ( ch == ')' ) {
          --count;
        } else if ( count == 0 ) {
          //index;
          last = T_PAREN;
          break;
        }
        --index;
      }
    } else if ( last != T_IDE && ch == '>' && ch2 != "->" && ch2 != "::") {
      int count = 0;
      while ( index > 0 ) {
        QChar ch = text[ index ];
        if ( ch == '<' ) {
          ++count;
        } else if ( ch == '>' ) {
          --count;
        } else if ( count == 0 ) {
          //--index;
          last = T_TEMP;
          break;
        }
        --index;
      }
    } else if ( ch == ']' ) {
      int count = 0;
      while ( index > 0 ) {
        QChar ch = text[ index ];
        if ( ch == '[' ) {
          ++count;
        } else if ( ch == ']' ) {
          --count;
        } else if ( count == 0 ) {
          //--index;
          last = T_BRACKET;
          break;
        }
        --index;
      }
    } else if ( ch2 == "::" ) {
      index -= 2;
      last = T_ACCESS;
    } else if ( ch2 == "->" ) {
      index -= 2;
      last = T_ACCESS;
    } else {
      if ( start > index ) {
        ++index;
      }
      last = T_UNKNOWN;
      break;
    }
  }

  ///If we're at the first item, the above algorithm cannot be used safely,
  ///so just determine whether the sign is valid for the beginning of an expression, if it isn't reject it.
  if ( index == 0 && start > index && !( text[ index ].isLetterOrNumber() || text[ index ] == '_' || text[ index ] == ':' || text[ index ] == '$') ) {
    ++index;
  }

  return index;
}

}
