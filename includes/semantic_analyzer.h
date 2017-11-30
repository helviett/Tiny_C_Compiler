//
// Created by keltar on 11/23/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ANALYZER_H
#define TINY_C_COMPILER_SEMANTIC_ANALYZER_H

#include "scope_tree.h"
#include "nodes.h"
#include "type_builder.h"
#include <converter.h>
#include <iostream>

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
    StructureOrUnionMemberAccessByPointerNode *BuildStructureOrUnionMemberAccessByPointerNode(ExprNode *ptr,
                                                                                              IdNode *field);
    ArrayAccessNode *BuildArrayAccessNode(ExprNode *array, ExprNode *index);
    FunctionCallNode *BuildFunctionCallNode(ExprNode *func, ArgumentExprListNode *args);
    PrefixIncrementNode *BuildPrefixIncrementNode(ExprNode *expr);
    PrefixDecrementNode *BuildPrefixDecrementNode(ExprNode *expr);
    UnaryOpNode *BuildUnaryOpNode(std::shared_ptr<Token> unaryOp, ExprNode *expr);
    BinOpNode *BuildBinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> binOp);
private:
    void CheckIncDecRules(ExprNode *expr);
    bool isArithmeticType(SymType *type);
    bool isPointerType(SymType *type);
    bool isVoidPointer(SymType *type);
    bool isIntegerType(SymType *type);
    void performLvalueConversion(ExprNode *expr);
    bool isUnsignedIntegerType(SymType *type);
    bool isScalarType(SymType *type);
    ScopeTree scopeTree;
};

#endif //TINY_C_COMPILER_SEMANTIC_ANALYZER_H


