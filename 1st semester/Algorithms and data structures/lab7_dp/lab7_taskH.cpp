#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


int main() {
    int n, m;
    std::cin >> n >> m;
    std::string previousString, currentString;
    std::vector<int> currentRow(m + 1, 0);
    std::vector<int> previousRow(m + 1, 0);

    int maxSize = 0;
    int answerStartRow, answerStartCol;
    for (int i = 1; i <= n; ++i) {
        std::cin >> currentString;
        for (int j = 1; j <= m; ++j) {
            if (currentString[j - 1] == '5') {
                currentRow[j] = std::min({currentRow[j - 1], previousRow[j - 1], previousRow[j]}) + 1;
                if (currentRow[j] >= maxSize) {
                    maxSize = currentRow[j];
                    answerStartRow = i - currentRow[j] + 1;
                    answerStartCol = j - currentRow[j] + 1;
                }
            }
        }
        previousRow = currentRow;
        fill(currentRow.begin(), currentRow.end(), 0);
    }
    std::cout << maxSize << ' ' << answerStartRow << ' ' << answerStartCol;
}
