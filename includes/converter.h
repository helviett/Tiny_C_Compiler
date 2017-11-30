//
// Created by keltar on 11/30/17.
//

#ifndef TINY_C_COMPILER_CONVERTER_H
#define TINY_C_COMPILER_CONVERTER_H

#include "symbols.h"
#include <nodes.h>

class Converter
{
public:
    static void ImplicityConvert(ExprNode **left, ExprNode **right);
    static void Convert(ExprNode **expr, SymType *type);
};

#endif //TINY_C_COMPILER_CONVERTER_H
