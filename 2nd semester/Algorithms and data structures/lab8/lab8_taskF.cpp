#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Graph {
    int V;
    std::vector<std::vector<int>> adj;

  public:
    explicit Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int v, int w) {
        adj[v - 1].push_back(w - 1);
        adj[w - 1].push_back(v - 1);
    }

    std::vector<int> shortestPath(int start) {
        std::vector<int> dist(V, std::numeric_limits<int>::max());
        std::queue<int> q;

        dist[start - 1] = 0;
        q.push(start - 1);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v: adj[u]) {
                if (dist[v] == std::numeric_limits<int>::max()) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        return dist;
    }
};


int main() {
    int n;
    std::cin >> n;
    int m, k;
    std::cin >> m >> k;

    Graph graph(n);
    int vertex1, vertex2;

    for (int i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2;
        graph.addEdge(vertex1, vertex2);
    }

    std::vector<int> res = graph.shortestPath(1);

    bool noMatch = true;
    for (int i = 0; i < res.size(); i++) {
        if (res[i] == k) {
            noMatch = false;
            std::cout << i + 1 << '\n';
        }
    }
    if (noMatch){
        std::cout << "NO";
    }
}
