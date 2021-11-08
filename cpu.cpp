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
        case 0xb8: cycles = op_cp(reg_b); break;
        case 0xb9: cycles = op_cp(reg_c); break;
        case 0xba: cycles = op_cp(reg_d); break;
        case 0xbb: cycles = op_cp(reg_e); break;
        case 0xbc: cycles = op_cp(reg_h); break;
        case 0xbd: cycles = op_cp(reg_l); break;
        case 0xbe: cycles = op_cp(reg_h, reg_l); break;
        case 0xbf: cycles = op_cp(reg_a); break;

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

uint8_t CPU::op_cp(uint8_t &reg) {
    int result = reg_a - reg;

    flag_zero = (result == 0x00);
    flag_bcd_subtract = true;
    flag_bcd_half_carry = ((reg_a & 0xf) - (reg & 0xf)) & 0x10;
    flag_carry = (result < 0);
    return 4;
}

uint8_t CPU::op_cp(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    int result = reg_a - val;

    flag_zero = (result == 0x00);
    flag_bcd_subtract = true;
    flag_bcd_half_carry = ((reg_a & 0xf) - (val & 0xf)) & 0x10;
    flag_carry = (result < 0);
    return 8;
}
