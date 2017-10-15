//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_SYNTAX_TREE_H
#define TINY_C_COMPILER_SYNTAX_TREE_H

#include <iostream>
#include <ostream>
#include "nodes.h"

class SyntaxTree
{
public:

    Node *root;
    friend std::ostream &operator<<(std::ostream &os, SyntaxTree &st);
    void Print();
private:
    void print(std::ostream &os, uint64_t deph, const Node *n) const;
};

#endif //TINY_C_COMPILER_SYNTAX_TREE_H
