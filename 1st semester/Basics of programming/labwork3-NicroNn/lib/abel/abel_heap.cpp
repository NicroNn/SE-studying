#include "abel_heap.h"
#include "../bmp/bmp_writer.h"

void Topple(Field& field, uint16_t x, uint16_t y, const bool fast) {
    if (fast) {
        uint64_t temp_grids = field.grid[x][y] / 4;
        field.grid[x][y] %= 4;

        if (x - 1 >= 0) {
            field.grid[x - 1][y] += temp_grids;
        } else {
            field.ExtendLeft();
            field.grid[x - 1 + field.CoordsLimit][y] += temp_grids;
        }
        if (x + 1 < field.CoordsLimit) {
            field.grid[x + 1][y] += temp_grids;
        } else {
            field.ExtendRight();
            field.grid[x + 1 - field.CoordsLimit][y] += temp_grids;
        }
        if (y - 1 >= 0) {
            field.grid[x][y - 1] += temp_grids;
        } else {
            field.ExtendUp();
            field.grid[x][y - 1 + field.CoordsLimit] += temp_grids;
        }
        if (y + 1 < field.CoordsLimit) {
            field.grid[x][y + 1] += temp_grids;
        } else {
            field.ExtendDown();
            field.grid[x][y + 1 - field.CoordsLimit] += temp_grids;
        }
    } else {
        field.grid[x][y] -= 4;

        if (x - 1 >= 0) {
            ++field.grid[x - 1][y];
        } else {
            field.ExtendLeft();
            ++field.grid[x - 1 + field.CoordsLimit][y];
        }
        if (x + 1 < field.CoordsLimit) {
            ++field.grid[x + 1][y];
        } else {
            field.ExtendRight();
            ++field.grid[x + 1 - field.CoordsLimit][y];
        }
        if (y - 1 >= 0) {
            ++field.grid[x][y - 1];
        } else {
            field.ExtendUp();
            ++field.grid[x][y - 1 + field.CoordsLimit];
        }
        if (y + 1 < field.CoordsLimit) {
            ++field.grid[x][y + 1];
        } else {
            field.ExtendDown();
            ++field.grid[x][y + 1 - field.CoordsLimit];
        }
    }
}


void Simulate(Field& field, const Arguments& args) {
    Colors colors = GetColors(args.gamma);
    bool unstable = true;
    bool fast = false;
    uint64_t iterations = 0;
    while (unstable) {
        unstable = false;
        if (args.frequency == 0) {
            fast = true;
        }
        if (!fast) {
            ++iterations;
        }
        for (int x = 0; x < field.CoordsLimit; ++x) {
            for (int y = 0; y < field.CoordsLimit; ++y) {
                if (field.grid[x][y] > 3) {
                    if (fast) {
                        iterations += field.grid[x][y] / 4;
                    }
                    Topple(field, x, y, fast);

                    if (args.frequency != 0) {
                        if (iterations % args.frequency == 0) {
                            WriteResultToBmp(field, args.output, iterations, colors);
                        }
                    }
                    if (iterations >= args.iteration_limit && args.iteration_limit != 0) {
                        WriteResultToBmp(field, args.output, iterations, colors);
                        return;
                    }
                    unstable = true;
                }
            }
        }
    }
    if (!fast) {
        --iterations;
    }
    WriteResultToBmp(field, args.output, iterations, colors);
}

void PrintGrid(const Field& field) {
    for (int i = 0; i < field.CoordsLimit; ++i) {
        for (int j = 0; j < field.CoordsLimit; ++j) {
            std::cout << field.grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
