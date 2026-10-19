cmake_minimum_required(VERSION 3.15)
project(MathLibrary CXX)

add_library(MathLib STATIC math_utils.cpp math_utils.h)

target_include_directories(MathLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)