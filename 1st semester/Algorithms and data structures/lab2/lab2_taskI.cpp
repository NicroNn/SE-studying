#include <iostream>

int Median(int a, int b, int c) {
  return a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c);
}

void QuickSortMax(int* arr, int l, int r, int k) {
  int i = l;
  int j = r;
  int v = Median(arr[l], arr[(l + r) / 2], arr[r]);
  while (i <= j) {
    while (arr[i] > v) {
      i++;
    }
    while (arr[j] < v) {
      j--;
    }
    if (i <= j) {
      std::swap(arr[i++],arr[j--]);
    }
  }
  if (l < j && j >= k) {
    QuickSortMax(arr, l, j, k);
  }
  if (i < r && i < k) {
    QuickSortMax(arr, i, r, k);
  }
}

int CalcCost(int prev, int beforePrev, int a, int b, int c) {
  return beforePrev * a + prev * b + c;
}

int main() {
  int n, k, a, b, c;
  std::cin >> n >> k;

  int* costs = new int[n];
  std::cin >> a >> b >> c >> costs[0] >> costs[1];

  for (int i = 2; i < n; ++i) {
    costs[i] = CalcCost(costs[i - 1], costs[i - 2], a, b, c);
  }

  QuickSortMax(costs, 0, n - 1, k);

  int res = 0;
  for (int i = 0; i < k; ++i) {
    res = res xor costs[i];
  }

  std::cout << res;

  delete[] costs;
}
