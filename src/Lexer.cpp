//
// Created by Gabe Cordovado on 2022-09-25.
//

#include "../includes/Lexer.h"
#include <iostream>
#include <vector>
#include <utility>

std::vector<fennec::Lexeme> *fennec::Lexer::to_lexeme_array(std::string input_string)
{
    std::vector<fennec::Lexeme> *lexeme_array = new std::vector<fennec::Lexeme>();
    if (lexeme_array == nullptr)
    {
        return nullptr;
    }

    std::string buffer;
    for (auto itr = input_string.cbegin(); ; ++itr) {
        if ((*itr != ' ') && (itr != input_string.cend())) {
            if (*itr == '*') {
                Lexeme l;
                l.type = LexemeType::Indirect_Indicator;
                l.value = "*";
                lexeme_array->push_back(l);
            }
            else if (*itr == '<') {
                Lexeme l;
                l.type = LexemeType::Type_Bracket_Start;
                l.value = "<";
                lexeme_array->push_back(l);
            }
            else if (*itr == '>') {
                Lexeme l;
                l.type = LexemeType::Type_Bracket_End;
                l.value = ">";
                lexeme_array->push_back(l);
            }
            else {
                buffer.push_back(*itr);
            }
            continue;
        }

        fennec::Lexeme l;
        if (buffer == "add") {
            l.type = LexemeType::Instruction_Add;
        } else if (buffer == "subtract") {
            l.type = LexemeType::Instruction_Subtract;
        } else if (buffer == "interrupt") {
            l.type = LexemeType::Instruction_Interrupt;
        } else if (buffer == "move") {
            l.type = LexemeType::Instruction_Move;
        } else if ((buffer.length() == 2) && (*buffer.cbegin() == 'r')) {
            l.summary_type = fennec::LexemeSummaryType::Summary_Register;

            int register_number = 0;
            try {
                auto register_str_number = *(buffer.cend() - 1);
                register_number = ASCII_NUMBER_OFFSET - (int)register_str_number;
            }
            catch (std::invalid_argument &ia) {
                assert(true);   // error
            }

            if ((register_number < 0) || (register_number >= fennec::num_of_registers)) {
                assert(true);   // error
            }

            l.type = fennec::int_to_register[register_number];
        } else if (buffer.find(".f") != std::string::npos) {
            l.summary_type = fennec::LexemeSummaryType::Summary_Literal;
            l.type = fennec::LexemeType::Literal_Float;
        } else if (buffer.find("0x") != std::string::npos) {
            l.summary_type = fennec::LexemeSummaryType::Summary_Literal;
            l.type = fennec::LexemeType::Literal_Hex;
        } else {
            l.summary_type = fennec::LexemeSummaryType::Summary_Literal;
            l.type = fennec::LexemeType::Literal_Decimal;
        }
        l.value = buffer;

        lexeme_array->push_back(l);
        buffer.clear();

        if (itr == input_string.cend())
        {
            break;
        }
    }

    std::cout << "[Warning] lexeme_array(" << lexeme_array << ") must be released by caller" << std::endl;
    return lexeme_array;
}

void fennec::Lexer::print(std::vector<fennec::Lexeme>* lexeme_array)
{
    for (auto itr = lexeme_array->begin(); itr != lexeme_array->end(); ++itr)
    {
        std::cout << (*itr).value << " (" << fennec::lexeme_to_str[(*itr).type] << ")" << std::endl;
    }
}
