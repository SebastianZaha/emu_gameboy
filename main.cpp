#include <iostream>
#include <vector>
#include <fstream>
#include "constants.h"
#include "cpu.h"
#include "mem.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please provide a ROM file to run" << std::endl;
        exit(1);
    }

    auto const filename = argv[1];

    std::vector<std::string> flags(argv + 2, argv + argc);

    for (std::string& flag : flags) {
        // if (flag == "--debug") { cliOptions.options.debugger = true; }
    }


    // read bytes in rom file
    std::ifstream input( filename, std::ios::binary );
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    std::cout << "Read " << buffer.size() /1024 << " KB from " << filename << "\n";

    std::string title(buffer.begin() + CH_TITLE, buffer.begin() + CH_TITLE_END);
    std::cout << "TITLE: " << title << "\n";

    int ram_size =  buffer.at(CH_RAM_SIZE);
    std::cout << "RAM SIZE: " << std::hex << ram_size << "\n";
    std::cout << "ROM SIZE: " << std::hex << static_cast<int>(buffer.at(CH_ROM_SIZE)) << "\n";
    std::cout << "TYPE: " << std::hex << static_cast<int>(buffer.at(CH_TYPE)) << "\n";
    std::cout << "DESTINATION (JP=0h): " << std::hex << static_cast<int>(buffer.at(CH_DESTINATION_CODE)) << "\n";

    for (auto i = 0; i < std::size(LOGO); i++) {
        if (buffer.at(CH_LOGO + i) != LOGO[i]) {
            std::cout << "Error in logo at byte " << i << std::endl;
            exit(1);
        }
    }

    Mem mem(buffer);
    CPU cpu(mem);

    int total_cycles = 0;

    for (int i = 0; i < 20; ++i) {
        total_cycles += cpu.tick();
    }
    std::cout << "ran for " << total_cycles << " cycles" << std::endl;


    return 0;
}
