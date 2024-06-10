#include <iostream>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::string song;
    std::cin >> song;

    int correctAnswers = 0;

    for (int q = 0; q < m; q++) {
        int i, j, k;
        std::cin >> i >> j >> k;

        --i;
        --j;

        if (song.substr(i, k) == song.substr(j, k)) {
            correctAnswers++;
        }
    }
    std::cout << correctAnswers;
}
