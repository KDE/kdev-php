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

#include "declarationbuilder.h"
#include "predeclarationbuilder.h"

#include <QByteArray>

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/duchain/functiondeclaration.h>
#include <language/duchain/stringhelpers.h>
#include <language/duchain/aliasdeclaration.h>
#include <language/duchain/classdeclaration.h>

#include <klocalizedstring.h>

#include "phpast.h"
#include "parsesession.h"
#include "helper.h"
#include "constantdeclaration.h"
#include "variabledeclaration.h"
#include "classmethoddeclaration.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

KDevelop::ReferencedTopDUContext DeclarationBuilder::build(const KDevelop::IndexedString& url, Php::AstNode* node,
        KDevelop::ReferencedTopDUContext updateContext, bool useSmart)
{
    //Run DeclarationBuilder twice, to find uses of declarations that are
    //declared after the use. ($a = new Foo; class Foo {})
    {
        PreDeclarationBuilder prebuilder(&m_types, &m_functions, editor());
        updateContext = prebuilder.build(url, node, updateContext, useSmart);
    }

    // now skip through some things the DeclarationBuilderBase (ContextBuilder) would do,
    // most significantly don't clear imported parent contexts
    m_reportErrors = (url != IndexedString("internalfunctions"));
    return ContextBuilderBase::build(url, node, updateContext, useSmart);
}

