#ifndef WOMPWOMP_PARSER_H
#define WOMPWOMP_PARSER_H
#include <string>

struct arguments{
    bool isOmp = true;
    bool isDefault = false;
    int threads = 0;
    std::string input_file = "../test_data/in.txt";
    const char *output_file = "../out.txt";
};

arguments parse (int argc, char* argv[]){
    arguments args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--no-omp") {
            args.isOmp = false;
        }
        if (arg == "--omp-threads") {
            std::string threads = argv[++i];
            if (threads == "default") {
                args.isDefault = true;
                continue;
            }
            args.threads = std::stoi(threads);
        }
        if (arg == "--input") {
            args.input_file = argv[++i];
        }
        if (arg == "--output") {
            args.output_file = argv[++i];
        }
    }

    return args;
}

#endif //WOMPWOMP_PARSER_H
