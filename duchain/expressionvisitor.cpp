/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "expressionvisitor.h"
#include "parsesession.h"
#include "editorintegrator.h"
#include "helper.h"
#include "declarations/variabledeclaration.h"
#include "declarations/classdeclaration.h"

#include <language/duchain/topducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/unsuretype.h>

#include "duchaindebug.h"

#include <QRegExp>

#define ifDebug(x)

using namespace KDevelop;

namespace Php
{

ExpressionVisitor::ExpressionVisitor(EditorIntegrator* editor)
        : m_editor(editor), m_createProblems(false),
          m_offset(CursorInRevision::invalid()), m_currentContext(nullptr),
          m_isAssignmentExpressionEqual(false),
          m_inDefine(false)
{
}

DeclarationPointer ExpressionVisitor::processVariable(VariableIdentifierAst* variable)
{
    Q_ASSERT(m_currentContext);

    CursorInRevision position = m_editor->findPosition(variable->variable, EditorIntegrator::BackEdge);

    if ( m_offset.isValid() ) {
        position.line += m_offset.line;
        position.column += m_offset.column;
    }

    DeclarationPointer ret;
    Identifier identifier = identifierForNode(variable).last();

    ifDebug(qCDebug(DUCHAIN) << "processing variable" << identifier.toString() << position.castToSimpleCursor();)

    DUChainReadLocker lock;

    if (identifier.nameEquals(Identifier(QStringLiteral("this")))) {
        if (m_currentContext->parentContext()
                && m_currentContext->parentContext()->type() == DUContext::Class
                && m_currentContext->parentContext()->owner()) {
            ret = m_currentContext->parentContext()->owner();
        }
    } else {
        //DontSearchInParent-flag because (1) in Php global variables aren't available in function
        //context and (2) a function body consists of a single context (so this is no problem)
        ret = findVariableDeclaration(m_currentContext, identifier, position, DUContext::DontSearchInParent);
    }
    if (!ret && m_currentContext->type() == DUContext::Namespace)
    {
        ret = findVariableDeclaration(m_currentContext, identifier, position, DUContext::NoSearchFlags);
    }
    if (!ret) {
        //look for a function argument
        ///TODO: why doesn't m_currentContext->findDeclarations() work?
        ///      evaluate if the stuff below is fast enough (faster?) than findDeclarations()
        ///see r1028306
        foreach(const DUContext::Import &import, m_currentContext->importedParentContexts() ) {
            if ( !import.isDirect() || import.position > position ) {
                continue;
            }
            DUContext* ctx = import.context(m_currentContext->topContext());
            if ( ctx->type() == DUContext::Function ) {
                QList<Declaration*> args = ctx->findLocalDeclarations(identifier);
                if ( !args.isEmpty() ) {
                    ret = args.first();
                    break;
                }
            }
        }
    }
    if (!ret) {
        //look for a superglobal variable
        foreach(Declaration* dec, m_currentContext->topContext()->findDeclarations(identifier, position)) {
            VariableDeclaration* varDec = dynamic_cast<VariableDeclaration*>(dec);
            if (varDec && varDec->isSuperglobal()) {
                ret = dec;
                break;
            }
        }
    }

    lock.unlock();

    if ( !m_isAssignmentExpressionEqual || identifier.nameEquals( Identifier(QStringLiteral("this")) )
         // might be something like $s = $s . $s; in which case we have to add a use for the first $s
         || (ret && ret->range().end < position) )
    {
        // also don't report uses for the place of declaration
        if (!ret || ret->range().end != position) {
            usingDeclaration(variable, ret);
        }
    }
    ifDebug(qCDebug(DUCHAIN) << "found declaration:" << (ret ? ret->toString() : QString("no declaration found"));)
    return ret;
}

void ExpressionVisitor::visitNode(AstNode *node)
{
    if (node && node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);
    DefaultVisitor::visitNode(node);
}

void ExpressionVisitor::visitAssignmentExpression(AssignmentExpressionAst *node)
{
    if (node->assignmentExpressionEqual) {
        m_isAssignmentExpressionEqual = true;
    }
    visitNode(node->expression);
    m_isAssignmentExpressionEqual = false;

    visitNode(node->assignmentExpressionEqual);
    visitNode(node->assignmentExpression);

    if (node->operation == OperationPlus || node->operation == OperationMinus ||
            node->operation == OperationMul || node->operation == OperationDiv ||
            node->operation == OperationExp) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeInt)));
    } else if (node->operation == OperationConcat) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeString)));
    }
}

void ExpressionVisitor::visitArrayIndexSpecifier(ArrayIndexSpecifierAst* node)
{
    DefaultVisitor::visitArrayIndexSpecifier(node);

    // it's an array item but we don't support it really, so just assign type mixed and be done
    m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed)));
}

