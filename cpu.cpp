#include "cpu.h"
#include "fmt/core.h"

uint8_t CPU::tick() {
    auto opcode = read_byte_pc();
    uint8_t cycles = 4; // default is noop

    fmt::print("opcode {:#04x}", opcode);
    switch (opcode) {
        case 0x00: break; // noop
        case 0x01: cycles = op_ld_word(reg_b, reg_c); break;
        case 0x02: cycles = op_ld_mem_reg(reg_b, reg_c, reg_a); break;
        case 0x03: cycles = op_inc(reg_b, reg_c); break;
        case 0x04: cycles = op_inc(reg_b); break;
        case 0x05: cycles = op_dec(reg_b); break;
        case 0x06: cycles = op_ld_byte(reg_b); break;

        case 0x11: cycles = op_ld_word(reg_d, reg_e); break;

        case 0x21: cycles = op_ld_word(reg_h, reg_l); break;

        case 0x31: cycles = op_ld_word(sp); break;

        case 0x80: cycles = op_add(reg_b, ADD); break;
        case 0x81: cycles = op_add(reg_c, ADD); break;
        case 0x82: cycles = op_add(reg_d, ADD); break;
        case 0x83: cycles = op_add(reg_e, ADD); break;
        case 0x84: cycles = op_add(reg_h, ADD); break;
        case 0x85: cycles = op_add(reg_l, ADD); break;
        case 0x86: cycles = op_add(reg_h, reg_l, ADD); break;
        case 0x87: cycles = op_add(reg_a, ADD); break;
        case 0x88: cycles = op_add(reg_b, ADC); break;
        case 0x89: cycles = op_add(reg_c, ADC); break;
        case 0x8a: cycles = op_add(reg_d, ADC); break;
        case 0x8b: cycles = op_add(reg_e, ADC); break;
        case 0x8c: cycles = op_add(reg_h, ADC); break;
        case 0x8d: cycles = op_add(reg_l, ADC); break;
        case 0x8e: cycles = op_add(reg_h, reg_l, ADC); break;
        case 0x8f: cycles = op_add(reg_a, ADC); break;

        case 0x90: cycles = op_sub(reg_b, SUB); break;
        case 0x91: cycles = op_sub(reg_c, SUB); break;
        case 0x92: cycles = op_sub(reg_d, SUB); break;
        case 0x93: cycles = op_sub(reg_e, SUB); break;
        case 0x94: cycles = op_sub(reg_h, SUB); break;
        case 0x95: cycles = op_sub(reg_l, SUB); break;
        case 0x96: cycles = op_sub(reg_h, reg_l, SUB); break;
        case 0x97: cycles = op_sub(reg_a, SUB); break;
        case 0x98: cycles = op_sub(reg_b, SBC); break;
        case 0x99: cycles = op_sub(reg_c, SBC); break;
        case 0x9a: cycles = op_sub(reg_d, SBC); break;
        case 0x9b: cycles = op_sub(reg_e, SBC); break;
        case 0x9c: cycles = op_sub(reg_h, SBC); break;
        case 0x9d: cycles = op_sub(reg_l, SBC); break;
        case 0x9e: cycles = op_sub(reg_h, reg_l, SBC); break;
        case 0x9f: cycles = op_sub(reg_a, SBC); break;

        case 0xa0: cycles = op_and(reg_b); break;
        case 0xa1: cycles = op_and(reg_c); break;
        case 0xa2: cycles = op_and(reg_d); break;
        case 0xa3: cycles = op_and(reg_e); break;
        case 0xa4: cycles = op_and(reg_h); break;
        case 0xa5: cycles = op_and(reg_l); break;
        case 0xa6: cycles = op_and(reg_h, reg_l); break;
        case 0xa7: cycles = op_and(reg_a); break;
        case 0xa8: cycles = op_xor(reg_b); break;
        case 0xa9: cycles = op_xor(reg_c); break;
        case 0xaa: cycles = op_xor(reg_d); break;
        case 0xab: cycles = op_xor(reg_e); break;
        case 0xac: cycles = op_xor(reg_h); break;
        case 0xad: cycles = op_xor(reg_l); break;
        case 0xae: cycles = op_xor(reg_h, reg_l); break;
        case 0xaf: cycles = op_xor(reg_a); break;

        case 0xb0: cycles = op_or(reg_b); break;
        case 0xb1: cycles = op_or(reg_c); break;
        case 0xb2: cycles = op_or(reg_d); break;
        case 0xb3: cycles = op_or(reg_e); break;
        case 0xb4: cycles = op_or(reg_h); break;
        case 0xb5: cycles = op_or(reg_l); break;
        case 0xb6: cycles = op_or(reg_h, reg_l); break;
        case 0xb7: cycles = op_or(reg_a); break;
        case 0xb8: cycles = op_sub(reg_b, CP); break;
        case 0xb9: cycles = op_sub(reg_c, CP); break;
        case 0xba: cycles = op_sub(reg_d, CP); break;
        case 0xbb: cycles = op_sub(reg_e, CP); break;
        case 0xbc: cycles = op_sub(reg_h, CP); break;
        case 0xbd: cycles = op_sub(reg_l, CP); break;
        case 0xbe: cycles = op_sub(reg_h, reg_l, CP); break;
        case 0xbf: cycles = op_sub(reg_a, CP); break;

        case 0xc3: cycles = op_jp_word(); break;
        default:
            fmt::print(" !! unimplemented");
    }
    fmt::print("\n");
    return cycles;
}

