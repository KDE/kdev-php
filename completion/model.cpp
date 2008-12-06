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

#include "model.h"

#include <QIcon>
#include <QMetaType>
#include <QTextFormat>
#include <QBrush>
#include <QDir>
#include <kdebug.h>
#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <kiconloader.h>
#include <khtmlview.h>


#include <language/duchain/declaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/parsingenvironment.h>
#include <editorintegrator.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchainbase.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/dumpchain.h>


#include "context.h"
#include "worker.h"
#include "phplanguagesupport.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

CodeCompletionModel::CodeCompletionModel( QObject * parent )
  : KDevelop::CodeCompletionModel(parent)
{
  connect(this, SIGNAL(modifyCompletionRange(KTextEditor::View*, KTextEditor::SmartRange*, QRegExp&)),
        this, SLOT(modifyCompletionRangeInternal(KTextEditor::View*, KTextEditor::SmartRange*, QRegExp&)));
}

CodeCompletionModel::~CodeCompletionModel()
{
}

void CodeCompletionModel::completionInvokedInternal(KTextEditor::View* view, const KTextEditor::Range& range, InvocationType invocationType, const KUrl& url)
{
  Q_UNUSED(invocationType)

  DUChainReadLocker lock(DUChain::lock(), 400);
  if( !lock.locked() ) {
    kDebug(9007) << "could not lock du-chain in time";
    return;
  }

  TopDUContext* top = DUChain::self()->chainForDocument(view->document()->url());
  if(!top ) {
    kDebug(9007) << "no top level context available";
    return;
  }
  setCurrentTopContext(TopDUContextPointer(top));

  if (top) {
    kDebug(9007) << "completion invoked for context" << (DUContext*)top;

//     if( top->parsingEnvironmentFile()->modificationRevision() != EditorIntegrator::modificationRevision(url.prettyUrl()) ) {
//       kDebug(9007) << "Found context is not current. Its revision is " << top->parsingEnvironmentFile()->modificationRevision() << " while the document-revision is " << EditorIntegrator::modificationRevision(url.prettyUrl());
//     }

    DUContextPointer thisContext;
    {
      thisContext = top->findContextAt(SimpleCursor(range.start()));

       kDebug(9007) << "context is set to" << thisContext.data();
        if( thisContext ) {
          kDebug( 9007 ) << "================== duchain for the context =======================";
          DumpChain dump;
          dump.dump(thisContext.data());
        } else {
          kDebug( 9007 ) << "================== NO CONTEXT FOUND =======================";
          m_completionItems.clear();
          m_navigationWidgets.clear();
          reset();
          return;
        }
    }

    lock.unlock();

    emit completionsNeeded(thisContext, range.start(), view);
  } else {
    kDebug(9007) << "Completion invoked for unknown context. Document:" << url << ", Known documents:" << DUChain::self()->documents();
  }
}

Range CodeCompletionModel::completionRange(View* view, const Cursor &position)
{
    Range range = CodeCompletionModelControllerInterface::completionRange(view, position);
    if (range.start().column() > 0) {
        KTextEditor::Range preRange(Cursor(range.start().line(), range.start().column()-1),
                                    Cursor(range.start().line(), range.start().column()));
        kDebug() << preRange << view->document()->text(preRange);
        if (view->document()->text(preRange) == "$") {
            range.expandToRange(preRange);
            kDebug() << "using custom completion range" << range;
        }
    }
    return range;
}

bool CodeCompletionModel::shouldAbortCompletion(View* view, const SmartRange &range, const QString &currentCompletion)
{
    Q_UNUSED(view);
    Q_UNUSED(range);
    static const QRegExp allowedText("^\\$?(\\w*)");
    return !allowedText.exactMatch(currentCompletion);
    }

}

#include "model.moc"
