#include <iostream>
#include <vector>
#include <queue>
#include <climits>



void dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int start, int end, std::vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INT_MAX);
    dist[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<std::pair<int, int>>> graph(n);

    for (int i = 0; i < m; ++i) {
        int si, ti;
        std::cin >> si >> ti;
        std::vector<int> islands(si);
        for (int j = 0; j < si; ++j) {
            std::cin >> islands[j];
            islands[j]--;
        }
        for (int j = 0; j < si; ++j) {
            for (int l = j + 1; l < si; ++l) {
                graph[islands[j]].emplace_back(islands[l], ti);
                graph[islands[l]].emplace_back(islands[j], ti);
            }
        }
    }

    std::vector<int> dist;
    dijkstra(graph, 0, k-1, dist);

    std::cout << (dist[k-1] == INT_MAX ? -1 : dist[k-1]);
}
