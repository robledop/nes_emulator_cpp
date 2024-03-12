cmake_minimum_required(VERSION 3.27)
project(nes_emulator_cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)

add_executable(nes_emulator_cpp main.cpp
        cpu.cpp
        cpu.h
        PPU.cpp
        PPU.h
        Controller.cpp
        Controller.h
        NES.cpp
        NES.h)
target_link_libraries(nes_emulator_cpp ${SDL2_LIBRARIES})
