#include "config.h"


Config loadConfig(const std::string& filename) {
    Config config;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, ':')) {
            if (key == "cities") {
                std::string cities;
                if (std::getline(iss, cities)) {
                    std::istringstream cityStream(cities);
                    std::string city;
                    while (std::getline(cityStream, city, ',')) {
                        config.cities.push_back(city);
                    }
                }
            } else if (key == "frequency") {
                iss >> config.frequency;
            } else if (key == "days") {
                iss >> config.days;
            }
        }
    }
    return config;
}
