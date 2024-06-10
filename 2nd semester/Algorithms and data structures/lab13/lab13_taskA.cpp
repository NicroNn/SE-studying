#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string text, word;
    std::cin >> text >> word;

    std::vector<int> positions;
    int pos = text.find(word);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = text.find(word, pos + 1);
    }

    std::cout << positions.size() << '\n';
    for (int position : positions) {
        std::cout << position << ' ';
    }
}
