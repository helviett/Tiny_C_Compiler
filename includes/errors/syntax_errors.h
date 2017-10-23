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

    SyntaxError(Token *token, std::string msg): token(token), msg(std::move(msg)) {}

    const char * what() const throw() override
    {
        std::string s = "Syntax error has occured at (" + std::to_string(token->row) + ", " + std::to_string(token->col)
                        + "). "  + msg + " Text: " + token->text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }

private:
    Token *token;
    std::string msg;
};

#endif //TINY_C_COMPILER_SYNTAX_ERRORS_H
