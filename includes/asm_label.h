//
// Created by keltar on 1/3/18.
//

#ifndef TINY_C_COMPILER_ASM_LABEL_H
#define TINY_C_COMPILER_ASM_LABEL_H

#include "asm_element.h"

namespace Asm
{
    class AsmLabel: public AsmElement
    {
    public:
        void Print(std::ostream &os) override = 0;
        virtual std::string GetName() = 0;
    };

    class AsmSimpleLabel: public AsmLabel
    {
    public:
        explicit AsmSimpleLabel(size_t number);
        std::string GetName() override;
        void Print(std::ostream &os) override;
    private:
        size_t number;
    };

    class AsmFunction: public AsmLabel
    {
    public:
        AsmFunction(std::string name);
        std::string GetName() override;
        void Print(std::ostream &os) override;
    private:
        std::string name;
    };
}

#endif //TINY_C_COMPILER_ASM_LABEL_H
