#include <cinttypes>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../abel/abel_heap.h"

#ifndef LABWORK3_TSV_TSV_READER_H_
#define LABWORK3_TSV_TSV_READER_H_

uint16_t GetFieldSize(std::string& input_file);

void SetStartPoints(Field& field, std::string& input_file);

#endif //LABWORK3_TSV_TSV_READER_H_
