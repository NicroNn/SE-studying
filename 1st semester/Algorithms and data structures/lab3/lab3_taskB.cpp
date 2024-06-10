#include <iostream>

struct Node {
  long data;
  Node* next;

  Node(long _data) : data(_data), next(nullptr) {}
};

struct list {
  Node* first;
  Node* last;

  list() : first(nullptr), last(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push_back(long _data) {
    Node* p = new Node(_data);
    if (is_empty()) {
      first = p;
      last = p;
      return;
    }
    last -> next = p;
    last = p;
  }

  void print() {
    if (is_empty()) return;
    Node* p = first;
    while (p) {
      std::cout << p -> data << '\n';
      p = p -> next;
    }
  }

  void remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p -> next;
    delete p;
  }

};

int main(){
  list deletedQueue, queue;
  long n;
  std::cin >> n;
  char symbol = ' ';
  long currentQueue = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> symbol;
    if (symbol == '+'){
      std::cin >> currentQueue;
      queue.push_back(currentQueue);
    }
    if (symbol == '-'){
      deletedQueue.push_back(queue.first -> data);
      queue.remove_first();
    }
  }
  deletedQueue.print();
}

