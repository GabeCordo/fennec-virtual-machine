//
// Created by Gabe Cordovado on 2022-09-25.
//

#ifndef FENNEC_PARSER_H
#define FENNEC_PARSER_H

#include <vector>
#include <map>

#include "instruction.h"
#include "Lexer.h"

namespace fennec
{

    const std::string reserved_numerical_keywords[] = {
            "UInt8",
            "u8",
            "UInt16",
            "u16",
            "UInt32",
            "u32",
            "UInt64",
            "Int8",
            "8",
            "Int16",
            "16",
            "Int32",
            "32",
            "Int64",
            "64",
            "Float32",
            "F32",
            "Float64",
            "F64"
    };
    const uint16_t num_reserved_numerical_keywords = 19;

    class Literal
    {
    private:
        fennec::LexemeType  type;
        uint64_t            value;
    public:
        explicit Literal(fennec::Lexeme &lexeme);

        [[nodiscard]] const fennec::LexemeType& get_type() const;
        uint64_t get_value() const;
    };

    class Register
    {
    private:
        fennec::LexemeType type;
        uint64_t           number;
    public:
        explicit  Register(fennec::Lexeme &lexeme);

        [[nodiscard]] const fennec::LexemeType& get_type() const;
        uint64_t get_number() const;
    };

    class TypeTable
    {
    private:
        std::map<uint64_t, fennec::LexemeType> link;
    public:
        TypeTable();
    };

    class FASMNode
    {
    private:
        fennec::Lexeme lexeme;
        std::vector<FASMNode*> children;
    public:
        FASMNode() = default;
        explicit FASMNode(fennec::Lexeme lexeme);
        ~FASMNode();

        const fennec::Lexeme &get_lexeme();
        void set_lexeme(fennec::Lexeme new_lexeme);

        const std::vector<fennec::FASMNode*> &get_children();
        void add_child(fennec::FASMNode* node);
    };

    class FASMParser
    {
    private:
        bool instruction(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool instruction_move(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool instruction_add(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool instruction_subtract(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool source(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool source_prime(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool numerical_type(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool is_register(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
        bool is_literal(std::vector<fennec::Lexeme>::iterator itr, fennec::FASMNode *ast_node);
    public:
        FASMParser() = default;
        ~FASMParser() = default;

        FASMNode* to_ast(std::vector<fennec::Lexeme> *lexeme_array);
        fennec::Instruction to_instruction(FASMNode *ast_root);
    };

}

#endif //FENNEC_PARSER_H
