cmake_minimum_required(VERSION 3.15)
project(ChatServer C)

set(CMAKE_C_STANDARD 99)

add_executable(ChatServer main.c source.c header.h data.h)