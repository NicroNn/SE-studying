cmake_minimum_required(VERSION 3.26)
project(wompwomp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp -O2")

add_executable(omp
        main.cpp
        hit.h
        parser.h
)
