#include "bmp_reader.h"

Colors GetColors(const std::string& gamma_file) {
    std::ifstream bmp_file(gamma_file, std::ios::binary);

    bmp_file.seekg(54, std::ios::beg);

    std::unordered_map<unsigned int, int> color_frequency;

    const int pixel_size = 3;
    unsigned char pixel[pixel_size];
    while (bmp_file.read(reinterpret_cast<char*>(pixel), pixel_size)) {
        unsigned int color = (pixel[0] << 16) | (pixel[1] << 8) | pixel[2];
        color_frequency[color]++;
    }

    std::vector<std::pair<unsigned int, int>> color_count_vector;
    for (const auto& entry : color_frequency) {
        color_count_vector.emplace_back(entry.first, entry.second);
    }

    std::sort(color_count_vector.begin(), color_count_vector.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    Colors result;

    if (color_count_vector.size() >= 1) {
        unsigned int color = color_count_vector[0].first;
        result.color1[0] = (color >> 16) & 0xFF;
        result.color1[1] = (color >> 8) & 0xFF;
        result.color1[2] = color & 0xFF;
    }

    if (color_count_vector.size() >= 2) {
        unsigned int color = color_count_vector[1].first;
        result.color2[0] = (color >> 16) & 0xFF;
        result.color2[1] = (color >> 8) & 0xFF;
        result.color2[2] = color & 0xFF;
    }

    if (color_count_vector.size() >= 3) {
        unsigned int color = color_count_vector[2].first;
        result.color3[0] = (color >> 16) & 0xFF;
        result.color3[1] = (color >> 8) & 0xFF;
        result.color3[2] = color & 0xFF;
    }

    if (color_count_vector.size() >= 4) {
        unsigned int color = color_count_vector[3].first;
        result.color4[0] = (color >> 16) & 0xFF;
        result.color4[1] = (color >> 8) & 0xFF;
        result.color4[2] = color & 0xFF;
    }

    if (color_count_vector.size() >= 5) {
        unsigned int color = color_count_vector[4].first;
        result.color5[0] = (color >> 16) & 0xFF;
        result.color5[1] = (color >> 8) & 0xFF;
        result.color5[2] = color & 0xFF;
    }

    /* got colors
    std::cout << unsigned (result.color1[0]) << ' '
              << unsigned (result.color1[1]) << ' '  << unsigned (result.color1[2]) << '\n';
    std::cout << unsigned (result.color2[0]) << ' '
              << unsigned (result.color2[1]) << ' '  << unsigned (result.color2[2]) << '\n';
    std::cout << unsigned (result.color3[0]) << ' '
              << unsigned (result.color3[1]) << ' '  << unsigned (result.color3[2]) << '\n';
    std::cout << unsigned (result.color4[0]) << ' '
              << unsigned (result.color4[1]) << ' '  << unsigned (result.color4[2]) << '\n';
    std::cout << unsigned (result.color5[0]) << ' '
              << unsigned (result.color5[1]) << ' '  << unsigned (result.color5[2]) << '\n';
    */
    return result;
}
