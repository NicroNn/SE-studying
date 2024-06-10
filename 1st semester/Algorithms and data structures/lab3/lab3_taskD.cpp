#include <iostream>

struct Node {
  int data;
  Node* next;
  Node* prev;

  Node(int _data) : data(_data), next(nullptr), prev(nullptr) {}
};

struct list {
  Node* first;
  Node* last;

  list() : first(nullptr), last(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push_back(int _data) {
    Node* p = new Node(_data);
    if (is_empty()) {
      first = p;
      last = p;
      return;
    }
    p->prev = last;
    last->next = p;
    last = p;
  }

  void print() {
    if (is_empty()) return;
    Node* p = first;
    while (p) {
      std::cout << p->data << " ";
      p = p->next;
    }
  }

  void remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    if (first) {
      first->prev = nullptr;
    } else {
      last = nullptr;
    }
    delete p;
  }

  void remove_last() {
    if (is_empty()) return;
    if (first == last) {
      remove_first();
      return;
    }
    Node* p = last;
    last = p->prev;
    last->next = nullptr;
    delete p;
  }
};


int main() {
  int n, m, weigh, tempFirst, tempLast, tempMed, tempMax;
  std::cin >> n >> m;
  list treasures;
  for (int i = 0; i < n; ++i) {
    std::cin >> weigh;
    if (i + 1 <= m) {
      treasures.push_back(weigh);
    } else {
      tempFirst = treasures.first->data;
      tempLast = treasures.last->data;

      treasures.remove_first();
      treasures.remove_last();

      tempMax = std::max(std::max(tempFirst, tempLast), weigh);
      tempMed = tempLast + tempFirst + weigh - std::min(std::min(tempFirst, tempLast), weigh) - tempMax;
      treasures.push_back(tempMed);
      treasures.push_back(tempMax);

    }
  }
  treasures.print();
}
