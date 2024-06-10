#include <iostream>

void merge(long *&mainArr, long *&subArr, long l, long m, long r){
  long it1 = 0;
  long it2 = 0;
  long *mainRes = new long[r - l];
  long *subRes = new long[r - l];
  while ((l + it1 < m) && (m + it2 < r)){
    if (mainArr[l + it1] <= mainArr[m + it2]){
      mainRes[it1 + it2] = mainArr[l + it1];
      subRes[it1 + it2] = subArr[l + it1];
      ++it1;
    } else{
      mainRes[it1 + it2] = mainArr[m + it2];
      subRes[it1 + it2] = subArr[m + it2];
      ++it2;
    }
  }
  while (l + it1 < m){
    mainRes[it1 + it2] = mainArr[l + it1];
    subRes[it1 + it2] = subArr[l + it1];
    ++it1;
  }
  while (m + it2 < r){
    mainRes[it1 + it2] = mainArr[m + it2];
    subRes[it1 + it2] = subArr[m + it2];
    ++it2;
  }
  for (int i = 0; i < it1 + it2; ++i) {
    mainArr[l + i] = mainRes[i];
    subArr[l + i] = subRes[i];
  }
  delete [] mainRes;
  delete[] subRes;
}

void MergeSort(long *&mainArr, long *&subArr, long l, long r){
  if (l + 1 >= r) {
    return;
  }
  long m = (l + r) / 2;
  MergeSort(mainArr,subArr, l, m);
  MergeSort(mainArr,subArr, m, r);
  merge(mainArr, subArr, l, m, r);
}


int main() {
  long n;
  std::cin >> n;
  long* moneys = new long[n];
  long* horseIds = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> moneys[i];
  }
  for (int i = 0; i < n; ++i) {
    horseIds[i] = i;
  }

  MergeSort(moneys, horseIds, 0, n);

  for (int i = 0; i < n; ++i) {
    if (horseIds[i] != i){
      moneys[i] += (horseIds[i] - i);
    }
  }

  bool IsSorted = true;
  for (int i = 0; i < n - 1; ++i) {
    if (moneys[i] > moneys[i + 1]){
      IsSorted = false;
      break;
    }
  }
  if (IsSorted) {
    for (int i = 0; i < n; ++i) {
      std::cout << moneys[i] << ' ';
    }
  } else{
    std::cout << ":(";
  }

  delete[] moneys;
}

