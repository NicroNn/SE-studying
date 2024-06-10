#include <iostream>
#include <string>
#include <vector>

// Узел BST
struct Node {
    std::string word;
    int count[3]{};
    Node* left, * right;

    Node(std::string w) : word(w), left(nullptr), right(nullptr) {}
};

Node* insert(Node* node, std::string word, int line) {
    if (!node) {
        Node* new_node = new Node(word);
        ++new_node->count[line];
        return new_node;
    }

    if (word < node->word)
        node->left = insert(node->left, word, line);
    else if (word > node->word)
        node->right = insert(node->right, word, line);
    else
        node->count[line]++;

    return node;
}

int calculateScore(Node* node, int line) {
    if (!node) return 0;

    int score = calculateScore(node->left, line) + calculateScore(node->right, line);

    if (node->count[line] == 1) {
        if (node->count[(line + 1) % 3] == 0 && node->count[(line + 2) % 3] == 0)
            score += 3;
        else if (node->count[(line + 1) % 3] == 1 && node->count[(line + 2) % 3] == 0 ||
            node->count[(line + 1) % 3] == 0 && node->count[(line + 2) % 3] == 1)
            score += 1;
    }

    return score;
}

void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    int n;
    std::cin >> n;

    Node* root = nullptr;
    std::string line, word;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> word;
            root = insert(root, word, i);
        }
    }

    for (int i = 0; i < 3; ++i) {
        int a = calculateScore(root, i);
        std::cout << a << ' ';
    }

}
