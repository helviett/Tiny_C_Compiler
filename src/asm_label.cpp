#include <utility>

#include "../includes/asm_label.h"

void Asm::AsmSimpleLabel::Print(std::ostream &os)
{
    os << ".L" << std::to_string(number) << ":" << std::endl;
}

Asm::AsmSimpleLabel::AsmSimpleLabel(size_t number): number(number) {}

void Asm::AsmFunction::Print(std::ostream &os)
{
    os << name << ":" << std::endl;
}

Asm::AsmFunction::AsmFunction(std::string name): name(std::move(name)) {}
