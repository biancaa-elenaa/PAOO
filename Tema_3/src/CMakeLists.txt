cmake_minimum_required(VERSION 3.15)
project(SrcApp CXX)

add_executable(Src main.cpp)
target_link_libraries(Src PRIVATE BufferLib)