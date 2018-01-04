#include "../includes/assembly.h"
#include "../includes/nodes/expressions.h"

std::ostream &Asm::operator<<(std::ostream &os, Asm::Assembly &assembly)
{
    os << ".extern printf" << std::endl;
    os << ".section .data" << std::endl;
    os << assembly.dataSection << std::endl;
    os << ".section .text" << std::endl << ".globl main" << std::endl;
    os << assembly.textSection << std::endl;
}

Asm::Section &Asm::Assembly::TextSection()
{
    return textSection;
}

Asm::Section &Asm::Assembly::DataSection()
{
    return dataSection;
}

Asm::Section &Asm::Assembly::BssSection()
{
    return bssSection;
}

Asm::AsmSimpleLabel *Asm::Assembly::NextLabel()
{
    return new AsmSimpleLabel(nextLabel++);
}

Asm::AsmFunction *Asm::Assembly::MakeFunctionLabel(std::string name)
{
    return new AsmFunction(std::move(name));
}
