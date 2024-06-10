#include <iostream>
#include <vector>
#include <stack>

void dfsTopSort(int vertexNo, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::stack<int>& stack) {
    visited[vertexNo] = true;

    for (int i = 0; i < graph[vertexNo].size(); ++i) {
        int adj = graph[vertexNo][i];
        if (!visited[adj]) {
            dfsTopSort(adj, graph, visited, stack);
        }
    }

    stack.push(vertexNo);
}

std::vector<int> topologicalSort(std::vector<std::vector<int>>& graph, int vertex) {
    std::vector<bool> visited(vertex, false);
    std::stack<int> stack;
    std::vector<int> result;

    for (int i = 0; i < vertex; ++i) {
        if (!visited[i]) {
            dfsTopSort(i, graph, visited, stack);
        }
    }

    while (!stack.empty()) {
        result.push_back(stack.top() + 1);
        stack.pop();
    }

    return result;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    std::vector<int> gifts (n);

    int giftNo1, giftNo2;
    for (int k = 0; k < m; ++k) {
        std::cin >> giftNo1 >> giftNo2;
        graph[giftNo1 - 1].push_back(giftNo2 - 1);
    }

    gifts = topologicalSort(graph, n);
    std::vector<int> result (n);
    for (int i = 0; i < gifts.size(); ++i) {
        result[gifts[i] - 1] = i;
    }
    for (int i : result) {
        std::cout << i + 1 << ' ';
    }
}
