#include <iostream>
#include <vector>

int main() {
    const int mod = 998244353;
    int n;
    std::cin >> n;
    std::vector<int> left(n), right(n);

    int leftHash = 0;
    int leftSum = 0;
    int rightHash = 0;
    int rightSum = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> left[i];
        leftHash ^= left[i];
        leftSum += left[i];
        leftSum %= mod;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> right[i];
        rightHash ^= right[i];
        rightSum += right[i];
        rightSum %= mod;
    }
    std::cout << ((leftHash == rightHash && leftSum == rightSum) ? "YES" : "NO");
}
