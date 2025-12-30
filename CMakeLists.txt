cmake_minimum_required(VERSION 3.28)
project(sudokuc C)

set(CMAKE_C_STANDARD 23)

add_executable(sudokuc main.c
        funcs.h
        funcs.c
        list.h
        list.c
        shared.h
)
