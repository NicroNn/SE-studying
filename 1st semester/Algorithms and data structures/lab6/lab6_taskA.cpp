#include <iostream>

struct Node {
    int key{};
    int key_left{};
    int key_right{};
    int height{};
};

int calculateHeights(Node* nodes, int current) {
    if (current == -1) {
        return 0;
    }
    nodes[current].height = std::max(calculateHeights(nodes, nodes[current].key_left),
                                     calculateHeights(nodes, nodes[current].key_right)) + 1;

    return nodes[current].height;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, l, r;
    std::cin >> n;
    Node* nodes = new Node[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> nodes[i].key >> l >> r;
        nodes[i].key_left = l - 1;
        nodes[i].key_right = r - 1;
    }
    calculateHeights(nodes, 0);
    for (int i = 0; i < n; ++i) {
        int right_height = (nodes[i].key_right != -1) ? nodes[nodes[i].key_right].height : 0;
        int left_height = (nodes[i].key_left != -1) ? nodes[nodes[i].key_left].height : 0;

        std::cout << right_height - left_height << '\n';
    }

}
