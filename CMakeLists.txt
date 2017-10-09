cmake_minimum_required(VERSION 3.8)
project(Tiny_C_Compiler)

add_definitions(-std=gnu++0x)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        includes/args.hxx
        main.cpp
        includes/tokenizer.h includes/token.h src/tokenizer.cpp tests/tokenizer_tests/tokenizer_test.cpp)

include_directories(includes src)
add_subdirectory(tests)

add_executable(tcc ${SOURCE_FILES})
