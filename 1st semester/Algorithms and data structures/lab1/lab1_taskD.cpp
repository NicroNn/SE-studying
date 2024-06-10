#include <iostream>

int main() {
  int n, m, q, count;
  std::cin >> n >> m >> q;
  int ser[n][m];
  std::fill(ser[0], ser[0] + n * m, 0);
  int a, b;
  count = 0;
  for (int i = 0; i < q; i++) {
    std::cin >> a >> b;
    ser[b - 1][a - 1] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ser[i][j] == 1) {
        count++;
      }
    }
  }
  std::cout << n * m - count << "\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ser[i][j] != 1) {
        std::cout << j + 1 << " " << i + 1 << "\n";
      }
    }
  }
}