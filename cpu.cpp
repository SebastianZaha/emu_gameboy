#include "cpu.h"
#include "fmt/core.h"

uint8_t CPU::tick() {
    auto opcode = read_byte_and_inc(pc);
    uint8_t cycles = 4; // default is noop

    fmt::print("opcode {:#04x}", opcode);
    switch (opcode) {
        case 0x00: break; // noop
        case 0x01: cycles = op_ld_16bit(reg_b, reg_c); break;
        case 0x02: cycles = op_ld_mem_reg(reg_b, reg_c, reg_a); break;
        case 0x03: cycles = op_inc(reg_b, reg_c); break;
        case 0x04: cycles = op_inc(reg_b); break;
        case 0x05: cycles = op_dec(reg_b); break;
        case 0x06: cycles = op_ld_byte(reg_b); break;
        case 0x07: cycles = op_rlca(); break;
        case 0x08: cycles = op_ld_mem_sp(); break;
        case 0x09: cycles = op_add_16bit(reg_h, reg_l, reg_b, reg_c); break;
        case 0x0a: cycles = op_ld_reg_mem(reg_a, reg_b, reg_c); break;
        case 0x0b: cycles = op_dec(reg_b, reg_c); break;
        case 0x0c: cycles = op_inc(reg_c); break;
        case 0x0d: cycles = op_dec(reg_c); break;
        case 0x0e: cycles = op_ld_byte(reg_c); break;
        case 0x0f: cycles = op_rrca(); break;

        case 0x10: cycles = 0; break;
        case 0x11: cycles = op_ld_16bit(reg_d, reg_e); break;
        case 0x12: cycles = op_ld_mem_reg(reg_d, reg_e, reg_a); break;
        case 0x13: cycles = op_inc(reg_d, reg_e); break;
        case 0x14: cycles = op_inc(reg_d); break;
        case 0x15: cycles = op_dec(reg_d); break;
        case 0x16: cycles = op_ld_byte(reg_d); break;
        case 0x17: cycles = op_rla(); break;
        case 0x18: cycles = op_jr(); break;
        case 0x19: cycles = op_add_16bit(reg_h, reg_l, reg_d, reg_e); break;
        case 0x1a: cycles = op_ld_reg_mem(reg_a, reg_d, reg_e); break;
        case 0x1b: cycles = op_dec(reg_d, reg_e); break;
        case 0x1c: cycles = op_inc(reg_e); break;
        case 0x1d: cycles = op_dec(reg_e); break;
        case 0x1e: cycles = op_ld_byte(reg_e); break;
        case 0x1f: cycles = op_rra(); break;

        case 0x20: cycles = op_jr_nz(); break;
        case 0x21: cycles = op_ld_16bit(reg_h, reg_l); break;
        case 0x22: cycles = op_ld_mem_reg_inc(reg_h, reg_l, reg_a); break;
        case 0x23: cycles = op_inc(reg_h, reg_l); break;
        case 0x24: cycles = op_inc(reg_h); break;
        case 0x25: cycles = op_dec(reg_h); break;
        case 0x26: cycles = op_ld_byte(reg_h); break;
        case 0x27: cycles = op_daa(); break;
        case 0x28: cycles = op_jr_z(); break;
        case 0x29: cycles = op_add_16bit(reg_h, reg_l, reg_h, reg_l); break;
        case 0x2a: cycles = op_ld_reg_mem_inc(reg_a, reg_h, reg_l); break;
        case 0x2b: cycles = op_dec(reg_h, reg_l); break;
        case 0x2c: cycles = op_inc(reg_l); break;
        case 0x2d: cycles = op_dec(reg_l); break;
        case 0x2e: cycles = op_ld_byte(reg_l); break;
        case 0x2f: cycles = op_cpl(); break;

        case 0x30: cycles = op_jr_nc(); break;
        case 0x31: cycles = op_ld_16bit(sp); break;
        case 0x32: cycles = op_ld_mem_reg_dec(reg_h, reg_l, reg_a); break;
        case 0x33: cycles = op_inc(sp); break;
        case 0x34: cycles = op_inc_mem(reg_h, reg_l); break;
        case 0x35: cycles = op_dec_mem(reg_h, reg_l); break;
        case 0x36: cycles = op_ld_mem_byte(reg_h, reg_l); break;
        case 0x37: cycles = op_scf(); break;
        case 0x38: cycles = op_jr_c(); break;
        case 0x39: cycles = op_add_16bit(reg_h, reg_l, sp); break;
        case 0x3a: cycles = op_ld_reg_mem_dec(reg_a, reg_h, reg_l); break;
        case 0x3b: cycles = op_dec(sp); break;
        case 0x3c: cycles = op_inc(reg_a); break;
        case 0x3d: cycles = op_dec(reg_a); break;
        case 0x3e: cycles = op_ld_byte(reg_a); break;
        case 0x3f: cycles = op_ccf(); break;

        case 0x40: cycles = op_ld(reg_b, reg_b); break;
        case 0x41: cycles = op_ld(reg_b, reg_c); break;
        case 0x42: cycles = op_ld(reg_b, reg_d); break;
        case 0x43: cycles = op_ld(reg_b, reg_e); break;
        case 0x44: cycles = op_ld(reg_b, reg_h); break;
        case 0x45: cycles = op_ld(reg_b, reg_l); break;
        case 0x46: cycles = op_ld_reg_mem(reg_b, reg_h, reg_l); break;
        case 0x47: cycles = op_ld(reg_b, reg_a); break;
        case 0x48: cycles = op_ld(reg_c, reg_b); break;
        case 0x49: cycles = op_ld(reg_c, reg_c); break;
        case 0x4a: cycles = op_ld(reg_c, reg_d); break;
        case 0x4b: cycles = op_ld(reg_c, reg_e); break;
        case 0x4c: cycles = op_ld(reg_c, reg_h); break;
        case 0x4d: cycles = op_ld(reg_c, reg_l); break;
        case 0x4e: cycles = op_ld_reg_mem(reg_c, reg_h, reg_l); break;
        case 0x4f: cycles = op_ld(reg_c, reg_a); break;

        case 0x50: cycles = op_ld(reg_d, reg_b); break;
        case 0x51: cycles = op_ld(reg_d, reg_c); break;
        case 0x52: cycles = op_ld(reg_d, reg_d); break;
        case 0x53: cycles = op_ld(reg_d, reg_e); break;
        case 0x54: cycles = op_ld(reg_d, reg_h); break;
        case 0x55: cycles = op_ld(reg_d, reg_l); break;
        case 0x56: cycles = op_ld_reg_mem(reg_d, reg_h, reg_l); break;
        case 0x57: cycles = op_ld(reg_d, reg_a); break;
        case 0x58: cycles = op_ld(reg_e, reg_b); break;
        case 0x59: cycles = op_ld(reg_e, reg_c); break;
        case 0x5a: cycles = op_ld(reg_e, reg_d); break;
        case 0x5b: cycles = op_ld(reg_e, reg_e); break;
        case 0x5c: cycles = op_ld(reg_e, reg_h); break;
        case 0x5d: cycles = op_ld(reg_e, reg_l); break;
        case 0x5e: cycles = op_ld_reg_mem(reg_e, reg_h, reg_l); break;
        case 0x5f: cycles = op_ld(reg_e, reg_a); break;

        case 0x60: cycles = op_ld(reg_h, reg_b); break;
        case 0x61: cycles = op_ld(reg_h, reg_c); break;
        case 0x62: cycles = op_ld(reg_h, reg_d); break;
        case 0x63: cycles = op_ld(reg_h, reg_e); break;
        case 0x64: cycles = op_ld(reg_h, reg_h); break;
        case 0x65: cycles = op_ld(reg_h, reg_l); break;
        case 0x66: cycles = op_ld_reg_mem(reg_h, reg_h, reg_l); break;
        case 0x67: cycles = op_ld(reg_h, reg_a); break;
        case 0x68: cycles = op_ld(reg_l, reg_b); break;
        case 0x69: cycles = op_ld(reg_l, reg_c); break;
        case 0x6a: cycles = op_ld(reg_l, reg_d); break;
        case 0x6b: cycles = op_ld(reg_l, reg_e); break;
        case 0x6c: cycles = op_ld(reg_l, reg_h); break;
        case 0x6d: cycles = op_ld(reg_l, reg_l); break;
        case 0x6e: cycles = op_ld_reg_mem(reg_l, reg_h, reg_l); break;
        case 0x6f: cycles = op_ld(reg_l, reg_a); break;

        case 0x70: cycles = op_ld_mem_reg(reg_h, reg_l, reg_b); break;
        case 0x71: cycles = op_ld_mem_reg(reg_h, reg_l, reg_c); break;
        case 0x72: cycles = op_ld_mem_reg(reg_h, reg_l, reg_d); break;
        case 0x73: cycles = op_ld_mem_reg(reg_h, reg_l, reg_e); break;
        case 0x74: cycles = op_ld_mem_reg(reg_h, reg_l, reg_h); break;
        case 0x75: cycles = op_ld_mem_reg(reg_h, reg_l, reg_l); break;
        case 0x76: cycles = 0; break;
        case 0x77: cycles = op_ld_mem_reg(reg_h, reg_l, reg_a); break;
        case 0x78: cycles = op_ld(reg_a, reg_b); break;
        case 0x79: cycles = op_ld(reg_a, reg_c); break;
        case 0x7a: cycles = op_ld(reg_a, reg_d); break;
        case 0x7b: cycles = op_ld(reg_a, reg_e); break;
        case 0x7c: cycles = op_ld(reg_a, reg_h); break;
        case 0x7d: cycles = op_ld(reg_a, reg_l); break;
        case 0x7e: cycles = op_ld_reg_mem(reg_a, reg_h, reg_l); break;
        case 0x7f: cycles = op_ld(reg_a, reg_a); break;

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

        case 0xc0: cycles = op_ret_nz(); break;
        case 0xc1: cycles = op_pop(reg_b, reg_c); break;
        case 0xc2: cycles = op_jp_nz(); break;
        case 0xc3: cycles = op_jp_16bit(); break;
        case 0xc4: cycles = op_call_nz(); break;
        case 0xc5: cycles = op_push(reg_b, reg_c); break;
        case 0xc6: cycles = op_add_d8(AddMode::ADD);
        case 0xc7: cycles = op_rst(0x0000);
        case 0xc8: cycles = op_ret_z(); break;
        case 0xc9: cycles = op_ret(); break;
        case 0xca: cycles = op_jp_z(); break;
        // FIXME: cb prefix
        case 0xcc: cycles = op_call_z(); break;
        case 0xcd: cycles = op_call(); break;
        case 0xce: cycles = op_add_d8(AddMode::ADC);
        case 0xcf: cycles = op_rst(0x0008);

        case 0xd0: cycles = op_ret_nc(); break;
        case 0xd1: cycles = op_pop(reg_d, reg_e); break;
        case 0xd2: cycles = op_jp_nc(); break;
        // empty
        case 0xd4: cycles = op_call_nc(); break;
        case 0xd5: cycles = op_push(reg_d, reg_e); break;
        case 0xd6: cycles = op_sub_d8(SubMode::SUB); break;
        case 0xd7: cycles = op_rst(0x0010);
        case 0xd8: cycles = op_ret_c(); break;
        case 0xd9: cycles = op_reti(); break;
        case 0xda: cycles = op_jp_c(); break;
        // empty
        case 0xdc: cycles = op_call_c(); break;
        // empty
        case 0xde: cycles = op_sub_d8(SubMode::SBC); break;
        case 0xdf: cycles = op_rst(0x0018);

        case 0xe0: cycles = op_ldh_mem_reg(); break;
        case 0xe1: cycles = op_pop(reg_h, reg_l); break;
        case 0xe2: cycles = op_ld_mem_c_a(); break;
        // empty
        // empty
        case 0xe5: cycles = op_push(reg_h, reg_l); break;
        case 0xe6: cycles = op_and(); break;
        case 0xe7: cycles = op_rst(0x0020);
        case 0xe8: cycles = op_add_sp_s8();
        case 0xe9: cycles = op_jp_16bit(reg_h, reg_l); break;
        case 0xea: cycles = op_ld_mem_a(); break;
        // empty
        // empty
        // empty
        case 0xee: cycles = op_xor(); break;
        case 0xef: cycles = op_rst(0x0028);

        case 0xf0: cycles = op_ldh_reg_mem(); break;
        case 0xf1: cycles = op_pop_af(); break;
        case 0xf2: cycles = op_ld_a_mem_c(); break;
        case 0xf3: cycles = op_di(); break;
        // empty
        case 0xf5: cycles = op_push_af(); break;
        case 0xf6: cycles = op_or(); break;
        case 0xf7: cycles = op_rst(0x0030);
        case 0xf8: cycles = op_ld_hl_sp_plus_s8(); break;
        case 0xf9: cycles = op_ld(sp, reg_h, reg_l); break;
        case 0xfa: cycles = op_ld_a_mem(); break;
        case 0xfb: cycles = op_ei(); break;
        // empty
        // empty
        case 0xfe: cycles = op_sub_d8(SubMode::CP); break;
        case 0xff: cycles = op_rst(0x0038);

        default:
            fmt::print(" !! unimplemented");
    }
    fmt::print("\n");
    return cycles;
}

