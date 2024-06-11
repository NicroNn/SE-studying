#ifndef LABWORK7_LIB_CONFIG_H_
#define LABWORK7_LIB_CONFIG_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cinttypes>

struct Config {
    std::vector<std::string> cities;
    int frequency = 6000;
    int days = 1;
    uint8_t current_city = 0;
};

Config loadConfig(const std::string& filename);

#endif //LABWORK7_LIB_CONFIG_H_
