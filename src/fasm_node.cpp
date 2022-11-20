//
// Created by Gabe Cordovado on 2022-09-28.
//

#include "../includes/Parser.h"

fennec::FASMNode::FASMNode(fennec::Lexeme lexeme, FASMNode* parent) : lexeme(lexeme), parent(parent), shared_type_table(
        nullptr)
{}

fennec::FASMNode::FASMNode(fennec::Lexeme lexeme) : lexeme(lexeme), parent(nullptr), shared_type_table(nullptr)
{}

fennec::FASMNode::~FASMNode() {
    if (is_root())
    {
        delete shared_type_table;
    }

    // iterate over each child and invoke the delete function
    for (auto itr = children.begin(); itr != children.end(); ++itr)
    {
        delete *itr;
    }
}

const fennec::Lexeme &fennec::FASMNode::get_lexeme()
{
    return lexeme;
}

const std::vector<fennec::FASMNode*> &fennec::FASMNode::get_children()
{
    return children;
}

void fennec::FASMNode::add_child(fennec::FASMNode *node)
{
    children.push_back(node);
}

bool fennec::FASMNode::is_root() const
{
    return (parent != nullptr);
}

void fennec::FASMNode::set_lexeme(fennec::Lexeme new_lexeme)
{
    lexeme = new_lexeme;
}

fennec::FASMTypeTable &fennec::FASMNode::get_type_table()
{
    return *shared_type_table;
}

void fennec::FASMNode::link_type_table(fennec::FASMTypeTable *type_table)
{
    assert(type_table != nullptr);
    shared_type_table = type_table;
}
