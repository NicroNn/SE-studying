#include "number.h"
#include <cstring>
#include <string>

int2023_t from_int(int32_t int_32) {
  int2023_t number;
  uint8_t pointer = int2023_t::kNumberMaxLength - 1;
  bool is_negative = int_32 < 0;
  if (is_negative) {
    int_32 = -int_32;
    number._number[0] = 0;
  }
  while (int_32 >= int2023_t::kNotation) {
    number._number[pointer] += int_32 & int2023_t::kNotation;  // % 256
    int_32 >>= int2023_t::kByteNotation;  // /= 256
    if (pointer == 0 && int_32 != 0) {
      static_assert(true, "Overflow");
    }
    --pointer;
  }
  if (pointer != 0 || is_negative) {
    number._number[pointer] = int_32;
  } else {
    number._number[pointer] = int_32 + int2023_t::kLastElementRange;
  }
  if (!is_negative && number._number[0] == 0) {
    number._number[0] = int2023_t::kLastElementRange;
  }
  return number;
}

int2023_t from_string(const char* buff) {
  int2023_t result;
  uint16_t string_length = std::strlen(buff);
  bool is_negative = false;
  int2023_t scale = from_int(1);
  for (int characterIndex = string_length - 1; characterIndex >= 0; --characterIndex) {
    if (buff[characterIndex] == '-') {
      is_negative = true;
      break;
    }
    result = result + from_int(buff[characterIndex] - '0') * scale;  //-'0' to get int from char
    scale = scale * from_int(10);
  }

  if (is_negative) {
    result._number[0] -= int2023_t::kLastElementRange;
  }

  return result;
}

int2023_t operator-(const int2023_t number) {
  int2023_t result = number;
  if (result._number[0] < int2023_t::kLastElementRange) {
    result._number[0] += int2023_t::kLastElementRange;
  } else {
    result._number[0] -= int2023_t::kLastElementRange;
  }

  return result;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t result;

  if (lhs._number[0] >= int2023_t::kLastElementRange && rhs._number[0] < int2023_t::kLastElementRange) {
    return lhs - (-rhs);
  }
  if (lhs._number[0] < int2023_t::kLastElementRange && rhs._number[0] >= int2023_t::kLastElementRange) {
    return rhs - (-lhs);
  }

  uint8_t addition = 0;
  for (int digit_index = int2023_t::kNumberMaxLength - 1; digit_index > 0; --digit_index) {
    result._number[digit_index] = (lhs._number[digit_index] + rhs._number[digit_index] + addition) &
        int2023_t::kNotation;
    if (lhs._number[digit_index] + rhs._number[digit_index] + addition > int2023_t::kNotation) {
      addition = 1;
    } else {
      addition = 0;
    }
  }

  uint8_t digit1 = lhs._number[0], digit2 = rhs._number[0];
  if (lhs._number[0] >= int2023_t::kLastElementRange && rhs._number[0] >= int2023_t::kLastElementRange) {
    if (digit1 + digit2 - int2023_t::kLastElementRange + addition < 2 * int2023_t::kLastElementRange) {
      digit1 = lhs._number[0] - int2023_t::kLastElementRange;
    } else {
      static_assert(true, "Overflow");
    }
    result._number[0] = digit1 + digit2 + addition;
  } else {
    if (digit1 + digit2 + addition < int2023_t::kLastElementRange) {
      result._number[0] = digit1 + digit2 + addition;
    } else {
      static_assert(true, "Overflow");
    }
  }

  return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t result;

  if (lhs._number[0] >= int2023_t::kLastElementRange && rhs._number[0] < int2023_t::kLastElementRange) {
    return lhs + (-rhs);
  }
  if (lhs._number[0] < int2023_t::kLastElementRange && rhs._number[0] >= int2023_t::kLastElementRange) {
    return lhs + (-rhs);
  }
  if (lhs._number[0] < int2023_t::kLastElementRange && rhs._number[0] < int2023_t::kLastElementRange) {
    return -rhs - (-lhs);
  }
  if (lhs < rhs) {
    return -(rhs - lhs);
  }

  uint8_t subtraction = 0;
  for (int digit_index = int2023_t::kNumberMaxLength - 1; digit_index > 0; --digit_index) {
    if (rhs._number[digit_index] + subtraction > lhs._number[digit_index]) {
      result._number[digit_index] = int2023_t::kNotation + 1 - rhs._number[digit_index] - subtraction +
          lhs._number[digit_index];
      subtraction = 1;
    } else {
      result._number[digit_index] = lhs._number[digit_index] - rhs._number[digit_index] - subtraction;
      subtraction = 0;
    }

  }
  result._number[0] = lhs._number[0] - rhs._number[0] - subtraction + int2023_t::kLastElementRange;

  return result;
}

