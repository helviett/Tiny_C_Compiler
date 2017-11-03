//
// Created by keltar on 10/22/17.
//

#ifndef TINY_C_COMPILER_SYNTAX_ERRORS_H
#define TINY_C_COMPILER_SYNTAX_ERRORS_H

#include "compilation_error.h"

class SyntaxError: public CompilationError
{
public:
    SyntaxError(Token *token): token(token) {}
    const char * what() const throw() override = 0;
protected:
    Token *token;
};

class UnexpectedTokenError: public SyntaxError
{
public:
    UnexpectedTokenError(Token *token, TokenType expectation): SyntaxError(token), expectation(expectation)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
                ") SyntaxError: expected " + TokenTypeToString[expectation] + ", got " + token->text + ".";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
private:
    TokenType expectation;
};

#endif //TINY_C_COMPILER_SYNTAX_ERRORS_H
