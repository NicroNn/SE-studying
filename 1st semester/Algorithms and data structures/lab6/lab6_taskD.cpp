#include <iostream>

class Node {
  public:
    std::string key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

Node* newNode(std::string key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return (node);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalanceFactor(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

int countUniqueChars(const std::string& str) {
    int count = 0;
    bool charSet[256]{};

    for (char ch : str) {
        if (!charSet[static_cast<unsigned char>(ch)]) {
            charSet[static_cast<unsigned char>(ch)] = true;
            count++;
        }
    }

    return count;
}

Node* insertNode(Node* node, std::string key, int& counter) {
    if (node == nullptr)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key, counter);
    else if (key > node->key)
        node->right = insertNode(node->right, key, counter);
    else {
        counter += countUniqueChars(key);
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        } else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        } else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Node* nodeWithMaxValue(Node* node) {
    Node* current = node;
    while (current->right != nullptr)
        current = current->right;
    return current;
}

bool contains(Node* root, std::string key) {
    if (root == nullptr)
        return false;
    if (key < root->key)
        return contains(root->left, key);
    else if (key > root->key)
        return contains(root->right, key);
    else
        return true;
}

Node* deleteNode(Node* root, std::string key) {
    if (!contains(root, key))
        return root;

    if (root == nullptr)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
        } else {
            Node* temp = nodeWithMaxValue(root->left);
            root->key = temp->key;
            root->left = deleteNode(root->left, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void printTree(Node* root, std::string indent, bool last) {
    if (root != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->key << '\n';
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    Node* root = nullptr;
    int n;
    std::cin >> n;
    std::string string;
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> string;
        root = insertNode(root, string, counter);
    }
    std::cout << counter;
}