#include "../abel/abel_heap.h"
#include "bmp_reader.h"
#include <iostream>
#include <fstream>

#ifndef LABWORK3_BMP_WRITER_H_
#define LABWORK3_BMP_WRITER_H_

void WriteResultToBmp(const Field& field, const std::string& output_path, uint64_t iteration, Colors colors);

#endif //LABWORK3_BMP_WRITER_H_
