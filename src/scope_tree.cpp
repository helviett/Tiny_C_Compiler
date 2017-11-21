#include "../includes/scope_tree.h"

ScopeTree::ScopeTree()
{
    root = activeScope = new SymbolTable();
}

SymbolTable *ScopeTree::ActiveScope() const
{
    return activeScope;
}
