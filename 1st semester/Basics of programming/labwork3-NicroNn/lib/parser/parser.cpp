#include "parser.h"

bool IsDigit(const std::string& num) {
    for (char i : num) {
        if (!std::isdigit(i)) {
            return false;
        }
    }
    return true;
}

void ParseArguments(char* argv[], int argc, Arguments& args) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-i") {
            args.input = argv[++i];
        }
        if (arg == "-o") {
            args.output = argv[++i];
        }
        if (arg == "-g") {
            args.gamma = argv[++i];
        }
        if (arg == "-m") {
            if (IsDigit(argv[++i])) {
                args.iteration_limit = std::stoi(argv[i]);
            } else {
                std::cout << "No iteration limit specified, default value will be used\n";
            }
        }
        if (arg == "-f") {
            if (IsDigit(argv[++i])) {
                args.frequency = std::stoi(argv[i]);
            } else {
                std::cout << "No frequency specified, default value will be used\n";
            }
        }

        if (arg.substr(0, Arguments::kInputArgumentLength) == "--input=") {
            args.input = arg.substr(Arguments::kInputArgumentLength);
        }
        if (arg.substr(0, Arguments::kOutputArgumentLength) == "--output=") {
            args.output = arg.substr(Arguments::kOutputArgumentLength);
        }
        if (arg.substr(0, Arguments::kOutputArgumentLength) == "--gamma=") {
            args.gamma = arg.substr(Arguments::kGammaArgumentLength);
        }
        if (arg.substr(0, Arguments::kIterationArgumentLength) == "--max-iter=") {
            args.iteration_limit = std::stoi(arg.substr(Arguments::kIterationArgumentLength));
        }
        if (arg.substr(0, Arguments::kFrequencyArgumentLength) == "--freq=") {
            args.frequency = std::stoi(arg.substr(Arguments::kFrequencyArgumentLength));
        }
    }
}
