#include <iostream>
#include <fstream>

bool IsDigit(const std::string& num) {
  for (char i : num) {
    if (!std::isdigit(i)) {
      return false;
    }
  }
  return true;
}