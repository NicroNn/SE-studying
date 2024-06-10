#include <iostream>

void CountSort(long* arr, long n) {
  long max = 100001;
  long count[max + 1];
  for (int i = 0; i < max + 1; ++i) {
    count[i] = 0;
  }
  for (long i = 0; i < n; ++i) {
    ++count[arr[i]];
  }
  for (long i = 1; i <= max; ++i) {
    count[i] += count[i - 1];
  }
  long* sortedArr = new long[n];
  for (long i = n - 1; i >= 0; --i) {
    sortedArr[count[arr[i]] - 1] = arr[i];
    --count[arr[i]];
  }
  for (long i = 0; i < n; ++i) {
    arr[i] = sortedArr[i];
  }
  delete[] sortedArr;
}

int main(){
  long n, k;
  std::cin >> n >> k;
  long* fems = new long[n];
  long* men = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> fems[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> men[i];
  }
  CountSort(fems, n);
  CountSort(men, n);
  for (int i = 0; i < n; ++i) {
    std::cout << fems[i] << ' ';
  }
  std::cout << '\n';
  for (int i = 0; i < n; ++i) {
    std::cout << men[i] << ' ';
  }

}
