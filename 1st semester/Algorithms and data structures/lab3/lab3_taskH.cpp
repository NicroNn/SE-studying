#include <iostream>

struct Node {
  long data;
  Node* next;

  Node(long _data) : data(_data), next(nullptr) {}
};

struct list {
  Node* first;

  list() : first(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push(long data) {
    Node* newNode = new Node(data);
    newNode->next = first;
    first = newNode;
  }

  void pop() {
    if (is_empty()) return;
    Node* p = first;
    first = first->next;
    delete p;
  }
};

long MaxArea(long hist[], long n) {
  list stack;
  long maxArea = 0;
  long head;
  long areaWithTop;

  long i = 0;
  while (i < n) {
    if (stack.is_empty() || hist[stack.first->data] <= hist[i])
      stack.push(i++);
    else {
      head = stack.first->data;
      stack.pop();
      areaWithTop = hist[head] * (stack.is_empty() ? i : i - stack.first->data - 1);
      if (maxArea < areaWithTop)
        maxArea = areaWithTop;
    }
  }
  while (!stack.is_empty()) {
    head = stack.first->data;
    stack.pop();
    areaWithTop = hist[head] * (stack.is_empty() ? i : i - stack.first->data - 1);
    if (maxArea < areaWithTop)
      maxArea = areaWithTop;
  }

  return maxArea;
}

int main() {
  long n;
  std::cin >> n;
  long* boards = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> boards[i];
  }
  std::cout << MaxArea(boards, n);
}
