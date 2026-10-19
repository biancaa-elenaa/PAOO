cmake_minimum_required(VERSION 3.15)
project(Config CXX)

add_executable(ConfigApp main.cpp)

target_link_libraries(ConfigApp PRIVATE MathLib)