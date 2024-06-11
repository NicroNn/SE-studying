#include <iostream>
#include "../lib/parser/parser.h"
#include "../lib/abel/abel_heap.h"
#include "../lib/bmp/bmp_writer.h"
#include "../lib/tsv/tsv_reader.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Error: Please provide a filename." << std::endl;
        return EXIT_FAILURE;
    }

    Arguments args;

    ParseArguments(argv, argc, args);

    //std::cout << GetFieldSize(args.input);

    Field field(GetFieldSize(args.input));
    SetStartPoints(field, args.input);
    Simulate(field, args);
}