uint8_t CPU::read_byte_and_inc(uint16_t &reg) {
    auto b = mem.read_byte_at(reg);
    reg += 1;
    return b;
}

void CPU::write_byte_and_dec(uint16_t &reg, uint8_t value) {
    mem.write_byte_at(reg, value);
    reg -= 1;
}

uint8_t CPU::op_ld_16bit(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_lo = read_byte_and_inc(pc);
    reg_hi = read_byte_and_inc(pc);
    return 12;
}

uint8_t CPU::op_ld_16bit(uint16_t &reg) {
    auto lo = read_byte_and_inc(pc);
    auto hi = read_byte_and_inc(pc);
    reg = (hi << 8) + lo;
    return 12;
}


uint8_t CPU::op_ld_byte(uint8_t &reg) {
    reg = read_byte_and_inc(pc);
    return 8;
}

uint8_t CPU::op_ld(uint8_t &reg_target, uint8_t &reg_source) {
    reg_target = reg_source;
    return 4;
}

uint8_t CPU::op_ld(uint16_t reg_target, uint8_t &reg_source_hi, uint8_t &reg_source_lo) {
    reg_target = (reg_source_hi << 8) + reg_source_lo;
    return 8;
}

uint8_t CPU::op_ld_mem_byte(uint8_t &address_hi, uint8_t &address_lo) {
    uint16_t address = (address_hi << 8) + address_lo;
    mem.write_byte_at(address, read_byte_and_inc(pc));
    return 12;
}

