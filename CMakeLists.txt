cmake_minimum_required(VERSION 4.1)
project(Proiect_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proiect_1 main.cpp
        materials.h
        providers.h
        orders.h
        materials.cpp
        providers.cpp
        orders.cpp
        inventory.h
        inventory.cpp
)