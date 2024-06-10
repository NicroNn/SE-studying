#include <iostream>
#include <queue>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

void insert(Node*& root, int key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    if (key < root->key) {
        insert(root->left, key);
    } else {
        if (key != root->key) {
            insert(root->right, key);
        }
    }
}

void printRightmostNodes(Node* root) {
    if (!root) return;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();
        for (int i = 1; i <= n; i++) {
            Node* temp = q.front();
            q.pop();

            if (i == n) {
                std::cout << temp->key << " ";
            }

            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

int main() {
    Node* root = nullptr;
    int n, val;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        insert(root, val);
    }
    printRightmostNodes(root);
}
