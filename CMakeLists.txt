cmake_minimum_required(VERSION 4.1)
project(Proiect_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proiect_1 main.cpp
        materials.h
        providers.h
        materials.cpp
        providers.cpp
        inventory.h
        inventory.cpp
        transactions.h
        transactions.cpp
        utils.h
        exceptions.h
        menu.h
        menu.cpp
        repository.h
        transaction_factory.h
        stock_observer.h
)