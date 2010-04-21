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

#include "phphighlighting.h"
#include <language/duchain/declaration.h>
#include <language/duchain/use.h>
#include <language/highlighting/colorcache.h>
#include <language/highlighting/configurablecolors.h>

#include <KTextEditor/SmartRange>
#include <KTextEditor/SmartInterface>
#include <KTextEditor/Document>

using namespace KDevelop;
using namespace Php;
using namespace KTextEditor;

#define LOCK_SMART(range) KTextEditor::SmartInterface* iface = dynamic_cast<KTextEditor::SmartInterface*>(range->document()); QMutexLocker lock(iface ? iface->smartMutex() : 0);

class HighlightingInstance : public CodeHighlightingInstance {
public:
    HighlightingInstance(const CodeHighlighting* highlighting);
    virtual void highlightDeclaration(Declaration* declaration, const QColor& color) const;
    virtual void highlightUse(DUContext* context, int index, const QColor& color) const;

};

HighlightingInstance::HighlightingInstance(const CodeHighlighting* highlighting)
    : CodeHighlightingInstance(highlighting)
{
}

bool isConstDeclaration(Declaration* decl) {
    return decl && !decl->isFunctionDeclaration() &&
           decl->abstractType() && decl->abstractType()->modifiers() & AbstractType::ConstModifier;
}

///TODO: make this easier by rewriting some parts in the KDevplatform CodeHighlightingInstance
///      essentially we'd need to overwrite TypeForDeclaration
void HighlightingInstance::highlightDeclaration(Declaration* declaration, const QColor& color) const
{
    if (isConstDeclaration(declaration)) {
        // highlight const class members and defines differently from normal variables
        if (SmartRange* range = declaration->smartRange()) {
            LOCK_SMART(range);
            range->setAttribute(m_highlighting->attributeForType(EnumType, DeclarationContext, color));
        }
    } else {
        CodeHighlightingInstance::highlightDeclaration(declaration, color);
    }
}

///TODO: make this easier by rewriting some parts in the KDevplatform CodeHighlightingInstance
///      essentially we'd need to overwrite TypeForDeclaration
void HighlightingInstance::highlightUse(DUContext* context, int index, const QColor& color) const
{
    if (SmartRange* range = context->useSmartRange(index)) {
        Declaration* decl = context->topContext()->usedDeclarationForIndex(context->uses()[index].m_declarationIndex);
        if (isConstDeclaration(decl)) {
            LOCK_SMART(range);
            range->setAttribute(m_highlighting->attributeForType(EnumType, ReferenceContext, color));
            return;
        }
    }
    KDevelop::CodeHighlightingInstance::highlightUse(context, index, color);
}


Highlighting::Highlighting(QObject* parent)
    : CodeHighlighting(parent)
{

}

CodeHighlightingInstance* Highlighting::createInstance() const
{
    return new HighlightingInstance(this);
}
