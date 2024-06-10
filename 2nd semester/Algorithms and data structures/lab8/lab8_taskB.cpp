#include <iostream>
#include <vector>

class Graph {
    int V;
    std::vector<std::vector<int>> adj;

  public:
    explicit Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int v, int w) {
        adj[v - 1].push_back(w - 1);
    }

    bool isReachable(int v, int dest, std::vector<bool>& visited) {
        if (v == dest)
            return true;

        visited[v] = true;

        for (int i : adj[v]) {
            if (!visited[i] && isReachable(i, dest, visited))
                return true;
        }
        return false;
    }

    bool hasPath(int start, int dest) {
        std::vector<bool> visited(V, false);
        return isReachable(start, dest, visited);
    }

    bool hasCycleContainingPath(int start, int dest) {
        return hasPath(start, dest) && hasPath(dest, start);
    }
};




int main() {
    int n, m, q;
    std::cin >> n >> m >> q;

    Graph graph(n);
    int vertex1, vertex2;

    for (int i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2;
        graph.addEdge(vertex1, vertex2);
    }

    for (int i = 0; i < q; ++i) {
        std::cin >> vertex1 >> vertex2;
        if (graph.hasCycleContainingPath(vertex1 - 1, vertex2 - 1)){
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
}