uint8_t CPU::op_ld_mem_reg(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_source) {
    uint16_t address = (address_hi << 8) + address_lo;
    mem.write_byte_at(address, reg_source);
    return 8;
}

uint8_t CPU::op_ld_mem_sp() {
    auto lo = read_byte_and_inc(pc);
    auto hi = read_byte_and_inc(pc);
    uint16_t address = (hi << 8) + lo;

    auto sp_hi = static_cast<uint8_t>(sp >> 8);
    mem.write_byte_at(address, sp_hi);
    mem.write_byte_at(address+1, static_cast<uint8_t>(sp));
    return 20;
}

uint8_t CPU::op_ld_mem_a() {
    auto lo = read_byte_and_inc(pc);
    auto hi = read_byte_and_inc(pc);
    uint16_t address = (hi << 8) + lo;
    mem.write_byte_at(address, reg_a);
    return 16;
}

uint8_t CPU::op_ld_a_mem() {
    auto lo = read_byte_and_inc(pc);
    auto hi = read_byte_and_inc(pc);
    uint16_t address = (hi << 8) + lo;
    reg_a = mem.read_byte_at(address);
    return 16;
}

uint8_t CPU::op_ldh_mem_reg() {
    auto lo = read_byte_and_inc(pc);
    mem.write_byte_at(0xff00 + lo, reg_a);
    return 12;
}

