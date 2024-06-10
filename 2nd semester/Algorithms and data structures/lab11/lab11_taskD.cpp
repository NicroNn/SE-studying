#include <vector>
#include <iostream>

bool prefers(const std::vector<std::vector<int>>& prefer, int man, int cat1, int cat2) {
    for (int pref : prefer[man]) {
        if (pref == cat2)
            return true;
        if (pref == cat1)
            return false;
    }
    return false;
}

void stableMatch(int n, const std::vector<std::vector<int>>& prefer) {
    std::vector<int> mansCat(n, -1);
    std::vector<bool> freeCat(n, false);

    for (int counter = n; counter > 0;) {
        int cat;
        for (cat = 0; cat < n; ++cat)
            if (!freeCat[cat])
                break;

        for (int i = 0; i < n && !freeCat[cat]; ++i) {
            int man = prefer[cat][i];

            if (mansCat[man - n] == -1) {
                mansCat[man - n] = cat;
                freeCat[cat] = true;
                --counter;
            } else {
                int cat2 = mansCat[man - n];

                if (!prefers(prefer, man, cat, cat2)) {
                    mansCat[man - n] = cat;
                    freeCat[cat] = true;
                    freeCat[cat2] = false;
                }
            }
        }
    }

    std::vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
        answer[mansCat[i]] = i;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << i << ' ' << answer[i] << '\n';
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> prefer(2 * n, std::vector<int>(n));

    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> prefer[i][j];
            if (i < n) prefer[i][j] += n;
        }
    }

    stableMatch(n, prefer);
}
