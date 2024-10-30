cmake_minimum_required(VERSION 3.26)
project(se_comp_arch24_cache_isa_NicroNn)

set(CMAKE_CXX_STANDARD 20)

add_executable(se_comp_arch24_cache_isa_NicroNn
        main.cpp
        parser.h
        implementations.h
        reader.h
        instructions.h
        cache.h
        system.h)
