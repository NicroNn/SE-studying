#pragma once
#include <cinttypes>
#include <iostream>

struct int2023_t {
  static const uint8_t kNotation = 255;

  static const uint8_t kByteNotation = 8;

  static const uint8_t kLastElementRange = 128;

  static const uint8_t kNumberMaxLength = 253;

  uint8_t _number[kNumberMaxLength]{};
};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_int(int32_t int_32);

int2023_t from_string(const char* buff);

int2023_t operator-(const int2023_t number);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

uint8_t GetLength(const int2023_t& number);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

void ShiftLeft(int2023_t& lhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

bool operator>(const int2023_t& lhs, const int2023_t& rhs);

bool operator<(const int2023_t& lhs, const int2023_t& rhs);

bool operator>=(const int2023_t& lhs, const int2023_t& rhs);

bool operator<=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);
