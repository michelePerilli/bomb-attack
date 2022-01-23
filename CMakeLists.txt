cmake_minimum_required(VERSION 3.19)
project(Bomb_Attack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bomb_Attack
        Bomb.cpp
        Bomb.h
        Casa.cpp
        Casa.h
        Collider.cpp
        Collider.h
        main.cpp)
