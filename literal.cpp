//
// Created by Gabe Cordovado on 2022-09-26.
//

#include "Parser.h"

fennec::Literal::Literal(fennec::Lexeme &lexeme)
{
    assert(lexeme.summary_type == fennec::LexemeSummaryType::Summary_Literal);
    type = lexeme.type;

    if (type == fennec::LexemeType::Literal_Hex)
    {
        value = std::stoul(lexeme.value, nullptr, 16);
    }
    else if (type == fennec::LexemeType::Literal_Float)
    {
        value = std::stof(lexeme.value, nullptr);
    }
    else
    {
        value = std::stoi(lexeme.value);
    }
}

const fennec::LexemeType &fennec::Literal::get_type() const
{
    return type;
}

uint64_t fennec::Literal::get_value() const
{
    return value;
}
