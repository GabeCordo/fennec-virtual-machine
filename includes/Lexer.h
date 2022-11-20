//
// Created by Gabe Cordovado on 2022-09-25.
//

#ifndef FENNEC_LEXER_H
#define FENNEC_LEXER_H

#include <string>

namespace fennec
{
    const int ASCII_NUMBER_OFFSET = 48;

    enum LexemeSummaryType
    {
        Summary_Register,
        Summary_Literal,
        Summary_Instruction,
        Summary_Type
    };

    enum LexemeType
    {
        Register_0, Register_1, Register_2, Register_3, Register_4, Register_5, Register_6, Register_7,
        Register_Base_Pointer, Register_Stack_Pointer, Register_Index_Pointer,
        Literal_Hex, Literal_Float, Literal_Decimal,
        Indirect_Indicator,
        Instruction_Add, Instruction_Subtract, Instruction_Interrupt, Instruction_Move,
        Type_Bracket_Start, Type_Bracket_End,
        Type_UInt64, Type_UInt32, Type_UInt16, Type_UInt8, Type_Int32, Type_Int16, Type_Int8,
        Type_Float64, Type_Float32,
    };

    const std::string lexeme_to_str[] = {
            "Register_0", "Register_1", "Register_2", "Register_3", "Register_4", "Register_5", "Register_6", "Register_7",
            "Register_Base_Pointer", "Register_Stack_Pointer", "Register_Index_Pointer",
            "Literal_Hex", "Literal_Float", "Literal_Decimal",
            "Indirect_Indicator",
            "Instruction_Add", "Instruction_Subtract", "Instruction_Interrupt", "Instruction_Move",
            "Type_Bracket_Start", "Type_Bracket_End",
            "Type_UInt64", "Type_UInt32","Type_UInt16", "Type_UInt8", "Type_UInt64", "Type_Int32","Type_Int16", "Type_Int8",
            "Type_Float64", "Type_Float32"
    };

    const uint64_t num_of_registers = 8;
    const LexemeType int_to_register[] = {Register_0,
                                          Register_1,
                                          Register_2,
                                          Register_3,
                                          Register_4,
                                          Register_5,
                                          Register_6,
                                          Register_7};

    struct Lexeme
    {
        fennec::LexemeSummaryType summary_type;
        fennec::LexemeType        type;
        std::string               value;
    };

    class Lexer
    {
    private:
        fennec::Lexeme to_lexeme(std::string input);
    public:
        std::vector<fennec::Lexeme>* to_lexeme_array(std::string input_string);
        void print(std::vector<fennec::Lexeme>* lexeme_array);
    };

}


#endif //FENNEC_LEXER_H
