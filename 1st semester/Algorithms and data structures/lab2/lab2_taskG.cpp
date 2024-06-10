#include <iostream>

long Median(long a, long b, long c) {
  return a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c);
}

long Partition2(long mainArr[], long subArr[], long l, long r) {
  long v = Median(mainArr[l], mainArr[(l + r) / 2], mainArr[r]);
  long i = l;
  long j = r;
  while (i <= j) {
    while (mainArr[i] < v) {
      i++;
    }
    while (mainArr[j] > v) {
      j--;
    }
    if (i >= j) {
      break;
    }
    std::swap(mainArr[i], mainArr[j]);
    if (mainArr[i] != mainArr[j]) {
      std::swap(subArr[i], subArr[j]);
    }
    ++i;
    --j;
  }
  return j;
}

void QuickSort2(long *&mainArr, long *&subArr, long l, long r) {
  if (l < r) {
    long i = Partition2(mainArr, subArr, l, r);
    QuickSort2(mainArr, subArr, l, i);
    QuickSort2(mainArr, subArr, i + 1, r);
  }
}

int main(){
  long n;
  std::cin >> n;
  long *ts = new long[n];
  long *ds = new long[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> ts[i] >> ds[i];
  }

  QuickSort2(ts, ds, 0, n - 1);

  long s = 0;
  long day = 0;
  for (int i = 0; i < n; ++i) {
    day += ts[i];
    s += ds[i] - day;
  }

  std::cout << s;

  delete[] ts;
  delete[] ds;
}

