cmake_minimum_required(VERSION 3.27)
project(lab06)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic" clang-tidy -checks=cppcoreguidelines-*)

add_executable(Lab06_7 main.cpp domain.cpp domain.h repo.cpp repo.h service.cpp service.h UI.cpp UI.h tests.cpp tests.h vector_man.cpp vector_man.h recipe_class.cpp recipe_class.h undo_act.h)
