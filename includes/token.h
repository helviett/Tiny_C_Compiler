//
// Created by keltar on 10/8/17.
//

#ifndef TINY_C_COMPILER_TOKEN_H
#define TINY_C_COMPILER_TOKEN_H

#include <string>

enum TokenType
{
    ID, NUM_INT, NUM_FLOAT
};

struct Token
{
    TokenType type;
    std::string text;

    Token(TokenType type)
    {
        this->type = type;
    }
};

#endif //TINY_C_COMPILER_TOKEN_H
