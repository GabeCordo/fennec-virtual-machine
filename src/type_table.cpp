//
// Created by Gabe Cordovado on 2022-09-27.
//

#include "../includes/Parser.h"

bool fennec::FASMTypeTable::is_type_enforced(uint64_t address)
{
    // only if a type is assigned for that address, is it enforced
    return (table.find(address) != table.end());
}

void fennec::FASMTypeTable::assign_type(uint64_t address, fennec::LexemeType type)
{
    // assign_type should not be used to override an existing enforced type
    if (table.find(address) != table.end()) return;

    table.insert(std::pair<uint64_t, fennec::LexemeType>(address, type));
}

void fennec::FASMTypeTable::override_type(uint64_t address, fennec::LexemeType type)
{
    if (table.find(address) != table.end())
    {
        table.erase(address);
    }

    table.insert(std::pair<uint64_t, fennec::LexemeType>(address, type));
}