uint8_t GetLength(const int2023_t& number) {
  uint8_t length = 0;
  bool is_number_begin = false;
  if (number._number[0] != 0 && number._number[0] != int2023_t::kLastElementRange) {
    return int2023_t::kNumberMaxLength;
  }
  for (int i = 1; i < int2023_t::kNumberMaxLength; ++i) {
    if (!is_number_begin) {
      if (number._number[i] == 0) {
        continue;
      }
      is_number_begin = true;
    }
    ++length;
  }
  return length;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t result;

  uint8_t addition = 0;
  for (int first_digit_index = int2023_t::kNumberMaxLength - 1; first_digit_index > 0; --first_digit_index) {
    for (int second_digit_index = int2023_t::kNumberMaxLength - 1; second_digit_index > 0; --second_digit_index) {
      uint8_t result_index = int2023_t::kNumberMaxLength - 1 - (int2023_t::kNumberMaxLength - first_digit_index - 1) -
          (int2023_t::kNumberMaxLength - second_digit_index - 1);
      result._number[result_index] += (lhs._number[first_digit_index] * rhs._number[second_digit_index] + addition)
          & int2023_t::kNotation;
      if (result._number[result_index] < ((lhs._number[first_digit_index] * rhs._number[second_digit_index] + addition)
      & int2023_t::kNotation)) {
        addition = 1 + ((lhs._number[first_digit_index] *
            rhs._number[second_digit_index] + addition) >> int2023_t::kByteNotation);
      } else {
        addition = (lhs._number[first_digit_index] *
            rhs._number[second_digit_index] + addition) >> int2023_t::kByteNotation;
      }
    }
  }

  if (lhs._number[0] >= int2023_t::kLastElementRange && rhs._number[0] >= int2023_t::kLastElementRange) {
    if ((lhs._number[0] - int2023_t::kLastElementRange) * (rhs._number[0] - int2023_t::kLastElementRange) + addition <
        int2023_t::kLastElementRange) {
      result._number[0] = (lhs._number[0] - int2023_t::kLastElementRange) *
          (rhs._number[0] - int2023_t::kLastElementRange) + addition + int2023_t::kLastElementRange;
    } else {
      static_assert(true, "Overflow");
    }
  } else if (lhs._number[0] < int2023_t::kLastElementRange && rhs._number[0] < int2023_t::kLastElementRange) {
    if (lhs._number[0] * rhs._number[0] + addition < int2023_t::kLastElementRange) {
      result._number[0] = lhs._number[0] * rhs._number[0] + addition + int2023_t::kLastElementRange;
    } else {
      static_assert(true, "Overflow");
    }
  } else {
    if ((std::max(lhs._number[0], rhs._number[0]) - int2023_t::kLastElementRange) *
        std::min(lhs._number[0], rhs._number[0]) + addition) {
      result._number[0] = (std::max(lhs._number[0], rhs._number[0]) - int2023_t::kLastElementRange) *
          std::min(lhs._number[0], rhs._number[0]) + addition;
    } else {
      static_assert(true, "Overflow");
    }
  }

  return result;
}

int2023_t Abs(const int2023_t number){
  int2023_t result = number;
  if (number._number[0] < int2023_t::kLastElementRange){
    result._number[0] += int2023_t::kLastElementRange;
  }
  return result;
}

