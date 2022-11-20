//
// Created by Gabe Cordovado on 2022-09-25.
//

#include "../includes/Parser.h"

fennec::FASMNode* fennec::FASMParser::to_ast(std::vector<fennec::Lexeme> *lexeme_array)
{
    fennec::FASMNode *fasm_ast_root = new fennec::FASMNode;
    assert(fasm_ast_root != nullptr); // system ran out of memory

    fennec::FASMTypeTable *fasm_type_table = new fennec::FASMTypeTable;
    assert(fasm_type_table != nullptr); // system ran out of memory

    // the type table associates addresses to a specific type for dependant instructions
    fasm_ast_root->link_type_table(fasm_type_table);

    std::vector<fennec::Lexeme>::iterator lexeme_array_itr = lexeme_array->begin();

    assert(instruction(lexeme_array_itr, fasm_ast_root));

    return fasm_ast_root;
}

bool fennec::FASMParser::instruction(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    ast_node->set_lexeme(*itr); // the first lexeme should be the instruction (the root)

    if (instruction_add(itr, ast_node))
    {
        return true;
    }

    if (instruction_subtract(itr, ast_node))
    {
        return true;
    }

    if (instruction_move(itr, ast_node))
    {
        return true;
    }

    return false;
}

bool fennec::FASMParser::numerical_type(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node) {
    for (int i = 0; i < fennec::num_reserved_numerical_keywords; ++i)
    {
        if (reserved_numerical_keywords[i] == (*itr).value)
        {
            fennec::FASMNode *node = new fennec::FASMNode(*itr, ast_node);
            ast_node->add_child(node);
            return true;
        }
    }
    //TODO - can this be made into a heap to reduce time from O(n) to O(1)
    return false;
}

bool fennec::FASMParser::is_register(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node) {
    if ((*itr).summary_type != fennec::LexemeSummaryType::Summary_Register)
    {
        return false;
    }

    fennec::FASMNode *node = new fennec::FASMNode(*itr, ast_node);
    assert(node != nullptr); // memory ran out

    ast_node->add_child(node);
    return true;
}

bool fennec::FASMParser::is_literal(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    if ((*itr).summary_type != fennec::LexemeSummaryType::Summary_Literal)
    {
        return false;
    }

    fennec::FASMNode *node = new fennec::FASMNode(*itr, ast_node);
    assert(node != nullptr); // memory ran out

    ast_node->add_child(node);
    return true;
}

bool fennec::FASMParser::instruction_move(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    if ((*itr).type != fennec::LexemeType::Instruction_Move)
    {
        return false;
    }
    itr++;

    if ((*itr).type != fennec::LexemeType::Type_Bracket_Start)
    {
        return false;
    }
    itr++;

    if ((*itr).summary_type != fennec::LexemeSummaryType::Summary_Type)
    {
        return false;
    }
    itr++;

    if ((*itr).type != fennec::LexemeType::Type_Bracket_End)
    {
        return false;
    }
    itr++;

    if (!is_register(itr, ast_node))
    {
        return false;
    }
    itr++;

    if (!source_prime(itr, ast_node))
    {
        return false;
    }

    return true;
}

bool fennec::FASMParser::instruction_add(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    if ((*itr).type != fennec::LexemeType::Instruction_Add)
    {
        return false;
    }
    itr++;

    if (!is_register(itr, ast_node))
    {
        return false;
    }
    itr++;

    if (!source(itr, ast_node))
    {
        return false;
    }

    return true;
}

bool fennec::FASMParser::instruction_subtract(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    if ((*itr).type != fennec::LexemeType::Instruction_Subtract)
    {
        return false;
    }
    itr++;

    if (!is_register(itr, ast_node))
    {
        return false;
    }
    itr++;

    if (!source_prime(itr, ast_node))
    {
        return false;
    }

    return true;
}

bool fennec::FASMParser::source(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    if (!source_prime(itr, ast_node))
    {
        return false;
    }
    itr++;

    if (!source_prime(itr, ast_node))
    {
        return false;
    }

    return true;
}

bool fennec::FASMParser::source_prime(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node)
{
    if (is_register(itr, ast_node))
    {
        return true;
    }

    if (is_literal(itr, ast_node))
    {
        return true;
    }

    return false;
}

fennec::Instruction fennec::FASMParser::to_instruction(fennec::FASMNode *ast_root)
{
    fennec::Instruction instruction;

    switch (ast_root->get_lexeme().type)
    {
        case fennec::LexemeType::Instruction_Interrupt:     instruction.set_opcode(0x0); break;
        case fennec::LexemeType::Instruction_Move:          instruction.set_opcode(0x1); break;
        case fennec::LexemeType::Instruction_Add:           instruction.set_opcode(0x2); break;
        case fennec::LexemeType::Instruction_Subtract:      instruction.set_opcode(0x3); break;
    }

    auto ast_children = ast_root->get_children();
    auto ast_itr = ast_children.begin();

    if (instruction.get_opcode() == 0x0)
    {
        // Interrupt Instruction

        auto interrupt_code_lexeme = (*ast_itr)->get_lexeme();
        fennec::Literal literal(interrupt_code_lexeme);
        instruction.set_rs1(literal.get_value());
    }
    else if (instruction.get_opcode() == 0x1)
    {
        // Move Instruction

        auto move_destination_register_lexeme = (*ast_itr)->get_lexeme();

        fennec::Register move_destination_register(move_destination_register_lexeme);
        instruction.set_rd1(move_destination_register.get_number());

        ast_itr++; // switch to the literal or register

        auto src_address_lexeme = (*ast_itr)->get_lexeme();

        if (src_address_lexeme.summary_type == fennec::LexemeSummaryType::Summary_Register)
        {
            // The source is a register
            fennec::Register src_address_register(src_address_lexeme);
            instruction.set_rs1(src_address_register.get_number());
        }
        else
        {
            // The source is literal
            fennec::Literal src_address_literal(src_address_lexeme);
            instruction.set_rs1(src_address_literal.get_value());
        }
    }
    else if ((instruction.get_opcode() == 0x2) || (instruction.get_opcode() == 0x2))
    {
        // Add Instruction
        // TODO - add type checking

        auto add_destination_register_lexeme = (*ast_itr)->get_lexeme();

        fennec::Register add_destination_register(add_destination_register_lexeme);
        instruction.set_rd1(add_destination_register.get_number());

        ast_itr++;

        // Source 1
        auto src1_address_lexeme = (*ast_itr)->get_lexeme();

        if (src1_address_lexeme.summary_type == fennec::LexemeSummaryType::Summary_Register)
        {
            // Source 1 is a register
            fennec::Register src1_register(src1_address_lexeme);
            instruction.set_rs1(src1_register.get_number());
        }
        else
        {
            // Source 1 is a literal
            fennec::Literal src1_literal(src1_address_lexeme);
            instruction.set_rs1(src1_literal.get_value());
        }
        ast_itr++;

        // Source 2
        auto src2_address_lexeme = (*ast_itr)->get_lexeme();

        if (src2_address_lexeme.summary_type == fennec::LexemeSummaryType::Summary_Register)
        {
            // Source 2 is a register
            fennec::Register src2_register(src2_address_lexeme);
            instruction.set_rs2(src2_register.get_number());
        }
        else
        {
            // Source 2 is a literal
            fennec::Literal src2_literal (src2_address_lexeme);
            instruction.set_rs2(src2_literal.get_value());
        }
    }

    return instruction;
}
