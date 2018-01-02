#include "../includes/commands.h"

Asm::OneArgumentCommand::OneArgumentCommand(Asm::CommandName name,
                                            Asm::Argument *argument,
                                            Asm::CommandSuffix suffix): Command(name, suffix), argument(argument) {}

void Asm::OneArgumentCommand::Print(std::ostream &os)
{
    Command::Print(os);
    os << argument;
}

Asm::TwoArgumentsCommand::TwoArgumentsCommand(Asm::CommandName name,
                                              Asm::Argument *firstArgument,
                                              Asm::Argument *secondArgument,
                                              Asm::CommandSuffix suffix):
        Command(name, suffix), left(firstArgument), right(secondArgument) {}

void Asm::TwoArgumentsCommand::Print(std::ostream &os)
{
    Command::Print(os);
    os << left << ", " << right;
}

std::ostream &::Asm::operator<<(std::ostream &os, Asm::Command *command)
{
    command->Print(os);
    return os;
}

void Asm::Command::Print(std::ostream &os)
{
    os << Asm::CommandNameToString[name] << CommandSuffixToString[suffix] << "  ";
}

Asm::Command::Command(Asm::CommandName name, Asm::CommandSuffix suffix): name(name), suffix(suffix) {}