void ExpressionVisitor::visitCompoundVariableWithSimpleIndirectReference(CompoundVariableWithSimpleIndirectReferenceAst *node)
{
    if (node->variable) {
        m_result.setDeclaration(processVariable(node->variable));
    }
    DefaultVisitor::visitCompoundVariableWithSimpleIndirectReference(node);
}

void ExpressionVisitor::visitVariable(VariableAst* node)
{
    if ( node->variablePropertiesSequence &&
         node->variablePropertiesSequence->front() &&
         node->variablePropertiesSequence->front()->element &&
         node->variablePropertiesSequence->front()->element->variableProperty &&
         node->variablePropertiesSequence->front()->element->variableProperty->objectProperty ) {
        // make sure we mark $foo as a use in $foo->...
        bool isAssignmentExpressionEqual = m_isAssignmentExpressionEqual;
        m_isAssignmentExpressionEqual = false;
        DefaultVisitor::visitVariable(node);
        m_isAssignmentExpressionEqual = isAssignmentExpressionEqual;
    } else {
        DefaultVisitor::visitVariable(node);
    }
}

void ExpressionVisitor::visitVarExpression(VarExpressionAst *node)
{
    DefaultVisitor::visitVarExpression(node);
    if (node->isGenerator != -1) {
        DeclarationPointer generatorDecl = findDeclarationImport(ClassDeclarationType, QualifiedIdentifier(u"generator"));

        if (generatorDecl) {
            m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed)));
            if (hasCurrentClosureReturnType()) {
                auto closureType = currentClosureReturnType().staticCast<FunctionType>();
                closureType->setReturnType(generatorDecl->abstractType());
            }
        }
    }
}

void ExpressionVisitor::visitVarExpressionNewObject(VarExpressionNewObjectAst *node)
{
    DefaultVisitor::visitVarExpressionNewObject(node);
    if (node->classNameReference->className && node->classNameReference->className->staticIdentifier != -1) {
        static const QualifiedIdentifier id(QStringLiteral("static"));
        DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, id);
        usingDeclaration(node->classNameReference->className, dec);
        m_result.setDeclaration(dec);
    } else if (node->classNameReference->className && node->classNameReference->className->identifier) {
        const QualifiedIdentifier id = identifierForNamespace(node->classNameReference->className->identifier, m_editor);
        DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, id);
        usingDeclaration(node->classNameReference->className->identifier->namespaceNameSequence->back()->element, dec);
        buildNamespaceUses(node->classNameReference->className->identifier, id);
        m_result.setDeclaration(dec);
    }
}

void ExpressionVisitor::visitVarExpressionArray(VarExpressionArrayAst *node)
{
    DefaultVisitor::visitVarExpressionArray(node);
    m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeArray)));
}

void ExpressionVisitor::visitClosure(ClosureAst* node)
{
    auto* closureType = new FunctionType;
    closureType->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    openClosureReturnType(AbstractType::Ptr(closureType));
    if (node->functionBody) {
        visitInnerStatementList(node->functionBody);
    }
    if (node->returnType) {
        visitReturnType(node->returnType);
    }

    //Override found type with return typehint or phpdoc return typehint
    AbstractType::Ptr type = returnType(node->returnType, {}, m_editor, m_currentContext);

    if (type) {
        closureType->setReturnType(type);
    }

    if (node->parameters->parametersSequence) {
        const KDevPG::ListNode< ParameterAst* >* it = node->parameters->parametersSequence->front();
        forever {
            AbstractType::Ptr type = parameterType(it->element, {}, m_editor, m_currentContext);
            closureType->addArgument(type);

            if (it->element->parameterType) {
                visitParameterType(it->element->parameterType);
            }

            if (it->element->defaultValue) {
                visitExpr(it->element->defaultValue);
            }
            if ( it->hasNext() ) {
                it = it->next;
            } else {
                break;
            }
        }
    }

    if (node->lexicalVars && node->lexicalVars->lexicalVarsSequence) {
        const KDevPG::ListNode< LexicalVarAst* >* it = node->lexicalVars->lexicalVarsSequence->front();
        DUChainWriteLocker lock;
        forever {
            DeclarationPointer found;
            foreach(Declaration* dec, m_currentContext->findDeclarations(identifierForNode(it->element->variable))) {
                if (dec->kind() == Declaration::Instance) {
                    found = dec;
                    break;
                }
            }
            usingDeclaration(it->element->variable, found);
            if ( it->hasNext() ) {
                it = it->next;
            } else {
                break;
            }
        }
    }

    m_result.setType(AbstractType::Ptr(closureType));
    closeClosureReturnType();
}

void ExpressionVisitor::visitFunctionCallParameterList( FunctionCallParameterListAst* node )
{
    QList<DeclarationPointer> decs = m_result.allDeclarations();
    AbstractType::Ptr type = m_result.type();

    DefaultVisitor::visitFunctionCallParameterList( node );

    m_result.setDeclarations(decs);
    m_result.setType(type);
}

