//
// Created by Gabe Cordovado on 2022-09-25.
//

#include "instruction.h"

fennec::Condition::Condition() : raw_bytes(0x0)
{}

fennec::Condition::Condition(uint64_t raw) : raw_bytes(raw)
{}

fennec::Condition::Condition(const fennec::Condition &condition) : raw_bytes(condition.raw_bytes)
{}

bool fennec::Condition::equal()
{
    return raw_bytes & 0x1; // the right-most bit
}

bool fennec::Condition::greater_than()
{
    return (raw_bytes & 0x2) >> 1;
}

bool fennec::Condition::less_than()
{
    return (raw_bytes & 0x4) >> 2;
}

bool fennec::Condition::approximately()
{
    return (raw_bytes & 0x8) >> 3;
}
