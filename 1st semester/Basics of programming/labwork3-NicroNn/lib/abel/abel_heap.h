#include <cinttypes>
#include <iostream>
#include "../parser/parser.h"
#include "../bmp/bmp_reader.h"

#ifndef LABWORK3_ABEL_HEAP_H_
#define LABWORK3_ABEL_HEAP_H_

struct Field {
    uint16_t CoordsLimit;  //sqrt(grains) * 0.8
    uint64_t** grid;

    Field(uint16_t limit) : CoordsLimit(limit) {
        grid = new uint64_t* [CoordsLimit];
        for (uint16_t i = 0; i < CoordsLimit; i++) {
            grid[i] = new uint64_t[CoordsLimit]();
        }
    }

    Field(const Field& other) {
        grid = new uint64_t* [CoordsLimit];
        for (uint16_t i = 0; i < CoordsLimit; i++) {
            grid[i] = new uint64_t[CoordsLimit];
            memcpy(grid[i], other.grid[i], CoordsLimit * sizeof(uint64_t));
        }
    }

    ~Field() {
        for (uint16_t i = 0; i < CoordsLimit; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    void ExtendDown() {
        uint16_t newLimit = CoordsLimit * 2;
        uint64_t** newGrid = new uint64_t*[newLimit];

        for (uint16_t i = 0; i < newLimit; ++i) {
            newGrid[i] = new uint64_t[newLimit]();
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            for (uint16_t j = 0; j < CoordsLimit; ++j) {
                newGrid[i][j] = grid[i][j];
            }
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            delete[] grid[i];
        }
        delete[] grid;

        grid = newGrid;
        CoordsLimit = newLimit;
    }

    void ExtendUp() {
        uint16_t newLimit = CoordsLimit * 2;
        uint64_t** newGrid = new uint64_t*[newLimit];

        for (uint16_t i = 0; i < newLimit; ++i) {
            newGrid[i] = new uint64_t[newLimit]();
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            for (uint16_t j = 0; j < CoordsLimit; ++j) {
                newGrid[i + CoordsLimit][j] = grid[i][j];
            }
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            delete[] grid[i];
        }
        delete[] grid;

        grid = newGrid;
        CoordsLimit = newLimit;
    }

    void ExtendRight() {
        uint16_t newLimit = CoordsLimit * 2;
        uint64_t** newGrid = new uint64_t*[newLimit];

        for (uint16_t i = 0; i < newLimit; ++i) {
            newGrid[i] = new uint64_t[newLimit]();
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            for (uint16_t j = 0; j < CoordsLimit; ++j) {
                newGrid[i][j] = grid[i][j];
            }
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            delete[] grid[i];
        }
        delete[] grid;

        grid = newGrid;
        CoordsLimit = newLimit;
    }

    void ExtendLeft() {
        uint16_t newLimit = CoordsLimit * 2;
        uint64_t** newGrid = new uint64_t*[newLimit];

        for (uint16_t i = 0; i < newLimit; ++i) {
            newGrid[i] = new uint64_t[newLimit]();
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            for (uint16_t j = 0; j < CoordsLimit; ++j) {
                newGrid[i][j + CoordsLimit] = grid[i][j];
            }
        }

        for (uint16_t i = 0; i < CoordsLimit; ++i) {
            delete[] grid[i];
        }
        delete[] grid;

        grid = newGrid;
        CoordsLimit = newLimit;
    }

};

void Simulate(Field& field, const Arguments& args);

void PrintGrid(const Field& field);

#endif // LABWORK3_ABEL_HEAP_H_