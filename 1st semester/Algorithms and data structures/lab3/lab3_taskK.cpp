#include <iostream>

struct Node {
  Node* next;
  Node* connected;

  Node() : next(nullptr), connected(nullptr) {}
};

struct list {
  Node* first;

  list() : first(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push() {
    Node* newNode = new Node();
    newNode->next = first;
    first = newNode;
  }

  long getLoopLength(Node* list) {
    Node* slowPointer = list;
    Node* fastPointer = list;

    while (fastPointer && fastPointer->connected && fastPointer->connected->connected) {
      slowPointer = slowPointer->connected;
      fastPointer = fastPointer->connected->connected;
      if (slowPointer == fastPointer) {
        int length = 1;
        fastPointer = fastPointer->connected;
        while (slowPointer != fastPointer) {
          fastPointer = fastPointer->connected;
          length++;
        }
        return length;
      }
    }
    return -1;
  }
};

int main() {
  long n, temp;
  std::cin >> n;
  list staplers;

  long* indexes = new long[n];
  Node** connects = new Node*[n];

  for (int i = 0; i < n; ++i) {
    connects[i] = new Node();
  }

  long i = 0;
  while (std::cin >> temp){
    connects[i]->connected = connects[temp - 1];
    ++i;
  }

  std::cout << staplers.getLoopLength(connects[0]);

  delete[] indexes;
  delete[] connects;

  return 0;
}
