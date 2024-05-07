cmake_minimum_required(VERSION 3.25)

project(GlobalPSO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE main.cpp
    PRIVATE particle.h
    PRIVATE particle.cpp
    PRIVATE swarm.h
    PRIVATE swarm.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
