#include <iostream>
#include <string>
#include <map>

void arithmeticCode(const std::string& string){
    std::map<char, int> frequencies;
    for (char c : string) {
        frequencies[c]++;
    }

    std::map<char, std::pair<double, double>> ranges;
    double total = 0.0;

    for (auto const& pair : frequencies) {
        double low = total;
        total += (double)pair.second / string.length();
        double high = total;
        ranges[pair.first] = std::make_pair(low, high);
    }

    double low = 0.0;
    double high = 1.0;

    for (char c : string) {
        double range = high - low;
        high = low + ranges[c].second * range;
        low = low + ranges[c].first * range;
    }

    double code = low;

    std::cout.precision(6);
    std::cout << std::fixed << code;
}

int main() {
    std::string string;
    std::cin >> string;
    arithmeticCode(string);
}
