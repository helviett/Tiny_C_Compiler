#include <utility>

#include "../includes/asm_directive.h"


void Asm::AsmStringDirective::Print(std::ostream &os)
{
    os << ".string " << str << std::endl;
}

Asm::AsmStringDirective::AsmStringDirective(std::string str): str(std::move(str)) {}
