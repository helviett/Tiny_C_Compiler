//
// Created by keltar on 10/11/17.
//

#ifndef TINY_C_COMPILER_TCC_EXCEPTIONS_H
#define TINY_C_COMPILER_TCC_EXCEPTIONS_H

#include <string>
#include <exception>
#include <utility>
#include "token.h"

class CompilationError: public std::exception
{
public:
    const char * what() const throw() override = 0;
};

class LexicalError: public CompilationError
{
public:
    LexicalError(int row, int col, std::string text): row(row), col(col), text(std::move(text)) {}

    const char * what() const throw() override
    {
        std::string s = "Lexical error has occured at (" + std::to_string(row) + ", " + std::to_string(col) +
                "). Text: " + text;
        return s.c_str();
    }

private:
    int row, col;
    std::string text;
};

class SyntaxError: public CompilationError
{
public:
    SyntaxError(Token *token): token(token) {}

    const char * what() const throw() override
    {
        std::string s = "Lexical error has occured at (" + std::to_string(token->row) + ", " + std::to_string(token->col)
                        + "). Text: " + token->text;
        return s.c_str();
    }

private:
    Token *token;
};
#endif //TINY_C_COMPILER_TCC_EXCEPTIONS_H
