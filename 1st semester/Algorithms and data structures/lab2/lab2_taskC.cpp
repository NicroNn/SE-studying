#include <iostream>

long Median(long a, long b, long c) {
  return a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c);
}

long Partition(long arr[], long l, long r) {
  long v = Median(arr[l], arr[(l + r) / 2], arr[r]);
  long i = l;
  long j = r;
  while (i <= j) {
    while (arr[i] > v) {
      i++;
    }
    while (arr[j] < v) {
      j--;
    }
    if (i >= j) {
      break;
    }
    std::swap(arr[i++], arr[j--]);
  }
  return j;
}

void QuickSort(long *&arr, long l, long r) {
  if (l < r) {
    long i = Partition(arr, l, r);
    QuickSort(arr, l, i);
    QuickSort(arr, i + 1, r);
  }
}

int main() {
  long n;
  std::cin >> n;
  long *arr = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  QuickSort(arr, 0, n - 1);

  bool IsNewSquare = true;
  long temp = 0, max_square = 0;

  for (int i = 0; i < n - 1; ++i) {
    if (arr[i] == arr[i + 1] || arr[i] - 1 == arr[i + 1]) {
      if (IsNewSquare) {
        if (arr[i] - 1 == arr[i + 1]) {
          temp = arr[i] - 1;
        } else {
          temp = arr[i];
        }
        IsNewSquare = false;
      } else {
        if (arr[i] - 1 == arr[i + 1]) {
          max_square += temp * (arr[i] - 1);
        } else {
          max_square += temp * arr[i];
        }

        temp = 0;
        IsNewSquare = true;
      }
      ++i;
    }
  }

  std::cout << max_square;

}
