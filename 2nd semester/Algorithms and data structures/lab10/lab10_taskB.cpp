#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

#define INF INT_MAX

struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

int primMST(std::vector<std::vector<Edge>>& graph, int V) {
    std::vector<int> parent(V, -1);
    std::vector<bool> inMST(V, false);
    std::vector<int> key(V, INF);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int src = 0;
    pq.push(std::make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push(std::make_pair(key[v], v));
            }
        }
    }
    int res = 0;
    for (int i = 1; i < V; ++i) {
        res += key[i];
    }

    return res;
}

int main() {
    int V, E;
    std::cin >> V >> E;

    std::vector<std::vector<Edge>> graph(V);

    for (int i = 0; i < E; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from;
        --to;
        graph[from].push_back(Edge(to, weight));
        graph[to].push_back(Edge(from, weight));
    }

    std::cout << primMST(graph, V);
}

