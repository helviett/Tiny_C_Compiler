//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_TRANSLATION_UNIT_H
#define TINY_C_COMPILER_TRANSLATION_UNIT_H

#include "node.h"
#include <list>

//external-declaration ::= function-definition | declaration

class ExternalDeclarationNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

//translation-unit ::= external-declaration | translation-unit external-declaration

class TranslationUnitNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(ExternalDeclarationNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<ExternalDeclarationNode *> list;
};

#endif //TINY_C_COMPILER_TRANSLATION_UNIT_H