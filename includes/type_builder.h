//
// Created by keltar on 11/16/17.
//

#ifndef TINY_C_COMPILER_TYPE_BUILDER_H
#define TINY_C_COMPILER_TYPE_BUILDER_H

#include "symbols.h"

class StructDeclarationListNode;

class DeclarationSpecifiersNode;

class TypeBuilder
{
public:
    static SymType *Build(DeclarationSpecifiersNode *declarationSpecifiers);
    static SymRecord *Build(StructDeclarationListNode *structDeclarationList);
};
#endif //TINY_C_COMPILER_TYPE_BUILDER_H
