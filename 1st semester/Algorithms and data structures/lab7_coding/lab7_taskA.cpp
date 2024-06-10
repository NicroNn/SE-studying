#include <iostream>
#include <vector>
#include <bitset>

std::vector<std::string> generateGrayCodes(long n) {
    std::vector<std::string> grayCodes;
    for (int i = 0; i < (1 << n); ++i) {
        int grayCode = i ^ (i >> 1);
        grayCodes.push_back(std::bitset<64>(grayCode).to_string().substr(64-n));
    }
    return grayCodes;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> grayCodes = generateGrayCodes(n);
    for (const std::string &code : grayCodes) {
        std::cout << code << '\n';
    }
}
