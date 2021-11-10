#pragma once
#include <cstdint>
#include "mem.h"

enum SubMode { CP, SUB, SBC };
enum AddMode { ADD, ADC };

class CPU {

public:
    explicit CPU(Mem& mem): mem(mem) {}

    static const auto CLOCK_SPEED = 4'194'304;

    uint8_t tick();

private:
    Mem &mem;

    uint8_t reg_a = 0x01; // accumulator

    bool flag_1000_zero = true;
    bool flag_0100_bcd_subtract = false;
    bool flag_0010_bcd_half_carry = true;
    bool flag_0001_carry = true;

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

    bool ime = false;

    uint8_t op_inc(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_inc(uint8_t &reg);
    uint8_t op_dec(uint8_t &reg);
    uint8_t op_ld_16bit(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_ld_mem_reg(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_source);
    uint8_t op_ld_byte(uint8_t &reg);
    uint8_t op_ld_16bit(uint16_t &reg);
    uint8_t op_jp_16bit();
    uint8_t op_xor(uint8_t &reg);
    uint8_t op_xor(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_and(uint8_t &reg);
    uint8_t op_and(uint8_t &reg_hi, uint8_t &reg_lo);
    uint8_t op_or(uint8_t &reg);
    uint8_t op_or(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_sub(uint8_t &reg, SubMode mode);
    uint8_t op_sub(uint8_t &reg_hi, uint8_t &reg_lo, SubMode mode);

    void _op_sub(uint8_t val, SubMode mode);

    uint8_t op_add(uint8_t &reg, AddMode mode);

    uint8_t op_add(uint8_t &reg_hi, uint8_t &reg_lo, AddMode mode);

    void _op_add(uint8_t val, AddMode mode);

    uint8_t op_ld_mem_reg_inc(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_source);

    uint8_t op_ld_mem_reg_dec(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_source);

    uint8_t op_dec(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_inc(uint16_t &reg);

    uint8_t op_inc_mem(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_dec_mem(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_jr_z();
    uint8_t op_jr_nz();
    uint8_t op_jr_c();
    uint8_t op_jr_nc();

    uint8_t op_ld_mem_byte(uint8_t &address_hi, uint8_t &address_lo);

    uint8_t op_ld(uint8_t &reg_target, uint8_t &reg_source);

    uint8_t op_ld_reg_mem(uint8_t &reg_target, uint8_t &address_hi, uint8_t &address_lo);

    uint8_t op_ld_reg_mem_inc(uint8_t &reg_target, uint8_t &address_hi, uint8_t &address_lo);

    uint8_t op_ld_reg_mem_dec(uint8_t &reg_target, uint8_t &address_hi, uint8_t &address_lo);

    uint8_t op_rlca();

    uint8_t op_rla();

    uint8_t op_rrca();

    uint8_t op_rra();

    uint8_t op_ld_mem_sp();

    uint8_t op_add_16bit(uint8_t &reg1_hi, uint8_t &reg1_lo, uint8_t &reg2_hi, uint8_t &reg2_lo);

    uint8_t op_add_16bit(uint8_t &reg1_hi, uint8_t &reg1_lo, uint16_t &reg2);

    uint8_t op_dec(uint16_t &reg);

    uint8_t op_jr();

    uint8_t op_daa();
    uint8_t op_scf();

    uint8_t op_cpl();

    uint8_t op_ccf();

    uint8_t op_jp_nz();

    uint8_t op_jp_z();

    uint8_t op_jp_nc();

    uint8_t op_jp_c();

    uint8_t op_jp_16bit(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_ld_mem_a();

    uint8_t op_ldh_mem_reg();

    uint8_t op_ldh_reg_mem();

    uint8_t op_ld_a_mem();

    uint8_t op_ld_mem_reg(uint8_t &reg_source);

    uint8_t op_ld_mem_c_a();

    uint8_t op_ld_a_mem_c();

    uint8_t op_ld_hl_sp_plus_s8();

    uint8_t op_pop(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_pop_af();

    uint8_t op_ld(uint16_t reg_target, uint8_t &reg_source_hi, uint8_t &reg_source_lo);

    uint8_t read_byte_and_inc(uint16_t &reg);
    void write_byte_and_dec(uint16_t &reg, uint8_t value);

    uint8_t op_push(uint8_t &reg_hi, uint8_t &reg_lo);

    uint8_t op_push_af();

    uint8_t op_call();

    uint8_t op_push(uint16_t &reg);

    uint8_t op_ret();

    uint8_t op_pop(uint16_t &reg);

    uint8_t op_ret_nz();

    uint8_t op_call_nz();

    uint8_t op_ret_z();

    uint8_t op_call_z();

    uint8_t op_ret_nc();

    uint8_t op_call_nc();

    uint8_t op_ret_c();

    uint8_t op_call_c();

    uint8_t op_add_d8(AddMode mode);

    uint8_t op_sub_d8(SubMode mode);

    uint8_t op_and();

    uint8_t op_or();

    uint8_t op_xor();

    uint8_t op_rst(uint16_t addr);

    uint8_t op_add_sp_s8();

    uint8_t op_ei();

    uint8_t op_di();

    uint8_t op_reti();
};
