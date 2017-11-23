//
// Created by keltar on 11/23/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ANALYZER_H
#define TINY_C_COMPILER_SEMANTIC_ANALYZER_H

#include <nodes/expressions.h>
#include <symbols.h>

class SemanticAnalyzer
{
public:
    IdNode *BuildIdNode(std::shared_ptr<Token> token, Symbol *symbol);
private:

};

#endif //TINY_C_COMPILER_SEMANTIC_ANALYZER_H
