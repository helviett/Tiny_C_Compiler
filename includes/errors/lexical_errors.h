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

    LexicalError(int row, int col, std::string text): row(row), col(col)
    {
        msg = "Lexical error has occured at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text: " + text;
    }

    const char * what() const throw() override
    {
        return msg.c_str();
    }

protected:
    int row, col;
};

class WrongStringLiteral: public LexicalError
{
public:
    WrongStringLiteral(int row, int col, std::string text): LexicalError(row, col, std::move(text))
    {
        msg = "WrongStringLiteral at (" + std::to_string(row) + ", " + std::to_string(col) +
              "). Text:" + text;
    }

    const char *what() const throw() override
    {
        return msg.c_str();
    }

};

class WrongNumberLiteral: public LexicalError
{
public:
    WrongNumberLiteral(int row, int col, std::string text): LexicalError(row, col, std::move(text))
    {
        msg = "WrongNumberLiteral at (" + std::to_string(row) + ", " + std::to_string(col) +
                        "). Text:" + text;
    }

    const char *what() const throw() override
    {
        return msg.c_str();
    }
};

class WrongCharacterLiteral: public LexicalError
{
public:
    WrongCharacterLiteral(int row, int col, std::string text): LexicalError(row, col, std::move(text))
    {
        msg = "WrongCharacterLiteral at (" + std::to_string(row) + ", " + std::to_string(col) +
        "). Text:" + text;
    }

    const char *what() const throw() override
    {
        return msg.c_str();
    }
};

class UnknownSymbol: public LexicalError
{
public:
    UnknownSymbol(int row, int col, std::string text): LexicalError(row, col, std::move(text))
    {
        msg = "UnknownSymbol at (" + std::to_string(row) + ", " + std::to_string(col) +
        "). Text:" + text;
    }

    const char *what() const throw() override
    {
        return msg.c_str();
    }
};

class NumberOutOfRange: public LexicalError
{
public:
    NumberOutOfRange(int row, int col, std::string text): LexicalError(row, col, std::move(text))
    {
        msg = "NumberOutOfRange at (" + std::to_string(row) + ", " + std::to_string(col) +
        "). Text:" + text;
    }

    const char *what() const throw() override
    {
        return msg.c_str();
    }
};

#endif //TINY_C_COMPILER_LEXICAL_ERROR_H
