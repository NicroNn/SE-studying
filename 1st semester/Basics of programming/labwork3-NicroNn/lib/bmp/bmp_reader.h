#include "../parser/parser.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#ifndef LABWORK3_LIB_BMP_BMP_READER_H_
#define LABWORK3_LIB_BMP_BMP_READER_H_

struct Colors {
    unsigned char color1[3] = {255, 255, 255};
    unsigned char color2[3] = {0, 255, 0};
    unsigned char color3[3] = {255, 255, 0};
    unsigned char color4[3] = {255, 0, 255};
    unsigned char color5[3] = {0, 0, 0};
};

Colors GetColors(const std::string& gamma_file);

#endif //LABWORK3_LIB_BMP_BMP_READER_H_
