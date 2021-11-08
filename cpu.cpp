
#include <iostream>
#include "cpu.h"

uint8_t CPU::tick() {

    auto opcode = read_byte_pc();
    std::cout << "got opcode " << std::hex << static_cast<int>(opcode) << std::endl;
    switch (opcode) {
        case 0x00: return 4; // nop
        case 0x01: return op_ld_word(reg_b, reg_c);
        case 0x02: return op_ld_mem_reg(reg_b, reg_c, reg_a);
        case 0x03: return op_inc(reg_b, reg_c);
        case 0x04: return op_inc(reg_b);
        case 0x05: return op_dec(reg_b);
        case 0x06: return op_ld_byte(reg_b);
        default:
            std::cout << "opcode " << std::hex << opcode << " unimplemented. NOOP" << std::endl;
            return 4; // noop / unimplemented
    }

    return 0;
}

uint8_t CPU::read_byte_pc() {
    auto b = mem.read_byte_at(pc);
    pc += 1;
    return b;
}

uint8_t CPU::op_ld_word(uint8_t &reg_hi, uint8_t &reg_lo) {
    reg_hi = read_byte_pc();
    reg_lo = read_byte_pc();
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

    if (reg == 0x00) {
        flag_carry = true;
    }
    flag_bcd_half_carry = (reg & 0x0F) == 0x00;
    flag_bcd_subtract = false;
    return 4;
}

uint8_t CPU::op_dec(uint8_t &reg) {
    reg -= 1;

    if (reg == 0xFF) {
        flag_carry = true;
    }
    flag_bcd_half_carry = (reg & 0x0F) == 0x00;
    flag_bcd_subtract = true;
    return 4;
}
