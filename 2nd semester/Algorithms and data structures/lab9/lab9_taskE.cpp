#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct Graph {
    int NodeNum;
    std::vector<std::vector<int>> adj;

    Graph(int n) : NodeNum(n) {
        adj.resize(NodeNum + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<std::pair<int, int>> findConnects() {

        std::vector<bool> visited(NodeNum + 1, false);
        std::vector<int> dtime(NodeNum + 1, 0);
        std::vector<int> lowTime(NodeNum + 1, 0);
        std::vector<std::pair<int, int>> bridges;
        int time = 0;

        std::function<void(int, int)> pFunction = [&](int u, int parent) {
            visited[u] = true;
            dtime[u] = lowTime[u] = ++time;

            for (int v : adj[u]) {
                if (v == parent) continue;

                if (visited[v]) {
                    lowTime[u] = std::min(lowTime[u], dtime[v]);
                } else {
                    pFunction(v, u);
                    lowTime[u] = std::min(lowTime[u], lowTime[v]);

                    if (lowTime[v] > dtime[u]) {
                        bridges.emplace_back(std::min(u, v), std::max(u, v));
                    }
                }
            }
        };

        for (int i = 1; i <= NodeNum; ++i) {
            if (!visited[i]) {
                pFunction(i, -1);
            }
        }

        return bridges;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int st, ed;
        std::cin >> st >> ed;
        graph.addEdge(st, ed);
    }

    std::vector<std::pair<int, int>> bridges = graph.findConnects();
    sort(bridges.begin(), bridges.end());

    for (const auto& bridge : bridges) {
        std::cout << bridge.first << " " << bridge.second << '\n';
    }
}
