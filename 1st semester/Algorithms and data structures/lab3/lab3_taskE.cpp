#include <iostream>
#include <string>

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
      std::cout << p -> data << " ";
      p = p -> next;
    }
    std::cout << '\n';
  }

  Node* find(std::string _data) {
    Node* p = first;
    while (p && p -> data != _data) p = p -> next;
    return (p && p -> data == _data) ? p : nullptr;
  }

  void remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p -> next;
    delete p;
  }

  void remove_last() {
    if (is_empty()) return;
    if (first == last) {
      remove_first();
      return;
    }
    Node* p = first;
    while (p->next != last) p = p -> next;
    p -> next = nullptr;
    delete last;
    last = p;
  }

  void remove(std::string _data) {
    if (is_empty()) return;
    if (first -> data == _data) {
      remove_first();
      return;
    } else if (last -> data == _data) {
      remove_last();
      return;
    }
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->data != _data) {
      fast = fast -> next;
      slow = slow -> next;
    }
    if (!fast) {
      std::cout << "This element does not exist" << '\n';
      return;
    }
    slow -> next = fast -> next;
    delete fast;
  }

  Node* operator[](const int index) {
    if (is_empty()) return nullptr;
    Node* p = first;
    for (int i = 0; i < index; i++) {
      p = p -> next;
      if (!p) return nullptr;
    }
    return p;
  }

  void push_front(std::string _data) {
    Node* p = new Node(_data);
    if (is_empty()) {
      first = p;
      last = p;
      return;
    }
    p->next = first;
    first = p;
  }
};

void countingSort(std::string& str) {
  const int maxRange = 26;  // Assuming the string contains only uppercase letters
  int count[maxRange] = {0};

  for (char c : str) {
    count[c - 'A']++;
  }

  int index = 0;
  for (int i = 0; i < maxRange; i++) {
    while (count[i] > 0) {
      str[index] = static_cast<char>('A' + i);
      index++;
      count[i]--;
    }
  }
}

std::string expandFormula(const std::string& formula) {
  list stack;
  std::string currentElement = "";
  std::string currentNumber = "1";

  for (char c : formula) {
    if (isalpha(c)) {
      currentElement += c;
    } else if (isdigit(c)) {
      currentNumber += c;
    } else if (c == '(') {
      stack.push_back(currentElement);
      stack.push_back(currentNumber);
      currentElement = "";
      currentNumber = "1";
    } else if (c == ')') {
      std::string expandedFormula = "";
      while (!stack.is_empty() && stack.last->data != "(") {
        std::string number = stack.last->data;
        stack.remove_last();
        std::string element = stack.last->data;
        stack.remove_last();
        expandedFormula += element;
        int multiplier = std::stoi(number);
        for (char& ch : currentElement) {
          expandedFormula += std::to_string(multiplier) + ch;
        }
      }
      stack.push_back(expandedFormula);
      stack.remove_last();  // Pop the '('
    }
  }

  std::string expandedFormula = "";
  while (!stack.is_empty()) {
    std::string number = stack.last->data;
    stack.remove_last();
    std::string element = stack.last->data;
    stack.remove_last();
    expandedFormula += element;
    int multiplier = std::stoi(number);
    for (char& ch : currentElement) {
      expandedFormula += std::to_string(multiplier) + ch;
    }
  }

  countingSort(expandedFormula);

  return expandedFormula;
}

int main() {
  std::string inputFormula;
  std::getline(std::cin, inputFormula);

  std::cout << expandFormula(inputFormula);

  return 0;
}
