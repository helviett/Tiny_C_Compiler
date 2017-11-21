//
// Created by keltar on 11/21/17.
//

#ifndef TINY_C_COMPILER_SYMBOL_H
#define TINY_C_COMPILER_SYMBOL_H

#include <string>
#include <ostream>

class Symbol
{
public:
    void SetName(std::string name);
    std::string GetName() const;
    virtual void Print(std::ostream &os, std::string indent, bool isTail) = 0;
protected:
    std::string name;
};

#endif //TINY_C_COMPILER_SYMBOL_H
