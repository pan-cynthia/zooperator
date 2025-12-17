option(ENABLE_COVERAGE "Enable code coverage flags" OFF)
cmake_minimum_required(VERSION 3.23)

project(zooperator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(zooperator_lib src/animal.cpp src/bear.cpp src/penguin.cpp src/rabbit.cpp src/exhibit.cpp src/zoo.cpp src/player.cpp src/game.cpp src/elephant.cpp src/lion.cpp src/monkey.cpp src/tortoise.cpp src/MissionSystem.cpp)

target_include_directories(zooperator_lib PUBLIC include)

target_compile_options(zooperator_lib PRIVATE -Wall -Wextra -pedantic)

add_executable(zooperator src/main.cpp)

target_link_libraries(zooperator PRIVATE zooperator_lib)

enable_testing()
add_subdirectory(test)

option(ENABLE_COVERAGE "Enable code coverage flags" OFF)
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Enabling coverage flags")

    # Flags for compilation (Note the separate quotes for each flag)
    set(COVERAGE_COMPILE_FLAGS "-O0" "-g" "-fprofile-instr-generate" "-fcoverage-mapping")

    # Flags for linking
    set(COVERAGE_LINK_FLAGS "-fprofile-instr-generate")

    foreach(tgt zooperator_lib zooperator zooperator_tests)
        target_compile_options(${tgt} PRIVATE ${COVERAGE_COMPILE_FLAGS})
        target_link_options(${tgt} PRIVATE ${COVERAGE_LINK_FLAGS})
    endforeach()
endif()
