#include "../includes/symbol_table.h"

Symbol *SymbolTable::Find(std::string name) const
{
    auto it = table.find(name);
    return  it != table.end() ? (*it).second : nullptr;
}

void SymbolTable::Insert(std::string name, Symbol *symbol)
{
    table[name] = symbol;
}
