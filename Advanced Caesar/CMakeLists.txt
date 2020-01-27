cmake_minimum_required(VERSION 3.15)
project(Caesar C)

set(CMAKE_C_STANDARD 99)

add_executable(Caesar main.c file.c file.h caesar.c caesar.h)