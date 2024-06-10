#include <iostream>
#include <vector>

void siftDown(std::vector<long>& heap, long i) {
  while (2 * i + 1 < heap.size()) {
    long l = 2 * i + 1;
    long r = 2 * i + 2;
    long j = l;
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

void siftUp(std::vector<long>& heap, long i){
  while (heap[i] < heap[(i - 1) / 2]){
    std::swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void extractMin(std::vector<long>& heap) {
  if (heap.size() == 0){
    std::cout << '*' << '\n';
    return;
  }
  long min = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  siftDown(heap, 0);

  std::cout << min << '\n';
}

void insert(std::vector<long>& heap, long newElement){
  heap.push_back(newElement);
  siftUp(heap, heap.size() - 1);
}

void heapify(std::vector<long>& heap){
  for (int i = heap.size() / 2; i >= 0; --i) {
    siftDown(heap, i);
  }
}

void merge(std::vector<long>& heap1, std::vector<long>& heap2){
  for (long i : heap2) {
    insert(heap1, i);
  }
  heapify(heap1);
}

void decreaseKey(std::vector<long>& heap, long oldData, long newData){
  for (int i = 0; i < heap.size(); ++i) {
    if (heap[i] == oldData){
      heap[i] = newData;
      siftUp(heap, i);
      break;
    }
  }
}


int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::string command;
  long k, x, y, m;
  std::vector<std::vector<long>> heaps;
  while (std::cin >> command) {
    if (command == "create") {
      heaps.emplace_back();
    }
    if (command == "insert") {
      std::cin >> k >> x;
      insert(heaps[k], x);
    }
    if (command == "extract-min") {
      std::cin >> k;
      extractMin(heaps[k]);
    }
    if (command == "merge") {
      std::cin >> k >> m;
      std::vector newHeap = heaps[k];
      merge(newHeap, heaps[m]);
      heaps.push_back(newHeap);
    }
    if (command == "decrease-key") {
      std::cin >> k >> x >> y;
      decreaseKey(heaps[k], x, y);
    }
  }
}
