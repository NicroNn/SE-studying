#include <iostream>

struct Node {
    std::string key;
    Node* left{};
    Node* right{};
    int left_num = 1;
};

Node* newNode(std::string key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* insertNode(Node* node, std::string key) {
    if (node == nullptr) {
        return newNode(key);
    }
    if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else if (key <= node->key) {
        node->left = insertNode(node->left, key);
    }
    ++node->left_num;

    return node;
}

std::string k_minimal(Node* root, int k) {
    if (root == nullptr) {
        return "";
    }
    int lc = root->left ? root->left->left_num : 0;
    if (lc + 1 == k) {
        return root->key;
    } else if (lc >= k) {
        return k_minimal(root->left, k);
    } else {
        k -= lc + 1;
        return k_minimal(root->right, k);
    }
}

int main() {
    Node* root = nullptr;
    int n;
    std::string x;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        if (isdigit(x[0])) {
            int k = std::stoi(x);
            std::cout << k_minimal(root, k) << '\n';
        } else {
            root = insertNode(root, x);
        }
    }
}
