//
// Created by keltar on 1/3/18.
//

#ifndef TINY_C_COMPILER_ASM_DIRECTIVE_H
#define TINY_C_COMPILER_ASM_DIRECTIVE_H

#include <unordered_map>
#include "asm_element.h"

namespace Asm
{

    class AsmDirective: public AsmElement
    {
    public:
        void Print(std::ostream &os) override = 0;
    };

    class AsmStringDirective: public AsmDirective
    {
    public:
        AsmStringDirective(std::string str);
        void Print(std::ostream &os) override;
    private:
        std::string str;
    };
}

#endif //TINY_C_COMPILER_ASM_DIRECTIVE_H
