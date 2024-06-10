#include <iostream>
#include <vector>
#include <queue>

void pruferCode(std::vector<std::vector<int>>& graph, int& n) {
    std::vector<int> degree(n, 0);
    std::vector<int> prufer(n - 2);
    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;

    for (int i = 0; i < n; ++i) {
        degree[i] = graph[i].size();
        if (degree[i] == 1) {
            leaves.push(i);
        }
    }

    int index = 0;
    int neighbor;
    int leaf;
    while (index < n - 2) {
        leaf = leaves.top();
        leaves.pop();
        neighbor = -1;
        for (int i : graph[leaf]) {
            if (degree[i] > 0) {
                neighbor = i;
                break;
            }
        }
        std::cout << neighbor + 1 << ' ';
        ++index;

        --degree[neighbor];
        --degree[leaf];
        if (degree[neighbor] == 1) {
            leaves.push(neighbor);
        }
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n + 1);
    int u, v;
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pruferCode(adj, n);
}
