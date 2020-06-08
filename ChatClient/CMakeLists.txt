cmake_minimum_required(VERSION 3.15)
project(ChatClient C)

set(CMAKE_C_STANDARD 99)

add_executable(ChatClient main.c header.h source.c)