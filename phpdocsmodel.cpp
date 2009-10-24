/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "phpdocsmodel.h"

#include <language/duchain/duchain.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainlock.h>

#include <language/duchain/types/structuretype.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguage.h>
#include <interfaces/ilanguagecontroller.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/backgroundparser/parsejob.h>

using namespace KDevelop;

PhpDocsModel::PhpDocsModel(QObject* parent)
    : QAbstractListModel(parent)
{
    // make sure the php plugin is loaded
    ILanguage* phpLangPlugin = ICore::self()->languageController()->language("Php");
    if ( !phpLangPlugin ) {
        qWarning() << "could not load PHP language support plugin";
        return;
    }
    fillModel();
}

PhpDocsModel::~PhpDocsModel()
{
}

void PhpDocsModel::slotParseJobFinished( ParseJob* job )
{
    if ( job->document() == IndexedString("InternalFunctions.php") ) {
        disconnect(ICore::self()->languageController()->backgroundParser(), SIGNAL(parseJobFinished(KDevelop::ParseJob*)),
                   this, SLOT(slotParseJobFinished(KDevelop::ParseJob*)));
        fillModel();
    }
}

void PhpDocsModel::fillModel()
{
    DUChainReadLocker lock(DUChain::self()->lock());

    TopDUContext* top = DUChain::self()->chainForDocument(IndexedString("InternalFunctions.php"));
    if ( !top ) {
        qWarning() << "could not find DUChain for InternalFunctions.php, connecting to background parser";
        connect(ICore::self()->languageController()->backgroundParser(), SIGNAL(parseJobFinished(KDevelop::ParseJob*)),
                this, SLOT(slotParseJobFinished(KDevelop::ParseJob*)));
        return;
    }

    kDebug() << "filling model";
    typedef QPair<Declaration*, int> DeclDepthPair;
    foreach ( const DeclDepthPair& declpair, top->allDeclarations(top->range().end, top) ) {
        m_declarations << declpair.first;

        if ( StructureType::Ptr type = declpair.first->type<StructureType>() ) {
            foreach ( Declaration* dec, type->internalContext(top)->localDeclarations() ) {
                m_declarations << dec;
            }
        }
    }
}

bool PhpDocsModel::hasChildren(const QModelIndex& parent) const
{
    // only the top-level has children
    return parent == QModelIndex();
}

QVariant PhpDocsModel::data(const QModelIndex& index, int role) const
{
    switch ( role ) {
        case Qt::DisplayRole:
        case Qt::EditRole: {
            Declaration* dec = declarationForIndex(index);
            DUChainReadLocker lock(DUChain::self()->lock());
            QString ret = dec->qualifiedIdentifier().toString();
            if ( dec->isFunctionDeclaration() ) {
                ret += "()";
            }
            return ret;
        }
        case DeclarationRole: {
            Declaration* dec = declarationForIndex(index);
            return QVariant(QMetaType::VoidStar, &dec);
        }
        /*
        case Qt::ToolTipRole:
        case Qt::AccessibleTextRole:
        case Qt::AccessibleDescriptionRole:
        */
        default:
            return QVariant();
    }
}

int PhpDocsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return m_declarations.count();
}

bool PhpDocsModel::canFetchMore(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return false;
}

Declaration* PhpDocsModel::declarationForIndex(const QModelIndex& index) const
{
    Q_ASSERT(m_declarations.size() > index.row());

    return m_declarations[index.row()];
}

#include "phpdocsmodel.moc"
