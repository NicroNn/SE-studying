#include <iostream>

int main() {
  long n = 0;
  std::cin >> n;
  long *arr = new long[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = i + 1;
  }
  for (int i = 2; i < n; ++i) {
    std::swap(arr[i], arr[i / 2]);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << ' ';
  }
  delete[] arr;
}
