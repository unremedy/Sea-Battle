cmake_minimum_required(VERSION 3.19)
project(Ships)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ships main.cpp AddShipsComputer.cpp Constants.h ShipsComputer.h AllFunc.h ShipsUser.h)