cmake_minimum_required(VERSION 3.27)
project(lab06)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic" clang-tidy -checks=cppcoreguidelines-*)

add_executable(lab06 main.cpp
        domain.cpp
        domain.h
        repository.cpp
        repository.h
        ui.cpp
        ui.h
        service.cpp
        service.h
        validators.cpp
        validators.h)