uint8_t CPU::op_ldh_reg_mem() {
    auto lo = read_byte_and_inc(pc);
    reg_a = mem.read_byte_at(0xff00 + lo);
    return 12;
}

uint8_t CPU::op_ld_mem_c_a() {
    mem.write_byte_at(0xff00 + reg_c, reg_a);
    return 8;
}

uint8_t CPU::op_ld_a_mem_c() {
    reg_a = mem.read_byte_at(0xff00 + reg_c);
    return 8;
}

uint8_t CPU::op_ld_mem_reg(uint8_t &reg_source) {
    auto lo = read_byte_and_inc(pc);
    auto hi = read_byte_and_inc(pc);
    uint16_t address = (hi << 8) + lo;
    mem.write_byte_at(address, reg_a);
    return 16;
}

uint8_t CPU::op_ld_reg_mem(uint8_t &reg_target, uint8_t &address_hi, uint8_t &address_lo) {
    uint16_t address = (address_hi << 8) + address_lo;
    reg_target = mem.read_byte_at(address);
    return 8;
}

uint8_t CPU::op_ld_mem_reg_inc(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_source) {
    uint16_t address = (address_hi << 8) + address_lo;
    mem.write_byte_at(address, reg_source);
    op_inc(address_hi, address_lo);
    return 8;
}

