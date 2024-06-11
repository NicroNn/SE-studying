#include <iostream>
#include "funcs.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Error: Please provide a filename." << std::endl;
    return EXIT_FAILURE;
  }

  Arguments args;

  args.filename = GetFilename(argv, argc);
  if (args.filename == " ") {
    std::cout << "Error: Unable to open file.";
    return EXIT_FAILURE;
  }

  ParseArguments(argv, argc, args);

  PrintFile(args.filename, args.lines_limit, args.delim, args.is_tail);

  return 0;
}