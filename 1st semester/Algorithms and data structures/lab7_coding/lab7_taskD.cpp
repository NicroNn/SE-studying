#include <iostream>
#include <vector>
#include <cmath>

void correctHammingCode(std::vector<int>& code) {
    int n = code.size();
    int r = 0;

    while ((1 << r) < (n + r + 1)) {
        r++;
    }

    int errorPos = 0;
    for (int i = 0; i < r; i++) {
        int position = (1 << i);
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (j & position) {
                count += code[j];
            }
        }
        if (count % 2 != 0) {
            errorPos += position;
        }
    }

    if (errorPos > 0) {
        code[errorPos - 1] = (code[errorPos - 1] == 1) ? 0 : 1;
    }

    for (int i = 0; i < n; i++) {
        if ((i + 1) != pow(2, floor(log2(i + 1)))) {
            std::cout << code[i];
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> codes(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> codes[i];
    }

    for (int i = 0; i < n; ++i) {
        std::vector<int> curCode (codes[i].length());
        for (int j = 0; j < codes[i].length(); ++j) {
            curCode[j] = codes[i][j] - '0';
        }
        correctHammingCode(curCode);
        std::cout << '\n';
    }

}
