#include "tsv_reader.h"

uint16_t GetFieldSize(std::string& input_file) {
    std::ifstream file(input_file);

    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return 0;
    }

    std::string line;
    uint64_t max_grains = 0;
    while (std::getline(file, line)) {
        std::istringstream string_stream(line);
        uint16_t x, y;
        uint64_t grains;

        if (!(string_stream >> x >> y >> grains)) {
            std::cerr << "Reading line error" << std::endl;
            break;
        }
        if (grains > max_grains){
            max_grains = grains;
        }

    }
    return std::max(static_cast<uint16_t>(sqrt(max_grains) * 0.8), static_cast<uint16_t>(50));
}

void SetStartPoints(Field& field, std::string& input_file) {
    std::ifstream file(input_file);

    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream string_stream(line);
        uint16_t x, y;
        uint64_t grains;

        if (!(string_stream >> x >> y >> grains)) {
            std::cerr << "Reading line error" << std::endl;
            return;
        }

        bool placedSuccessfully = false;
        while (!placedSuccessfully) {
            uint16_t actualX, actualY;

            if (field.CoordsLimit / 2 + x > field.CoordsLimit) {
                field.ExtendRight();
                actualX = field.CoordsLimit / 4 + x;
                actualY = field.CoordsLimit / 4 + y;
            } else {
                actualX = field.CoordsLimit / 2 + x;
                actualY = field.CoordsLimit / 2 + y;
            }

            if (actualX < field.CoordsLimit && actualY < field.CoordsLimit) {
                field.grid[actualX][actualY] = grains;
                placedSuccessfully = true;
            } else {
                field.ExtendRight();
            }
        }
    }
}
