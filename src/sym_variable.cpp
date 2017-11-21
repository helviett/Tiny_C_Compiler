#include "../includes/symbols/sym_variable.h"

SymVariable::SymVariable(std::string name, SymType *type): type(type)
{
    this->name = std::move(name);
}
