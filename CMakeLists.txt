cmake_minimum_required(VERSION 3.16)
project(emu_gameboy)

set(CMAKE_CXX_STANDARD 20)

add_executable(emu_gameboy main.cpp cpu.h cpu.cpp mem.h mem.cpp)
