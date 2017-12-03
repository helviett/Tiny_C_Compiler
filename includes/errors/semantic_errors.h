//
// Created by keltar on 12/3/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ERRORS_H
#define TINY_C_COMPILER_SEMANTIC_ERRORS_H

#include "compilation_error.h"

class SemanticError: public CompilationError
{
public:
    const char *what() const throw() override = 0;
};

class UndeclaredIdentifierError: public SemanticError
{
public:
    explicit UndeclaredIdentifierError(std::shared_ptr<Token> token)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              ") UndeclaredIdentifierError: " + token->stringValue + ".";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class TooLongError: public SemanticError
{
public:
    explicit TooLongError(std::shared_ptr<Token> token, int longtimes)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              "): " + std::to_string(longtimes) + "is too long for tcc.";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class UnsupportedTypeError: public SemanticError
{
public:
    explicit UnsupportedTypeError(std::shared_ptr<Token> token)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              "): Unsupported combination of declaration specifiers. ";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class DuplicateError: public SemanticError
{
public:
    explicit DuplicateError(std::shared_ptr<Token> token)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              "): duplicate " + token->text + ".";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class ManyDataTypesError: public SemanticError
{
public:
    explicit ManyDataTypesError(std::shared_ptr<Token> token)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              "): two or more data types in declaration specifiers. ";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class IncompatibleDeclarationSpecifiersError: public SemanticError
{
public:
    explicit IncompatibleDeclarationSpecifiersError(std::shared_ptr<Token> token, std::string spec)
    {
        msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
              "): both " + token->text + " and " + spec + " presented.";
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }
};

class RequiredLvalueError: public SemanticError
{

};

#endif //TINY_C_COMPILER_SEMANTIC_ERRORS_H
