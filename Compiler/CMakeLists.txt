cmake_minimum_required(VERSION 3.3)
project(Final_Compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SymbolTable.cpp SymbolTable.h)
add_executable(Final_Compiler ${SOURCE_FILES})