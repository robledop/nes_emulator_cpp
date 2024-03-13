project(tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run lda_tests.cpp)

target_link_libraries(Google_Tests_run nes_emulator)

target_link_libraries(Google_Tests_run gtest gtest_main)