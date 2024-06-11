#ifndef LABWORK6_LIB_HAMMING_HAMMING_H_
#define LABWORK6_LIB_HAMMING_HAMMING_H_
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
class Hamming {
  public:
    static std::bitset<12> encode(std::bitset<8> data);
    static std::bitset<8> decode(std::bitset<12>& data);
};

#endif //LABWORK6_LIB_HAMMING_HAMMING_H_
