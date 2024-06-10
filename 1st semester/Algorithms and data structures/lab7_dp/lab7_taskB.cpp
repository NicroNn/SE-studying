#include <iostream>
#include <vector>
#include <algorithm>

int lengthOfLIS(std::vector<int>& piles) {
    std::vector<int> dp;

    for (int pile : piles) {
        auto it = std::lower_bound(dp.begin(), dp.end(), pile);
        if (it == dp.end()) {
            dp.push_back(pile);
        } else {
            *it = pile;
        }
    }

    return dp.size();
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> piles(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> piles[i];
    }

    std::cout << lengthOfLIS(piles);
}
