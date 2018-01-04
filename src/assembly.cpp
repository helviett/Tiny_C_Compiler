#include "../includes/assembly.h"
#include "../includes/nodes/expressions.h"

//template<typename... Args>
//void Asm::Assembly::Add(Asm::CommandName name, Args... args)
//{
//    return new Command(name, std::forward(args)...);
//}
std::ostream &Asm::operator<<(std::ostream &os, Asm::Assembly &assembly)
{
    os << ".section .text" << std::endl << ".globl main" << std::endl;
    os << assembly.textSection << std::endl;
}

Asm::Section &Asm::Assembly::TextSection()
{
    return textSection;
}
