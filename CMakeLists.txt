cmake_minimum_required(VERSION 3.27)
project(nes_emulator)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)

include_directories(nes_emulator)

add_executable(nes_emulator nes_emulator/main.cpp
        nes_emulator/cpu.cpp
        nes_emulator/cpu.h
        nes_emulator/PPU.cpp
        nes_emulator/PPU.h
        nes_emulator/Controller.cpp
        nes_emulator/Controller.h
        nes_emulator/NES.cpp
        nes_emulator/NES.h)
set_property(TARGET nes_emulator PROPERTY ENABLE_EXPORTS 1)
target_link_libraries(nes_emulator ${SDL2_LIBRARIES})

add_subdirectory(tests)
