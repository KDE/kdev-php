/*
 * KDevelop Php Code Completion Support
 *
 * Copyright 2006-2008 Hamish Rodda <rodda@kde.org>
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

#include "worker.h"

#include <kdebug.h>

#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <klocale.h>

#include <language/duchain/declaration.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchainbase.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/duchain.h>
#include "duchain/types.h"
#include "model.h"

using namespace KDevelop;

namespace Php {

CodeCompletionWorker::CodeCompletionWorker(CodeCompletionModel* parent)
  : KDevelop::CodeCompletionWorker(parent)
{
}

CodeCompletionModel* CodeCompletionWorker::model() const
{
  return static_cast<CodeCompletionModel*>(const_cast<QObject*>(parent()));
}

void CodeCompletionWorker::computeCompletions(KDevelop::DUContextPointer context, const KTextEditor::Cursor& position, KTextEditor::View* view, const KTextEditor::Range& contextRange, const QString& contextText)
{
qDebug() << "<<<<<<<<<<<<<<<CREATING CodeCompletionContext>>>>>>>>>>>>>>>>>>>>>>>" << contextText;
  CodeCompletionContext::Ptr completionContext( new CodeCompletionContext( context, contextText ) );
  if (CodeCompletionModel* m = model())
    m->setCompletionContext(KDevelop::CodeCompletionContext::Ptr::staticCast(completionContext));

  if( completionContext->isValid() ) {
    DUChainReadLocker lock(DUChain::lock());

    if (!context) {
      kDebug(9007) << "Completion context disappeared before completions could be calculated";
      return;
    }

    QList<CompletionTreeItemPointer> items = completionContext->completionItems(SimpleCursor(position), aborting());

    if (aborting())
      return;
    
    computeGroups( items, completionContext );

  } else {
    kDebug(9007) << "setContext: Invalid code-completion context";
  }
}

///Always the last item of a grouping chain: Only inserts the items
struct LastGrouper {
  LastGrouper(QList<KSharedPtr<CompletionTreeElement> >& tree, CompletionTreeNode* parent, QList<CompletionTreeItemPointer> items)
  {
    foreach( CompletionTreeItemPointer item, items ) {
      item->setParent(parent);
      tree << KSharedPtr<CompletionTreeElement>( item.data() );
    }
  }
};

///Helper class that helps us grouping the completion-list. A chain of groupers can be built, by using NextGrouper.
template<class KeyExtractor, class NextGrouper = LastGrouper>
struct ItemGrouper {
  typedef typename KeyExtractor::KeyType KeyType;
  
  ItemGrouper(QList<KSharedPtr<CompletionTreeElement> >& tree, CompletionTreeNode* parent, QList<CompletionTreeItemPointer> items)
  {
    typedef QMap<KeyType, QList<CompletionTreeItemPointer> > GroupMap;
    GroupMap groups;
    
    foreach(const CompletionTreeItemPointer& item, items) {
      KeyType key = KeyExtractor::extract(item);
      typename GroupMap::iterator it = groups.find(key);
      if(it == groups.end())
        it = groups.insert(key, QList<CompletionTreeItemPointer>());

      (*it).append(item);
    }

    for( typename GroupMap::const_iterator it = groups.begin(); it != groups.end(); ++it ) {
      KSharedPtr<CompletionTreeNode> node(new CompletionTreeNode());
      node->setParent(parent);
      node->role = (KTextEditor::CodeCompletionModel::ExtraItemDataRoles)KeyExtractor::Role;
      node->roleValue = QVariant(it.key());

      tree << KSharedPtr<CompletionTreeElement>( node.data() );
      
      NextGrouper nextGrouper(node->children, node.data(), *it);
    }
  }
};

///Extracts the argument-hint depth from completion-items, to be used in ItemGrouper for grouping by argument-hint depth.
struct ArgumentHintDepthExtractor {
  typedef int KeyType;
  enum { Role = KTextEditor::CodeCompletionModel::ArgumentHintDepth };
  
  static KeyType extract( const CompletionTreeItemPointer& item ) {
    return item->argumentHintDepth();
  }
};

struct InheritanceDepthExtractor {
  typedef int KeyType;
  
  enum { Role = KTextEditor::CodeCompletionModel::InheritanceDepth };
  
  static KeyType extract( const CompletionTreeItemPointer& item ) {
    return item->inheritanceDepth();
  }
};

struct SimplifiedAttributesExtractor {
  typedef int KeyType;
  
  enum { Role = KTextEditor::CodeCompletionModel::CompletionRole };

  static int groupingProperties;
  
  static KeyType extract( const CompletionTreeItemPointer& item ) {
    const NormalDeclarationCompletionItem* decItem = item->asItem<NormalDeclarationCompletionItem>();
    if( decItem && decItem->declaration().data() )
      return DUChainUtils::completionProperties(decItem->declaration().data()) & groupingProperties;
    else
      return 0;
  }
};

///@todo make configurable. These are the attributes that can be respected for grouping.
int SimplifiedAttributesExtractor::groupingProperties = CodeCompletionModel::Public | CodeCompletionModel::Protected | CodeCompletionModel::Private | CodeCompletionModel::Static | CodeCompletionModel::TypeAlias | CodeCompletionModel::Variable | CodeCompletionModel::Class | CodeCompletionModel::GlobalScope | CodeCompletionModel::LocalScope | CodeCompletionModel::GlobalScope | CodeCompletionModel::NamespaceScope;

void CodeCompletionWorker::computeGroups(QList<CompletionTreeItemPointer> items, KSharedPtr<CodeCompletionContext> completionContext)
{
  kDebug(9007) << "grouping" << items.count() << "completion-items";
  QList<KSharedPtr<CompletionTreeElement> > tree;
  /**
   * 1. Group by argument-hint depth
   * 2. Group by inheritance depth
   * 3. Group by simplified attributes
   * */
  ItemGrouper<ArgumentHintDepthExtractor, ItemGrouper<InheritanceDepthExtractor, ItemGrouper<SimplifiedAttributesExtractor> > > argumentHintDepthGrouper(tree, 0, items);

  emit foundDeclarations( tree, completionContext.data() );
}

}

#include "worker.moc"
