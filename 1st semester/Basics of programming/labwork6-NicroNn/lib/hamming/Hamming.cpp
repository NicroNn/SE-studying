#include "Hamming.h"

std::bitset<12> Hamming::encode(std::bitset<8> data) {
    std::bitset<12> encoded;
    encoded[0] = false;
    encoded[1] = false;
    encoded[3] = false;
    encoded[7] = false;
    encoded[2] = data[0];
    encoded[4] = data[1];
    encoded[5] = data[2];
    encoded[6] = data[3];
    encoded[8] = data[4];
    encoded[9] = data[5];
    encoded[10] = data[6];
    encoded[11] = data[7];
    encoded[7] = encoded[7] ^ encoded[8] ^ encoded[9] ^ encoded[10] ^ encoded[11];
    encoded[3] = encoded[3] ^ encoded[4] ^ encoded[5] ^ encoded[6] ^ encoded[11];
    encoded[1] = encoded[1] ^ encoded[2] ^ encoded[5] ^ encoded[6] ^ encoded[9] ^ encoded[10];
    encoded[0] = encoded[0] ^ encoded[2] ^ encoded[4] ^ encoded[6] ^ encoded[8] ^ encoded[10];

    return encoded;
}

std::bitset<8> Hamming::decode(std::bitset<12>& data) {
    std::bitset<8> decoded;
    bool c0 = data[0] ^ data[2] ^ data[4] ^ data[6] ^ data[8] ^ data[10];
    bool c1 = data[1] ^ data[2] ^ data[5] ^ data[6] ^ data[9] ^ data[10];
    bool c3 = data[3] ^ data[4] ^ data[5] ^ data[6] ^ data[11];
    bool c7 = data[7] ^ data[8] ^ data[9] ^ data[10] ^ data[11];

    int error_position = c0 + c1 * 2 + c3 * 4 + c7 * 8;
    if (0 > error_position || error_position > 12) {
        std::cerr << "Impossible to fix error.";
        return decoded;
    }
    if (error_position != 0) {
        data.flip(error_position - 1);
    }
    decoded[0] = data[2];
    decoded[1] = data[4];
    decoded[2] = data[5];
    decoded[3] = data[6];
    decoded[4] = data[8];
    decoded[5] = data[9];
    decoded[6] = data[10];
    decoded[7] = data[11];

    return decoded;
}
