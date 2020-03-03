cmake_minimum_required(VERSION 3.15)
project(Casino C)

set(CMAKE_C_STANDARD 99)

add_executable(Casino main.c casino.h structures.h casino.c data.h)