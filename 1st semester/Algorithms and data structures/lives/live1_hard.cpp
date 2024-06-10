#include <iostream>
#include <cmath>
#include <vector>

void siftDown(std::vector<int>& heap, int i) {
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

void siftUp(std::vector<int>& heap, int i){
  while (heap[i] < heap[(i - 1) / 2]){
    std::swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void extractMin(std::vector<int>& heap) {
  if (heap.size() == 0){
    std::cout << '*' << '\n';
    return;
  }
  int min = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  siftDown(heap, 0);

}

void insert(std::vector<int>& heap, int newElement){
  heap.push_back(newElement);
  siftUp(heap, heap.size() - 1);
}


int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  double currentDist = 0.0;
  double currentSpeed = 1.0;
  double currentTime = 0.0;
  char argChar = ' ';
  int argDigit = 0;
  std::vector<int> ts;
  std::vector<int> ds;
  for (int i = 0; i < n; ++i) {
    std::cin >> argChar >> argDigit;
    if (argChar == 'T') {
      insert(ts, argDigit);
    }
    if (argChar == 'D') {
      insert(ds, argDigit);
    }
  }
  long stops = 1;
  while (currentDist < 1000){
    if (!ts.empty() && ts[0] <= currentTime){
      currentSpeed = 1.0 / (stops + 1.0);
      ++stops;
      extractMin(ts);
    } else if (!ds.empty() && ds[0] <= currentDist){
      currentSpeed = 1.0 / (stops + 1.0);
      ++stops;
      extractMin(ds);
    } else if (!ts.empty() || !ds.empty()){
      currentDist += currentSpeed;
      currentTime += 1.0;
    } else {
      break;
    }
  }
  currentTime += (1000.0 - currentDist) / currentSpeed;
  std::cout << std::ceil(currentTime);
}
