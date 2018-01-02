//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_TRANSLATION_UNIT_H
#define TINY_C_COMPILER_TRANSLATION_UNIT_H

#include "node.h"
#include <list>

class ExternalDeclarationNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    virtual void Generate(Asm::Assembly *assembly) = 0;
};

class TranslationUnitNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(ExternalDeclarationNode *initDeclarator);
    uint64_t Size();
    void Generate(Asm::Assembly *assembly) override;
protected:
    std::list<ExternalDeclarationNode *> list;
};

#endif //TINY_C_COMPILER_TRANSLATION_UNIT_H
