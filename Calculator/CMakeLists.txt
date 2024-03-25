cmake_minimum_required(VERSION 3.27)
project(laby)

set(CMAKE_CXX_STANDARD 17)

add_executable(laby main.cpp
        Stack_char.h
        Stack_int.h
        Node.h
        Node_int.h
        DynamicArray.h)
