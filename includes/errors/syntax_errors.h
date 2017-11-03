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

class UnexpectedKeywordError: public SyntaxError
{
public:
    UnexpectedKeywordError(Token *token, Keyword expectation): SyntaxError(token)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              ") SyntaxError: expected " + std::to_string((int)expectation) + ", got " + token->text + ".";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class NoDeclarationSpecifiers: public SyntaxError
{
public:
    NoDeclarationSpecifiers(Token *token): SyntaxError(token)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              ") SyntaxError: missing declaration specifiers";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class EmptyEnumeratorListError: public SyntaxError
{
public:
    EmptyEnumeratorListError(Token *token): SyntaxError(token)
            {
                    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
                          ") SyntaxError: empty enumerator list";
            }

            const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class InvalidExpression: public SyntaxError
{
public:
    InvalidExpression(Token *token): SyntaxError(token)
            {
                    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
                          ") SyntaxError: invalid expression";
            }

            const char * what() const throw() override
    {
        return msg.c_str();
    }
};

#endif //TINY_C_COMPILER_SYNTAX_ERRORS_H
