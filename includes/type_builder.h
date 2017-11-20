//
// Created by keltar on 11/16/17.
//

#ifndef TINY_C_COMPILER_TYPE_BUILDER_H
#define TINY_C_COMPILER_TYPE_BUILDER_H

#include "data_type.h"

class DeclarationSpecifiersNode;

class TypeBuilder
{
public:
    static Type *Build(DeclarationSpecifiersNode *declarationSpecifiers);
};
#endif //TINY_C_COMPILER_TYPE_BUILDER_H
