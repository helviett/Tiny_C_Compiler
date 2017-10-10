//
// Created by keltar on 10/11/17.
//

#ifndef TINY_C_COMPILER_TCC_EXCEPTIONS_H
#define TINY_C_COMPILER_TCC_EXCEPTIONS_H

#include <string>
#include <exception>
#include <utility>

class LexicalError : public std::exception
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
#endif //TINY_C_COMPILER_TCC_EXCEPTIONS_H
