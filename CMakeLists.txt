cmake_minimum_required(VERSION 3.23)

project(zooperator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(zooperator src/main.cpp src/animal.cpp)

target_include_directories(zooperator PRIVATE include src)

target_compile_options(zooperator PRIVATE -Wall -Wextra -pedantic)