void ExpressionVisitor::visitFunctionCallParameterListElement(FunctionCallParameterListElementAst* node)
{
    DefaultVisitor::visitFunctionCallParameterListElement(node);

    if (m_inDefine) m_inDefine = false; //reset after first parameter passed, the second argument can be a class name
}

void ExpressionVisitor::visitFunctionCall(FunctionCallAst* node)
{
    if (node->stringFunctionNameOrClass && !node->stringFunctionName && !node->varFunctionName) {
        QualifiedIdentifier id = identifierForNamespace(node->stringFunctionNameOrClass, m_editor);
        if (id.toString(RemoveExplicitlyGlobalPrefix) == QLatin1String("define")
                && node->stringParameterList && node->stringParameterList->parametersSequence
                && node->stringParameterList->parametersSequence->count() > 0) {
            //in a define() call the first argument is the constant name. we don't want to look for a class name to build uses
            m_inDefine = true;
        }
    }

    DefaultVisitor::visitFunctionCall(node);

    m_inDefine = false;

    if (node->stringFunctionNameOrClass) {
        if (node->stringFunctionName) {
            //static function call foo::bar()
            DUContext* context = findClassContext(node->stringFunctionNameOrClass);
            if (context) {
                DUChainReadLocker lock(DUChain::lock());
                QualifiedIdentifier methodName(stringForNode(node->stringFunctionName).toLower());
                m_result.setDeclarations(context->findDeclarations(methodName));
                lock.unlock();
                if (!m_result.allDeclarations().isEmpty()) {
                    usingDeclaration(node->stringFunctionName, m_result.allDeclarations().last());
                    FunctionType::Ptr function = m_result.allDeclarations().last()->type<FunctionType>();
                    if (function) {
                        m_result.setType(function->returnType());
                    } else {
                        m_result.setType(AbstractType::Ptr());
                    }
                }
            } else {
                m_result.setHadUnresolvedIdentifiers(true);
                usingDeclaration(node->stringFunctionName, DeclarationPointer());
                m_result.setType(AbstractType::Ptr());
            }
        } else if (node->varFunctionName) {
            //static function call foo::$bar()
        } else if (node->expr) {
            //static function call foo::{expr}()
            const QualifiedIdentifier id = identifierForNamespace(node->stringFunctionNameOrClass, m_editor);
            DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, id);
            usingDeclaration(node->stringFunctionNameOrClass->namespaceNameSequence->back()->element, dec);
            buildNamespaceUses(node->stringFunctionNameOrClass, id);
            m_result.setDeclaration(dec);
        } else {
            //global function call foo();
            QualifiedIdentifier id = identifierForNamespace(node->stringFunctionNameOrClass, m_editor);
            DeclarationPointer dec = findDeclarationImport(FunctionDeclarationType, id);
            if (!dec) {
                id.setExplicitlyGlobal(true);
                dec = findDeclarationImport(FunctionDeclarationType, id);
            }
            ifDebug(qCDebug(DUCHAIN) << "function call of" << (dec ? dec->toString() : QString("function not found"));)
            m_result.setDeclaration(dec);
            usingDeclaration(node->stringFunctionNameOrClass->namespaceNameSequence->back()->element, dec);
            buildNamespaceUses(node->stringFunctionNameOrClass, id);
            if (dec) {
                FunctionType::Ptr function = dec->type<FunctionType>();
                if (function) {
                    m_result.setType(function->returnType());
                } else {
                    m_result.setType(AbstractType::Ptr());
                }
            } else {
                m_result.setHadUnresolvedIdentifiers(true);
            }
        }
    }
}
///TODO: DUContext pointer?
DUContext* ExpressionVisitor::findClassContext(IdentifierAst* className)
{
    DUContext* context = nullptr;
    DeclarationPointer declaration = findDeclarationImport(ClassDeclarationType, className);
    usingDeclaration(className, declaration);
    if (declaration) {
        DUChainReadLocker lock(DUChain::lock());
        context = declaration->internalContext();
        if (!context && m_currentContext->parentContext() && m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
            //className is currentClass (internalContext is not yet set)
            context = m_currentContext->parentContext();
        }
    }
    return context;
}
///TODO: DUContext pointer?
DUContext* ExpressionVisitor::findClassContext(NamespacedIdentifierAst* className)
{
    DUContext* context = nullptr;
    const QualifiedIdentifier id = identifierForNamespace(className, m_editor);
    DeclarationPointer declaration = findDeclarationImport(ClassDeclarationType, id);
    usingDeclaration(className->namespaceNameSequence->back()->element, declaration);
    buildNamespaceUses(className, id);
    if (declaration) {
        DUChainReadLocker lock(DUChain::lock());
        context = declaration->internalContext();
        if (!context && m_currentContext->parentContext() && m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
            //className is currentClass (internalContext is not yet set)
            context = m_currentContext->parentContext();
        }
    }
    return context;
}

