#include <iostream>

class Node {
  public:
    int key;
    Node* left;
    Node* right;
    int right_num = 1;
};


Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return (node);
}

Node* insertNode(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }
    if (key > node->key) {
        node->right = insertNode(node->right, key);
    }
    else if (key < node->key) {
        node->left = insertNode(node->left, key);
    }
    ++node->right_num;

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
    if (root == nullptr) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            return temp;
        }
        Node* temp = nodeWithMinimumValue(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    root->right_num--;
    return root;
}

int k_maximal(Node* root, int k) {
    if (root == nullptr) {
        return -1;
    }
    int rc = root->right ? root->right->right_num : 0;
    if (rc + 1 == k) {
        return root->key;
    } else if (rc >= k) {
        return k_maximal(root->right, k);
    } else {
        k -= rc + 1;
        return k_maximal(root->left, k);
    }
}


int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    Node* root = nullptr;
    int n, x;
    std::string command;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> command >> x;
        if (command == "1") {
            root = insertNode(root, x);
        }
        if (command == "-1") {
            root = deleteNode(root, x);
        }
        if (command == "0") {
            std::cout << k_maximal(root, x) << '\n';
        }

    }
}