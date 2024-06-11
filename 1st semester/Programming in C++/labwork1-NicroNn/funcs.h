#include <cinttypes>
#ifndef LABWORK1_FUNCS_H
#define LABWORK1_FUNCS_H

struct Arguments {
  std::string filename = " ";
  uint64_t lines_limit = UINT64_MAX;
  char delim = '\n';
  bool is_tail = false;
};

void PrintFile(const std::string& filename, uint64_t lines_limit, char delim, bool is_tail);

char GetSpecialDelimiter(char symbol);

bool IsDigit(const std::string& num);
std::string GetFilename(char* argv[], int argc);
void ParseArguments(char* argv[], int argc, Arguments& args);

#endif // LABWORK1_FUNCS_H
