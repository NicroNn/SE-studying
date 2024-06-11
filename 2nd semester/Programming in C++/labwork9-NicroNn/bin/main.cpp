#include "lib/adapters.h"

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    auto squared = v | transform(v, [](int i){ return i * i; }) | reverse(v) | filter(v, [](int i){ return i % 2;});
    for (auto& elem : squared) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::unordered_map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};

    auto extractedKeys = m | keys(m);

    for (auto& key : extractedKeys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    auto extractedValues = m | values(m);

    for (auto& value : extractedValues) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
