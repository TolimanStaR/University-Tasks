cmake_minimum_required(VERSION 3.15)
project(Dict C)

set(CMAKE_C_STANDARD 99)

add_executable(Dict main.c dict.c dict.h structures.h)