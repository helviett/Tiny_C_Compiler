#include "../includes/asm_directive.h"

Asm::AsmDirective::AsmDirective(Asm::DirectiveName name): name(name) {}

void Asm::AsmDirective::Print(std::ostream &os)
{

}

void Asm::AsmStringDirective::Print(std::ostream &os)
{
    os << ".string " << str << std::endl;
}