uint8_t CPU::op_ld_mem_reg_dec(uint8_t &address_hi, uint8_t &address_lo, uint8_t &reg_source) {
    uint16_t address = (address_hi << 8) + address_lo;
    mem.write_byte_at(address, reg_source);
    op_dec(address_hi, address_lo);
    return 8;
}

uint8_t CPU::op_ld_reg_mem_inc(uint8_t &reg_target, uint8_t &address_hi, uint8_t &address_lo) {
    uint16_t address = (address_hi << 8) + address_lo;
    reg_target = mem.read_byte_at(address);
    op_inc(address_hi, address_lo);
    return 8;
}

uint8_t CPU::op_ld_reg_mem_dec(uint8_t &reg_target, uint8_t &address_hi, uint8_t &address_lo) {
    uint16_t address = (address_hi << 8) + address_lo;
    reg_target = mem.read_byte_at(address);
    op_dec(address_hi, address_lo);
    return 8;
}

uint8_t CPU::op_inc(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_lo += 1;
    if (reg_lo == 0x00) {
        reg_hi += 1;
    }
    return 8;
}

uint8_t CPU::op_inc_mem(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto addr = (reg_hi << 8) + reg_lo;
    auto val = mem.read_byte_at(addr);
    val += 1;

    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = (val & 0x0F) == 0x00;
    if (val == 0x00) {
        flag_0001_carry = true;
    }

    mem.write_byte_at(addr, val);
    return 12;
}

uint8_t CPU::op_inc(uint16_t &reg) {
    reg += 1;
    return 8;
}

uint8_t CPU::op_inc(uint8_t &reg) {
    reg += 1;

    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = (reg & 0x0F) == 0x00;
    flag_1000_zero = (reg == 0x00);
    return 4;
}

uint8_t CPU::op_dec(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_lo -= 1;
    if (reg_lo == 0xff) {
        reg_hi -= 1;
    }
    return 8;
}

uint8_t CPU::op_dec(uint16_t &reg) {
    reg -= 1;
    return 8;
}


uint8_t CPU::op_dec(uint8_t &reg) {
    reg -= 1;
    flag_0100_bcd_subtract = true;
    flag_0010_bcd_half_carry = (reg & 0x0F) == 0x00;
    flag_1000_zero = (reg == 0x00);
    return 4;
}

uint8_t CPU::op_dec_mem(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto addr = (reg_hi << 8) + reg_lo;
    auto val = mem.read_byte_at(addr);
    val -= 1;

    flag_0100_bcd_subtract = true;
    flag_0010_bcd_half_carry = (val & 0x0F) == 0x00;
    if (val == 0xff) {
        flag_0001_carry = true;
    }

    mem.write_byte_at(addr, val);
    return 12;
}

uint8_t CPU::op_jp_16bit() {
    auto lo = read_byte_and_inc(pc);
    auto hi = read_byte_and_inc(pc);
    pc = (hi << 8) + lo;
    return 16;
}