void ExpressionVisitor::visitConstantOrClassConst(ConstantOrClassConstAst *node)
{
    DefaultVisitor::visitConstantOrClassConst(node);

    if (node->classConstant) {
        //class constant Foo::BAR
        DUContext* context = findClassContext(node->constant);
        if (context) {
            DUChainReadLocker lock(DUChain::lock());
            m_result.setDeclarations(context->findDeclarations(Identifier(m_editor->parseSession()->symbol(node->classConstant))));
            lock.unlock();
            if (!m_result.allDeclarations().isEmpty()) {
                usingDeclaration(node->classConstant, m_result.allDeclarations().last());
            } else {
                usingDeclaration(node->classConstant, DeclarationPointer());
            }
            if (!stringForNode(node->classConstant).compare(QLatin1String("class"), Qt::CaseInsensitive)) {
                m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeString)));
            }
        } else {
            m_result.setType(AbstractType::Ptr());
        }
    } else {
        QString str(stringForNode(node->constant).toLower());
        if (str == QLatin1String("true") || str == QLatin1String("false")) {
            m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeBoolean)));
        } else if (str == QLatin1String("null")) {
            m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeNull)));
        } else {
            //constant (created with declare('foo', 'bar')) or const Foo = 1;
            QualifiedIdentifier id = identifierForNamespace(node->constant, m_editor, true);
            DeclarationPointer declaration = findDeclarationImport(ConstantDeclarationType, id);
            if (!declaration) {
                id.setExplicitlyGlobal(true);
                declaration = findDeclarationImport(ConstantDeclarationType, id);
            }
            if (!declaration) {
                ///TODO: is this really wanted?
                //it could also be a global function call, without ()
                declaration = findDeclarationImport(FunctionDeclarationType, id);
            }
            m_result.setDeclaration(declaration);
            usingDeclaration(node->constant->namespaceNameSequence->back()->element, declaration);
            buildNamespaceUses(node->constant, id);
        }
    }
}

void ExpressionVisitor::visitScalar(ScalarAst *node)
{
    DefaultVisitor::visitScalar(node);

    if (node->commonScalar) {
        uint type = IntegralType::TypeVoid;
        switch (node->commonScalar->scalarType) {
        case ScalarTypeInt:
            type = IntegralType::TypeInt;
            break;
        case ScalarTypeFloat:
            type = IntegralType::TypeFloat;
            break;
        case ScalarTypeString:
            type = IntegralType::TypeString;
            break;
        }
        m_result.setType(AbstractType::Ptr(new IntegralType(type)));
    } else if (node->varname != -1) {
        //STRING_VARNAME-Token, probably the type of varname should be used
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeString)));
    } else if (node->encapsList) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeString)));
    }

    if (!m_inDefine && node->commonScalar && node->commonScalar->scalarType == ScalarTypeString) {
        QString str = m_editor->parseSession()->symbol(node->commonScalar);
        QRegExp exp("^['\"]([A-Za-z0-9_]+)['\"]$");
        if (exp.exactMatch(str)) {
            //that *could* be a class name
            QualifiedIdentifier id(exp.cap(1).toLower());
            DeclarationPointer declaration = findDeclarationImport(ClassDeclarationType, id);
            if (declaration) {
                usingDeclaration(node->commonScalar, declaration);
            } else {
                m_result.setHadUnresolvedIdentifiers(true);
            }
        }
    }
}


void ExpressionVisitor::visitStaticScalar(StaticScalarAst *node)
{
    if (node->ducontext) {
        m_currentContext = node->ducontext;
    }
    Q_ASSERT(m_currentContext);

    DefaultVisitor::visitStaticScalar(node);

    uint type = IntegralType::TypeVoid;
    if (node->value) {
        switch (node->value->scalarType) {
        case ScalarTypeInt:
            type = IntegralType::TypeInt;
            break;
        case ScalarTypeFloat:
            type = IntegralType::TypeFloat;
            break;
        case ScalarTypeString:
            type = IntegralType::TypeString;
            break;
        }
    } else if (node->plusValue || node->minusValue) {
        type = IntegralType::TypeInt;
    } else if (node->array != -1) {
        type = IntegralType::TypeArray;
    }
    if (type != IntegralType::TypeVoid) {
        m_result.setType(AbstractType::Ptr(new IntegralType(type)));
    }
}

