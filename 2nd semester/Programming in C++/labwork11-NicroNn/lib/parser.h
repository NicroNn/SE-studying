#ifndef LABWORK11_LIB_PARSER_H_
#define LABWORK11_LIB_PARSER_H_
#include <string>
struct arguments{
    bool isIndex = false;
    bool isSearch = false;
    std::string path_to_index = "../../index.txt";
    std::string directory = "../../";
};

arguments parse (int argc, char* argv[]){
    arguments args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--index") {
            args.isIndex = true;
        }
        if (arg == "--search") {
            args.isSearch = true;
        }
        if (arg == "--ipath") {
            args.path_to_index = argv[++i];
        }
        if (arg == "--directory") {
            args.directory = argv[++i];
        }
    }

    return args;
}
#endif //LABWORK11_LIB_PARSER_H_
