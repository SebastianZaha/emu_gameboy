#pragma once
#include <cstdint>
#include "mem.h"

class CPU {

public:
    explicit CPU(Mem& mem): mem(mem) {}

    static const auto CLOCK_SPEED = 4'194'304;

    uint8_t tick();

private:
    Mem &mem;

    uint8_t reg_a = 0x01; // accumulator

    bool flag_zero = true;
    bool flag_bcd_subtract = false;
    bool flag_bcd_half_carry = true;
    bool flag_carry = true;

    /* The Flag Register (lower 8bit of AF register)
        Bit  Name  Set Clr  Expl.
        7    zf    Z   NZ   Zero Flag
        6    n     -   -    Add/Sub-Flag (BCD)
        5    h     -   -    Half Carry Flag (BCD)
        4    cy    C   NC   Carry Flag
        3-0  -     -   -    Not used (always zero)
        Contains the result from the recent instruction which has affected flags.

        The Zero Flag (Z)
        This bit becomes set (1) if the result of an operation has been zero (0). Used for conditional jumps.

        The Carry Flag (C, or Cy)
        Becomes set when the result of an addition became bigger than FFh (8bit) or FFFFh (16bit).
        Or when the result of a subtraction or comparision became less than zero (much as for Z80 and 80x86 CPUs,
        but unlike as for 65XX and ARM CPUs).
        Also the flag becomes set when a rotate/shift operation has shifted-out a "1"-bit.
        Used for conditional jumps, and for instructions such like ADC, SBC, RL, RLA, etc.

        The BCD Flags (N, H)
        These flags are (rarely) used for the DAA instruction only, N Indicates whether the previous instruction
        has been an addition or subtraction, and H indicates carry for lower 4bits of the result, also for DAA,
        the C flag must indicate carry for upper 8bits.
        After adding/subtracting two BCD numbers, DAA is intended to convert the result into BCD format;
        BCD numbers are ranged from 00h to 99h rather than 00h to FFh.
        Because C and H flags must contain carry-outs for each digit, DAA cannot be used for 16bit operations
        (which have 4 digits), or for INC/DEC operations (which do not affect C-flag). */

    uint8_t reg_b = 0x00;
    uint8_t reg_c = 0x13;

    uint8_t reg_d = 0x00;
    uint8_t reg_e = 0xD8;

    uint8_t reg_h = 0x01;
    uint8_t reg_l = 0x4D;

    uint16_t sp = 0xFFFE;   // stack pointer
    uint16_t pc = 0x0100;   // program counter / pointer

    uint8_t read_byte_pc();

    uint8_t op_inc(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_inc(uint8_t &reg);
    uint8_t op_dec(uint8_t &reg);
    uint8_t op_ld_word(uint8_t &regHi, uint8_t &regLo);
    uint8_t op_ld_mem_reg(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_target);
    uint8_t op_ld_byte(uint8_t &reg);
    uint8_t op_ld_word(uint16_t &reg);
    uint8_t op_jp_word();
    uint8_t op_xor(uint8_t &reg);
    uint8_t op_xor(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_and(uint8_t &reg);
    uint8_t op_and(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_or(uint8_t &reg);
    uint8_t op_or(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_cp(uint8_t &reg);
    uint8_t op_cp(uint8_t &reg_hi, uint8_t &reg_lo);
};
