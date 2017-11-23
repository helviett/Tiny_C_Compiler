#include <utility>

#include "../includes/symbols/symbol.h"

std::string Symbol::GetName() const
{
    return name;
}

void Symbol::SetName(std::string name)
{
    this->name = std::move(name);
}

SymbolClass Symbol::GetSymbolClass() const
{
    return symbolClass;
}
