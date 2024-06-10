#include <iostream>
#include <stack>
#include <limits>
#include <sstream>

struct Node {
    int key;
    Node *left, *right;
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

bool isBST(Node* node, int minKey, int maxKey) {
    if (node == nullptr) {
        return true;
    }
    if (node->key <= minKey || node->key >= maxKey) {
        return false;
    }
    return isBST(node->left, minKey, node->key) && isBST(node->right, node->key, maxKey);
}

int sumOfTree(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->key + sumOfTree(node->left) + sumOfTree(node->right);
}

int findMaxBSTSum(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (isBST(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())) {
        return sumOfTree(root);
    }
    return std::max(findMaxBSTSum(root->left), findMaxBSTSum(root->right));
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    std::stack<Node*> stack;
    Node *root = nullptr, *current = nullptr;

    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            int key = std::stoi(token);
            Node* node = new Node(key);
            if (root == nullptr) {
                root = node;
            } else if (!stack.empty()) {
                current = stack.top();
                if (current->left == nullptr) {
                    current->left = node;
                } else {
                    current->right = node;
                }
            }
            stack.push(node);
        } else if (token == "u") {
            if (!stack.empty()) stack.pop();
        }
    }
    if (!stack.empty()) {
        root = stack.top();
    }
    int maxSum = findMaxBSTSum(root);
    std::cout << maxSum;
}