void ExpressionVisitor::visitEncapsVar(EncapsVarAst *node)
{
    DefaultVisitor::visitEncapsVar(node);
    if (node->variable) {
        // handle $foo
        DeclarationPointer dec = processVariable(node->variable);
        if (dec && node->propertyIdentifier) {
            // handle property in $foo->bar
            DeclarationPointer foundDec;
            DUChainReadLocker lock(DUChain::lock());
            if ( StructureType::Ptr structType = dec->type<StructureType>() ) {
                if ( ClassDeclaration* cdec = dynamic_cast<ClassDeclaration*>(structType->declaration(m_currentContext->topContext())) ) {
                    ///TODO: share code with visitVariableProperty
                    DUContext* ctx = cdec->internalContext();
                    if (!ctx && m_currentContext->parentContext()) {
                        if (m_currentContext->parentContext()->localScopeIdentifier() == cdec->qualifiedIdentifier()) {
                            //class is currentClass (internalContext is not yet set)
                            ctx = m_currentContext->parentContext();
                        }
                    }
                    if (ctx) {
                        foreach( Declaration* pdec, ctx->findDeclarations(identifierForNode(node->propertyIdentifier)) ) {
                            if ( !pdec->isFunctionDeclaration() ) {
                                foundDec = pdec;
                                break;
                            }
                        }
                    }
                }
            }
            lock.unlock();
            usingDeclaration(node->propertyIdentifier, foundDec);
        }
    }
}

void ExpressionVisitor::visitVariableProperty(VariablePropertyAst *node)
{
    ifDebug(qCDebug(DUCHAIN) << "node:" << m_editor->parseSession()->symbol(node)
        << (node->isFunctionCall != -1 ? QString("is function call") : QString("is no function call"));)
    if (node->objectProperty && node->objectProperty->objectDimList) {
        //handle $foo->bar() and $foo->baz, $foo is m_result.type()

        AbstractType::Ptr type = m_result.type();

        //If the variable type is unsure, try to see if it contains a StructureType. If so, use that
        //    (since the other types do not allow accessing properties)
        if (auto unsureType = type.dynamicCast<UnsureType>()) {
            int numStructureType = 0;
            StructureType::Ptr structureType;

            for (unsigned int i = 0; i<unsureType->typesSize(); ++i) {
                StructureType::Ptr subType = unsureType->types()[i].type<StructureType>();
                if (subType) {
                    structureType = subType;
                    ++numStructureType;
                }
            }

            //Only use the found structureType if there's exactly *one* such type
            if (numStructureType == 1) {
                Q_ASSERT(structureType);
                type = AbstractType::Ptr(structureType);
            }
        }

        if (type && type.dynamicCast<StructureType>()) {
            DUChainReadLocker lock(DUChain::lock());
            Declaration* declaration = type.staticCast<StructureType>()->declaration(m_currentContext->topContext());
            if (declaration) {
                ifDebug(qCDebug(DUCHAIN) << "parent:" << declaration->toString();)
                DUContext* context = declaration->internalContext();
                if (!context && m_currentContext->parentContext()) {
                    if (m_currentContext->parentContext()->localScopeIdentifier() == declaration->qualifiedIdentifier()) {
                        //class is currentClass (internalContext is not yet set)
                        context = m_currentContext->parentContext();
                    }
                }
                if (context) {
                    QualifiedIdentifier propertyId;
                    if ( node->isFunctionCall != -1 ) {
                        propertyId = QualifiedIdentifier(stringForNode(node->objectProperty->objectDimList->variableName->name).toLower());
                    } else {
                        propertyId = identifierForNode(node->objectProperty->objectDimList->variableName->name);
                    }
                    ifDebug(qCDebug(DUCHAIN) << "property id:" << propertyId.toString();)

                    QList<Declaration*> decs;
                    foreach ( Declaration* dec, context->findDeclarations(propertyId) ) {
                        if ( node->isFunctionCall != -1 ) {
                            if ( dec->isFunctionDeclaration() ) {
                                decs << dec;
                                ifDebug(qCDebug(DUCHAIN) << "found:" << dec->toString();)
                            }
                        } else {
                            if ( !dec->isFunctionDeclaration() ) {
                                ClassMemberDeclaration *classDec = dynamic_cast<ClassMemberDeclaration*>(dec);
                                if (classDec && classDec->accessPolicy() == Declaration::Private) {
                                    if (declaration == dec->context()->owner()) {
                                        decs << dec;
                                        ifDebug(qCDebug(DUCHAIN) << "found private:" << dec->toString();)
                                    }
                                } else {
                                    decs << dec;
                                    ifDebug(qCDebug(DUCHAIN) << "found:" << dec->toString();)
                                }
                            }
                        }
                    }
                    m_result.setDeclarations(decs);
                    lock.unlock();
                    if (!m_result.allDeclarations().isEmpty()) {
                        if ( !m_isAssignmentExpressionEqual ) {
                            usingDeclaration(node->objectProperty->objectDimList->variableName, m_result.allDeclarations().last());
                        }
                        if (node->isFunctionCall != -1) {
                            FunctionType::Ptr function = m_result.allDeclarations().last()->type<FunctionType>();
                            if (function) {
                                m_result.setType(function->returnType());
                            } else {
                                m_result.setType(AbstractType::Ptr());
                            }
                        }
                    } else {
                        if ( !m_isAssignmentExpressionEqual ) {
                            usingDeclaration(node->objectProperty->objectDimList->variableName,
                                             DeclarationPointer());
                        }
                        m_result.setType(AbstractType::Ptr());
                    }
                } else {
                    m_result.setType(AbstractType::Ptr());
                }
            } else {
                m_result.setType(AbstractType::Ptr());
            }
        }
    }
    DefaultVisitor::visitVariableProperty(node);
}

