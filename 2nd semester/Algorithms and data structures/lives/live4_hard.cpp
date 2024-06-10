#include <iostream>
#include <vector>
#include <string>
#include <bitset>

std::string stringRecovery(const std::vector<int> & pi) {
    if (pi.size() == 0) {
        return "";
    }

    std::string result = "a";

    for (int i = 1; i < pi.size(); i++) {
        if (pi[i] != 0) {
            result += result[pi[i] - 1];
        } else {
            std::bitset<26> used(false);

            size_t k = pi[i - 1];
            while (k > 0) {
                used[result[k] - 'a'] = true;
                k = pi[k - 1];
            }

            char ch = 'b';
            while (used[ch - 'a']) ch++;

            result += ch;
        }
    }

    return result;
}

int main() {
    std::vector<int> pf;
    int n;
    std::cin >> n;
    pf.resize(n);
    for (int i = 0; i < n; ++i)
        std::cin >> pf[i];

    std::cout << stringRecovery(pf);
}
