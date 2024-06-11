#include <iostream>
#include <fstream>
#include "funcs.h"

void PrintAll(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);

  char ch;

  while (file.get(ch)) {
    std::cout << ch;
  }
}

void PrintLines(const std::string& filename, uint64_t lines_limit, char delim) {
  std::ifstream file(filename, std::ios::binary);

  long printed_lines = 0;
  char ch;
  while (file.get(ch) && printed_lines < lines_limit) {
    if (ch == delim) {
      printed_lines++;
    }
    std::cout << ch;
  }
}

void PrintTail(const std::string& filename, uint64_t lines_limit, char delim) {
  std::ifstream file(filename, std::ios::binary);

  long lines = 0;
  char ch;

  file.seekg(-1, std::ios::end);
  while (lines < lines_limit) {
    file.seekg(-1, std::ios::cur);
    file.get(ch);
    if (ch == delim) {
      lines++;
    }
    file.seekg(-1, std::ios::cur);
    if (file.tellg() == 0) {
      std::cout << file.get();
      break;
    }
  }
  file.seekg(1, std::ios::cur);
  while (file.get(ch)) {
    std::cout << ch;
  }
}

void PrintFile(const std::string &filename, uint64_t lines_limit, char delim, bool is_tail) {
  if (lines_limit == UINT64_MAX) {
    PrintAll(filename);
  }
  else {
    if (is_tail) {
      PrintTail(filename, lines_limit, delim);
    }
    else {
      PrintLines(filename, lines_limit, delim);
    }
  }
}

