add_library(weather
        UI.cpp
        weather.cpp
        config.cpp
        config.h)

target_link_libraries(weather PRIVATE cpr::cpr)
target_link_libraries(weather PRIVATE nlohmann_json::nlohmann_json)
