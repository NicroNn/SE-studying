#include <iostream>
#include <vector>

std::vector<std::vector<long>> calculateDP(const std::vector<std::vector<int>>& grid, bool fromTopLeft) {
    int rows = grid.size(), cols = grid[0].size();
    std::vector<std::vector<long>> dp(rows, std::vector<long>(cols, 0));

    if (fromTopLeft) {
        dp[0][0] = grid[0][0];
        for (int i = 1; i < rows; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < cols; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
    } else {
        dp[rows - 1][cols - 1] = grid[rows - 1][cols - 1];
        for (int i = rows - 2; i >= 0; --i) {
            dp[i][cols - 1] = dp[i + 1][cols - 1] + grid[i][cols - 1];
        }
        for (int j = cols - 2; j >= 0; --j) {
            dp[rows - 1][j] = dp[rows - 1][j + 1] + grid[rows - 1][j];
        }
        for (int i = rows - 2; i >= 0; --i) {
            for (int j = cols - 2; j >= 0; --j) {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]) + grid[i][j];
            }
        }
    }

    return dp;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int rows, cols;
    std::cin >> rows >> cols;
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> grid[i][j];
        }
    }

    auto dpTopLeft = calculateDP(grid, true);
    auto dpBottomRight = calculateDP(grid, false);

    int queries;
    std::cin >> queries;
    while (queries--) {
        int x, y;
        std::cin >> x >> y;
        long result = dpTopLeft[x][y] + dpBottomRight[x][y] - grid[x][y];
        std::cout << result << '\n';
    }
}
