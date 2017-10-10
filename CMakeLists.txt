cmake_minimum_required(VERSION 2.8)
project(Tiny_C_Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        includes/args.hxx
        main.cpp
        includes/tokenizer.h includes/token.h src/tokenizer.cpp src/token.cpp includes/dfa.h includes/tcc_exceptions.h)

include_directories(includes src)

add_executable(tcc ${SOURCE_FILES})