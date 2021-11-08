#include <cstdint>
#include <ios>
#include <iostream>
#include "mem.h"

uint8_t Mem::read_byte_at(uint16_t address) {
    std::cout << "reading byte at address: " << std::hex << address << std::endl;
    return buffer.at(address);
}

void Mem::write_byte_at(uint16_t address, uint8_t value) {
    buffer.at(address) = value;
}
