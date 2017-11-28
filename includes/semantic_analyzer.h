//
// Created by keltar on 11/23/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ANALYZER_H
#define TINY_C_COMPILER_SEMANTIC_ANALYZER_H

#include "scope_tree.h"
#include "nodes.h"
#include "type_builder.h"

class SemanticAnalyzer
{
public:
    IdNode *BuildIdNode(std::shared_ptr<Token> token);
    StructSpecifierNode *BuildStructSpecifierNode(IdNode *tag, StructDeclarationListNode *structDeclarationList);
    ScopeTree *GetScopeTree();
    PostfixDecrementNode *BuildPostfixDecrementNode(ExprNode *expr);
    PostfixIncrementNode *BuildPostfixIncrementNode(ExprNode *expr);
    InitDeclaratorNode *BuildInitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer);
    StructureOrUnionMemberAccessNode *BuildStructureOrUnionMemberAccessNode(ExprNode *structure, IdNode *field);
    StructureOrUnionMemberAccessByPointerNode *BuildStructureOrUnionMemberAccessByPointerNode(ExprNode *ptr, IdNode *field);
private:
    void CheckPostfixIncDecRules(ExprNode *expr);
    bool isArithmeticType(SymType *type);
    bool isPointerType(SymType *type);
    bool isVoidPointer(SymType *type);
    ScopeTree scopeTree;
};

#endif //TINY_C_COMPILER_SEMANTIC_ANALYZER_H