void ExpressionVisitor::visitStaticMember(StaticMemberAst* node)
{
    //don't call DefaultVisitor::visitStaticMember(node);
    //because we would end up in visitCompoundVariableWithSimpleIndirectReference
    if (node->staticProperty && node->staticProperty->staticProperty) {
        if (node->staticProperty->staticProperty->variable) {
            DUContext* context = findClassContext(node->className);
            if (context) {
                useDeclaration(node->staticProperty->staticProperty->variable, context);
            } else {
                usingDeclaration(node->className, DeclarationPointer());
                m_result.setType(AbstractType::Ptr());
            }
        } else if (node->staticProperty->staticProperty->expr) {
            const QualifiedIdentifier id = identifierForNamespace(node->className, m_editor);
            DeclarationPointer declaration = findDeclarationImport(ClassDeclarationType, id);
            usingDeclaration(node->className->namespaceNameSequence->back()->element, declaration);
            buildNamespaceUses(node->className, id);

            visitExpr(node->staticProperty->staticProperty->expr);

            m_result.setType(AbstractType::Ptr());
        }
    }

    if (node->staticProperty && node->staticProperty->offsetItemsSequence) {
        const KDevPG::ListNode< DimListItemAst* >* it = node->staticProperty->offsetItemsSequence->front();
        do {
            visitDimListItem(it->element);
        } while(it->hasNext() && (it = it->next));
    }
}

void ExpressionVisitor::visitClassNameReference(ClassNameReferenceAst* node)
{
    if (node->staticProperty) {
        DUContext* context = findClassContext(node->className->identifier);

        if (context && node->staticProperty && node->staticProperty->staticProperty) {
            if (node->staticProperty->staticProperty->variable) {
                // static properties (object::$property)
                useDeclaration(node->staticProperty->staticProperty->variable, context);
            } else if (node->staticProperty->staticProperty->expr) {
                // variable static properties (object::${$property})
                visitExpr(node->staticProperty->staticProperty->expr);
                usingDeclaration(node->className, DeclarationPointer());
            }
        }

        if (node->staticProperty && node->staticProperty->offsetItemsSequence) {
            const KDevPG::ListNode< DimListItemAst* >* dim_it = node->staticProperty->offsetItemsSequence->front();
            do {
                visitDimListItem(dim_it->element);
            } while(dim_it->hasNext() && (dim_it = dim_it->next));
        }
    }

    if (node->baseVariable) {
        DefaultVisitor::visitVariableWithoutObjects(node->baseVariable);
    }

    if (node->propertiesSequence) {
        if (!m_result.allDeclarations().isEmpty()) {
            DUContext* context = nullptr;
            StructureType::Ptr type;

            Declaration *declaration = nullptr;
            const KDevPG::ListNode< ClassPropertyAst* >* it = node->propertiesSequence->front();

            do {
                // first check for property names held in variables ($object->$property)
                if (it->element->property && it->element->property->variableWithoutObjects
                        && it->element->property->variableWithoutObjects->variable->variable) {
                    VariableIdentifierAst *varnode = it->element->property->variableWithoutObjects->variable->variable;
                    useDeclaration(varnode, m_currentContext);
                } else if (it->element->property && it->element->property->variableWithoutObjects
                        && it->element->property->variableWithoutObjects->variable->expr) {
                        // variable dynamic properties ($object->${$property})
                        visitExpr(it->element->property->variableWithoutObjects->variable->expr);
                } else if (!m_result.allDeclarations().isEmpty()) {
                    // Handle dynamic static properties first, as they don't need a class context
                    if (it->element->staticProperty && it->element->staticProperty->staticProperty
                      && it->element->staticProperty->staticProperty->expr) {
                        // variable static properties ($object::${$property})
                        visitExpr(it->element->staticProperty->staticProperty->expr);
                        usingDeclaration(it->element->staticProperty, DeclarationPointer());
                    }

                    type = m_result.allDeclarations().last()->type<StructureType>();

                    if (!type) {
                        context = nullptr;
                        visitClassNameReferenceDimListItems(it->element);
                        continue;
                    }

                    DUChainReadLocker lock(DUChain::lock());
                    declaration = type->declaration(m_currentContext->topContext());
                    lock.unlock();

                    if (!declaration) {
                        context = nullptr;
                        visitClassNameReferenceDimListItems(it->element);
                        continue;
                    }

                    context = declaration->internalContext();

                    if (!context || context->type() != DUContext::Class) {
                        context = nullptr;
                        visitClassNameReferenceDimListItems(it->element);
                        continue;
                    }

                    if (it->element->staticProperty && it->element->staticProperty->staticProperty
                      && it->element->staticProperty->staticProperty->variable) {
                        // static properties ($object::$property)
                        VariableIdentifierAst *varnode = it->element->staticProperty->staticProperty->variable;
                        useDeclaration(varnode, context);
                    } else if (it->element->property && it->element->property->objectDimList
                            && it->element->property->objectDimList->variableName->name) {
                        // normal properties ($object->property)
                        IdentifierAst *varidnode = it->element->property->objectDimList->variableName->name;
                        useDeclaration(varidnode, context);
                    } else {
                        context = nullptr;
                    }

                    visitClassNameReferenceDimListItems(it->element);
                }
            } while(it->hasNext() && (it = it->next));
        }
    }
}

