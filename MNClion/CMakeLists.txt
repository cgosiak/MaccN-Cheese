cmake_minimum_required(VERSION 3.3)
project(MNClion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SymbolTable.cpp SymbolTable.h DataEntry.cpp DataEntry.h)
add_executable(MNClion ${SOURCE_FILES})