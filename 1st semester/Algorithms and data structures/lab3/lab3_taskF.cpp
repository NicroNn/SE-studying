#include <iostream>

struct Node {
  long data;
  long index;
  Node* next;

  Node(long _data, long _index) : data(_data), index(_index), next(nullptr) {}
};

struct list {
  Node* first;

  list() : first(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push(long data, long index) {
    Node* newNode = new Node(data, index);
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

int main() {
  long n;
  std::cin >> n;
  long* tasks = new long[n];
  long* answer = new long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> tasks[i];
    answer[i] = -1;
  }
  list stack;
  for (int i = 0; i < n; ++i) {
   while (!stack.is_empty() && stack.first->data < tasks[i]) {
      answer[stack.first->index] = (i - stack.first->index);
      stack.pop();
    }
    stack.push(tasks[i], i);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << answer[i] << ' ';
  }
  delete[] tasks;
  delete[] answer;
}
