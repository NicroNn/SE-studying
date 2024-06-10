#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int shortestCycle(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> visited(n, false);
    std::vector<int> path;
    std::vector<std::vector<int>> cycles;

    std::function<void(int, int, std::vector<int>&, std::vector<int>&)> dfs =
        [&](int v, int parent, std::vector<int>& path, std::vector<int>& visited) {
            visited[v] = true;
            path.push_back(v);

            for (int neighbor : adj[v]) {
                if (neighbor == parent)
                    continue;
                if (!visited[neighbor]) {
                    dfs(neighbor, v, path, visited);
                } else {
                    auto it = std::find(path.rbegin(), path.rend(), neighbor);
                    if (it != path.rend()) {
                        std::vector<int> cycle;
                        cycle.insert(cycle.end(), path.rbegin(), it + 1);
                        std::reverse(cycle.begin(), cycle.end());
                        if (cycle.size() > 2)
                            cycles.push_back(cycle);
                    }
                }
            }
            path.pop_back();
        };

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            std::vector<int> path;
            dfs(i, -1, path, visited);
        }
    }

    int minLength = n + 1;
    for (const auto& cycle : cycles)
        if (cycle.size() < minLength)
            minLength = cycle.size();
    return minLength == n + 1 ? -1 : minLength;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::cout << shortestCycle(n, adj);

    return 0;
}
