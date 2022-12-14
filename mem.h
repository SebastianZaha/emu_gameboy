#pragma once

#include <array>
#include <vector>

class Mem {

public:
    explicit Mem(std::vector<uint8_t> rom);
    uint8_t read_byte_at(uint16_t address);

    void write_byte_at(uint16_t address, uint8_t value);

private:
    std::vector<uint8_t> rom;
    std::array<uint8_t, 64 * 1024> addressable;
};
