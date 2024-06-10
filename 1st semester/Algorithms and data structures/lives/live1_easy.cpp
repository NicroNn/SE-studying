#include <iostream>
#include <vector>

int Median(int a, int b, int c){
  return a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c);
}

int Partition(std::vector<int>& arr, int l, int r){
  int v = Median(arr[l], arr[(l + r) / 2], arr[r]);
  int i = l;
  int j = r;
  while (i <= j){
    while (arr[i] < v){
      i++;
    }
    while (arr[j] > v){
      j--;
    }
    if (i >= j){
      break;
    }
    std::swap(arr[i++], arr[j--]);
  }
  return j;
}

void QuickSort(std::vector<int>& arr, int l, int r){
  if (l < r){
    int i = Partition(arr, l, r);
    QuickSort(arr, l, i);
    QuickSort(arr, i + 1, r);
  }
}


int findLeftmostGreaterOrEqual(const std::vector<int>& sortedArray, int target) {
  int left = 0;
  int right = sortedArray.size() - 1;
  int result = -1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (sortedArray[mid] >= target) {
      result = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return result;
}

int findRightmostLessOrEqual(const std::vector<int>& sortedArray, int target) {
  int left = 0;
  int right = sortedArray.size() - 1;
  int result = -1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (sortedArray[mid] <= target) {
      result = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return result;
}

int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  std::vector<int> products(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> products[i];
  }

  QuickSort(products, 0, n - 1);

  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int l, r;
    std::cin >> l >> r;
    if (l > products[n - 1]){
      std::cout << 0 << ' ';
      continue;
    }
    std::cout << findRightmostLessOrEqual(products, r) - findLeftmostGreaterOrEqual(products, l) + 1 << ' ';
  }
}
