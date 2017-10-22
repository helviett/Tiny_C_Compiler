//
// Created by keltar on 10/22/17.
//

#ifndef TINY_C_COMPILER_LEXICAL_ERROR_H
#define TINY_C_COMPILER_LEXICAL_ERROR_H

#include <cstring>

class LexicalError: public CompilationError
{
public:
    LexicalError () = default;

    LexicalError(int row, int col, std::string text): row(row), col(col), text(std::move(text)) {}

    const char * what() const throw() override
    {
        std::string s = "Lexical error has occured at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text: " + text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }

protected:
    int row, col;
    std::string text;
};

class WrongStringLiteral: public LexicalError
{
public:
    WrongStringLiteral(int row, int col, std::string text): LexicalError(row, col, std::move(text)) {}

    const char *what() const throw() override
    {
        std::string s = "WrongStringLiteral at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text:" + text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }

};

class WrongNumberLiteral: public LexicalError
{
public:
    WrongNumberLiteral(int row, int col, std::string text): LexicalError(row, col, std::move(text)) {}

    const char *what() const throw() override
    {
        std::string s = "WrongNumberLiteral at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text:" + text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }
};

class WrongCharacterLiteral: public LexicalError
{
public:
    WrongCharacterLiteral(int row, int col, std::string text): LexicalError(row, col, std::move(text)) {}

    const char *what() const throw() override
    {
        std::string s = "WrongCharacterLiteral at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text:" + text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }
};

class UnknownSymbol: public LexicalError
{
public:
    UnknownSymbol(int row, int col, std::string text): LexicalError(row, col, std::move(text)) {}

    const char *what() const throw() override
    {
        std::string s = "UnknownSymbol at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text:" + text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }
};

class NumberOutOfRange: public LexicalError
{
public:
    NumberOutOfRange(int row, int col, std::string text): LexicalError(row, col, std::move(text)) {}

    const char *what() const throw() override
    {
        std::string s = "NumberOutOfRange at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text:" + text;
        char *res = new char[s.length() + 1];
        std::strcpy(res, s.c_str());
        return res;
    }
};

#endif //TINY_C_COMPILER_LEXICAL_ERROR_H
