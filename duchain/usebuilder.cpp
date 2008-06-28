/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "usebuilder.h"

#include "editorintegrator.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php {

UseBuilder::UseBuilder (ParseSession* session)
{
    setEditor(session);
}

UseBuilder::UseBuilder (EditorIntegrator* editor)
{
    setEditor(editor);
}

void UseBuilder::visitParameter(ParameterAst *node)
{
    UseBuilderBase::visitParameter(node);

    if (node->parameterType) {
        newUse(node->parameterType);
    }
}

void UseBuilder::visitClassImplements(ClassImplementsAst *node)
{
    UseBuilderBase::visitClassImplements(node);

    const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
    do
    {
        newUse(__it->element);
    }
    while (__it != __end);
}

void UseBuilder::visitClassExtends(ClassExtendsAst *node)
{
    UseBuilderBase::visitClassExtends(node);
    newUse(node->identifier);
}

void UseBuilder::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    UseBuilderBase::visitVarExpressionNewObject(node);
    if (node->className->identifier) {
        newUse(node->className->identifier);
    }
}

}
