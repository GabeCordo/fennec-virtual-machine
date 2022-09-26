cmake_minimum_required(VERSION 3.22)
project(fennec)

set(CMAKE_CXX_STANDARD 17)

add_executable(fennec main.cpp interpreter.cpp interpreter.h instruction.cpp instruction.h conditional.cpp Parser.cpp Parser.h Lexer.cpp Lexer.h literal.cpp register.cpp)
