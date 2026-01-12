cmake_minimum_required(VERSION 3.5)

set(This circ_buff)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)

set(Headers
    circ_buff.hpp
)
set(Sources
    circ_buff.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})