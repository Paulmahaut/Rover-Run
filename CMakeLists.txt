cmake_minimum_required(VERSION 3.27)
project(Rover_Run C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Rover_Run
        loc.c
        loc.h
        main.c
        map.c
        map.h
        moves.c
        moves.h
        queue.c
        queue.h
        stack.c
        stack.h
        tree.h
        tree.c)
