cmake_minimum_required(VERSION 3.0.0)
project(labwork3 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(labwork3 bin/main.cpp
        lib/parser/parser.cpp
        lib/parser/parser.h
        lib/bmp/bmp_writer.cpp
        lib/bmp/bmp_writer.h
        lib/bmp/bmp_reader.cpp
        lib/bmp/bmp_reader.h
        lib/abel/abel_heap.cpp
        lib/abel/abel_heap.h
        lib/tsv/tsv_reader.cpp
        lib/tsv/tsv_reader.h)