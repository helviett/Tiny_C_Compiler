//
// Created by keltar on 10/22/17.
//

#ifndef TINY_C_COMPILER_COMPILATION_ERROR_H
#define TINY_C_COMPILER_COMPILATION_ERROR_H

#include "token.h"
#include <cstring>

class CompilationError: public std::exception
{
public:
    const char * what() const throw() override = 0;
protected:
    std::string msg;
};

#endif //TINY_C_COMPILER_COMPILATION_ERROR_H
