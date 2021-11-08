mkdir -p build/default && cd build/default
cmake -GNinja ../..
ninja && ./emu_gameboy <path to rom>
