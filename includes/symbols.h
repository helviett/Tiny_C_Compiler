//
// Created by keltar on 11/11/17.
//

#ifndef TINY_C_COMPILER_SYMBOLS_H
#define TINY_C_COMPILER_SYMBOLS_H

#include <string>
#include "symbol_table.h"

class Symbol
{
protected:
    std::string name;
};

class SymType: Symbol
{

};

class SymVariable: Symbol
{

};

class SymFunc: Symbol
{
private:
    SymbolTabel *params, body;
};

class SymInteger: SymType
{

};

class SymFloat: SymType
{

};

class SymStruct: SymType
{
private:
    SymbolTabel *fields;
};

class SymPointer: SymType
{

};

class SymArray: SymType
{
private:
    ConstantExprNode *size;
};

class SymAlias: SymType
{

};

#endif //TINY_C_COMPILER_SYMBOLS_H