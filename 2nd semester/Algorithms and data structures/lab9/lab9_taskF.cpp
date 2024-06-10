#include <iostream>
#include <vector>
#include <set>

const long INF = 2e18;

struct edge {
    int u, v;
    int w;
};

bool hasNegativeCycle(std::vector<edge> graph, std::vector<long> dist, std::vector<int> p, int n, int m, int k) {
    int change;
    for (int i = 0; i < n; ++i) {
        change = -1;
        for (int j = 0; j < m; ++j) {
            if (dist[graph[j].v] > dist[graph[j].u] + graph[j].w) {
                dist[graph[j].v] = std::max(-INF, dist[graph[j].u] + graph[j].w);
                p[graph[j].v] = graph[j].u;
                change = graph[j].v;
            }
        }
    }
    if (change == -1) {
        return true;
    }
    int y = change;
    for (int i = 0; i < n; ++i) {
        y = p[y];
    }
    std::vector<int> path;
    for (int cur = y;; cur = p[cur]) {
        path.push_back(cur);
        if (cur == y && path.size() > 1)
            break;
    }
    if (path.size() > k) {
        return false;
    } else {
        return true;
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<edge> graph;
    std::vector<long> dist;
    std::vector<int> p;
    int n, m, k;
    int blocks = 1;

    std::cin >> blocks >> k;

    while (blocks--) {
        std::cin >> n >> m;
        graph.resize(m);
        p.resize(n, -1);
        dist.resize(n, INF);
        int u, v;
        int w;

        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v >> w;
            u--;
            v--;
            graph[i] = {u, v, w};
        }

        std::cout << (hasNegativeCycle(graph, dist, p, n, m, k) ? "YES\n" : "NO\n");
    }
}
