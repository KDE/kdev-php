/*
 * KDevelop Php Code Completion Support
 *
 * Copyright 2009 Milian Wolff <mail@milianw.de>
 * Based on Cpp ImplementationHelperItem
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
#ifndef KEYWORDITEM_H
#define KEYWORDITEM_H

#include "item.h"

using namespace KDevelop;

namespace Php {

class KeywordItem : public NormalDeclarationCompletionItem
{
public:

  KeywordItem( const QString &keyword,
                KSharedPtr<KDevelop::CodeCompletionContext> context = KSharedPtr<KDevelop::CodeCompletionContext>() )
    : NormalDeclarationCompletionItem( KDevelop::DeclarationPointer(), context, 0 ),
      m_keyword( keyword )
  {}
  
  virtual void execute( KTextEditor::Document* document, const KTextEditor::Range& word );
  
  virtual QVariant data( const QModelIndex& index, int role, const KDevelop::CodeCompletionModel* model ) const;

private:
  const QString m_keyword;
};

}

#endif // KEYWORDITEM_H
