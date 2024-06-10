#include <iostream>
#include <vector>
#include <experimental/random>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cards (n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cards[i];
    }
    for (int i = n / 2; i >= 0; --i) {
        int index0 = i;
        int index1 = i - 1;
        bool isPalinsky = true;
        while (index0 < n && index1 >= 0) {
            if (cards[index0++] != cards[index1--]) {
                isPalinsky = false;
                if (std::experimental::randint(0, 1)){
                    continue;
                } else {
                    break;
                }
            }
        }
        if (isPalinsky) {
            std::cout << n - i << ' ';
        }
    }
}
