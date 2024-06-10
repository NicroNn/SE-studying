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
    std::cout << first -> data << '\n';
    first = first->next;
    delete p;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  list messages;
  long n;
  std::cin >> n;
  char symbol = ' ';
  long currentMessage = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> symbol;
    if (symbol == '-') {

      messages.pop();
    }
    if (symbol == '+'){
      std::cin >> currentMessage;
      messages.push(currentMessage);
    }
  }
}