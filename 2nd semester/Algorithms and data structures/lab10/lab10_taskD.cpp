#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

void dfs(int v, std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u, adj, visited);
        }
    }
}

void eulerianCycle(int v, std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<bool> visited(n, false);
    dfs(v, adj, visited);

    for (int i = 1; i < n; ++i) {
        if (adj[i].size() > 0 && !visited[i]) {
            std::cout << ":(";
            return;
        }
    }

    std::vector<int> degree(n, 0);
    for (int i = 0; i < n; ++i) {
        degree[i] = adj[i].size();
    }

    for (int deg : degree) {
        if (deg % 2 != 0) {
            std::cout << ":(";
            return;
        }
    }

    std::stack<int> stk;
    std::vector<int> path;
    stk.push(v);
    while (!stk.empty()) {
        int u = stk.top();
        if (!adj[u].empty()) {
            int next = adj[u].front();
            adj[u].erase(adj[u].begin());
            auto it = find(adj[next].begin(), adj[next].end(), u);
            adj[next].erase(it);
            stk.push(next);
        } else {
            stk.pop();
            path.push_back(u);
        }
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] + 1 << ' ';
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n + 1);
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    eulerianCycle(0, adj);
}
