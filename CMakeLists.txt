cmake_minimum_required(VERSION 3.10)


project(Graph VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")


set(CMAKE_CXX_STANDARD 11)


# --------------------------------------------
include_directories(include)

add_executable(graph ./src/graph.cpp)

