#include <iostream>
#include <cinttypes>

#ifndef LABWORK3_PARSER_H_
#define LABWORK3_PARSER_H_

struct Arguments {
    static const uint8_t kInputArgumentLength = 8;
    static const uint8_t kOutputArgumentLength = 9;
    static const uint8_t kIterationArgumentLength = 11;
    static const uint8_t kFrequencyArgumentLength = 7;
    static const uint8_t kGammaArgumentLength = 8;

    std::string input = "../input/input.tsv";
    std::string output = "../output/";
    std::string gamma = "../gamma/pic.bmp";
    uint64_t iteration_limit = 0;
    uint64_t frequency = 0;
};

void ParseArguments(char* argv[], int argc, Arguments& args);

#endif //LABWORK3_PARSER_H_
