#include <functional>
#include <lib/ArgParser.h>

#include <iostream>
#include <numeric>


int main(int argc, char** argv) {
    ArgumentParser::ArgParser args("my args");
    std::vector<std::string> input {"app", "--param1=value1", "--p=5"};
    args.AddStringArgument("param1");
    args.AddIntArgument("p");
    args.AddFlag("a");
    args.Parse(input);
    std::cout << args.GetStringValue("param1") << ' ' << args.GetIntValue("p") << ' ' << args.GetFlag("a");
}
