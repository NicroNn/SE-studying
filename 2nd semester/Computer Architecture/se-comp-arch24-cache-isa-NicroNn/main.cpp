#include "parser.h"
#include "reader.h"
#include "implementations.h"

int main (int argc, char* argv[]) {
    arguments args = parse(argc, argv);

    auto instructions = readFile(args.path_to_asm);

    instructionCaller(instructions);
    translate_to_binary(instructions, args.out_filename);

    if (args.rep_type == 0 | args.rep_type == 2) {
        printf("LRU\thit rate: %3.4f%%\n", memory.getCacheHitRate() * 100);
    }
    if (args.rep_type == 1 | args.rep_type == 2) {
        printf("pLRU\thit rate: %3.4f%%\n", memoryp.getCacheHitRate() * 100);
    }
}
