//
// Created by Gabe Cordovado on 2022-09-26.
//

#include "Parser.h"

fennec::Register::Register(fennec::Lexeme &lexeme)
{
    assert(lexeme.summary_type == fennec::LexemeSummaryType::Summary_Register);

    int tmp_register_number = 0;
    try
    {
        // registers are identified by r0, r1, r2, ..., rn
        // we can use the last character in the string sequence to identify the register we want to use
        tmp_register_number = fennec::ASCII_NUMBER_OFFSET - (int)(*lexeme.value.cend());
    }
    catch(std::invalid_argument &ia)
    {
        assert(true); // Lexemes are being corrupted, likely at the lexer phase, there is a bigger issue here
    }

    number = tmp_register_number;
}

const fennec::LexemeType &fennec::Register::get_type() const
{
    return type;
}

uint64_t fennec::Register::get_number() const
{
    return number;
}
