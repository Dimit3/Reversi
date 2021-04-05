cmake_minimum_required(VERSION 3.14)
project(PROJETOOO C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PROJETOOO
        Auxiliares.c
        Auxiliares.h
        estado.c
        estado.h
        main.c
        Printas.c
        Printas.h)
