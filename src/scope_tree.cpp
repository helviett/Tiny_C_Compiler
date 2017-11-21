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
    Symbol *res;
    auto currentScope = activeScope;
    do
    {
        if ((res = currentScope->Find(name))) return res;
    } while ((currentScope = activeScope->GetParent()));
    return nullptr;
}

void ScopeTree::EndScope()
{
    activeScope = activeScope->GetParent();
}

void ScopeTree::SetActiveScope(SymbolTable *table)
{
    activeScope = table;
}
