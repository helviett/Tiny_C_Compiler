#include "../includes/asm_section.h"

void Asm::Section::AddCommand(Command *command, CommandSuffix suffix)
{
    asmElements.push_back(command);
}

void Asm::Section::AddCommand(Asm::CommandName name, Asm::Register aregister, CommandSuffix suffix)
{
    asmElements.push_back(new OneArgumentCommand(name, Asm::Registers[aregister], suffix));
}

void Asm::Section::AddCommand(Asm::CommandName name, Asm::Register firstRegister, Asm::Register secondRegister, CommandSuffix suffix)
{
    asmElements.push_back(new TwoArgumentsCommand(name,
                                                  Asm::Registers[firstRegister],
                                                  Asm::Registers[secondRegister], suffix));
}

std::ostream &Asm::operator<<(std::ostream &os, Asm::Section &assembly)
{
    for (auto command: assembly.asmElements)
        os << command << std::endl;
    return os;
}

void Asm::Section::AddCommand(Asm::CommandName name, ConstNode *constant, CommandSuffix suffix)
{
    asmElements.push_back(new OneArgumentCommand(name, new ArgumentConstant(constant), suffix));
}

void Asm::Section::AddCommand(Asm::CommandName name, Asm::CommandSuffix suffix)
{
    asmElements.push_back(new Command(name, suffix));
}

void Asm::Section::AddCommand(Asm::CommandName name, Asm::ArgumentAddress *address, CommandSuffix suffix)
{
    asmElements.push_back(new OneArgumentCommand(name, reinterpret_cast<Asm::Argument *>(address), suffix));
}

void Asm::Section::AddCommand(Asm::CommandName name, Asm::Argument *argument, Asm::CommandSuffix suffix)
{
    asmElements.push_back(new OneArgumentCommand(name, argument, suffix));
}