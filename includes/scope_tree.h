//
// Created by keltar on 11/21/17.
//

#ifndef TINY_C_COMPILER_SCOPE_TREE_H
#define TINY_C_COMPILER_SCOPE_TREE_H

#include "symbol_table.h"

class ScopeTree
{
public:
    ScopeTree();
    SymbolTable *ActiveScope() const;
private:
    SymbolTable *root, *activeScope;
};

#endif //TINY_C_COMPILER_SCOPE_TREE_H
