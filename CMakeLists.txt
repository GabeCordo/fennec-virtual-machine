cmake_minimum_required(VERSION 3.22)
project(fennec)

set(CMAKE_CXX_STANDARD 17)

add_executable(fennec main.cpp src/interpreter.cpp includes/interpreter.h src/instruction.cpp includes/instruction.h src/conditional.cpp src/Parser.cpp includes/Parser.h src/Lexer.cpp includes/Lexer.h src/literal.cpp src/register.cpp src/type_table.cpp src/fasm_node.cpp)
