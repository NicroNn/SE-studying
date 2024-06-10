#include <iostream>
#include <vector>

const int size = 3e6 + 3;
const int mod = 998244353;

int hashing(int diff) {
    int hash = (diff + mod) % size;
    hash = (hash * 17) % size;
    return hash;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> chairs (n);
    std::vector<int> table (size);
    for (int i = 0; i < n; ++i) {
        std::cin >> chairs[i];
    }

    for (int i = 0; i < n; ++i) {
        int diff = chairs[i] - i;
        size_t hash = hashing(diff);
        ++table[hash];
    }

    int ans = 0;
    for (int i = 0; i < size; ++i) {
        if (table[i] > 1) {
            ans += table[i] * (table[i] - 1) / 2;
        }
    }

    std::cout << ans;
}
