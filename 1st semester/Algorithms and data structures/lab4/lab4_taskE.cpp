#include <iostream>

void siftDown(long* heap, long heapSize, long i) {
  while (2 * i + 1 < heapSize){
    long l = 2 * i + 1;
    long r = 2 * i + 2;
    long j = l;
    if (r < heapSize && heap[r] > heap[l]){
      j = r;
    }
    if (heap[i] >= heap[j]){
      break;
    }
    std::swap(heap[i], heap[j]);
    i = j;
  }
}

long extractMin(long* heap, long heapSize){
  long min = heap[0];
  heap[0] = heap[heapSize - 1];
  --heapSize;
  siftDown(heap, heapSize, 0);

  return min;
}

int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  long n;
  std::cin >> n;
  long* a = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = n / 2; i >= 0; --i) {
    siftDown(a, n, i);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << extractMin(a, n - i) << ' ';
  }
  delete[] a;
}
