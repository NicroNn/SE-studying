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

struct Num{
  long value;
  int prime;
  int power;

  bool operator<(const Num& right) {
    return (this->value < right.value);
  }
  bool operator==(const Num& right) {
    return (this->value == right.value);
  }
  bool operator<=(const Num& right) {
    return (*this < right || *this == right);
  }
};

std::vector<bool> getPrimes(int n) {
  std::vector<bool> isPrime(n + 1, true);

  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i * i <= n; ++i) {
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }
  return isPrime;
}

void siftDown(std::vector<Num>& heap, int i) {
  while (2 * i + 1 < heap.size()) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int j = l;
    if (r < heap.size() && heap[r] < heap[l]) {
      j = r;
    }
    if (heap[i] <= heap[j]) {
      break;
    }
    std::swap(heap[i], heap[j]);
    i = j;
  }
}

void siftUp(std::vector<Num>& heap, int i){
  while (heap[i] < heap[(i - 1) / 2]){
    std::swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void insert(std::vector<Num>& heap, Num newElement){
  heap.push_back(newElement);
  siftUp(heap, heap.size() - 1);
}


int main(){
  int n;
  std::cin >> n;
  std::vector<bool> primes;
  primes = getPrimes(55000000);

  std::vector<Num> heap;
  std::vector<int> res;

  for (int i = 0; i < 5500000; ++i) {
    if (primes[i]) {
      Num x;
      x.value = i;
      x.power = 1;
      x.prime = i;
      insert(heap, x);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < heap[0].power; ++j) {
      res.push_back(heap[0].prime);
    }
    heap[0].value *= heap[0].value;
    heap[0].power += heap[0].power;
    siftDown(heap, 0);
  }

  QuickSort(res, 0, res.size() - 1);

  int result = res.size();
  std::cout << result << '\n';

  for (int i = 0; i < result; ++i) {
    std::cout << res[i] << ' ';
  }

}
