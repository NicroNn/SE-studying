#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


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

    void findConnects(int u, int parent, std::vector<bool>& visited, std::vector<int>& dtime, std::vector<int>& lowTime, std::set<std::pair<int, int>>& bridges, int& time) {
        visited[u] = true;
        dtime[u] = lowTime[u] = ++time;

        for (int v : adj[u]) {
            if (v == parent) continue;

            if (visited[v]) {
                lowTime[u] = std::min(lowTime[u], dtime[v]);
            } else {
                findConnects(v, u, visited, dtime, lowTime, bridges, time);
                lowTime[u] = std::min(lowTime[u], lowTime[v]);

                if (lowTime[v] > dtime[u]) {
                    bridges.insert({std::min(u, v), std::max(u, v)});
                }
            }
        }
    }

    void dfsColor(int index, std::vector<int>& colors, std::vector<bool>& visited, int color, const std::set<std::pair<int, int>>& bridges) {
        visited[index] = true;
        colors[index] = color;

        for (int u : adj[index]) {
            if (!visited[u] && bridges.find({std::min(index, u), std::max(index, u)}) == bridges.end()) {
                dfsColor(u, colors, visited, color, bridges);
            }
        }
    }

    void colorComponents(std::vector<int>& coloring) {
        std::vector<bool> visited(adj.size(), false);
        std::set<std::pair<int, int>> bridges;
        int color = 1;
        int time = 0;

        for (int i = 1; i <= NodeNum; ++i) {
            if (!visited[i]) {
                std::vector<int> dtime(NodeNum + 1, 0);
                std::vector<int> lowTime(NodeNum + 1, 0);
                findConnects(i, -1, visited, dtime, lowTime, bridges, time);
            }
        }

        visited.assign(adj.size(), false);
        for (int i = 1; i <= NodeNum; ++i) {
            if (!visited[i]) {
                dfsColor(i, coloring, visited, color, bridges);
                color++;
            }
        }
    }
};

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;

    Graph graph(n);
    int x, y;
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        graph.addEdge(x, y);
    }
    std::vector<int> colors (n + 1);
    graph.colorComponents(colors);
    for (int i = 0; i < q; ++i) {
        std::cin >> x >> y;
        std::cout << ((colors[x] == colors[y]) ? "YES" : "NO") << '\n';
    }
}
