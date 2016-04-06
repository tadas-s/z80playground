cmake_minimum_required(VERSION 2.8)
project(z80playground)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic")

set(SOURCE_FILES main.c)
add_executable(z80playground ${SOURCE_FILES})
target_link_libraries(z80playground z80ex ncurses)
