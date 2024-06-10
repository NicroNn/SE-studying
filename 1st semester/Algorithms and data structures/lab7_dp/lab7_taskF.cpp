#include <iostream>
#include <vector>
#include <algorithm>


void findRightmostBottommostLargestSquare(const std::vector<std::string>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<int> dp(cols, 0);
    int maxSize = 0, maxRow = 0, maxCol = 0, prev = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int temp = dp[j];
            if (matrix[i][j] == '5') {
                if (i == 0 || j == 0) {
                    dp[j] = 1;
                } else {
                    dp[j] = std::min({ dp[j], dp[j - 1], prev }) + 1;
                }
                if (dp[j] > maxSize) {
                    maxSize = dp[j];
                    maxRow = i;
                    maxCol = j;
                } else if (dp[j] == maxSize && (i > maxRow || (i == maxRow && j > maxCol))) {
                    maxRow = i;
                    maxCol = j;
                }
            } else {
                dp[j] = 0;
            }
            prev = temp;
        }
    }

        std::cout << maxSize << " " << (maxRow - maxSize + 2) << " " << (maxCol - maxSize + 2);

}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> matrix(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> matrix[i];
    }

    findRightmostBottommostLargestSquare(matrix);
}
