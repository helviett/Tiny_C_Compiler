//
// Created by keltar on 12/17/17.
//

#ifndef TINY_C_COMPILER_COMMANDS_H
#define TINY_C_COMPILER_COMMANDS_H


#include <string>
#include <arguments.h>
#include <unordered_map>
#include <ostream>

namespace Asm
{
    enum class CommandName
    {
        PUSH, POP, MOV, ADD, SUB, FLD, FILD, FST, FSTP, FADDP
    };

    static std::unordered_map<CommandName, std::string> CommandNameToString =
    {
            {CommandName::PUSH, "push"}, {CommandName::POP, "pop"},
            {CommandName::MOV, "mov"}, {CommandName::ADD, "add"},
            {CommandName::SUB, "sub"}, {CommandName::FLD, "fld"},
            {CommandName::FADDP, "faddp"}, {CommandName::FSTP, "fstp"},
    };

    enum class CommandSuffix
    {
        B, S, W, L, Q, T, NONE
    };

    static std::unordered_map<CommandSuffix, std::string> CommandSuffixToString =
    {
            {CommandSuffix::L, "l"}, {CommandSuffix::B, "b"},
            {CommandSuffix::S, "s"}, {CommandSuffix::W, "w"},
            {CommandSuffix::Q, "q"}, {CommandSuffix::T, "t"},
            {CommandSuffix::NONE, ""},
    };

    class Command
    {
    public:
        explicit Command(CommandName name, CommandSuffix suffix = CommandSuffix::NONE);
        virtual void Print(std::ostream &os);
    protected:
        CommandName name;
        CommandSuffix suffix{CommandSuffix::NONE};
    };

    class OneArgumentCommand: public Command
    {
    public:
        OneArgumentCommand(CommandName name, Argument *argument, CommandSuffix suffix = CommandSuffix::NONE);
        void Print(std::ostream &os) override;
    protected:
        Argument *argument;
    };

    class TwoArgumentsCommand: public Command
    {
    public:
        TwoArgumentsCommand(CommandName name, Argument *firstArgument, Argument *secondArgument,
                            CommandSuffix suffix = CommandSuffix::NONE);
        void Print(std::ostream &os) override;
    protected:
        Argument *left, *right;
    };

    std::ostream &operator<<(std::ostream &os, Command *command);
}

#endif //TINY_C_COMPILER_COMMANDS_H
