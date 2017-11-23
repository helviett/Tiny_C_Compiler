#include "../includes/scope_tree.h"

ScopeTree::ScopeTree()
{
    root = activeScope = new SymbolTable();
}

SymbolTable *ScopeTree::GetActiveScope() const
{
    return activeScope;
}

SymbolTable *ScopeTree::StartScope()
{
    auto inner = new SymbolTable();
    inner->SetParent(activeScope);
    activeScope->AddChild(inner);
    activeScope = inner;
}

Symbol *ScopeTree::Find(const std::string &name)
{
    Symbol *res = nullptr;
    auto currentScope = activeScope;
    do
    {
        if ((res = currentScope->Find(name))) return res;
        currentScope = currentScope->GetParent();
    } while (currentScope);
    return res;
}

void ScopeTree::EndScope()
{
    activeScope = activeScope->GetParent();
}

void ScopeTree::SetActiveScope(SymbolTable *table)
{
    activeScope = table;
}
