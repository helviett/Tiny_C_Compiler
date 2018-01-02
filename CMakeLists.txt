cmake_minimum_required(VERSION 2.8)
project(Tiny_C_Compiler)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        includes/args.hxx
        main.cpp
        includes/tokenizer.h includes/token.h src/tokenizer.cpp src/token.cpp includes/dfa.h
        includes/errors/tcc_exceptions.h includes/nodes.h includes/syntax_tree.h includes/parser.h src/parser.cpp
        src/nodes.cpp src/syntax_tree.cpp includes/errors/compilation_error.h includes/errors/lexical_errors.h includes/errors/syntax_errors.h
        includes/nodes/expressions.h includes/nodes/node.h includes/nodes/statements.h includes/nodes/declaration_specifier_nodes.h includes/nodes/pointer.h includes/nodes/decls.h
        includes/nodes/enum.h includes/nodes/struct.h includes/nodes/initializer.h includes/nodes/type_name_cast.h
        includes/nodes/function_definition.h includes/nodes/translation_unit.h
        includes/symbols.h includes/symbol_table.h includes/symbols/sym_type.h includes/nodes/declaration_specifier_nodes.h
        includes/type_builder.h src/type_builder.cpp src/sym_type.cpp includes/symbols/sym_type.h includes/symbols/symbol.h
        src/symbol_table.cpp includes/scope_tree.h src/scope_tree.cpp includes/symbols/sym_variable.h src/sym_variable.cpp
        src/symbol.cpp includes/semantic_analyzer.h src/semantic_analyzer.cpp includes/value_category.h
        includes/errors/semantic_errors.h src/semantic_errors.cpp includes/evaluator.h src/evaluator.cpp includes/assembly.h src/assembly.cpp
        includes/commands.h includes/arguments.h src/commands.cpp src/arguments.cpp)

include_directories(includes src)

add_executable(tcc ${SOURCE_FILES})