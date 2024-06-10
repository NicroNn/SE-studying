#include <iostream>

long Median(long a, long b, long c) {
  return a + b + c - std::min(std::min(a, b), c) - std::max(std::max(a, b), c);
}

long Partition(long mainArr[], long subArr[], long l, long r) {
  long v = Median(mainArr[l], mainArr[(l + r) / 2], mainArr[r]);
  long i = l;
  long j = r;
  while (i <= j) {
    while (mainArr[i] > v) {
      i++;
    }
    while (mainArr[j] < v) {
      j--;
    }
    if (i >= j) {
      break;
    }
    std::swap(mainArr[i], mainArr[j]);

    std::swap(subArr[i], subArr[j]);

    ++i;
    --j;
  }
  return j;
}

void QuickSort(long *&mainArr, long *&subArr, long l, long r) {
  if (l < r) {
    long i = Partition(mainArr, subArr, l, r);
    QuickSort(mainArr, subArr, l, i);
    QuickSort(mainArr, subArr, i + 1, r);
  }
}

int main() {
  long n, m, k, curRating;
  std::cin >> n >> m >> k;
  if (k > m) {
    k = m;
  }

  long *critics = new long[n];
  long *filmRatings = new long[m];
  long *filmIds = new long[m];

  for (int i = 0; i < m; ++i) {
    filmRatings[i] = 0;
    filmIds[i] = i + 1;
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> critics[i];
  }

  for (int film = 0; film < m; ++film) {
    for (int rating = 0; rating < n; ++rating) {
      std::cin >> curRating;
      filmRatings[film] += curRating * critics[rating];
      filmRatings[film] %= 1000000007;
    }
  }

  QuickSort(filmRatings, filmIds, 0, m - 1);

  for (int i = 0; i < k; ++i) {
    std::cout << filmIds[i] << ' ';
  }
  delete[] critics;
  delete[] filmRatings;
  delete[] filmIds;
}
