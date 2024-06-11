#ifndef LABWORK7_LIB_WEATHER_H_
#define LABWORK7_LIB_WEATHER_H_
#include "config.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

json getCityJson(const std::string& city);

json getWeatherJson(const Config& config, json city_json);

struct Day{
    std::string date;
    std::string weather_type;
    std::string temp_min;
    std::string temp_max;
};

std::vector<Day> parseDays(const Config& config, json weather_json);

#endif //LABWORK7_LIB_WEATHER_H_
