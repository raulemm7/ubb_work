cmake_minimum_required(VERSION 3.27)
project(lab02 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab02 main.c
        domain.c
        domain.h
        repository.c
        repository.h
        ui.c
        ui.h
        validator.c
        validator.h
        service.c
        service.h
)
