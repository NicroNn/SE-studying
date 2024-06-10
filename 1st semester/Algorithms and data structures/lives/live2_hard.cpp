#include <iostream>
#include <vector>

int main() {
    int x, y, z;
    std::cin >> x >> y >> z;

    std::vector<std::vector<std::vector<int>>> dp(x + 1, std::vector<std::vector<int>>(y + 1, std::vector<int>(z + 1, 0)));
    std::vector<std::vector<std::vector<int>>> coins(x + 1, std::vector<std::vector<int>>(y + 1, std::vector<int>(z + 1, 0)));

    int xi, yi, zi, ci;
    while (std::cin >> xi >> yi >> zi >> ci) {
        coins[xi][yi][zi] = ci;
    }

    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= y; ++j) {
            for (int k = 1; k <= z; ++k) {
                int from_previous = std::max(std::max(dp[i-1][j][k], dp[i][j-1][k]), dp[i][j][k-1]);
                dp[i][j][k] = from_previous + coins[i][j][k];
            }
        }
    }

    std::cout << dp[x][y][z];
}
