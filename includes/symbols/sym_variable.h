//
// Created by keltar on 11/21/17.
//

#ifndef TINY_C_COMPILER_SYM_VARIABLE_H
#define TINY_C_COMPILER_SYM_VARIABLE_H

#include "symbol.h"
#include <utility>

class SymType;
class IdNode;

class SymVariable: public Symbol
{
public:
    SymVariable(std::string name, SymType *type, IdNode *id);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetType() const;
    void SetType(SymType *type);
    IdNode *GetId() const;
    void SetId(IdNode *id);
private:
    SymType *type;
    IdNode *id;
};

#endif //TINY_C_COMPILER_SYM_VARIABLE_H
