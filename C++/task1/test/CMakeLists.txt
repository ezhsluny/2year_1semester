cmake_minimum_required(VERSION 3.8)

set(This circ_buff_tests)

set(Sources
    circ_buff_test.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    circ_buff
)

add_test(
    NAME ${This}
    COMMAND ${This}
)