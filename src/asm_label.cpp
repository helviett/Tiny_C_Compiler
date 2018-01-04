#include <utility>

#include "../includes/asm_label.h"

void Asm::AsmSimpleLabel::Print(std::ostream &os)
{
    os << ".L" << std::to_string(number) << ":";
}

Asm::AsmSimpleLabel::AsmSimpleLabel(size_t number): number(number) {}

std::string Asm::AsmSimpleLabel::GetName()
{
    return ".L" + std::to_string(number);
}

void Asm::AsmFunction::Print(std::ostream &os)
{
    os << name << ":";
}

Asm::AsmFunction::AsmFunction(std::string name): name(std::move(name)) {}

std::string Asm::AsmFunction::GetName()
{
    return name;
}
