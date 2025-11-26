cmake_minimum_required(VERSION 3.23)

project(zooperator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(zooperator_lib src/animal.cpp src/bear.cpp src/penguin.cpp src/rabbit.cpp src/exhibit.cpp)

target_include_directories(zooperator_lib PUBLIC include)

target_compile_options(zooperator_lib PRIVATE -Wall -Wextra -pedantic)

add_executable(zooperator src/main.cpp)

target_link_libraries(zooperator PRIVATE zooperator_lib)

enable_testing()
add_subdirectory(test)
