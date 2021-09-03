cmake_minimum_required(VERSION 3.10)

project(edi C CXX)
include(Dart)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/lib/grafolistaadj)
add_subdirectory(src/lib/grafomatadj)
add_subdirectory(src/lib/grafonavegacao)
add_subdirectory(src/lib/grafomenorcaminho)
add_subdirectory(src/lib/grafomst)

add_executable(main src/main.cpp src/lib/grafomst/grafomst.cpp)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)
