#include "../includes/scope_tree.h"

ScopeTree::ScopeTree()
{
    root = activeScope = new SymbolTable();
}

SymbolTable *ScopeTree::ActiveScope() const
{
    return activeScope;
}

SymbolTable *ScopeTree::StartScope()
{
    auto inner = new SymbolTable();
    activeScope->AddChild(inner);
    activeScope = inner;
}

Symbol *ScopeTree::Find(const std::string &name)
{
    Symbol *res;
    auto currentScope = activeScope;
    do
    {
        if ((res = currentScope->Find(name))) return res;
    } while ((currentScope = activeScope->GetParent()));
    throw "";
}

void ScopeTree::EndScope()
{
    activeScope = activeScope->GetParent();
}
