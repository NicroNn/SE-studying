#include <iostream>

class Node {
  public:
    int key;
    Node* left;
    Node* right;
};


Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return (node);
}

Node* insertNode(Node* node, int key) {
    if (node == nullptr)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    return node;
}

Node* nodeWithMinimumValue(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

bool contains(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (key < root->key)
        return contains(root->left, key);
    else if (key > root->key)
        return contains(root->right, key);
    else
        return true;
}

Node* deleteNode(Node* root, int key) {
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
            Node* temp = nodeWithMinimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    return root;
}

void next(Node* root, int x) {
    Node* current = root;
    Node* successor = nullptr;
    while (current != nullptr) {
        if (current->key > x) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (successor == nullptr) {
        std::cout << "none\n";
        return;
    };
    std::cout << successor->key << '\n';
}

void prev(Node* root, int x) {
    Node* current = root;
    Node* predecessor = nullptr;
    while (current != nullptr) {
        if (current->key < x) {
            predecessor = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    if (predecessor == nullptr) {
        std::cout << "none\n";
        return;
    };
    std::cout << predecessor->key << '\n';
}


int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    Node* root = nullptr;
    int x;
    std::string command;
    while (std::cin >> command >> x) {
        if (command == "insert") {
            root = insertNode(root, x);
        }
        if (command == "delete") {
            root = deleteNode(root, x);
        }
        if (command == "exists") {
            if (contains(root, x)) {
                std::cout << "true" << '\n';
            } else {
                std::cout << "false" << '\n';
            }
        }
        if (command == "next"){
            next(root, x);
        }
        if (command == "prev"){
            prev(root, x);
        }

    }
}