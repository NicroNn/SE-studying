#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <cinttypes>

#define INF 1e12

struct Edge {
    int64_t to;
    int64_t weight;
    Edge(int64_t _to, int64_t _weight) : to(_to), weight(_weight) {}
};

int64_t primMST(std::vector<std::vector<Edge>>& graph, int64_t V) {
    std::vector<int64_t> parent(V, -1);
    std::vector<bool> inMST(V, false);
    std::vector<int64_t> key(V, INF);

    std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>, std::greater<std::pair<int64_t, int64_t>>> pq;

    int64_t src = 0;
    pq.push(std::make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()) {
        int64_t u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto& edge : graph[u]) {
            int64_t v = edge.to;
            int64_t weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push(std::make_pair(key[v], v));
            }
        }
    }
    int64_t res = 0;
    for (int64_t i = 1; i < V; ++i) {
        res += key[i];
    }

    return res;
}

int main() {
    int64_t V, E;
    std::cin >> V >> E;

    std::vector<std::vector<Edge>> graph(V);

    for (int64_t i = 0; i < E; ++i) {
        int64_t from, to, weight;
        std::cin >> from >> to >> weight;
        --from;
        --to;
        graph[from].push_back(Edge(to, weight));
        graph[to].push_back(Edge(from, weight));
    }

    std::cout << primMST(graph, V);
}

