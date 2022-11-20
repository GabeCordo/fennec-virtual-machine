//
// Created by Gabe Cordovado on 2022-09-24.
//

#ifndef FENNEC_INSTRUCTION_H
#define FENNEC_INSTRUCTION_H

#include <iostream>

namespace fennec {

    const uint8_t INSTRUCTION_BIT_SIZE = 64;
    const uint64_t FIRST_SIX_BITS = 0xFC00000000000000;
    const uint64_t FIRST_BIT = 0x8000000000000000;
    const uint64_t MAX_INSTRUCTION_VALUE = 0xFFFFFFFFFFFFFFFF;
    const uint64_t NUM_INSTRUCTION_BITS = 64;

    enum OpCode
    {
        OpCode_Interrupt,
        OpCode_Move,
        OpCode_Add,
        OpCode_Subtract,
    };

    uint64_t to_int(fennec::OpCode opcode);

    enum InstructionType
    {
        UInt8,
        UInt16,
        UInt32,
        UInt64,
        Int8,
        Int16,
        Int32,
        Int64,
        Float32,
        Float64,
        Character,
        String
    };

    const uint64_t MAX_NUM_OF_TYPES = 64;
    const fennec::InstructionType int_to_type_array[] = {UInt8,
                                              UInt16,
                                              UInt32,
                                              UInt64,
                                              Int8,
                                              Int16,
                                              Int32,
                                              Int64,
                                              Float32,
                                              Float64,
                                              Character,
                                              String};

    fennec::InstructionType to_type(uint64_t raw);

    enum DI
    {
        Direct,
        Indirect
    };

    uint64_t to_int(fennec::DI di);

    class Condition
    {
    private:
        uint64_t raw_bytes;
    public:
        Condition();
        Condition(uint64_t raw);
        Condition(const Condition& condition);

        bool equal();
        bool greater_than();
        bool less_than();
        bool approximately();
    };

    class Instruction
    {
    private:
        uint64_t raw_bytes;

        uint64_t swap_bits(uint64_t start_pos, uint64_t end_pos, uint64_t data) const;
    public:
        Instruction();
        explicit Instruction(uint64_t raw);
        Instruction(const Instruction &other);

        fennec::OpCode get_opcode() const;
        void set_opcode(uint64_t data);

        fennec::DI get_rd1_di() const;
        void set_rd1_di(fennec::DI di);
        uint64_t get_rd1() const;
        void set_rd1(uint64_t raw);

        fennec::DI get_rd2_di() const;
        void set_rd2_di(fennec::DI di);
        uint64_t get_rd2() const;
        void set_rd2(uint64_t raw);

        fennec::DI get_rs1_di() const;
        void set_rs1_di(fennec::DI di);
        uint64_t get_rs1() const;
        void set_rs1(uint64_t raw);

        fennec::DI get_rs2_di() const;
        void set_rs2_di(fennec::DI di);
        uint64_t get_rs2() const;
        void set_rs2(uint64_t raw);

        fennec::InstructionType get_type() const;
        void set_type(fennec::InstructionType type);

        fennec::Condition get_condition() const;
        void set_condition(fennec::Condition condition);
    };
}


#endif //FENNEC_INSTRUCTION_H
