
#include <lib/number.h>
#include <iostream>

int main() {
  int2023_t value1, value2, value3;
  //value1 = from_string("1");
  //value2 = from_string("0");
  value1 = from_string("65535");
  value2 = from_string("10000000");
  ShiftLeft(value1);
  std::cout << value1; //<< '\n' << value2 << '\n' << (value1 * value2); // << '\n' << value2 << '\n' << value3 << '\n' << (value1 + value2 == value3);
  //1 119 149 108 134 186 53 138 138 149 24 154 124 240 116 206 133 88 175 92 119 207 13 0 197 222 194 36 218 24 15 210 97
  //std::cout << (-value1) << '\n';
  //std::cout << value1 << '\n' << value2 << '\n' << (value1 + value2) << std::endl;
  return 0;
  //- 168 161 182 128 228 76 206 227 184 13 142 251 204 229 132 179 16 91 36 227 77 75 163 101 63 135 52 61 194 148 134 83
  //   - 125 173 156 251 29 108 59 139 92 90 249 200 88 134 135 195 170 178 96 108 156 19 79 185 18 93 96 179 85 170 83 59
}
