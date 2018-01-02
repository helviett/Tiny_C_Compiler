//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_POINTER_H
#define TINY_C_COMPILER_POINTER_H

#include "node.h"
#include "declaration_specifier_nodes.h"

class PointerNode: public Node
{
public:
    PointerNode(DeclarationSpecifiersNode *typeQualifierList, PointerNode *pointer);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    DeclarationSpecifiersNode *typeQualifierList{};
    PointerNode *pointer;
};

#endif //TINY_C_COMPILER_POINTER_H
