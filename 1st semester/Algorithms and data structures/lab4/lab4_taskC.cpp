#include <iostream>
#include <vector>

struct Cook {
  long salary = 0;
  long startOrderTime = 0;
  long orderNeedTime = 0;
};

void siftDown(std::vector<Cook>& heap, long i) {
  while (2 * i + 1 < heap.size()) {
    long l = 2 * i + 1;
    long r = 2 * i + 2;
    long j = l;
    if (r < heap.size() && heap[r].salary < heap[l].salary) {
      j = r;
    }
    if (heap[i].salary <= heap[j].salary) {
      break;
    }
    std::swap(heap[i], heap[j]);
    i = j;
  }
}

Cook extractMin(std::vector<Cook>& heap) {
  if (heap.size() == 0) {
    return Cook();
  }
  Cook min = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  siftDown(heap, 0);

  return min;
}

void siftUp(std::vector<Cook>& heap, long i) {
  while (heap[i].salary < heap[(i - 1) / 2].salary) {
    std::swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void insert(std::vector<Cook>& heap, Cook newCook) {
  heap.push_back(newCook);
  siftUp(heap, heap.size() - 1);
}

void heapify(std::vector<Cook>& heap) {
  for (int i = heap.size() / 2; i >= 0; --i) {
    siftDown(heap, i);
  }
}

void siftDownTime(std::vector<Cook>& heap, long i) {
  while (2 * i + 1 < heap.size()) {
    long l = 2 * i + 1;
    long r = 2 * i + 2;
    long j = l;
    if (r < heap.size()
        && heap[r].startOrderTime + heap[r].orderNeedTime < heap[l].startOrderTime + heap[l].orderNeedTime) {
      j = r;
    }
    if (heap[i].startOrderTime + heap[i].orderNeedTime <= heap[j].startOrderTime + heap[j].orderNeedTime) {
      break;
    }
    std::swap(heap[i], heap[j]);
    i = j;
  }
}

Cook extractMinTime(std::vector<Cook>& heap) {
  if (heap.size() == 0) {
    return Cook();
  }
  Cook min = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  siftDownTime(heap, 0);

  return min;
}

void siftUpTime(std::vector<Cook>& heap, long i) {
  while (heap[i].startOrderTime + heap[i].orderNeedTime
      < heap[(i - 1) / 2].startOrderTime + heap[(i - 1) / 2].orderNeedTime) {
    std::swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void insertTime(std::vector<Cook>& heap, Cook newCook) {
  heap.push_back(newCook);
  siftUpTime(heap, heap.size() - 1);
}

int main() {
  long n, m, sum = 0;
  std::cin >> n >> m;
  std::vector<Cook> freeCooks(n), busyCooks;
  for (int i = 0; i < n; ++i) {
    std::cin >> freeCooks[i].salary;
  }
  heapify(freeCooks);
  long t, f;
  for (int i = 0; i < m; ++i) {
    std::cin >> t >> f;
    while (!busyCooks.empty() && busyCooks[0].startOrderTime + busyCooks[0].orderNeedTime <= t) {
      Cook doneCook = extractMinTime(busyCooks);
      insert(freeCooks, doneCook);
    }

    if (freeCooks.empty()) {
      continue;
    }
    Cook currentCook = extractMin(freeCooks);
    currentCook.startOrderTime = t;
    currentCook.orderNeedTime = f;
    sum += currentCook.salary * f;
    insertTime(busyCooks, currentCook);
  }

  std::cout << sum;
}
