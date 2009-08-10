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
#include <language/duchain/types/integraltype.h>

#include <klocalizedstring.h>

#include "phpast.h"
#include "parsesession.h"
#include "helper.h"
#include "constantdeclaration.h"
#include "variabledeclaration.h"
#include "classmethoddeclaration.h"
#include "expressionvisitor.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace Php
{

void DeclarationBuilder::getVariableIdentifier(VariableAst* node,
                                                QualifiedIdentifier &identifier,
                                                QualifiedIdentifier &parent,
                                                AstNode* &targetNode,
                                                bool &arrayAccess)
{
    parent = QualifiedIdentifier();
    if ( node->variablePropertiesSequence ) {
        // at least one "->" in the assigment target
        // => find he parent of the target
        // => find the target (last object property)
        if ( node->variablePropertiesSequence->count() == 1 ) {
            // $parent->target
            ///TODO: $parent[0]->target = ... (we don't know the type of [0] yet, need proper array handling first)
            if ( node->var && node->var->baseVariable && node->var->baseVariable->var
                && !node->var->baseVariable->offsetItemsSequence ) {
                parent = identifierForNode(
                    node->var->baseVariable->var->variable
                );
            }
        } else {
            // $var->...->parent->target
            ///TODO: $var->...->parent[0]->target = ... (we don't know the type of [0] yet, need proper array handling first)
            const KDevPG::ListNode< VariablePropertyAst* >* parentNode = node->variablePropertiesSequence->at(
                node->variablePropertiesSequence->count() - 2
            );
            if ( parentNode->element && parentNode->element->objectProperty
                && parentNode->element->objectProperty->objectDimList
                && parentNode->element->objectProperty->objectDimList->variableName
                && !parentNode->element->objectProperty->objectDimList->offsetItemsSequence ) {
                parent = identifierForNode(
                    parentNode->element->objectProperty->objectDimList->variableName->name
                );
            }
        }

        if ( !parent.isEmpty() ) {
            const KDevPG::ListNode< VariablePropertyAst* >* tNode = node->variablePropertiesSequence->at(
                node->variablePropertiesSequence->count() - 1
            );
            if ( tNode->element && tNode->element->objectProperty
                && tNode->element->objectProperty->objectDimList
                && tNode->element->objectProperty->objectDimList->variableName ) {
                arrayAccess = (bool) tNode->element->objectProperty->objectDimList->offsetItemsSequence;
                identifier = identifierForNode(
                    tNode->element->objectProperty->objectDimList->variableName->name
                );
                targetNode = tNode->element->objectProperty->objectDimList->variableName->name;
            }
        }
    } else {
        // simple assignment to $var
        if ( node->var && node->var->baseVariable && node->var->baseVariable->var ) {
            arrayAccess = (bool) node->var->baseVariable->offsetItemsSequence;
            identifier = identifierForNode(
                node->var->baseVariable->var->variable
            );
            targetNode = node->var->baseVariable->var->variable;
        }
    }
}

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
    m_reportErrors = (url != IndexedString("PHPInternalFunctions"));
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
    DUChainWriteLocker lock(DUChain::lock());
    while (curClass->baseClassesSize() > 0) {
        StructureType::Ptr type;
        FOREACH_FUNCTION(BaseClassInstance base, curClass->baseClasses) {
            DUChainReadLocker lock(DUChain::lock());
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
    QualifiedIdentifier name = identifierForNode(node->variable);
    if (m_reportErrors) {   // check for redeclarations
        DUChainWriteLocker lock(DUChain::lock());
        Q_ASSERT(currentContext()->type() == DUContext::Class);
        foreach(Declaration * dec, currentContext()->findLocalDeclarations(name.first())) {
            if (!dec->isFunctionDeclaration() && ! dec->abstractType()->modifiers() & AbstractType::ConstModifier) {
                reportRedeclarationError(dec, node);
                break;
            }
        }
    }
    openClassMemberDeclaration(node->variable, name);
    DeclarationBuilderBase::visitClassVariable(node);
    closeDeclaration();
}

void DeclarationBuilder::openClassMemberDeclaration(AstNode* node, const QualifiedIdentifier &name)
{
    DUChainWriteLocker lock(DUChain::lock());

    // dirty hack: declarations of class members outside the class context would
    //             make the class context encompass the newRange. This is not what we want.
    SimpleRange oldRange = currentContext()->range();

    SimpleRange newRange = editorFindRange(node, node);
    openDefinition<ClassMemberDeclaration>(name, newRange);

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

    currentContext()->setRange(oldRange);
}

void DeclarationBuilder::declareClassMember(DUContext *parentCtx, AbstractType::Ptr type,
                                                const QualifiedIdentifier& identifier,
                                                AstNode* node )
{
    // check for redeclaration of private or protected stuff
    {
        // only interesting context might be the class context when we are inside a method
        DUContext *ctx = currentContext()->parentContext();
        foreach ( Declaration* dec, parentCtx->findDeclarations(identifier) ) {
            if ( ClassMemberDeclaration* cdec = dynamic_cast<ClassMemberDeclaration*>(dec) ) {
                if ( cdec->accessPolicy() == Declaration::Private && cdec->context() != ctx ) {
                    reportError(i18n("Cannot redeclare private property %1 from this context.",
                                        cdec->toString()), node);
                    return;
                } else if ( cdec->accessPolicy() == Declaration::Protected
                            && cdec->context() != ctx
                            && ( !ctx || !ctx->imports(cdec->context()) ) ) {
                    reportError(i18n("Cannot redeclare protected property %1 from this context.",
                                        cdec->toString()), node);
                    return;
                }
                if ( cdec->abstractType()->indexed() == type->indexed() ) {
                    kDebug() << "skipping redeclaration of" << cdec->toString();
                    return;
                }
            }
        }
    }

    // this member should be public and non-static
    m_currentModifers = ModifierPublic;
    injectContext(editor()->smart(), parentCtx);
    openClassMemberDeclaration(node, identifier);
    m_currentModifers = 0;
    //own closeDeclaration() that doesn't use lastType()
    currentDeclaration()->setType(type);
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
    closeInjectedContext(editor()->smart());
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
    if ( m_reportErrors ) {
        // const class members may only be ints, floats, bools or strings
        bool badType = true;
        if ( IntegralType* type = fastCast<IntegralType*>(lastType().unsafeData()) ) {
            switch( type->dataType() ) {
                case IntegralType::TypeBoolean:
                case IntegralType::TypeFloat:
                case IntegralType::TypeInt:
                case IntegralType::TypeString:
                    badType = false;
                    break;
                default:
                    // every other type is a badType (see above)
                    break;
            }
        }
        if ( badType ) {
            reportError(i18n("Only booleans, ints, floats and strings are allowed for class constants."), node->scalar);
        }
    }
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
    if (filename == "PHPInternalFunctions") {
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
void DeclarationBuilder::visitTopStatement(TopStatementAst* node)
{
    //docblock of an AssignmentExpression
    setComment(formatComment(node, editor()));
    m_lastTopStatementComment = editor()->parseSession()->docComment(node->startToken);

    DeclarationBuilderBase::visitTopStatement(node);
}

void DeclarationBuilder::visitAssignmentExpression(AssignmentExpressionAst* node)
{
    if ( node->assignmentExpressionEqual ) {
        bool lastFindVariable = m_findVariable;
        QualifiedIdentifier lastVariable = m_variable;
        QualifiedIdentifier lastVariableParent = m_variableParent;
        bool lastIsArray = m_variableIsArray;
        AstNode* lastNode = m_variableNode;

        m_findVariable = true;
        m_variable = QualifiedIdentifier();
        m_variableParent = QualifiedIdentifier();
        m_variableIsArray = false;
        m_variableNode = 0;

        DeclarationBuilderBase::visitAssignmentExpression(node);

        m_findVariable = lastFindVariable;
        m_variable = lastVariable;
        m_variableParent = lastVariableParent;
        m_variableIsArray = lastIsArray;
        m_variableNode = lastNode;
    } else {
        DeclarationBuilderBase::visitAssignmentExpression(node);
    }
}

void DeclarationBuilder::visitVariable(VariableAst* node)
{
    if ( m_findVariable ) {
        getVariableIdentifier(node, m_variable, m_variableParent,
                                    m_variableNode, m_variableIsArray);
        m_findVariable = false;
    }
    DeclarationBuilderBase::visitVariable(node);
}

void DeclarationBuilder::declareVariable(DUContext* parentCtx, AbstractType::Ptr type,
                                            const QualifiedIdentifier& identifier,
                                            AstNode* node)
{
    // we must not re-assign $this in a class context
    if ( identifier == QualifiedIdentifier("this")
            && currentContext()->parentContext()
            && currentContext()->parentContext()->type() == DUContext::Class ) {
        reportError(i18n("Cannot re-assign $this."), QList<AstNode*>() << node);
        return;
    }

    DUChainWriteLocker lock(DUChain::lock());

    // check if this variable is already declared
    {
        QList< Declaration* > decs = parentCtx->findLocalDeclarations(identifier.first());
        if ( !decs.isEmpty() ) {
            QList< Declaration* >::const_iterator it = decs.constEnd() - 1;
            while ( true ) {
                // we expect that the list of declarations has the newest declaration at back
                if ( dynamic_cast<VariableDeclaration*>( *it ) ) {
                    if ( (*it)->abstractType()->indexed() == type->indexed() ) {
                        kDebug() << "skipping redeclaration of" << (*it)->toString();
                        return;
                    }
                    break;
                }
                if ( it == decs.constBegin() ) {
                    break;
                }
                --it;
            }
        }
    }

    SimpleRange newRange = editorFindRange(node, node);

    VariableDeclaration *dec = openDefinition<VariableDeclaration>(identifier, newRange);
    dec->setKind(Declaration::Instance);
    if (!m_lastTopStatementComment.isEmpty()) {
        QRegExp rx("\\* +@superglobal");
        if (rx.indexIn(m_lastTopStatementComment) != -1) {
            dec->setSuperglobal(true);
        }
    }
    //own closeDeclaration() that doesn't use lastType()
    currentDeclaration()->setType(type);
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

///TODO: we need to handle assignment to array-members properly
///      currently we just make sure the the array is declared, but don't know
///      anything about its contents
void DeclarationBuilder::visitAssignmentExpressionEqual(AssignmentExpressionEqualAst *node)
{
    DeclarationBuilderBase::visitAssignmentExpressionEqual(node);

    if ( !m_variable.isEmpty() && currentAbstractType()) {
        //create new declaration assignments to not-yet declared variables and class members

        AbstractType::Ptr type;
        if ( m_variableIsArray ) {
            // implicit array declaration
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeArray));
        } else {
            type = currentAbstractType();
        }

        if ( !m_variableParent.isEmpty() ) {
            // assignment to class members

            DUChainWriteLocker lock(DUChain::lock());

            // get parent class context
            DUContext* parentCtx = 0;
            if ( m_variableParent == QualifiedIdentifier("this") ) {
                if ( currentContext()->parentContext() && currentContext()->parentContext()->type() == DUContext::Class ) {
                    parentCtx = currentContext()->parentContext();
                }
            } else {
                foreach( Declaration* parent, currentContext()->topContext()->findDeclarations(m_variableParent) ) {
                    if ( StructureType::Ptr ctype = parent->type<StructureType>() ) {
                        parentCtx = ctype->internalContext(currentContext()->topContext());
                        break;
                    }
                }
            }

            if ( parentCtx ) {
                declareClassMember(parentCtx, type, m_variable, m_variableNode );
            }
        } else {
            // assigment to other variables
            declareVariable(currentContext(), type, m_variable, m_variableNode );
        }
    }
}

void DeclarationBuilder::visitFunctionCall(FunctionCallAst* node)
{
    {
        FunctionType::Ptr oldFunction = m_currentFunctionType;

        Declaration* dec = 0;
        if ( node->stringFunctionName ) {
            dec = findDeclarationImport(FunctionDeclarationType, node->stringFunctionName);
        } else if ( node->stringFunctionNameOrClass ) {
            dec = findDeclarationImport(FunctionDeclarationType, node->stringFunctionNameOrClass);
        } else {
            ///TODO: node->varFunctionName
        }

        if ( dec ) {
            m_currentFunctionType = dec->type<FunctionType>();
        } else {
            m_currentFunctionType = 0;
        }

        DeclarationBuilderBase::visitFunctionCall(node);

        m_currentFunctionType = oldFunction;
    }

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

void DeclarationBuilder::visitFunctionCallParameterList(FunctionCallParameterListAst* node)
{
    int oldPos = m_functionCallParameterPos;
    m_functionCallParameterPos = 0;

    DeclarationBuilderBase::visitFunctionCallParameterList(node);

    m_functionCallParameterPos = oldPos;
}

void DeclarationBuilder::visitFunctionCallParameterListElement(FunctionCallParameterListElementAst* node)
{
    bool lastFindVariable = m_findVariable;
    QualifiedIdentifier lastVariable = m_variable;
    QualifiedIdentifier lastVariableParent = m_variableParent;
    bool lastIsArray = m_variableIsArray;
    AstNode* lastNode = m_variableNode;

    m_findVariable = true;
    m_variable = QualifiedIdentifier();
    m_variableParent = QualifiedIdentifier();
    m_variableIsArray = false;
    m_variableNode = 0;

    DeclarationBuilderBase::visitFunctionCallParameterListElement(node);

    if ( m_variableNode && !m_currentFunctionType.isNull() &&
            m_currentFunctionType->arguments().count() > m_functionCallParameterPos) {
        ReferenceType::Ptr refType = m_currentFunctionType->arguments()
                                        .at(m_functionCallParameterPos).cast<ReferenceType>();
        if ( refType ) {
            // this argument is referenced, so if the node contains undeclared variables we have
            // to declare them with a NULL type, see also:
            // http://de.php.net/manual/en/language.references.whatdo.php
            ///TODO: support something like: foo($var[0])
            if ( !m_variableIsArray ) {
                DUContext *ctx;
                if ( m_variableParent.isEmpty() ) {
                    ctx = currentContext();
                } else {
                    ClassDeclaration* cdec = dynamic_cast<ClassDeclaration*>(
                        findDeclarationImport(ClassDeclarationType, m_variableParent, 0)
                    );
                    if ( cdec ) {
                        ctx = cdec->internalContext();
                    }
                }
                if ( ctx ) {
                    bool isDeclared = false;
                    {
                        DUChainWriteLocker lock(DUChain::lock());
                        foreach ( Declaration* dec, ctx->findDeclarations(m_variable) ) {
                            if ( dec->kind() == Declaration::Instance ) {
                                isDeclared = true;
                                break;
                            }
                        }
                    }
                    if ( !isDeclared && m_variableParent.isEmpty() ) {
                        // check also for global vars
                        isDeclared = findDeclarationImport(GlobalVariableDeclarationType, m_variable, m_variableNode);
                    }
                    if ( !isDeclared ) {
                        // couldn't find the dec, declare it with NULL type, just like PHP does:
                        AbstractType::Ptr newType(new IntegralType(IntegralType::TypeNull));
                        if ( !m_variableParent.isEmpty() ) {
                            declareClassMember(ctx, newType, m_variable, m_variableNode);
                        } else {
                            declareVariable(ctx, newType, m_variable, m_variableNode);
                        }
                    }
                }
            }
        }
    }

    m_findVariable = lastFindVariable;
    m_variable = lastVariable;
    m_variableParent = lastVariableParent;
    m_variableIsArray = lastIsArray;
    m_variableNode = lastNode;

    ++m_functionCallParameterPos;
}

void DeclarationBuilder::visitStatement(StatementAst* node)
{
    DeclarationBuilderBase::visitStatement(node);

    if (node->foreachVariable) {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->foreachVariable->variable, node->foreachVariable->variable);
        openDefinition<VariableDeclaration>(identifierForNode(node->foreachVariable->variable), newRange);
        currentDeclaration()->setKind(Declaration::Instance);
        closeDeclaration();

        clearLastType();
    }

    if (node->foreachVarAsVar) {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->foreachVarAsVar->variable, node->foreachVarAsVar->variable);
        openDefinition<VariableDeclaration>(identifierForNode(node->foreachVarAsVar->variable), newRange);
        currentDeclaration()->setKind(Declaration::Instance);
        closeDeclaration();
    }

    if (node->foreachExprAsVar) {
        DUChainWriteLocker lock(DUChain::lock());
        SimpleRange newRange = editorFindRange(node->foreachExprAsVar, node->foreachExprAsVar);
        openDefinition<VariableDeclaration>(identifierForNode(node->foreachExprAsVar), newRange);
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

void DeclarationBuilder::visitCatchItem(CatchItemAst *node)
{
    DeclarationBuilderBase::visitCatchItem(node);

    DUChainWriteLocker lock(DUChain::lock());
    SimpleRange newRange = editorFindRange(node->var, node->var);
    openDefinition<VariableDeclaration>(identifierForNode(node->var), newRange);
    currentDeclaration()->setKind(Declaration::Instance);
    closeDeclaration();
}

void DeclarationBuilder::visitUnaryExpression(UnaryExpressionAst* node)
{
    DeclarationBuilderBase::visitUnaryExpression(node);
    IndexedString includeFile = getIncludeFileForNode(node, editor());
    if ( !includeFile.isEmpty() ) {
        ///TODO: is there not a more elegant way to get a QualifiedIdentifier from a IndexedString?
        QualifiedIdentifier identifier(QString::fromUtf8(includeFile.byteArray()));

        DUChainWriteLocker lock(DUChain::lock());
        foreach ( Declaration* dec, currentContext()->topContext()->findDeclarations(identifier) ) {
            if ( dec->kind() == Declaration::Namespace && dec->range().isEmpty() ) {
                // nothing to do
                return;
            }
        }
        injectContext(editor()->smart(), currentContext()->topContext());
        openDefinition<Declaration>(identifier, SimpleRange(0, 0, 0, 0));
        currentDeclaration()->setKind(Declaration::Namespace);
        eventuallyAssignInternalContext();
        DeclarationBuilderBase::closeDeclaration();
        closeInjectedContext(editor()->smart());
    }
}

}
