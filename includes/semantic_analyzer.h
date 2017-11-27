//
// Created by keltar on 11/23/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ANALYZER_H
#define TINY_C_COMPILER_SEMANTIC_ANALYZER_H

#include "scope_tree.h"
#include "nodes/struct.h"
#include "type_builder.h"

class SemanticAnalyzer
{
public:
    IdNode *BuildIdNode(std::shared_ptr<Token> token);
    StructSpecifierNode *BuildStructSpecifierNode(IdNode *tag, StructDeclarationListNode *structDeclarationList);
    ScopeTree *GetScopeTree();
    void Declare(InitDeclaratorListNode *initDeclaratorList);
private:
    ScopeTree scopeTree;
};

#endif //TINY_C_COMPILER_SEMANTIC_ANALYZER_H


