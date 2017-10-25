//
// Created by keltar on 10/25/17.
//

#ifndef TINY_C_COMPILER_SPECIFIER_QUALIFIER_LIST_H
#define TINY_C_COMPILER_SPECIFIER_QUALIFIER_LIST_H

#include "token.h"
#include <list>

class TypeSpecifiers;
class TypeQualifier;

class TypeSpecifierQualifier
{
public:
    TypeSpecifierQualifier() {}
    Token *SpecOrQual() { return specOrQual; }
protected:
    Token *specOrQual;
};

class TypeSpecifier: public TypeSpecifierQualifier
{
public:
    TypeSpecifier(Token *specifier)
    {
        this->specOrQual = specifier;
    }
};

class TypeQualifier: public TypeSpecifierQualifier
{
public:
    TypeQualifier(Token *qualifier)
    {
        this->specOrQual = qualifier;
    }
};

using SpecifierQualifierList = std::list<TypeSpecifierQualifier *> ;




#endif //TINY_C_COMPILER_SPECIFIER_QUALIFIER_LIST_H
