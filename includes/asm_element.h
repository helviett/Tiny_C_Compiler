//
// Created by keltar on 1/3/18.
//

#ifndef TINY_C_COMPILER_ASM_ELEMENT_H
#define TINY_C_COMPILER_ASM_ELEMENT_H

#include <ostream>

namespace Asm
{
    class AsmElement
    {
    public:
        virtual void Print(std::ostream &os) = 0;
    };

    std::ostream &operator<<(std::ostream &os, AsmElement *element);
}

#endif //TINY_C_COMPILER_ASM_ELEMENT_H
