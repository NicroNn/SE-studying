#include "UI.h"

void updateUI(const Config& config){
    system("cls");
    std::cout << "-----------" << config.cities[config.current_city] << "-----------" << '\n';

    std::vector<Day> days = parseDays(config, getWeatherJson(config, getCityJson(config.cities[config.current_city])));
    for (const Day& day : days) {
        printDay(day);
    }
}

std::map<int, std::string> weatherMap{
    {0, "Clear sky"},
    {1, "Mainly clear"},
    {2, "Partly cloudy"},
    {3, "Overcast"},
    {45, "Fog"},
    {48, "Depositing rime fog"},
    {51, "Drizzle: Light intensity"},
    {52, "Drizzle: Moderate intensity"},
    {53, "Drizzle: Dense intensity"},
    {56, "Freezing Drizzle: Light intensity"},
    {57, "Freezing Drizzle: Dense intensity"},
    {61, "Rain: Slight intensity"},
    {63, "Rain: Moderate intensity"},
    {65, "Rain: Heavy intensity"},
    {66, "Freezing Rain: Light intensity"},
    {67, "Freezing Rain: Heavy intensity"},
    {71, "Snow fall: Slight intensity"},
    {73, "Snow fall: Moderate intensity"},
    {75, "Snow fall: Heavy intensity"},
    {77, "Snow grains"},
    {80, "Rain showers: Slight intensity"},
    {81, "Rain showers: Moderate intensity"},
    {82, "Rain showers: Violent intensity"},
    {85, "Snow showers: Slight intensity"},
    {86, "Snow showers: Heavy intensity"},
    {95, "Thunderstorm: Slight or moderate"},
    {96, "Thunderstorm with slight hail"},
    {99, "Thunderstorm with heavy hail"}
};

void printDay(const Day& day){
    std::cout << "===" << day.date << "===" << '\n';
    std::cout << weatherMap[std::stoi(day.weather_type)] << '\n';
    std::cout << "Temperature min: " << day.temp_min << " C" << '\n';
    std::cout << "Temperature max: " << day.temp_max << " C" << '\n';
    std::cout << "\n\n\n";
}
