cmake_minimum_required(VERSION 3.6)
project(Linker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp linker.h)
add_executable(Linker ${SOURCE_FILES} linker.h)