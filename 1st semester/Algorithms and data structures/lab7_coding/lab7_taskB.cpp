#include <iostream>
#include <string>
#include <map>

void lz78_compression(const std::string& input) {
    std::map<std::string, int> dictionary;
    std::string current_string = "";
    int dict_index = 1;

    for (char c : input) {
        current_string += c;
        if (dictionary.find(current_string) == dictionary.end()) {
            dictionary[current_string] = dict_index++;
            std::cout << dictionary[current_string.substr(0, current_string.length() - 1)] << ' ' << c << '\n';
            current_string = "";
        }
    }

    if (!current_string.empty()) {
        std::cout << dictionary[current_string] << ' ' << '\0' << '\n';
    }
}

int main() {
    std::string input;
    std::cin>> input;
    lz78_compression(input);
}
