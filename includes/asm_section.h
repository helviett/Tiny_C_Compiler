//
// Created by keltar on 1/3/18.
//

#ifndef TINY_C_COMPILER_ASM_SECTION_H
#define TINY_C_COMPILER_ASM_SECTION_H

#include <vector>
#include "commands.h"

namespace Asm
{
    class Section
    {
    public:
        void AddCommand(Command *command, CommandSuffix suffix = CommandSuffix::NONE);
        void AddCommand(CommandName name, CommandSuffix suffix = CommandSuffix::NONE);
        void AddCommand(CommandName name, Register aregister, CommandSuffix suffix = CommandSuffix::NONE);
        void AddCommand(CommandName name, Argument *argument, CommandSuffix suffix = CommandSuffix::NONE);
        void AddCommand(CommandName name, ConstNode *constant, CommandSuffix suffix = CommandSuffix::NONE);
        void AddCommand(CommandName name, Register firstRegister,
                        Register secondRegister, CommandSuffix suffix = CommandSuffix::NONE);
        void AddCommand(CommandName name, ArgumentAddress *address, CommandSuffix suffix = CommandSuffix::NONE);

        friend std::ostream &operator<<(std::ostream &os, Section &parser);
    private:
        std::vector<AsmElement *> asmElements;
    };

    std::ostream &operator<<(std::ostream &os, Section &parser);
}

#endif //TINY_C_COMPILER_ASM_SECTION_H
