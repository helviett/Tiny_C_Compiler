//
// Created by keltar on 11/23/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ANALYZER_H
#define TINY_C_COMPILER_SEMANTIC_ANALYZER_H

#include "scope_tree.h"
#include "nodes.h"
#include "type_builder.h"
#include <iostream>
#include <errors/semantic_errors.h>
#include <stack>
#include <algorithm>
#include "evaluator.h"

class SemanticAnalyzer
{
public:
    IdNode *BuildIdNode(std::shared_ptr<Token> token);
    StructSpecifierNode *BuildStructSpecifierNode(IdNode *tag,
                                                  StructDeclarationListNode *structDeclarationList,
                                                  std::shared_ptr<Token> structToken);
    ScopeTree *GetScopeTree();
    PostfixDecrementNode *BuildPostfixDecrementNode(ExprNode *expr, const std::shared_ptr<Token> &op);
    PostfixIncrementNode *BuildPostfixIncrementNode(ExprNode *expr, const std::shared_ptr<Token> &op);
    InitDeclaratorNode *BuildInitDeclaratorNode(DeclaratorNode *declarator,
                                                InitializerNode *initializer,
                                                bool isTypedef);
    StructureOrUnionMemberAccessNode *BuildStructureOrUnionMemberAccessNode(ExprNode *structure,
                                                                            IdNode *field,
                                                                            std::shared_ptr<Token> dot);
    StructureOrUnionMemberAccessByPointerNode *BuildStructureOrUnionMemberAccessByPointerNode(ExprNode *ptr,
                                                                                              IdNode *field,
                                                                                              std::shared_ptr<Token> arrow);
    ArrayAccessNode *BuildArrayAccessNode(ExprNode *array, ExprNode *index);
    FunctionCallNode *BuildFunctionCallNode(ExprNode *func, ArgumentExprListNode *args);
    PrefixIncrementNode *BuildPrefixIncrementNode(ExprNode *expr, const std::shared_ptr<Token> &op);
    PrefixDecrementNode *BuildPrefixDecrementNode(ExprNode *expr, const std::shared_ptr<Token> &op);
    UnaryOpNode *BuildUnaryOpNode(std::shared_ptr<Token> unaryOp, ExprNode *expr);
    BinOpNode *BuildBinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> binOp);
    TernaryOperatorNode *BuildTernaryOperatorNode(ExprNode *condition, ExprNode *iftrue, ExprNode *iffalse,
                                                  const std::shared_ptr<Token> &question,
                                                  const std::shared_ptr<Token> &colon);
    AssignmentNode *BuildAssignmentNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> assignmentOp);
    FunctionDefinitionNode *BuildFunctionDefinitionNode(DeclaratorNode *declarator, CompoundStatement *body);
    TypeCastNode *BuildTypeCastNode(SymType *typeName, ExprNode *castExpr);
    EnumeratorNode *BuildEnumeratorNode(IdNode *enumerator, ExprNode *expr);
    EnumSpecifierNode *BuildEnumSpecifierNode(IdNode *tag, EnumeratorList *list);
    ReturnStatementNode *BuildReturnStatementNode(std::shared_ptr<Token> statement, ExprNode *expr);
    BreakStatementNode *BuildBreakStatementNode(std::shared_ptr<Token> statement);
    ContinueStatementNode *BuildContinueStatementNode(std::shared_ptr<Token> statement);
    TypedefIdentifierNode *BuildTypedefIdentifierNode(const std::shared_ptr<Token> &id);
    ExprNode *EvaluateArraySizer(ExprNode *expr);
    void ProcessFunction(SymType *funcType);
    void FinishLastFunctionProcessing();
    void ProcessLoop(IterationStatementNode *loop);
    void FinishLastLoopProcessing();
private:
    void CheckIncDecRules(ExprNode *expr, std::shared_ptr<Token> op);
    bool isArithmeticType(SymType *type);
    bool isPointerType(SymType *type);
    bool isVoidPointer(SymType *type);
    bool isIntegerType(SymType *type);
    void performLvalueConversion(ExprNode *expr);
    bool isUnsignedIntegerType(SymType *type);
    bool isScalarType(SymType *type);
    bool isModifiableLvalue(ExprNode *expr);
    bool isConstQualified(ExprNode *expr);
    bool isStructType(SymType *type);
    bool isVoidType(SymType *type);
    std::shared_ptr<Token> extractArithmeticOperationFromAssignmentBy(const std::shared_ptr<Token> &assignemtBy);
    void ImplicitlyConvert(ExprNode **left, ExprNode **right);
    void Convert(ExprNode **expr, SymType *type);
    bool equalQualifiers(SymType *one, SymType *other);
    void analyseInitializerList(SymType *current, InitializerNode *initializer, DesignatorNode *designator = nullptr);
    SymType *unqualify(SymType *type);
    ScopeTree scopeTree;
    std::stack<SymType *> processingFunctions;
    std::stack<IterationStatementNode *> processingLoops;
    Evaluator evaluator;
};

#endif //TINY_C_COMPILER_SEMANTIC_ANALYZER_H


