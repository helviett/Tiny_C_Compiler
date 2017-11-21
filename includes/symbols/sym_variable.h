//
// Created by keltar on 11/21/17.
//

#ifndef TINY_C_COMPILER_SYM_VARIABLE_H
#define TINY_C_COMPILER_SYM_VARIABLE_H

#include "sym_type.h"
#include <utility>

class SymVariable: public Symbol
{
public:
    SymVariable(std::string name, SymType *type);
private:
    SymType *type;
};

#endif //TINY_C_COMPILER_SYM_VARIABLE_H
