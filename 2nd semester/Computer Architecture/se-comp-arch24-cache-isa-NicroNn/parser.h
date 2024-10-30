#ifndef SE_COMP_ARCH24_CACHE_ISA_NICRONN__PARSER_H_
#define SE_COMP_ARCH24_CACHE_ISA_NICRONN__PARSER_H_
#include <cinttypes>
#include <string>

struct arguments{
    int rep_type = 0;
    std::string path_to_asm = "../main.asm";
    std::string out_filename = "../res.bin";
};

arguments parse (int argc, char* argv[]){
    arguments args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--replacement") {
            args.rep_type = std::stoi(argv[++i]);
        }
        if (arg == "--asm") {
            args.path_to_asm = argv[++i];
        }
        if (arg == "--bin") {
            args.out_filename = argv[++i];
        }
    }

    return args;
}

#endif //SE_COMP_ARCH24_CACHE_ISA_NICRONN__PARSER_H_
