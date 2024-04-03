cmake_minimum_required(VERSION 3.27)
project(lab03 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_C_STANDARD 23)

add_executable(lab03 main.c
        ui.c
        ui.h
        domain.c
        domain.h
        service.c
        service.h
        repository.c
        repository.h
        validator.c
        validator.h
        sort.c
        sort.h)
