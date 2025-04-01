cmake_minimum_required(VERSION 3.26)
project(DFAtoRE)

set(CMAKE_CXX_STANDARD 17)

add_executable(DFAtoRE main.cpp
        DFA.cpp
        DFA.h
        State.cpp
        State.h
        RE.cpp
        RE.h)
