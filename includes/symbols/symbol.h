//
// Created by keltar on 11/21/17.
//

#ifndef TINY_C_COMPILER_SYMBOL_H
#define TINY_C_COMPILER_SYMBOL_H

#include <string>
#include <ostream>

enum class SymbolClass
{
    TYPE, VARIABLE, UNDEFINED
};

class Symbol
{
public:
    void SetName(std::string name);
    std::string GetName() const;
//    void SetSymbolClass(SymbolClass class);
    SymbolClass GetSymbolClass() const;
    virtual void Print(std::ostream &os, std::string indent, bool isTail) = 0;
protected:
    std::string name;
    SymbolClass symbolClass{SymbolClass::UNDEFINED};
};

#endif //TINY_C_COMPILER_SYMBOL_H
