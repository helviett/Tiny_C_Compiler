//
// Created by keltar on 12/17/17.
//

#ifndef TINY_C_COMPILER_COMMANDS_H
#define TINY_C_COMPILER_COMMANDS_H


#include <string>
#include <arguments.h>
#include <unordered_map>
#include <ostream>
#include "asm_element.h"

namespace Asm
{
    enum class CommandName
    {
        PUSH, POP, MOV, ADD, SUB, FLD, FILD, FST, FSTP, FADDP, CALL, LEAVE, RET, FSUBP,
        MUL, DIV, FMULP, FDIVP
    };

    static std::unordered_map<CommandName, std::string> CommandNameToString =
    {
            {CommandName::PUSH, "push"}, {CommandName::POP, "pop"},
            {CommandName::MOV, "mov"}, {CommandName::ADD, "add"},
            {CommandName::SUB, "sub"}, {CommandName::FLD, "fld"},
            {CommandName::FADDP, "faddp"}, {CommandName::FSTP, "fstp"},
            {CommandName::FILD, "fild"}, {CommandName::CALL, "call"},
            {CommandName::LEAVE, "leave"}, {CommandName::RET, "ret"},
            {CommandName::FSUBP, "fsubp"}, {CommandName::MUL, "mul"},
            {CommandName::DIV, "div"}, {CommandName::FMULP, "fmulp"},
            {CommandName::FDIVP, "fdivp"},
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

    class Command: public AsmElement
    {
    public:
        Command() = default;
        explicit Command(CommandName name, CommandSuffix suffix = CommandSuffix::NONE);
        void Print(std::ostream &os) override;
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

}

#endif //TINY_C_COMPILER_COMMANDS_H
