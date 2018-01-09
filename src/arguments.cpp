#include "../includes/nodes/expressions.h"
#include "../includes/arguments.h"

Asm::ArgumentRegister::ArgumentRegister(Asm::Register aregister)
{
    this->aregister = aregister;
}

void Asm::ArgumentRegister::Print(std::ostream &os)
{
    os << "%" << RegisterToString[aregister];
}

std::ostream &Asm::operator<<(std::ostream &os, Asm::Argument *argument)
{
    argument->Print(os);
    return os;
}

Asm::ArgumentConstant::ArgumentConstant(ConstNode *constNode): constant(constNode) {}

void Asm::ArgumentConstant::Print(std::ostream &os)
{
    void *typedConstant = nullptr;
    if ((typedConstant = dynamic_cast<IntConstNode *>(this->constant)))
        os << "$" + std::to_string(((IntConstNode *)typedConstant)->GetValue()) + " ";
    else if ((typedConstant = dynamic_cast<FloatConstNode *>(this->constant)))
    {
        float f = ((FloatConstNode *)typedConstant)->GetValue();
        os << "$" + std::to_string(*((unsigned int *)&f)) + " ";
    }
}

void Asm::ArgumentAddress::Print(std::ostream &os)
{
    if (address) os << address;
    os << "(";
    base->Print(os);
    os << ") ";
}

Asm::ArgumentAddress::ArgumentAddress(int32_t address, Asm::Argument *base): address(address), base(base) {}

Asm::ArgumentAddress::ArgumentAddress(Asm::Argument *base): base(base) {}

Asm::ArgumentAddress::ArgumentAddress(int32_t address, Asm::Register base): address(address), base(Asm::Registers[base]) {}

Asm::ArgumentAddress::ArgumentAddress(Asm::Register base): base(Asm::Registers[base]) {}

Asm::ArgumentLabel::ArgumentLabel(Asm::AsmLabel *label, bool asAddress): label(label), asAddress(asAddress) {}

void Asm::ArgumentLabel::Print(std::ostream &os)
{
    auto prefix = asAddress ? "$" : "";
    os << prefix << label->GetName();
}
