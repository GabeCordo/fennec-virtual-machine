#include <iostream>
#include <string>

#include "includes/instruction.h"
#include "includes/Lexer.h"
#include "includes/Parser.h"

int main() {
    uint64_t raw_add = 0x4000000000000000;
    fennec::Instruction add_instruction(raw_add);
    if (add_instruction.get_opcode() == fennec::OpCode::OpCode_Add)
    {
        std::cout << "Correct Instruction" << std::endl;
    }

    std::string add_str_instruction = "add r0 r1 r2";

    fennec::Lexer lexer;
    auto lexeme_array = lexer.to_lexeme_array(add_str_instruction);
    lexer.print(lexeme_array);

    fennec::FASMParser fasm_parser;
    fennec::FASMNode *add_ast = fasm_parser.to_ast(lexeme_array);

    fennec::Instruction instruction = fasm_parser.to_instruction(add_ast);
    if (instruction.get_opcode() == fennec::OpCode::OpCode_Add)
    {
        std::cout << "Parsed Correct Instruction" << std::endl;
    }
    return 0;
}
