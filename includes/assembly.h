//
// Created by keltar on 12/17/17.
//

#ifndef TINY_C_COMPILER_ASSEMBLY_H
#define TINY_C_COMPILER_ASSEMBLY_H

#include <vector>
#include <ostream>
#include "commands.h"

namespace Asm
{
    class Assembly
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

        friend std::ostream &operator<<(std::ostream &os, Assembly &parser);
    private:
        std::vector<Command *> commands;
    };
    std::ostream &operator<<(std::ostream &os, Assembly &parser);
}

#endif //TINY_C_COMPILER_ASSEMBLY_H
