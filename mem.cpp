#include <cstdint>
#include <ios>
#include <iostream>
#include <utility>
#include <fmt/core.h>
#include "mem.h"

Mem::Mem(std::vector<uint8_t> rom): rom(std::move(rom)) {}

uint8_t Mem::read_byte_at(uint16_t address) {
    if (address <= 0x3fff) {
        return rom.at(address);
    } else {
        fmt::print("\thigher address not supported {:#06x}\n", address);
        return 0;
    }
}

void Mem::write_byte_at(uint16_t address, uint8_t value) {
    std::cout << "[unimplemented] write at address" << address << value << static_cast<int>(value) << std::endl;
}