void ExpressionVisitor::visitClassNameReferenceDimListItems(ClassPropertyAst* node)
{
    // handle array indices after normal/static properties ($object->property[$index] // $object::$property[$index])
    if (node->property && node->property->objectDimList && node->property->objectDimList->offsetItemsSequence) {
        const KDevPG::ListNode< DimListItemAst* >* dim_it = node->property->objectDimList->offsetItemsSequence->front();
        do {
            visitDimListItem(dim_it->element);
        } while(dim_it->hasNext() && (dim_it = dim_it->next));
    } else if (node->staticProperty && node->staticProperty->offsetItemsSequence) {
        const KDevPG::ListNode< DimListItemAst* >* dim_it = node->staticProperty->offsetItemsSequence->front();
        do {
            visitDimListItem(dim_it->element);
        } while(dim_it->hasNext() && (dim_it = dim_it->next));
    }
}

void ExpressionVisitor::visitUnaryExpression(UnaryExpressionAst* node)
{
    DefaultVisitor::visitUnaryExpression(node);
    if (node->castType) {
        uint type = 0;
        switch (node->castType) {
        case CastInt:
            type = IntegralType::TypeInt;
            break;
        case CastDouble:
            type = IntegralType::TypeFloat;
            break;
        case CastString:
            type = IntegralType::TypeString;
            break;
        case CastArray:
            type = IntegralType::TypeArray;
            break;
        case CastObject: {
            /// Qualified identifier for 'stdclass'
            static const QualifiedIdentifier stdclassQId(QStringLiteral("stdclass"));
            DUChainReadLocker lock(DUChain::lock());
            m_result.setDeclarations(m_currentContext->findDeclarations(stdclassQId));
            break;
        }
        case CastBool:
            type = IntegralType::TypeBoolean;
            break;
        case CastUnset:
            //TODO
            break;
        }
        if (type) {
            m_result.setType(AbstractType::Ptr(new IntegralType(type)));
        }
    }
}

void ExpressionVisitor::visitAdditiveExpressionRest(AdditiveExpressionRestAst* node)
{
    DefaultVisitor::visitAdditiveExpressionRest(node);
    if (node->operation == OperationPlus || node->operation == OperationMinus) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeInt)));
    } else if (node->operation == OperationConcat) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeString)));
    }
}

void ExpressionVisitor::visitRelationalExpression(RelationalExpressionAst *node)
{
    DefaultVisitor::visitRelationalExpression(node);
    if (node->instanceofType && node->instanceofType->className && node->instanceofType->className->identifier) {
        const QualifiedIdentifier id = identifierForNamespace(node->instanceofType->className->identifier, m_editor);
        DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, id);
        usingDeclaration(node->instanceofType->className->identifier->namespaceNameSequence->back()->element, dec);
        buildNamespaceUses(node->instanceofType->className->identifier, id);

        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeBoolean)));
    }
}

void ExpressionVisitor::visitRelationalExpressionRest(RelationalExpressionRestAst *node)
{
    DefaultVisitor::visitRelationalExpressionRest(node);

    m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeBoolean)));
}

void ExpressionVisitor::visitEqualityExpressionRest(EqualityExpressionRestAst *node)
{
    DefaultVisitor::visitEqualityExpressionRest(node);

    if (node->operation && node->operation == OperationSpaceship) {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeInt)));
    } else {
        m_result.setType(AbstractType::Ptr(new IntegralType(IntegralType::TypeBoolean)));
    }
}

