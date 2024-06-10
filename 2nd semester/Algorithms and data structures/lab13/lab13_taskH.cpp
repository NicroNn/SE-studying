#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int q;
    std::cin >> q;

    while (q--) {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        --x1, --x2, --x3, --x4, --y1, --y2, --y3, --y4;

        if (x1 == x3 && x2 == x4 && y1 == y3 && y2 == y4){
            std::cout << "YES" << '\n';
            continue;
        }

        bool isMatrixSame = true;

        if ((x2 - x1) != (x4 - x3) || (y2 - y1) != (y4 - y3)) {
            isMatrixSame = false;
        } else {
            for (int i = 0; i <= (x2 - x1); ++i) {
                for (int j = 0; j <= (y2 - y1); ++j) {
                    if (matrix[x1 + i][y1 + j] != matrix[x3 + i][y3 + j]) {
                        isMatrixSame = false;
                        break;
                    }
                }
                if (!isMatrixSame) break;
            }
        }

        if (isMatrixSame) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
}
