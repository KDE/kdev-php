/*
 * KDevelop Php Code Completion Support
 *
 * Copyright 2009 Milian Wolff <mail@milianw.de>
 * Basec on Cpp ImplementationHelperItem
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

#include "implementationitem.h"

#include "helpers.h"

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/codecompletion/codecompletionmodel.h>

#include <ktexteditor/document.h>
#include <kicon.h>
#include <klocalizedstring.h>

using namespace KDevelop;

namespace Php {

#define RETURN_CACHED_ICON(name) {static QIcon icon(KIcon(name).pixmap(QSize(16, 16))); return icon;}

QVariant ImplementationItem::data(const QModelIndex& index, int role, const CodeCompletionModel* model) const
{
  QVariant ret = NormalDeclarationCompletionItem::data(index, role, model);
  switch ( role ) {
    case Qt::DecorationRole:
      if ( index.column() == KTextEditor::CodeCompletionModel::Icon ) {
        switch ( m_type ) {
          case Override:
            RETURN_CACHED_ICON("CTparents");
          case Implement:
            RETURN_CACHED_ICON("CTsuppliers");
        }
      }
      break;
    case Qt::DisplayRole:
      if ( index.column() == KTextEditor::CodeCompletionModel::Prefix ) {
        QString prefix;
        switch ( m_type ) {
          case Override:
            prefix = i18n("Override");
            break;
          case Implement:
            prefix = i18n("Implement");
            break;
        }

        ret = prefix + " " + ret.toString();
      }
      //TODO column == Name - required?
      break;
    case KTextEditor::CodeCompletionModel::ItemSelected:
      {
        DUChainReadLocker lock(DUChain::lock());
        if ( declaration().data() ) {
          QualifiedIdentifier parentScope = declaration()->context()->scopeIdentifier(true);
          return i18n("From %1", parentScope.toString());
        }
      }
      break;
    case KTextEditor::CodeCompletionModel::InheritanceDepth:
      return QVariant(0);
    default:
      //pass
      break;
  }

  return ret;
}

void ImplementationItem::execute(KTextEditor::Document* document, const KTextEditor::Range& word) {
  DUChainReadLocker lock(DUChain::lock());

  QString replText;

  if ( m_declaration ) {
    //TODO:respect custom code styles
    
    // get existing modifiers so we can respect the user's choice of public/protected and final
    QStringList modifiers = getMethodTokens( document->text( KTextEditor::Range(KTextEditor::Cursor::start(), word.start()) ) );
    // get range to replace
    KTextEditor::Range replaceRange(word);
    if ( !modifiers.isEmpty() ) {
      // TODO: is there no easy API to map QString Index to a KTextEditor::Cursor ?!
      QString methodText = document->text( KTextEditor::Range( KTextEditor::Cursor::start(), word.start() ) );
      methodText = methodText.left( methodText.lastIndexOf( modifiers.last(), -1, Qt::CaseInsensitive ) );
      replaceRange.start() = KTextEditor::Cursor( methodText.count( '\n' ), methodText.length() - methodText.lastIndexOf( '\n' ) - 1 );
    }

    // get indendation
    QString indendation;
    {
      QString currentLine = document->line( replaceRange.start().line() );
      
      int nonWhiteSpacePos = currentLine.indexOf( QRegExp("\\S"), 0 );
      indendation = currentLine.left( nonWhiteSpacePos );
      if ( nonWhiteSpacePos != -1 && nonWhiteSpacePos != replaceRange.start().column() ) {
        // since there's some non-whitespace in this line, skip to the next one
        replText += "\n" + indendation;
      }
      
      if ( indendation.isEmpty() ) {
        // use a minimal indendation
        // TODO: respect code style
        indendation = "  ";
        replText += indendation;
      }
    }
    
    // build phpdoc comment
    {
      QualifiedIdentifier parentClassIdentifier;
      if ( DUContext* pctx = m_declaration->context() ) {
        parentClassIdentifier = pctx->localScopeIdentifier();
      } else {
        kDebug() << "completion item for implementation has no parent context!";
      }
      
      replText += "/**\n" + indendation + " * ";
      // insert old comment:
      const QString indentationWithExtra = "\n" + indendation + " *";
      replText += m_declaration->comment().replace('\n', indentationWithExtra.toAscii().constData());
      replText += "\n" + indendation + " * @overload " + m_declaration->internalContext()->scopeIdentifier(true).toString();
      replText += "\n" + indendation + " **/\n" + indendation;
    }

    // write function signature
    
    // copy existing modifiers
    if ( !modifiers.isEmpty() ) {
      // the tokens are in a bad order and there's no reverse method or similar, so we can't simply join the tokens
      QStringList::const_iterator i = modifiers.constEnd() - 1;
      while ( true ) {
        replText += (*i) + " ";
        if ( i == modifiers.constBegin() ) {
          break;
        } else {
          --i;
        }
      }
    }
    
    if ( ClassFunctionDeclaration* method = dynamic_cast<ClassFunctionDeclaration*>(m_declaration.data()) ) {
      // NOTE: it should _never_ be private - but that's the completionmodel / context / worker's job
      if ( !modifiers.contains("public") && !modifiers.contains("protected") ) {
        if ( method->accessPolicy() == Declaration::Protected ) {
          replText += "protected ";
        } else {
          replText += "public ";
        }
      }
      if ( !modifiers.contains("static") && method->isStatic() ) {
        modifiers << "static";
      }
    } else {
      kDebug() << "completion item for implementation was not a classfunction declaration!";
    }
    
    if ( !modifiers.contains("function") ) {
      replText += "function ";
    }
    
    replText += m_declaration->identifier().toString();
    
    {
      // get argument list
      QString arguments;
      createArgumentList(*this, arguments, 0, true);
      
      replText += arguments;
    }
    
    // ) {...}
    replText += QString("{\n%1  \n%1}\n%1").arg(indendation);
    
    //TODO: properly place the cursor inside the {} part
    document->replaceText( replaceRange, replText );
  } else {
    kDebug() << "Declaration disappeared";
  }
}

}
