cmake_minimum_required(VERSION 3.8)
project(Tiny_C_Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        includes/args.hxx
        main.cpp
        README.md)

include_directories(includes)
include_directories(src)
include_directories(tests)

add_executable(tcc ${SOURCE_FILES})