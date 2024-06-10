#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>


struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void buildHuffmanTree(std::string text) {
    std::unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top();    pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    std::unordered_map<char, std::string> huffmanCode;
    encode(root, "", huffmanCode);

    std::string str = "";
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    std::cout << str.length();
}

int main() {
    std::string string;
    std::cin >> string;
    buildHuffmanTree(string);
}
