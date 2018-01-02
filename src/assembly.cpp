#include "../includes/assembly.h"
#include "../includes/nodes/expressions.h"

void Asm::Assembly::AddCommand(Command *command, CommandSuffix suffix)
{
    commands.push_back(command);
}

void Asm::Assembly::AddCommand(Asm::CommandName name, Asm::Register aregister, CommandSuffix suffix)
{
    commands.push_back(new OneArgumentCommand(name, Asm::Registers[aregister], suffix));
}

void Asm::Assembly::AddCommand(Asm::CommandName name, Asm::Register firstRegister, Asm::Register secondRegister, CommandSuffix suffix)
{
    commands.push_back(new TwoArgumentsCommand(name,
                                               Asm::Registers[firstRegister],
                                               Asm::Registers[secondRegister], suffix));
}

std::ostream &Asm::operator<<(std::ostream &os, Asm::Assembly &assembly)
{
    for (auto command: assembly.commands)
        os << command << std::endl;
    return os;
}

void Asm::Assembly::AddCommand(Asm::CommandName name, ConstNode *constant, CommandSuffix suffix)
{
    commands.push_back(new OneArgumentCommand(name, new ArgumentConstant(constant), suffix));
}

void Asm::Assembly::AddCommand(Asm::CommandName name, Asm::CommandSuffix suffix)
{
    commands.push_back(new Command(name, suffix));
}

void Asm::Assembly::AddCommand(Asm::CommandName name, Asm::ArgumentAddress *address, CommandSuffix suffix)
{
    commands.push_back(new OneArgumentCommand(name, reinterpret_cast<Asm::Argument *>(address), suffix));
}

void Asm::Assembly::AddCommand(Asm::CommandName name, Asm::Argument *argument, Asm::CommandSuffix suffix)
{
    commands.push_back(new OneArgumentCommand(name, argument, suffix));
}

//template<typename... Args>
//void Asm::Assembly::Add(Asm::CommandName name, Args... args)
//{
//    return new Command(name, std::forward(args)...);
//}
