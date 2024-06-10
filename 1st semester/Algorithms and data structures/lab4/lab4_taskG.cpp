#include <iostream>
#include <cmath>
#include <vector>

class Node {
 public:
  Node* parent;
  Node* child;
  Node* left;
  Node* right;
  int key;
  int degree;
  char mark;
  char c;

  Node() {
    parent = nullptr;
    child = nullptr;
    left = nullptr;
    right = nullptr;
    key = -1;
    degree = -1;
    mark = ' ';
    c = ' ';
  }
};

class FibonacciHeap {
 public:
  Node* mini;
  int no_of_nodes;

  FibonacciHeap() : mini(nullptr), no_of_nodes(0) {}

  void insertion(int val);
  void ExtractMin();
  void Consolidate();
  void display();
  void decreaseKey(Node* node, int newKey);
  void cut(Node* child, Node* parent);
  void cascadingCut(Node* node);
  Node* findNode(int x);
};

void FibonacciHeap::insertion(int val) {
  Node* new_node = new Node();
  new_node->key = val;
  new_node->degree = 0;
  new_node->mark = 'W';
  new_node->c = 'N';
  new_node->parent = nullptr;
  new_node->child = nullptr;
  new_node->left = new_node;
  new_node->right = new_node;

  if (mini != nullptr) {
    mini->left->right = new_node;
    new_node->right = mini;
    new_node->left = mini->left;
    mini->left = new_node;

    if (new_node->key < mini->key) {
      mini = new_node;
    }
  } else {
    mini = new_node;
  }

  no_of_nodes++;
}

void FibonacciHeap::ExtractMin() {
  if (mini == nullptr) {
    std::cout << '*' << '\n';
    return;
  }

  Node* extractedMin = mini;
  std::cout << extractedMin->key << '\n';

  if (extractedMin->child != nullptr) {
    Node* child = extractedMin->child;
    do {
      Node* nextChild = child->right;
      mini->left->right = child;
      child->right = mini;
      child->left = mini->left;
      mini->left = child;
      child->parent = nullptr;
      child = nextChild;
    } while (child != extractedMin->child);
  }

  extractedMin->left->right = extractedMin->right;
  extractedMin->right->left = extractedMin->left;

  if (extractedMin == extractedMin->right) {
    mini = nullptr;
  } else {
    mini = extractedMin->right;
    Consolidate();
  }

  no_of_nodes--;
  delete extractedMin;
}

void link(Node* smaller, Node* larger) {
  smaller->left->right = smaller->right;
  smaller->right->left = smaller->left;

  smaller->parent = larger;
  if (larger->child == nullptr) {
    larger->child = smaller;
    smaller->left = smaller;
    smaller->right = smaller;
  } else {
    smaller->left = larger->child->left;
    smaller->right = larger->child;
    larger->child->left->right = smaller;
    larger->child->left = smaller;
  }

  larger->degree++;
  smaller->mark = 'N';
}


void FibonacciHeap::Consolidate() {
  int maxDegree = static_cast<int>(log2(no_of_nodes)) + 1;
  std::vector<Node*> degreeTable(maxDegree, nullptr);

  std::vector<Node*> roots;
  Node* current = mini;
  do {
    roots.push_back(current);
    current = current->right;
  } while (current != mini);

  for (Node* root : roots) {
    int degree = root->degree;
    while (degreeTable[degree] != nullptr) {
      Node* other = degreeTable[degree];
      if (root->key > other->key) {
        std::swap(root, other);
      }
      link(other, root);
      degreeTable[degree] = nullptr;
      degree++;
    }
    degreeTable[degree] = root;
  }

  mini = nullptr;
  for (Node* root : degreeTable) {
    if (root != nullptr) {
      if (mini == nullptr) {
        mini = root;
      } else {
        root->left->right = root->right;
        root->right->left = root->left;

        root->left = mini->left;
        root->right = mini;
        mini->left->right = root;
        mini->left = root;

        if (root->key < mini->key) {
          mini = root;
        }
      }
    }
  }
}

