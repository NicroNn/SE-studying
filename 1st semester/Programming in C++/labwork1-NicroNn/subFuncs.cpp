#include <iostream>
#include <fstream>
#include "funcs.h"

char GetSpecialDelimiter(char symbol) {
  switch (symbol) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case '\n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    case '\'': return '\'';
    case '\"': return '\"';
    case '\\': return '\\';
    case '\?': return '\?';
    default:
      std::cout << "No delimiter specified, default value will be used";
      return '\n';
  }
}

std::string GetFilename(char* argv[], int argc) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    std::ifstream file(arg, std::ios::binary);
    if (file.is_open()) {
      return argv[i];
    }
  }
  return " ";
}

void ParseArguments(char* argv[], int argc, Arguments& args) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-l") {
      if (IsDigit(argv[++i])) {
        args.lines_limit = std::stoi(argv[i]);
      }
      else {
        std::cout << "No lines limit specified, default value will be used\n";
      }
    }
    if (arg == "-d") {
      if (argv[++i][0] == '\'') {
        args.delim = argv[i][1];
      }
      else {
        std::cout << "No delimiter specified, default value will be used\n";
      }

      if (args.delim == '\\' && argv[i][3] == '\'') {
        args.delim = GetSpecialDelimiter(argv[i][2]);
      }
    }
    if (arg == "-t") {
      args.is_tail = true;
    }

    if (arg.substr(0, 8) == "--lines=") {
      args.lines_limit = std::stoi(arg.substr(8));
    }
    if (arg.substr(0, 12) == "--delimiter=") {
      args.delim = arg[13];
      if (args.delim == '\\' && arg[15] == '\'') {
        args.delim = GetSpecialDelimiter(arg[14]);
      }
    }
    if (arg == "--tail") {
      args.is_tail = true;
    }
  }
}