uint8_t CPU::op_jp_16bit(uint8_t &reg_hi, uint8_t &reg_lo) {
    pc = (reg_hi << 8) + reg_lo;
    return 4;
}

uint8_t CPU::op_jp_nz() {
    return flag_1000_zero ? 12 : op_jp_16bit();
}

uint8_t CPU::op_jp_z() {
    return flag_1000_zero ? op_jp_16bit() : 12;
}

uint8_t CPU::op_jp_nc() {
    return flag_0001_carry ? 12 : op_jp_16bit();
}

uint8_t CPU::op_jp_c() {
    return flag_0001_carry ? op_jp_16bit() : 12;
}

uint8_t CPU::op_jr_z() {
    if (flag_1000_zero) {
        pc += static_cast<int8_t>(read_byte_and_inc(pc));
        return 12;
    }
    return 8;
}

uint8_t CPU::op_jr_c() {
    if (flag_0001_carry) {
        pc += static_cast<int8_t>(read_byte_and_inc(pc));
        return 12;
    }
    return 8;
}

uint8_t CPU::op_jr_nz() {
    if (!flag_1000_zero) {
        pc += static_cast<int8_t>(read_byte_and_inc(pc));
        return 12;
    }
    return 8;
}

uint8_t CPU::op_jr_nc() {
    if (!flag_0001_carry) {
        pc += static_cast<int8_t>(read_byte_and_inc(pc));
        return 12;
    }
    return 8;
}

uint8_t CPU::op_jr() {
    auto delta = static_cast<int8_t>(read_byte_and_inc(pc));
    pc += delta;
    return 12;
}

