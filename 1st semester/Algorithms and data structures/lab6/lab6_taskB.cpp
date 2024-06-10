#include <iostream>

class Node {
  public:
    int key;
    Node* left;
    Node* right;
    int height = 0;
    int number = 0;
};

int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

void upd(Node* x) {
    x->height = std::max(height(x->right), height(x->left)) + 1;
}

Node* newNode(int key) {
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

Node* insertNode(Node* node, int key) {
    if (node == nullptr)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

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

void set_numbers(Node* root) {
    if (root == nullptr) return;
    static int number = 1;
    root->number = number;
    ++number;
    set_numbers(root->left);
    set_numbers(root->right);
}

void levelOrder(Node* root) {
    if (root == nullptr) return;
    std::cout << root->key << ' ';
    root->left ? std::cout << root->left->number << ' ' : std::cout << "0 ";
    root->right ? std::cout << root->right->number << '\n' : std::cout << "0\n";
    levelOrder(root->left);
    levelOrder(root->right);
}

Node* balance(Node* root) {
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


int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;

    Node* arr = new Node[n];
    for (int i = 0; i < n; ++i) {
        int value, left, right;
        std::cin >> value >> left >> right;
        arr[i].key = value;
        arr[i].left = left == 0 ? nullptr : &arr[left - 1];
        arr[i].right = right == 0 ? nullptr : &arr[right - 1];
    }
    Node* root = &arr[0];
    for (int i = n - 1; i > 0; --i) {
        upd(&arr[i]);
    }
    root = balance(root);
    set_numbers(root);
    std::cout << n << '\n';
    levelOrder(root);

}