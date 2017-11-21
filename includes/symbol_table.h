//
// Created by keltar on 11/12/17.
//

#ifndef TINY_C_COMPILER_SYMBOL_TABLE_H
#define TINY_C_COMPILER_SYMBOL_TABLE_H

#include <vector>
#include <set>
#include "symbols.h"

class SymbolTable
{
public:
    Symbol *Find(std::string name) const;
    void Insert(std::string name, Symbol *symbol);
    SymbolTable *GetParent() const;
    void SetParent(SymbolTable *parent);
    void AddChild(SymbolTable *child);
private:
    std::unordered_map<std::string, Symbol *> table;
    SymbolTable *parent = nullptr;
    std::list<SymbolTable *> children;
};

#endif //TINY_C_COMPILER_SYMBOL_TABLE_H
