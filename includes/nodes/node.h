//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_NODE_H
#define TINY_C_COMPILER_NODE_H

#include <ostream>
#include <memory>
#include <assembly.h>

// Abstract Class
class Node
{
public:
    virtual void Print(std::ostream &os, std::string ident, bool isTail) = 0;
    virtual void Generate(Asm::Assembly *assembly) = 0;
};

#endif //TINY_C_COMPILER_NODE_H