void ShiftLeft(int2023_t& lhs){
  if (lhs._number[0] != 0 && lhs._number[0] != int2023_t::kLastElementRange){
    static_assert(true, "Overflow");
  }
  lhs._number[0] = lhs._number[0];
  for (int i = 2; i < int2023_t::kNumberMaxLength; ++i) {
    lhs._number[i - 1] = lhs._number[i];
  }
  lhs._number[int2023_t::kNumberMaxLength - 1] = 0;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t result = from_int(0);
  if ((lhs._number[0] < int2023_t::kLastElementRange) && (rhs._number[0] >= int2023_t::kLastElementRange) ||
      (lhs._number[0] >= int2023_t::kLastElementRange) && (rhs._number[0] < int2023_t::kLastElementRange)) {
    result = Abs(lhs) / Abs(rhs);
    if (result == from_int(0)){
      return result;
    } else {
      return -result;
    }
  }
  if (lhs < rhs) {
    return from_int(0);
  }
  if (rhs == from_int(1)) {
    return lhs;
  }
  if (lhs == rhs){
    return from_int(1);
  }

  int2023_t temp_dividend = lhs, temp_divisor = rhs, division_scale = from_int(1);

  while (GetLength(temp_dividend) - 1 > GetLength(temp_divisor)) {
    ShiftLeft(temp_divisor);
    ShiftLeft(division_scale);
  }

  while (temp_dividend > temp_divisor) {
    temp_dividend = temp_dividend - temp_divisor;
    result = result + division_scale;
  }

  if (temp_divisor != rhs) {
    result = result + (temp_dividend / rhs);
  }

  return result;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
  for (int digit_index = 0; digit_index < int2023_t::kNumberMaxLength; ++digit_index) {
    if (lhs._number[digit_index] != rhs._number[digit_index]) {
      return false;
    }
  }

  return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
  return !(lhs == rhs);
}

bool operator>(const int2023_t& lhs, const int2023_t& rhs) {
  for (int digit_index = 0; digit_index < int2023_t::kNumberMaxLength; ++digit_index) {
    if (lhs._number[digit_index] < rhs._number[digit_index]) {
      return false;
    }
    if (lhs._number[digit_index] > rhs._number[digit_index]) {
      return true;
    }
  }

  return false;
}

bool operator<(const int2023_t& lhs, const int2023_t& rhs) {
  for (int digit_index = 0; digit_index < int2023_t::kNumberMaxLength; ++digit_index) {
    if (lhs._number[digit_index] > rhs._number[digit_index]) {
      return false;
    }
    if (lhs._number[digit_index] < rhs._number[digit_index]) {
      return true;
    }
  }

  return false;
}

bool operator>=(const int2023_t& lhs, const int2023_t& rhs) {
  if (lhs == rhs || lhs > rhs) {
    return true;
  }

  return false;
}

bool operator<=(const int2023_t& lhs, const int2023_t& rhs) {
  if (lhs == rhs || lhs < rhs) {
    return true;
  }

  return false;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
  bool is_number_begin = false;
  bool is_sign_digit = true;
  uint8_t zeroCounter = 0;
  for (unsigned char digit : value._number) {
    if (is_sign_digit) {
      if (digit != 0 && digit != int2023_t::kLastElementRange) {
        if (digit >= int2023_t::kLastElementRange) {
          stream << unsigned(digit - int2023_t::kLastElementRange) << ' ';
        } else {
          stream << '-' << ' ' << unsigned(digit) << ' ';
        }
        is_number_begin = true;
      } else if (digit == 0) {
        stream << '-' << ' ';
      }
      is_sign_digit = false;
      continue;
    }
    if (!is_number_begin) {
      if (digit == 0) {
        ++zeroCounter;
        if (zeroCounter == int2023_t::kNumberMaxLength - 1) {
          stream << 0;
        }
        continue;
      }
      is_number_begin = true;
    }
    stream << unsigned(digit) << ' ';
  }

  return stream;
}
