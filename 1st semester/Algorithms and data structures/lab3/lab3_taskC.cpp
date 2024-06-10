#include <iostream>

struct Node {
  std::string data;
  Node* next;

  Node(std::string _data) : data(_data), next(nullptr) {}
};

struct list {
  Node* first;
  Node* last;

  list() : first(nullptr), last(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push_back(std::string _data) {
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
};

void sortList(list& l, long k, long t) {
  Node* current = l.first;
  Node* index = nullptr;
  std::string tempData;

  if (l.first == nullptr) {
    return;
  }

  while (current != nullptr) {
    index = current -> next;

    while (index != nullptr) {
      if (current->data.substr(k - t) > index->data.substr(k - t)) {
        tempData = current -> data;
        current -> data = index -> data;
        index -> data = tempData;
      }
      index = index -> next;
    }
    current = current -> next;
  }
}

int main(){
  long n, k, t;
  list messages;
  std::string message = " ";
  std::cin >> n >> k >> t;
  for (int i = 0; i < n; ++i) {
    std::cin >> message;
    messages.push_back(message);
  }
  sortList(messages, k, t);
  messages.print();
}
