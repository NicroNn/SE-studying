#ifndef SE_COMP_ARCH24_CACHE_ISA_NICRONN__READER_H_
#define SE_COMP_ARCH24_CACHE_ISA_NICRONN__READER_H_
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>

const std::set<std::string> bracketInstructions {"lb", "lh", "lw", "lbu", "lbh", "sb", "sh", "sw"};

std::vector<std::pair<std::string, std::vector<std::string>>> readFile(const std::string& filename) {
    std::vector<std::pair<std::string, std::vector<std::string>>> allInstructions;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string instruction;
        ss >> instruction;
        if (instruction.empty()) continue;
        std::transform(instruction.begin(), instruction.end(), instruction.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        std::vector<std::string> arguments;
        std::string argument;
        bool isBracket = false;
        while (std::getline(ss, argument, ',')) {
            size_t startPos = argument.find_first_not_of(" \t");
            if (startPos != std::string::npos) {
                argument.erase(0, startPos);
            }

            size_t pos = argument.find('(');
            if (pos != std::string::npos){
                isBracket = true;
                std::string arg = argument.substr(pos + 1, argument.find(')') - pos - 1);
                std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c){ return std::tolower(c); });
                arguments.push_back(arg);

                std::string num = argument.substr(0, pos);
                arg = (num.find("0x") != std::string::npos) ? std::to_string(std::stoi(num, nullptr, 16)) : num;
                std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c){ return std::tolower(c); });
                arguments.push_back(arg);
            } else {
                std::string arg = (argument.find("0x") != std::string::npos) ?
                    std::to_string(std::stoi(argument, nullptr, 16)) : argument;
                std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c){ return std::tolower(c); });
                arguments.push_back(arg);
            }
        }
        if (!isBracket && bracketInstructions.contains(instruction)){
            arguments = {arguments[0], arguments[2], arguments[1]};
        }

        allInstructions.emplace_back(instruction, arguments);
    }

    return allInstructions;
}
#endif //SE_COMP_ARCH24_CACHE_ISA_NICRONN__READER_H_
