#include "../includes/symbol_table.h"
#include "../includes/scope_tree.h"

Symbol *SymbolTable::Find(std::string name) const
{
    auto it = table.find(name);
    return  it != table.end() ? (*it).second : nullptr;
}

void SymbolTable::Insert(std::string name, Symbol *symbol)
{
    table[name] = symbol;
}

SymbolTable *SymbolTable::GetParent() const
{
    return parent;
}

void SymbolTable::AddChild(SymbolTable *child)
{
    children.push_back(child);
}

void SymbolTable::SetParent(SymbolTable *parent)
{
    this->parent = parent;
}
