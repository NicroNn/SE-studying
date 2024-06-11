#include "weather.h"

json getCityJson(const std::string& city){
    cpr::Response city_r = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                    cpr::Parameters{{"name", city}},
                                    cpr::Header{{"X-Api-Key", "p904TQDnLWSNIUWEyRzWZw==5z2i7pqZJIVsCcQn"}});
    json city_json = json::parse(city_r.text);
    if (city_r.status_code != 200 || city_r.text == "[]"){
        std::cerr << "Api-ninja response error\nProgramm will be closed";
        Sleep(2000);
        std::exit(EXIT_FAILURE);
    }

    return city_json;
}

json getWeatherJson(const Config& config, json city_json){
    cpr::Response weather_r = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                       cpr::Parameters{{"latitude", city_json[0]["latitude"].dump()},
                                                       {"longitude", city_json[0]["longitude"].dump()},
                                                       {"forecast_days", std::to_string(config.days)},
                                                       {"daily", "temperature_2m_max"},
                                                       {"daily", "temperature_2m_min"},
                                                       {"daily", "weather_code"}});
    json weather_json = json::parse(weather_r.text);
    if (weather_r.status_code != 200 || weather_r.text == "[]"){
        std::cerr << "Weather response error\nProgramm will be closed";
        Sleep(2000);
        std::exit(EXIT_FAILURE);
    }

    return weather_json;
}

std::vector<Day> parseDays(const Config& config, json weather_json){
    std::vector<Day> result;
    for (int i = 0; i < config.days; ++i) {
        Day new_day;
        new_day.date = weather_json["daily"]["time"][i].dump();
        new_day.weather_type = weather_json["daily"]["weather_code"][i].dump();
        new_day.temp_min = weather_json["daily"]["temperature_2m_min"][i].dump();
        new_day.temp_max = weather_json["daily"]["temperature_2m_max"][i].dump();
        result.push_back(new_day);
    }

    return result;
}


