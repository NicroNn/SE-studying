#include <iostream>

long Median(long a, long b, long c) {
  return a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c);
}

long Partition(long arr[], long l, long r) {
  long v = Median(arr[l], arr[(l + r) / 2], arr[r]);
  long i = l;
  long j = r;
  while (i <= j) {
    while (arr[i] < v) {
      i++;
    }
    while (arr[j] > v) {
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

bool isPossible(const long arr[], long m, long n, long k){
  long cur = arr[0];
  long els = 1;
  for (int i = 0; i < n; ++i) {
    if (arr[i] - cur >= m){
      cur = arr[i];
      ++els;
      if (els == k){
        return true;
      }
    }
  }
  return false;
}

long minMaxDistance(long arr[], long n, long k){
  long result = 0;
  long l = 1, r = arr[n - 1];
  while (l < r){
    long m = (l + r) / 2;
    if (isPossible(arr, m, n, k)){
      result = std::max(result, m);
      l = m + 1;
    } else{
      r = m;
    }
  }
  return result;
}

int main(){
  long n, k, answer;
  std::cin >> n >> k;
  long* coords = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> coords[i];
  }
  QuickSort(coords, 0, n - 1);
  answer = minMaxDistance(coords, n, k);
  std::cout << answer;
}
