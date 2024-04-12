cmake_minimum_required(VERSION 3.27)
project(project_istvan)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_istvan main.cpp
        definedVector.h
        domain.h
        Pet.cpp
        Pet.h
        domain.cpp)
