#include "../includes/asm_element.h"

std::ostream &::Asm::operator<<(std::ostream &os, Asm::AsmElement *element)
{
    element->Print(os);
    return os;
}