uint8_t CPU::read_byte_pc() {
    auto b = mem.read_byte_at(pc);
    pc += 1;
    return b;
}

uint8_t CPU::op_ld_word(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_lo = read_byte_pc();
    reg_hi = read_byte_pc();
    return 12;
}

uint8_t CPU::op_ld_word(uint16_t &reg) {
    auto lo = read_byte_pc();
    auto hi = read_byte_pc();
    reg = (hi << 8) + lo;
    return 12;
}


uint8_t CPU::op_ld_byte(uint8_t &reg) {
    reg = read_byte_pc();
    return 8;
}

uint8_t CPU::op_ld_mem_reg(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_target) {
    uint16_t address = (address_hi << 8) + address_lo;
    mem.write_byte_at(address, reg_target);
    return 8;
}

uint8_t CPU::op_inc(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_lo += 1;
    if (reg_lo == 0x00) {
        reg_hi += 1;
    }
    return 8;
}

uint8_t CPU::op_inc(uint8_t &reg) {
    reg += 1;

    flag_bcd_subtract = false;
    flag_bcd_half_carry = (reg & 0x0F) == 0x00;
    if (reg == 0x00) {
        flag_carry = true;
    }
    return 4;
}

uint8_t CPU::op_dec(uint8_t &reg) {
    reg -= 1;

    flag_bcd_subtract = true;
    flag_bcd_half_carry = (reg & 0x0F) == 0x00;
    if (reg == 0xFF) {
        flag_carry = true;
    }
    return 4;
}

uint8_t CPU::op_jp_word() {
    auto lo = read_byte_pc();
    auto hi = read_byte_pc();
    pc = (hi << 8) + lo;
    return 16;
}

uint8_t CPU::op_xor(uint8_t &reg) {
    reg_a = reg xor reg_a;
    flag_zero = (reg_a == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = false;
    flag_carry = false;
    return 4;
}

uint8_t CPU::op_xor(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    reg_a = val xor reg_a;
    flag_zero = (reg_a == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = false;
    flag_carry = false;
    return 8;
}

uint8_t CPU::op_and(uint8_t &reg) {
    reg_a = reg and reg_a;
    flag_zero = (reg_a == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = true;
    flag_carry = false;
    return 4;
}

uint8_t CPU::op_and(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    reg_a = val and reg_a;
    flag_zero = (reg_a == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = true;
    flag_carry = false;
    return 8;
}

uint8_t CPU::op_or(uint8_t &reg) {
    reg_a = reg or reg_a;
    flag_zero = (reg_a == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = false;
    flag_carry = false;
    return 4;
}

uint8_t CPU::op_or(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    reg_a = val or reg_a;
    flag_zero = (reg_a == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = false;
    flag_carry = false;
    return 8;
}

uint8_t CPU::op_sub(uint8_t &reg, SubMode mode) {
    _op_sub(reg, mode);
    return 4;
}

uint8_t CPU::op_sub(uint8_t &reg_hi, uint8_t &reg_lo, SubMode mode) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    _op_sub(val, mode);
    return 8;
}

void CPU::_op_sub(uint8_t val, SubMode mode) {
    int carry = ((mode == SBC) && flag_carry ? 1 : 0);
    int result = reg_a - val - carry;

    flag_zero = (result == 0x00);
    flag_bcd_subtract = true;
    flag_bcd_half_carry = ((reg_a & 0xf) - (val & 0xf) - carry) & 0x10;
    flag_carry = (result < 0);

    switch (mode) {
        case CP: break;
        case SUB:
        case SBC: reg_a = result; break;
    }
}

uint8_t CPU::op_add(uint8_t &reg, AddMode mode) {
    _op_add(reg, mode);
    return 4;
}

uint8_t CPU::op_add(uint8_t &reg_hi, uint8_t &reg_lo, AddMode mode) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    _op_add(val, mode);
    return 8;
}

void CPU::_op_add(uint8_t val, AddMode mode) {
    int carry = ((mode == ADC) && flag_carry ? 1 : 0);
    int result = reg_a + val + carry;

    flag_zero = (result == 0x00);
    flag_bcd_subtract = false;
    flag_bcd_half_carry = ((reg_a & 0xf) + (val & 0xf) + carry) & 0x10;
    flag_carry = (result > 0xff);

    switch (mode) {
        case ADD: break;
        case ADC: reg_a = result; break;
    }
}