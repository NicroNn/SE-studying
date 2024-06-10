#include <iostream>
#include <vector>

const int INF = 1000000000 + 1e8;

void dijkstra(int v, int n, std::vector<int>& dist, std::vector<int>& used, std::vector<std::vector<std::pair<int, int>>>& graph) {
    dist[v] = 0;
    for (int i = 0; i < n; ++i) {
        used[v] = 1;
        for (auto u : graph[v]) {
            int to = u.first;
            int w = u.second;
            dist[to] = std::min(dist[to], dist[v] + w);
        }
        int minDist = INF;
        for (int j = 0; j < n; ++j) {
            if (minDist > dist[j] && !used[j]) {
                minDist = dist[j];
                v = j;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> graph;
    std::vector<int> dist;
    std::vector<int> used;

    graph.resize(n);
    dist.resize(n, INF);
    used.resize(n);

    int u, v, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({v, w });
    }

    dijkstra(0, n, dist, used, graph);

    std::cout << (dist[n - 1] == INF ? -1 : dist[n - 1]);
}