void FibonacciHeap::decreaseKey(Node* node, int newKey) {
  if (node == nullptr){
    return;
  }
  if (newKey > node->key) {
    return;
  }

  node->key = newKey;
  Node* parent = node->parent;

  if (parent != nullptr && node->key < parent->key) {
    cut(node, parent);
    cascadingCut(parent);
  }

  if (node->key < mini->key) {
    mini = node;
  }
}

void FibonacciHeap::cut(Node* child, Node* parent) {
  child->left->right = child->right;
  child->right->left = child->left;
  parent->degree--;

  if (parent->child == child) {
    parent->child = child->right;
  }

  if (parent->degree == 0) {
    parent->child = nullptr;
  }

  child->left = mini->left;
  child->right = mini;
  mini->left->right = child;
  mini->left = child;

  child->parent = nullptr;
  child->mark = 'N';
}

void FibonacciHeap::cascadingCut(Node* node) {
  Node* parent = node->parent;

  if (parent != nullptr) {
    if (node->mark == 'W') {
      node->mark = 'N';
    } else {
      cut(node, parent);
      cascadingCut(parent);
    }
  }
}

Node* findNodeHelper(Node* startNode, int x) {
  if (startNode == nullptr) {
    return nullptr;
  }

  Node* current = startNode;
  do {
    if (current->key == x) {
      return current;
    }

    Node* childResult = findNodeHelper(current->child, x);
    if (childResult != nullptr) {
      return childResult;
    }

    current = current->right;
  } while (current != startNode);

  return nullptr;
}

Node* FibonacciHeap::findNode(int x) {
  if (mini == nullptr){
    return nullptr;
  }
  return findNodeHelper(mini, x);
}

void FibonacciHeap::display() {
  Node* ptr = mini;

  if (ptr == nullptr) {
    std::cout << "The Heap is Empty" << '\n';
  } else {
    while (true) {
      std::cout << ptr->key;

      ptr = ptr->right;

      if (ptr != mini) {
        std::cout << "-->";
      }

      if (!(ptr != mini && ptr->right != nullptr)) {
        std::cout << '\n';
        break;
      }
    }
  }
}

void merge(Node* mergingRoot, FibonacciHeap& merged) {
  if (mergingRoot == nullptr){
    return;
  }

  Node* startNode = mergingRoot;
  bool start = true;

  while (mergingRoot != startNode || start) {
    start = false;

    if (mergingRoot->child != nullptr) {
      merge(mergingRoot->child, merged);
    }
    merged.insertion(mergingRoot->key);
    mergingRoot = mergingRoot->right;
  }
}

int main() {
  std::string command;
  long k, x, y, m;
  std::vector<FibonacciHeap> heaps;
  while (std::cin >> command) {
    if (command == "create") {
      heaps.emplace_back();
    }
    if (command == "insert") {
      std::cin >> k >> x;
      if (k > heaps.size() || heaps.empty()){
        continue;
      }
      heaps[k].insertion(x);
    }
    if (command == "extract-min") {
      std::cin >> k;
      if (k > heaps.size() || heaps.empty()){
        continue;
      }
      heaps[k].ExtractMin();
    }
    if (command == "merge") {
      std::cin >> k >> m;
      if (k > heaps.size() || m > heaps.size() || heaps.empty()){
        continue;
      }
      FibonacciHeap newHeap;
      merge(heaps[k].mini, newHeap);
      merge(heaps[m].mini, newHeap);
      heaps.push_back(newHeap);
    }
    if (command == "decrease-key") {
      std::cin >> k >> x >> y;
      if (k > heaps.size() || heaps.empty()){
        continue;
      }
      heaps[k].decreaseKey(heaps[k].findNode(x), y);
    }
  }
}
