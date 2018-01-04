//
// Created by keltar on 12/17/17.
//

#ifndef TINY_C_COMPILER_ASSEMBLY_H
#define TINY_C_COMPILER_ASSEMBLY_H

#include <vector>
#include <ostream>
#include "commands.h"
#include "asm_section.h"

namespace Asm
{
    class Assembly
    {
    public:
        Section &TextSection();
        friend std::ostream &operator<<(std::ostream &os, Assembly &parser);
    private:
        Section textSection;
        Section dataSection;
        Section bssSection;
    };

}

#endif //TINY_C_COMPILER_ASSEMBLY_H