uint8_t CPU::op_xor(uint8_t &reg) {
    reg_a = reg xor reg_a;
    flag_1000_zero = (reg_a == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = false;
    flag_0001_carry = false;
    return 4;
}

uint8_t CPU::op_xor(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    reg_a = val xor reg_a;
    flag_1000_zero = (reg_a == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = false;
    flag_0001_carry = false;
    return 8;
}

uint8_t CPU::op_xor() {
    auto val = read_byte_and_inc(pc);
    op_xor(val);
    return 8;
}

uint8_t CPU::op_and(uint8_t &reg) {
    reg_a = reg and reg_a;
    flag_1000_zero = (reg_a == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = true;
    flag_0001_carry = false;
    return 4;
}

uint8_t CPU::op_and() {
    auto val = read_byte_and_inc(pc);
    op_and(val);
    return 8;
}

uint8_t CPU::op_and(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    reg_a = val and reg_a;
    flag_1000_zero = (reg_a == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = true;
    flag_0001_carry = false;
    return 8;
}

uint8_t CPU::op_or(uint8_t &reg) {
    reg_a = reg or reg_a;
    flag_1000_zero = (reg_a == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = false;
    flag_0001_carry = false;
    return 4;
}

uint8_t CPU::op_or(uint8_t &reg_hi, uint8_t &reg_lo) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    reg_a = val or reg_a;
    flag_1000_zero = (reg_a == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = false;
    flag_0001_carry = false;
    return 8;
}

uint8_t CPU::op_or() {
    auto val = read_byte_and_inc(pc);
    op_or(val);
    return 8;
}

uint8_t CPU::op_sub(uint8_t &reg, SubMode mode) {
    _op_sub(reg, mode);
    return 4;
}

uint8_t CPU::op_sub_d8(SubMode mode) {
    auto d8 = read_byte_and_inc(pc);
    _op_sub(d8, mode);
    return 8;
}

uint8_t CPU::op_sub(uint8_t &reg_hi, uint8_t &reg_lo, SubMode mode) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    _op_sub(val, mode);
    return 8;
}

void CPU::_op_sub(uint8_t val, SubMode mode) {
    int carry = ((mode == SBC) && flag_0001_carry ? 1 : 0);
    int result = reg_a - val - carry;

    flag_1000_zero = (result == 0x00);
    flag_0100_bcd_subtract = true;
    flag_0010_bcd_half_carry = ((reg_a & 0xf) - (val & 0xf) - carry) & 0x10;
    flag_0001_carry = (result < 0);

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

uint8_t CPU::op_add_d8(AddMode mode) {
    auto d8 = read_byte_and_inc(pc);
    _op_add(d8, mode);
    return 8;
}

uint8_t CPU::op_add(uint8_t &reg_hi, uint8_t &reg_lo, AddMode mode) {
    auto val = mem.read_byte_at((reg_hi << 8) + reg_lo);
    _op_add(val, mode);
    return 8;
}

uint8_t CPU::op_add_16bit(uint8_t &reg1_hi, uint8_t &reg1_lo, uint8_t &reg2_hi, uint8_t &reg2_lo) {
    uint16_t sum_lo = reg1_lo + reg2_lo;
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = (sum_lo > 0xff);

    uint16_t sum_hi = reg1_hi + reg2_hi + (flag_0010_bcd_half_carry ? 1 : 0);
    flag_0001_carry = (sum_hi > 0xff);

    reg1_lo = sum_lo;
    reg1_hi = sum_hi;

    return 8;
}

uint8_t CPU::op_add_sp_s8() {
    flag_1000_zero = false;
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = false; // FIXME: half carry ?

    auto s8 = static_cast<int8_t>(read_byte_and_inc(pc));
    int result = sp + s8;
    if (result > 0xffff) {
        flag_0001_carry = true;
    }
    sp = result;
    return 16;
}

uint8_t CPU::op_add_16bit(uint8_t &reg1_hi, uint8_t &reg1_lo, uint16_t &reg2) {
    auto reg2_lo = static_cast<uint8_t>(reg2);
    auto reg2_hi = static_cast<uint8_t>(reg2 >> 8);
    return op_add_16bit(reg1_hi, reg1_lo, reg2_hi, reg2_lo);
}


void CPU::_op_add(uint8_t val, AddMode mode) {
    int carry = ((mode == ADC) && flag_0001_carry ? 1 : 0);
    int result = reg_a + val + carry;

    flag_1000_zero = (result == 0x00);
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = ((reg_a & 0xf) + (val & 0xf) + carry) & 0x10;
    flag_0001_carry = (result > 0xff);

    switch (mode) {
        case ADD: break;
        case ADC: reg_a = result; break;
    }
}

uint8_t CPU::op_rlca() {
    flag_0001_carry = (reg_a & 0b1000'0000) > 0;
    reg_a = reg_a << 1;
    if (flag_0001_carry) reg_a += 1;
    return 4;
}

uint8_t CPU::op_rla() {
    auto old_carry = flag_0001_carry;
    flag_0001_carry = (reg_a & 0b1000'0000) > 0;
    reg_a = reg_a << 1;
    if (old_carry) reg_a += 1;
    return 4;
}

uint8_t CPU::op_rrca() {
    flag_0001_carry = (reg_a & 1) > 0;
    reg_a = reg_a >> 1;
    if (flag_0001_carry) reg_a += 0b1000'0000;
    return 4;
}

uint8_t CPU::op_rra() {
    auto old_carry = flag_0001_carry;
    flag_0001_carry = (reg_a & 1) > 0;
    reg_a = reg_a >> 1;
    if (old_carry) reg_a += 0b1000'0000;
    return 4;
}

uint8_t CPU::op_daa() {
    flag_0100_bcd_subtract = false;
    auto lo_4 = reg_a & 0x0f;
    auto hi_4 = reg_a >> 4;

    if (lo_4 >= 10) {
        lo_4 -= 10;
        hi_4 += 1;
    }
    if (hi_4 >= 10) {
        hi_4 -= 10;
        flag_0001_carry = true;
    } else {
        flag_0001_carry = false;
    }

    reg_a = (hi_4 << 4) + lo_4;
    flag_1000_zero = (reg_a == 0);

    return 4;
}

uint8_t CPU::op_scf() {
    flag_0100_bcd_subtract = false;
    flag_0010_bcd_half_carry = false;
    flag_0001_carry = true;
    return 4;
}

uint8_t CPU::op_cpl() {
    reg_a = ~reg_a;
    return 4;
}

uint8_t CPU::op_ccf() {
    flag_0010_bcd_half_carry = false;
    flag_0100_bcd_subtract = false;
    flag_0001_carry = !flag_0001_carry;
    return 4;
}

// FIXME: set half carry here?
uint8_t CPU::op_ld_hl_sp_plus_s8() {
    auto s8 = static_cast<int8_t>(read_byte_and_inc(pc));
    auto result = sp + s8;

    if (result > 0xffff) {
        flag_0001_carry = true;
    }

    auto result_16bit = static_cast<uint16_t>(result);

    reg_h = result_16bit >> 8;
    reg_l = static_cast<uint8_t>(result_16bit);
    return 12;
}

uint8_t CPU::op_pop(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_lo = read_byte_and_inc(sp);
    reg_hi = read_byte_and_inc(sp);
    return 12;
}

uint8_t CPU::op_pop(uint16_t &reg) {
    auto reg_lo = read_byte_and_inc(sp);
    auto reg_hi = read_byte_and_inc(sp);
    reg = (reg_hi << 8) + reg_lo;
    return 12;
}

uint8_t CPU::op_pop_af() {
    reg_a = read_byte_and_inc(sp);
    auto flags = read_byte_and_inc(sp);
    flag_1000_zero           = (flags & 0b1000) == 0b1000;
    flag_0100_bcd_subtract   = (flags & 0b0100) == 0b0100;
    flag_0010_bcd_half_carry = (flags & 0b0010) == 0b0010;
    flag_0001_carry          = (flags & 0b0001) == 0b0001;
    return 12;
}

uint8_t CPU::op_push(uint8_t &reg_hi, uint8_t &reg_lo) {
    write_byte_and_dec(sp, reg_hi);
    write_byte_and_dec(sp, reg_lo);
    return 16;
}

uint8_t CPU::op_push(uint16_t &reg) {
    write_byte_and_dec(sp, reg >> 8);
    write_byte_and_dec(sp, reg);
    return 16;
}

uint8_t CPU::op_push_af() {
    uint8_t flags =
            (flag_1000_zero ? 0b1000 : 0) |
            (flag_0100_bcd_subtract ? 0b0100 : 0) |
            (flag_0010_bcd_half_carry ? 0b0010 : 0) |
            (flag_0001_carry ? 0b0001 : 0);

    write_byte_and_dec(sp, flags);
    write_byte_and_dec(sp, reg_a);
    return 16;
}

uint8_t CPU::op_call() {
    auto addr_lo = read_byte_and_inc(pc);
    auto addr_hi = read_byte_and_inc(pc);

    op_push(pc);
    pc = (addr_hi << 8) + addr_lo;
    return 24;
}

uint8_t CPU::op_rst(uint16_t addr) {
    op_push(pc);
    pc = addr;
    return 16;
}

uint8_t CPU::op_ret() {
    op_pop(pc);
    return 16;
}

uint8_t CPU::op_ret_nz() {
    if (!flag_1000_zero) {
        op_ret();
        return 5;
    }
    return 2;
}

uint8_t CPU::op_call_nz() {
    if (!flag_1000_zero) {
        op_call();
        return 6;
    }
    return 3;
}

uint8_t CPU::op_ret_z() {
    if (flag_1000_zero) {
        op_ret();
        return 5;
    }
    return 2;
}

uint8_t CPU::op_call_z() {
    if (flag_1000_zero) {
        op_call();
        return 6;
    }
    return 3;
}

uint8_t CPU::op_ret_nc() {
    if (!flag_0001_carry) {
        op_ret();
        return 5;
    }
    return 2;
}

uint8_t CPU::op_call_nc() {
    if (!flag_0001_carry) {
        op_call();
        return 6;
    }
    return 3;
}

uint8_t CPU::op_ret_c() {
    if (flag_0001_carry) {
        op_ret();
        return 5;
    }
    return 2;
}

uint8_t CPU::op_call_c() {
    if (flag_0001_carry) {
        op_call();
        return 6;
    }
    return 3;
}

uint8_t CPU::op_ei() {
    ime = true;
    return 4;
}

uint8_t CPU::op_di() {
    ime = false;
    return 4;
}

uint8_t CPU::op_reti() {
    ime = true;
    op_ret();
    return 16;
}
