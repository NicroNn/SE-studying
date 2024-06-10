#include <iostream>

void InsertionSort(long *&arr, long n) {
  long counter = 0;
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
      counter++;
      int tmp = arr[j - 1];
      arr[j - 1] = arr[j];
      arr[j] = tmp;
    }
  }
}

int main() {
  long n;
  std::cin >> n;
  long *arr = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  InsertionSort(arr, n);

  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
}