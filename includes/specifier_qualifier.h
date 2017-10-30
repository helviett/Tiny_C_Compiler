//
// Created by keltar on 10/25/17.
//

#ifndef TINY_C_COMPILER_SPECIFIER_QUALIFIER_LIST_H
#define TINY_C_COMPILER_SPECIFIER_QUALIFIER_LIST_H

#include "token.h"
#include <list>
class TypeSpecifiers;
class TypeQualifier;

class DeclarationSpecifier
{
public:
    DeclarationSpecifier() = default;
    explicit DeclarationSpecifier(Token *value): value(value) {}
    Token *Value() { return value; }
protected:
    Token *value;
};

class TypeSpecifierQualifier: public DeclarationSpecifier
{
public:
    TypeSpecifierQualifier() = default;
    TypeSpecifierQualifier(Token *value): DeclarationSpecifier(value) {}
};

class TypeSpecifier: public TypeSpecifierQualifier
{
public:
    TypeSpecifier(Token *specifier): TypeSpecifierQualifier(specifier) {}
};

class TypeQualifier: public TypeSpecifierQualifier
{
public:
    TypeQualifier(Token *qualifier): TypeSpecifierQualifier(qualifier) {}
};

class StorageClassSpecifier: public DeclarationSpecifier
{
public:
    StorageClassSpecifier(Token *specifier): DeclarationSpecifier(specifier) {}
};

class FunctionSpecifier: public DeclarationSpecifier
{
public:
    FunctionSpecifier(Token *specifier): DeclarationSpecifier(specifier) {}
};



#endif //TINY_C_COMPILER_SPECIFIER_QUALIFIER_LIST_H
