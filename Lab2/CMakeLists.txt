cmake_minimum_required(VERSION 3.15)
project(StaticLib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(library_project)
add_subdirectory(config)