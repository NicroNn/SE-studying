#include<iostream>
#include<vector>

const long long mod = 1e9 + 7;

int main() {
    int n;

    std::cin >> n;
    std::vector<int> deg1(n), deg2(n);
    if (n < 0) {
        std::cout << "NO";
        return 0;
    }
    if (n <= 1) {
        std::cout << "YES";
        return 0;
    }

    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> u >> v;
        --u, --v;
        ++deg1[u];
        ++deg1[v];
    }

    for (int i = 0; i < n - 1; ++i) {
        std::cin >> u >> v;
        --u, --v;
        ++deg2[u];
        ++deg2[v];
    }

    int hash1 = 0;
    int sum1 = 0;
    int hash2 = 0;
    int sum2 = 0;

    for (int i = 0; i < n; ++i) {
        hash1 ^= deg1[i];
        sum1 += deg1[i] * deg1[i];
        sum1 %= mod;
    }

    for (int i = 0; i < n; ++i) {
        hash2 ^= deg2[i];
        sum2 += deg2[i] * deg2[i];
        sum2 %= mod;
    }

    std::cout << ((hash1 == hash2 && sum1 == sum2) ? "YES" : "NO");
}
