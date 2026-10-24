cmake_minimum_required(VERSION 3.15)
project(BufferLibrary CXX)

add_library(BufferLib STATIC DataBuffer.cpp DataBuffer.h)

target_include_directories(BufferLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)