void ExpressionVisitor::visitStatement(StatementAst *node)
{
    DefaultVisitor::visitStatement(node);

    if (node->returnExpr) {
        auto closureType = currentClosureReturnType().dynamicCast<FunctionType>();

        if (closureType) {
            closureType->setReturnType(m_result.type());
        }
    }
}

void ExpressionVisitor::visitGenericTypeHint(GenericTypeHintAst *node) {
    if (node->genericType && isGenericClassTypehint(node->genericType, m_editor)) {
        NamespacedIdentifierAst* objectType = node->genericType;
        QualifiedIdentifier id = identifierForNamespace(objectType, m_editor);
        DeclarationPointer dec = findDeclarationImport(ClassDeclarationType, id);

        usingDeclaration(objectType->namespaceNameSequence->back()->element, dec);
        buildNamespaceUses(objectType, id);
    }
}

QString ExpressionVisitor::stringForNode(AstNode* id)
{
    if (!id)
        return QString();

    return m_editor->parseSession()->symbol(id);
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(IdentifierAst* id)
{
    if (!id)
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}

QString ExpressionVisitor::stringForNode(VariableIdentifierAst* id)
{
    if (!id)
        return QString();
    QString ret(m_editor->parseSession()->symbol(id->variable));
    ret = ret.mid(1); //cut off $
    return ret;
}

QualifiedIdentifier ExpressionVisitor::identifierForNode(VariableIdentifierAst* id)
{
    if (!id)
        return QualifiedIdentifier();

    return QualifiedIdentifier(stringForNode(id));
}

void ExpressionVisitor::setCreateProblems(bool v)
{
    m_createProblems = v;
}

void ExpressionVisitor::setOffset(const CursorInRevision& offset)
{
    m_offset = offset;
}

void ExpressionVisitor::buildNamespaceUses(NamespacedIdentifierAst* namespaces, const QualifiedIdentifier& identifier)
{
    QualifiedIdentifier curId;
    curId.setExplicitlyGlobal(identifier.explicitlyGlobal());
    Q_ASSERT(identifier.count() == namespaces->namespaceNameSequence->count());
    for ( int i = 0; i < identifier.count() - 1; ++i ) {
        curId.push(identifier.at(i));
        AstNode* node = namespaces->namespaceNameSequence->at(i)->element;
        DeclarationPointer dec = findDeclarationImport(NamespaceDeclarationType, curId);
        usingDeclaration(node, dec);
    }
}

void ExpressionVisitor::useDeclaration(VariableIdentifierAst* node, DUContext* context)
{
    DUChainReadLocker lock(DUChain::lock());
    m_result.setDeclarations(context->findDeclarations(identifierForNode(node)));
    lock.unlock();
    if (!m_result.allDeclarations().isEmpty()) {
        usingDeclaration(node, m_result.allDeclarations().last());
    } else {
        usingDeclaration(node, DeclarationPointer());
    }
}

void ExpressionVisitor::useDeclaration(IdentifierAst* node, DUContext* context)
{
    DUChainReadLocker lock(DUChain::lock());
    m_result.setDeclarations(context->findDeclarations(identifierForNode(node)));
    lock.unlock();
    if (!m_result.allDeclarations().isEmpty()) {
        usingDeclaration(node, m_result.allDeclarations().last());
    } else {
        usingDeclaration(node, DeclarationPointer());
    }
}

DeclarationPointer ExpressionVisitor::findDeclarationImport(DeclarationType declarationType, IdentifierAst* node)
{
    // methods and class names are case insensitive
    QualifiedIdentifier id;
    if ( declarationType == ClassDeclarationType || declarationType == FunctionDeclarationType ) {
        id = QualifiedIdentifier(stringForNode(node).toLower());
    } else {
        id = identifierForNode(node);
    }
    return findDeclarationImport(declarationType, id);
}

DeclarationPointer ExpressionVisitor::findDeclarationImport(DeclarationType declarationType, VariableIdentifierAst* node)
{
    return findDeclarationImport(declarationType, identifierForNode(node));
}

DeclarationPointer ExpressionVisitor::findDeclarationImport( DeclarationType declarationType,
                                                             const QualifiedIdentifier& identifier)
{
    return findDeclarationImportHelper(m_currentContext, identifier, declarationType);
}

Declaration* ExpressionVisitor::findVariableDeclaration(DUContext* context, Identifier identifier,
                                                        CursorInRevision position, DUContext::SearchFlag flag)
{
    QList<Declaration*> decls = context->findDeclarations(identifier, position,
                                                        nullptr, flag);
    for (int i = decls.count() - 1; i >= 0; i--) {
        Declaration *dec = decls.at(i);
        if (dec->kind() == Declaration::Instance && dynamic_cast<VariableDeclaration*>(dec)) {
            return dec;
        }
    }

    return nullptr;
}

}
