//
// Created by Gabe Cordovado on 2022-09-24.
//

#include "../includes/instruction.h"

uint64_t fennec::to_int(fennec::OpCode opcode)
{
    return 0; // TODO - implement
}

fennec::InstructionType fennec::to_type(uint64_t raw)
{
    // if there is an invalid type, this indicates that the instruction is corrupted
    assert(raw <= (fennec::MAX_NUM_OF_TYPES - 1));
    return fennec::int_to_type_array[raw];
}

uint64_t fennec::to_int(fennec::DI di)
{
    if (di == fennec::DI::Indirect)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

fennec::Instruction::Instruction() : raw_bytes(0x0)
{}

fennec::Instruction::Instruction(const fennec::Instruction &other)
{
    raw_bytes = other.raw_bytes;
}

fennec::Instruction::Instruction(uint64_t raw)
{
    raw_bytes = raw;
}

uint64_t fennec::Instruction::swap_bits(uint64_t start_pos, uint64_t end_pos, uint64_t data) const
{
    unsigned long int mask_p1 = (MAX_INSTRUCTION_VALUE << start_pos) & MAX_INSTRUCTION_VALUE;
    std::cout << "mask p1: " << mask_p1 << std::endl;

    unsigned long int mask_p2 = (MAX_INSTRUCTION_VALUE >> ((NUM_INSTRUCTION_BITS-1)-end_pos)) & MAX_INSTRUCTION_VALUE;
    std::cout << "mask p2: " << mask_p2 << std::endl;

    unsigned long int mask = ~(mask_p1 & mask_p2) & 63;
    std::cout << "mask: " << mask << std::endl;

    unsigned long int zeroed_raw_bytes = (raw_bytes & mask) & 63;
    std::cout << "zeroed raw bytes: " << zeroed_raw_bytes << std::endl;

    unsigned long int shifted_target = raw_bytes << start_pos;
    std::cout << "shifted_target: " << shifted_target << std::endl;

    unsigned long int final_value = zeroed_raw_bytes + shifted_target;
    std::cout << "final value: " << final_value << std::endl;

    return final_value;
}

fennec::OpCode fennec::Instruction::get_opcode() const
{
    uint64_t raw_opcode = raw_bytes && FIRST_SIX_BITS;
    if (raw_opcode == 0x00)
    {
        return fennec::OpCode::OpCode_Interrupt;
    }
    else if (raw_opcode == 0x01)
    {
        return fennec::OpCode::OpCode_Move;
    }
    else if (raw_opcode == 0x02)
    {
        return fennec::OpCode::OpCode_Add;
    }
    else
    {
        return fennec::OpCode::OpCode_Subtract;
    }
}

void fennec::Instruction::set_opcode(uint64_t data)
{
    // left-shift six positions to the right to get the OPCODE portion on the right-most side
    raw_bytes = swap_bits(63, 58, data);
}

fennec::DI fennec::Instruction::get_rd1_di() const {
    uint64_t raw_rd1_di = (raw_bytes << 6) & FIRST_BIT;
    if (raw_rd1_di == 1)
    {
        return fennec::Indirect;
    }
    else
    {
        return fennec::Direct;
    }
}

void fennec::Instruction::set_rd1_di(fennec::DI di)
{
    raw_bytes = swap_bits(57, 57, to_int(di));
}

uint64_t fennec::Instruction::get_rd1() const {
    return (raw_bytes << 7) & FIRST_SIX_BITS;
}

void fennec::Instruction::set_rd1(uint64_t raw)
{
    raw_bytes = swap_bits(56, 51, raw);
}

fennec::DI fennec::Instruction::get_rd2_di() const {
    uint64_t raw_rd2_di = (raw_bytes << 13) & FIRST_BIT;
    if (raw_rd2_di == 1)
    {
        return fennec::Indirect;
    }
    else
    {
        return fennec::Direct;
    }
}

void fennec::Instruction::set_rd2_di(fennec::DI di)
{
    raw_bytes = swap_bits(50, 50, to_int(di));
}

uint64_t fennec::Instruction::get_rd2() const {
    return (raw_bytes << 14) & FIRST_SIX_BITS;
}

void fennec::Instruction::set_rd2(uint64_t raw)
{
    raw_bytes = swap_bits(49, 43, raw);
}

fennec::DI fennec::Instruction::get_rs1_di() const {
    uint64_t raw_rs1_di = (raw_bytes << 20) & FIRST_BIT;
    if (raw_rs1_di == 1)
    {
        return fennec::Indirect;
    }
    else
    {
        return fennec::Direct;
    }
}

void fennec::Instruction::set_rs1_di(fennec::DI di)
{
    raw_bytes = swap_bits(42, 42, to_int(di));
}

uint64_t fennec::Instruction::get_rs1() const {
    return (raw_bytes << 21) & FIRST_SIX_BITS;
}

void fennec::Instruction::set_rs1(uint64_t raw)
{
    raw_bytes = swap_bits(41, 36, raw);
}

fennec::DI fennec::Instruction::get_rs2_di() const {
    uint64_t raw_rs2_di = (raw_bytes << 27) & FIRST_BIT;
    if (raw_rs2_di == 1)
    {
        return fennec::Indirect;
    }
    else
    {
        return fennec::Direct;
    }
}

void fennec::Instruction::set_rs2_di(fennec::DI di)
{
    raw_bytes = swap_bits(35, 35, to_int(di));
}

uint64_t fennec::Instruction::get_rs2() const {
    return (raw_bytes << 28) & FIRST_SIX_BITS;
}

void fennec::Instruction::set_rs2(uint64_t raw)
{
    raw_bytes = swap_bits(34, 29, raw);
}

fennec::InstructionType fennec::Instruction::get_type() const
{
    return fennec::UInt8;
}

void fennec::Instruction::set_type(fennec::InstructionType type) {

}


