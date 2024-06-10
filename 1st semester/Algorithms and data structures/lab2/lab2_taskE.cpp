#include <iostream>

long merge(long *&arr, long l, long m, long r){
  long it1 = 0;
  long it2 = 0;
  long count = 0;
  long *res = new long[r - l];
  while ((l + it1 < m) && (m + it2 < r)){
    if (arr[l + it1] <= arr[m + it2]){
      res[it1 + it2] = arr[l + it1];
      ++it1;
    } else{
      res[it1 + it2] = arr[m + it2];
      ++it2;
      count += m - (l + it1);
    }
  }
  while (l + it1 < m){
    res[it1 + it2] = arr[l + it1];
    ++it1;
  }
  while (m + it2 < r){
    res[it1 + it2] = arr[m + it2];
    ++it2;
  }
  for (int i = 0; i < it1 + it2; ++i) {
    arr[l + i] = res[i];
  }
  delete [] res;
  return count;
}

long MergeSort(long *&arr, long l, long r){
  long count = 0;
  if (l + 1 >= r) {
    return 0;
  }
  long m = (l + r) / 2;
  count += MergeSort(arr, l, m);
  count += MergeSort(arr, m, r);
  count += merge(arr, l, m, r);
  return count;
}

int main(){
  long n, count;
  std::cin >> n;

  long *arr = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  count = MergeSort(arr, 0, n);

  std::cout << count;

  delete[] arr;
}
