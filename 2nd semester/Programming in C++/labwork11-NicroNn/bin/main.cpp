#include "lib/index.h"
#include "lib/search.h"
#include "lib/parser.h"

int main(int argc, char* argv[]) {
    arguments args = parse(argc, argv);

    if (args.isIndex) {
        fs::path directory = args.directory;
        std::string outputFilePath = args.path_to_index;

        std::vector<File> files;
        std::unordered_map<std::string, std::unordered_map<int, double>> index;

        traverseDirectory(directory, files, index);

        saveIndex(files, index, outputFilePath);
    }
    if (args.isSearch) {
        std::vector<std::string> files;
        std::unordered_map<std::string, std::vector<std::pair<double, int>>> index;
        std::string query;

        std::cout << "Enter your query:\n";
        std::cin >> query;

        search(args.path_to_index, files, index, query);
    }

    return 0;
}