void DeclarationBuilder::closeDeclaration()
{
    if (currentDeclaration() && lastType()) {
        DUChainWriteLocker lock(DUChain::lock());
        currentDeclaration()->setType(lastType());
    }

    eventuallyAssignInternalContext();

    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::classContextOpened(KDevelop::DUContext* context)
{
    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setInternalContext(context);
}

void DeclarationBuilder::visitClassDeclarationStatement(ClassDeclarationStatementAst * node)
{
    ClassDeclaration* classDec = openTypeDeclaration(node->className, ClassDeclarationData::Class);
    openType(classDec->abstractType());
    DeclarationBuilderBase::visitClassDeclarationStatement(node);
    closeType();
    closeDeclaration();
}

void DeclarationBuilder::visitInterfaceDeclarationStatement(InterfaceDeclarationStatementAst *node)
{
    ClassDeclaration* interfaceDec = openTypeDeclaration(node->interfaceName, ClassDeclarationData::Interface);
    openType(interfaceDec->abstractType());
    DeclarationBuilderBase::visitInterfaceDeclarationStatement(node);
    closeType();
    closeDeclaration();
}

ClassDeclaration* DeclarationBuilder::openTypeDeclaration(IdentifierAst* name, ClassDeclarationData::ClassType type)
{
    ClassDeclaration* classDec = m_types.value(name->string, 0);
    Q_ASSERT(classDec);
    isGlobalRedeclaration(identifierForNode(name), name, ClassDeclarationType);
    Q_ASSERT(classDec->classType() == type);

    // seems like we have to do that manually, else the usebuilder crashes...
    setEncountered(classDec);
    openDeclarationInternal(classDec);

    return classDec;
}

bool DeclarationBuilder::isBaseMethodRedeclaration(const Identifier &identifier, ClassDeclaration *curClass,
        ClassStatementAst *node)
{
    while (curClass->baseClassesSize() > 0) {
        StructureType::Ptr type;
        FOREACH_FUNCTION(BaseClassInstance base, curClass->baseClasses) {
            type = base.baseClass.type<StructureType>();
            if (!type) {
                continue;
            }
            ClassDeclaration *nextClass = dynamic_cast<ClassDeclaration*>(type->declaration(currentContext()->topContext()));
            if (!nextClass || nextClass->classType() != ClassDeclarationData::Class) {
                type.clear();
                continue;
            }
            curClass = nextClass;
            break;
        }
        if (!type) {
            break;
        }
        {
            DUChainWriteLocker lock(DUChain::lock());
            if (!type->internalContext(currentContext()->topContext())) {
                continue;
            }
            foreach(Declaration * dec,
                    type->internalContext(currentContext()->topContext())->findLocalDeclarations(identifier)) {
                if (dec->isFunctionDeclaration()) {
                    ClassMethodDeclaration* func = dynamic_cast<ClassMethodDeclaration*>(dec);
                    if (!func) {
                        continue;
                    }
                    // we cannot redeclare final classes ever
                    if (func->isFinal()) {
                        reportRedeclarationError(dec, node->methodName);
                        return true;
                    }
                    // also we may not redeclare an already abstract method, we would have to implement it
                    // TODO: original error message?
                    // -> Can't inherit abstract function class::func() (previously declared in otherclass)
                    else if (func->isAbstract() && node->modifiers->modifiers & ModifierAbstract) {
                        reportRedeclarationError(dec, node->methodName);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void DeclarationBuilder::visitClassStatement(ClassStatementAst *node)
{
    setComment(formatComment(node, editor()));
    if (node->methodName) {
        //method declaration

        ClassDeclaration *parent =  dynamic_cast<ClassDeclaration*>(currentDeclaration());
        Q_ASSERT(parent);

        if (m_reportErrors) {   // check for redeclarations
            Q_ASSERT(currentContext()->type() == DUContext::Class);
            bool localError = false;
            Identifier id = identifierForNode(node->methodName).first();
            {
                DUChainWriteLocker lock(DUChain::lock());
                foreach(Declaration * dec, currentContext()->findLocalDeclarations(id)) {
                    if (dec->isFunctionDeclaration()) {
                        reportRedeclarationError(dec, node->methodName);
                        localError = true;
                        break;
                    }
                }
            }

            if (!localError) {
                // if we have no local error, check that we don't try to overwrite a final method of a baseclass
                isBaseMethodRedeclaration(id, parent, node);
            }
        }

        ClassMethodDeclaration* dec = openDefinition<ClassMethodDeclaration>(node->methodName, node);
        {
            DUChainWriteLocker lock(DUChain::lock());
            dec->clearDefaultParameters();
            dec->setKind(Declaration::Type);
            if (node->modifiers->modifiers & ModifierPublic) {
                dec->setAccessPolicy(Declaration::Public);
            } else if (node->modifiers->modifiers & ModifierProtected) {
                dec->setAccessPolicy(Declaration::Protected);
            } else if (node->modifiers->modifiers & ModifierPrivate) {
                dec->setAccessPolicy(Declaration::Private);
            }
            if (node->modifiers->modifiers & ModifierStatic) {
                dec->setStatic(true);
            }
            if (parent->classType() == ClassDeclarationData::Interface) {
                if (m_reportErrors) {
                    if (node->modifiers->modifiers & ModifierFinal || node->modifiers->modifiers & ModifierAbstract) {
                        reportError(i18n("Access type for interface method %1 must be omitted.",
                                         dec->toString()), node->modifiers);
                    }
                    if (!isEmptyMethodBody(node->methodBody)) {
                        reportError(i18n("Interface function %1 cannot contain body.",
                                         dec->toString()), node->methodBody);
                    }
                }
                // handle interface methods like abstract methods
                dec->setIsAbstract(true);
            } else {
                if (node->modifiers->modifiers & ModifierAbstract) {
                    if (!m_reportErrors) {
                        dec->setIsAbstract(true);
                    } else {
                        if (parent->classModifier() != ClassDeclarationData::Abstract) {
                            reportError(i18n("Class %1 contains abstract method %2 and must therefore be declared abstract "
                                             "or implement the method.",
                                             parent->identifier().toString(),
                                             dec->identifier().toString()),
                                        node->modifiers);
                        } else if (!isEmptyMethodBody(node->methodBody)) {
                            reportError(i18n("Abstract function %1 cannot contain body.",
                                             dec->toString()), node->methodBody);
                        } else if (node->modifiers->modifiers & ModifierFinal) {
                            reportError(i18n("Cannot use the final modifier on an abstract class member."),
                                        node->modifiers);
                        } else {
                            dec->setIsAbstract(true);
                        }
                    }
                } else if (node->modifiers->modifiers & ModifierFinal) {
                    dec->setIsFinal(true);
                }
                if (m_reportErrors && !dec->isAbstract() && isEmptyMethodBody(node->methodBody)) {
                    reportError(i18n("Non-abstract method %1 must contain body.", dec->toString()), node->methodBody);
                }
            }
        }

        DeclarationBuilderBase::visitClassStatement(node);

        closeDeclaration();
    } else {
        if (node->modifiers) {
            m_currentModifers = node->modifiers->modifiers;
            if (m_reportErrors) {
                // have to report the errors here to get a good problem range
                if (m_currentModifers & ModifierFinal) {
                    reportError(i18n("Properties cannot be declared final."), node->modifiers);
                }
                if (m_currentModifers & ModifierAbstract) {
                    reportError(i18n("Properties cannot be declared abstract."), node->modifiers);
                }
            }
        } else {
            m_currentModifers = 0;
        }
        DeclarationBuilderBase::visitClassStatement(node);
        m_currentModifers = 0;
    }
}

void DeclarationBuilder::visitClassExtends(ClassExtendsAst *node)
{
    addBaseType(node->identifier);
}

void DeclarationBuilder::visitClassImplements(ClassImplementsAst *node)
{
    const KDevPG::ListNode<IdentifierAst*> *__it = node->implementsSequence->front(), *__end = __it;
    do {
        addBaseType(__it->element);
        __it = __it->next;
    } while (__it != __end);
    DeclarationBuilderBase::visitClassImplements(node);
}

void DeclarationBuilder::visitClassVariable(ClassVariableAst *node)
{
    if (m_reportErrors) {   // check for redeclarations
        Q_ASSERT(currentContext()->type() == DUContext::Class);
        DUChainWriteLocker lock(DUChain::lock());
        foreach(Declaration * dec, currentContext()->findLocalDeclarations(identifierForNode(node->variable).first())) {
            if (!dec->isFunctionDeclaration() && ! dec->abstractType()->modifiers() & AbstractType::ConstModifier) {
                reportRedeclarationError(dec, node->variable);
                break;
            }
        }
    }
    {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->variable, node->variable);
        openDefinition<ClassMemberDeclaration>(identifierForNode(node->variable), newRange);

        ClassMemberDeclaration* dec = dynamic_cast<ClassMemberDeclaration*>(currentDeclaration());
        Q_ASSERT(dec);
        if (m_currentModifers & ModifierPublic) {
            dec->setAccessPolicy(Declaration::Public);
        } else if (m_currentModifers & ModifierProtected) {
            dec->setAccessPolicy(Declaration::Protected);
        } else if (m_currentModifers & ModifierPrivate) {
            dec->setAccessPolicy(Declaration::Private);
        }
        if (m_currentModifers & ModifierStatic) {
            dec->setStatic(true);
        }
        dec->setKind(Declaration::Instance);
    }

    DeclarationBuilderBase::visitClassVariable(node);
    closeDeclaration();
}

void DeclarationBuilder::visitClassConstantDeclaration(ClassConstantDeclarationAst *node)
{
    if (m_reportErrors) {   // check for redeclarations
        Q_ASSERT(currentContext()->type() == DUContext::Class);
        DUChainWriteLocker lock(DUChain::lock());
        foreach(Declaration * dec, currentContext()->findLocalDeclarations(identifierForNode(node->identifier).first())) {
            if (!dec->isFunctionDeclaration() && dec->abstractType()->modifiers() & AbstractType::ConstModifier) {
                reportRedeclarationError(dec, node->identifier);
                break;
            }
        }
    }
    openDefinition<ClassMemberDeclaration>(node->identifier, node->identifier);
    ClassMemberDeclaration* dec = dynamic_cast<ClassMemberDeclaration*>(currentDeclaration());
    Q_ASSERT(dec);
    {
        DUChainWriteLocker lock(DUChain::lock());
        dec->setAccessPolicy(Declaration::Public);
        dec->setStatic(true);
        dec->setKind(Declaration::Instance);
    }
    DeclarationBuilderBase::visitClassConstantDeclaration(node);
    closeDeclaration();
}

void DeclarationBuilder::visitParameter(ParameterAst *node)
{
    if (node->defaultValue) {
        AbstractFunctionDeclaration* funDec = dynamic_cast<AbstractFunctionDeclaration*>(currentDeclaration());
        if (funDec) {
            funDec->addDefaultParameter(IndexedString(editor()->parseSession()->symbol(node->defaultValue)));
        }
    }
    {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->variable, node->variable);
        openDefinition<Declaration>(identifierForNode(node->variable), newRange);
        currentDeclaration()->setKind(Declaration::Instance);
    }

    DeclarationBuilderBase::visitParameter(node);
    closeDeclaration();
}

void DeclarationBuilder::visitFunctionDeclarationStatement(FunctionDeclarationStatementAst* node)
{
    isGlobalRedeclaration(identifierForNode(node->functionName), node->functionName, FunctionDeclarationType);

    FunctionDeclaration* dec = m_functions.value(node->functionName->string, 0);
    Q_ASSERT(dec);
    // seems like we have to set that, else the usebuilder crashes
    DeclarationBuilderBase::setEncountered(dec);

    openDeclarationInternal(dec);
    openType(dec->abstractType());

    DeclarationBuilderBase::visitFunctionDeclarationStatement(node);

    closeType();
    closeDeclaration();
}

bool DeclarationBuilder::isGlobalRedeclaration(const QualifiedIdentifier &identifier, AstNode* node,
        DeclarationType type)
{
    if (!m_reportErrors) {
        return false;
    }
    ///TODO: method redeclaration etc.
    if (type != ClassDeclarationType
            && type != FunctionDeclarationType
            && type != ConstantDeclarationType) {
        // the other types can be redeclared
        return false;
    }

    DUChainWriteLocker lock(DUChain::lock());
    QList<Declaration*> declarations = currentContext()->topContext()->findDeclarations(
                                           identifier,
                                           editor()->findPosition(node->startToken, EditorIntegrator::FrontEdge)
                                       );
    foreach(Declaration* dec, declarations) {
        if (isMatch(dec, type)) {
            reportRedeclarationError(dec, node);
            return true;
        }
    }
    return false;
}

void DeclarationBuilder::reportRedeclarationError(Declaration* declaration, AstNode* node)
{
    if (declaration->range().contains(editor()->findRange(node).start)) {
        // make sure this is not a wrongly reported redeclaration error
        return;
    }
    QString filename(declaration->context()->topContext()->url().str());
    if (filename == "internalfunctions") {
        reportError(i18n("Cannot redeclare PHP internal %1.", declaration->toString()), node);
    } else {
        ///TODO: try to shorten the filename by removing the leading path to the current project
        reportError(
            i18n("Cannot redeclare %1, already declared in %2 on line %3.",
                 declaration->toString(), filename, declaration->range().start.line + 1
                ), node
        );
    }
}

void DeclarationBuilder::visitExpr(ExprAst *node)
{
    VariableIdentifierAst* lastIdentifier = m_lastVariableIdentifier;
    m_lastVariableIdentifier = 0;
    DeclarationBuilderBase::visitExpr(node);
    m_lastVariableIdentifier = lastIdentifier;
}

void DeclarationBuilder::visitTopStatement(TopStatementAst* node)
{
    //docblock of an AssignmentExpression
    setComment(formatComment(node, editor()));
    m_lastTopStatementComment = editor()->parseSession()->docComment(node->startToken);

    DeclarationBuilderBase::visitTopStatement(node);
}

void DeclarationBuilder::visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
{
    VariableIdentifierAst* leftSideVariableIdentifier = m_lastVariableIdentifier;
    DeclarationBuilderBase::visitAssignmentExpressionEqual(node);

    if (leftSideVariableIdentifier && currentAbstractType()) {
        //create new declaration for every assignment
        //TODO: don't create the same twice
        QualifiedIdentifier identifier = identifierForNode(leftSideVariableIdentifier);
        // TODO: we cannot assign anything to $this, but we are currently not in the position
        //       to decide whether we are really assigning to $this and are not using something
        //       like $this->foo[$bar] = ...
        //       => we really need better support for arrays here I think...
        if (identifier != QualifiedIdentifier("this")) {
            DUChainWriteLocker lock(DUChain::lock());
            SimpleRange newRange = editorFindRange(leftSideVariableIdentifier, leftSideVariableIdentifier);
            VariableDeclaration *dec = openDefinition<VariableDeclaration>(identifierForNode(leftSideVariableIdentifier), newRange);
            dec->setKind(Declaration::Instance);
            if (!m_lastTopStatementComment.isEmpty()) {
                QRegExp rx("\\* +@superglobal");
                if (rx.indexIn(m_lastTopStatementComment) != -1) {
                    dec->setSuperglobal(true);
                }
            }

            //own closeDeclaration() that uses currentAbstractType() instead of lastType()
            currentDeclaration()->setType(currentAbstractType());
            eventuallyAssignInternalContext();
            DeclarationBuilderBase::closeDeclaration();
        }
    }
}

void DeclarationBuilder::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    //needed in assignmentExpressionEqual
    m_lastVariableIdentifier = node->variable;
    DeclarationBuilderBase::visitCompoundVariableWithSimpleIndirectReference(node);
}

void DeclarationBuilder::visitFunctionCall(FunctionCallAst* node)
{
    DeclarationBuilderBase::visitFunctionCall(node);
    if (node->stringFunctionNameOrClass && !node->stringFunctionName && !node->varFunctionName) {
        if (identifierForNode(node->stringFunctionNameOrClass) == QualifiedIdentifier("define")
                && node->stringParameterList->parametersSequence->count() > 0) {
            //constant, defined through define-function

            //find name of the constant (first argument of the function call)
            CommonScalarAst* scalar = findCommonScalar(node->stringParameterList->parametersSequence->at(0)->element);
            if (scalar && scalar->string != -1) {
                QString constant = editor()->parseSession()->symbol(scalar->string);
                constant = constant.mid(1, constant.length() - 2);
                SimpleRange newRange = editorFindRange(scalar, scalar);
                DUChainWriteLocker lock(DUChain::lock());
                LockedSmartInterface iface = editor()->smart();
                injectContext(iface, currentContext()->topContext()); //constants are always global
                QualifiedIdentifier identifier(constant);
                isGlobalRedeclaration(identifier, scalar, ConstantDeclarationType);
                openDefinition<ConstantDeclaration>(identifier, newRange);
                currentDeclaration()->setKind(Declaration::Instance);
                closeDeclaration();
                closeInjectedContext(iface);
            }
        }
    }
}
void DeclarationBuilder::visitStatement(StatementAst* node)
{
    DeclarationBuilderBase::visitStatement(node);

    if (node->foreachExprAsVar) {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->foreachExprAsVar, node->foreachExprAsVar);
        openDefinition<VariableDeclaration>(identifierForNode(node->foreachExprAsVar), newRange);
        currentDeclaration()->setKind(Declaration::Instance);
        closeDeclaration();
    }

    if (node->foreachVarAsVar) {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->foreachVarAsVar->variable, node->foreachVarAsVar->variable);
        openDefinition<VariableDeclaration>(identifierForNode(node->foreachVarAsVar->variable), newRange);
        currentDeclaration()->setKind(Declaration::Instance);
        closeDeclaration();
    }

    if (node->foreachVariable) {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->foreachVariable->variable, node->foreachVariable->variable);
        openDefinition<VariableDeclaration>(identifierForNode(node->foreachVariable->variable), newRange);
        currentDeclaration()->setKind(Declaration::Instance);
        closeDeclaration();
    }

}

void DeclarationBuilder::visitStaticVar(StaticVarAst* node)
{
    DeclarationBuilderBase::visitStaticVar(node);

    DUChainWriteLocker lock(DUChain::lock());
    SimpleRange newRange = editorFindRange(node->var, node->var);
    openDefinition<VariableDeclaration>(identifierForNode(node->var), newRange);
    currentDeclaration()->setKind(Declaration::Instance);

    closeDeclaration();
}

void DeclarationBuilder::visitGlobalVar(GlobalVarAst* node)
{
    DeclarationBuilderBase::visitGlobalVar(node);
    if (node->var) {
        Declaration* aliasedDeclaration = findDeclarationImport(GlobalVariableDeclarationType, node->var);
        if (aliasedDeclaration) {
            DUChainWriteLocker lock(DUChain::lock());
            AliasDeclaration* dec = openDefinition<AliasDeclaration>(identifierForNode(node->var), editor()->findRange(node->var));
            dec->setAliasedDeclaration(aliasedDeclaration);
            closeDeclaration();
        }
    }
}

}
