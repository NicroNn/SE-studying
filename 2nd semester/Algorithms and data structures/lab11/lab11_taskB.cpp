#include <iostream>
#include <vector>
#include <queue>
#include <limits>

bool bfs(std::vector<std::vector<int>>& rGraph, int s, int t, std::vector<int>& parent) {
    int V = rGraph.size();
    std::vector<bool> visited(V, false);

    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

int fordFulkerson(std::vector<std::vector<int>>& graph, int s, int t) {
    int V = graph.size();
    std::vector<std::vector<int>> rGraph = graph;

    std::vector<int> parent(V);

    int maxFlow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, rGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        --u, --v;
        graph[u][v] = capacity;
    }

    std::cout << fordFulkerson(graph, 0, n - 1);
}
