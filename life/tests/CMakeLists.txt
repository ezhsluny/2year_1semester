cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(runTests test_GameOfLife.cpp ../GameOfLife.cpp)

target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(runTests gtest_main pthread)