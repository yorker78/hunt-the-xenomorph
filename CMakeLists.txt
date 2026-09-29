cmake_minimum_required(VERSION 3.27)
project(hunt_the_xenomorph)

set(CMAKE_CXX_STANDARD 14)

add_executable(hunt_the_xenomorph
        item.h
        item.cpp
        room.h
        room.cpp
        gamecontroller.h
        gamecontroller.cpp
        main.cpp
        character.h
        character.cpp
        command.h
        command.cpp
)
