#pragma once

#include <array>

class Mem {

public:
    uint8_t read_byte_at(uint16_t address);

    void write_byte_at(uint16_t address, uint8_t value);

private:
    std::array<uint8_t, 32 * 1024> buffer;
};
