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
        adj[w - 1].push_back(v - 1);
    }

    bool isCyclicUtil(int v, std::vector<bool>& visited, std::vector<int>& parent) {
        visited[v] = true;

        for (int u : adj[v]) {
            if (!visited[u]) {
                parent[u] = v;
                if (isCyclicUtil(u, visited, parent))
                    return true;
            } else if (parent[v] != u) {
                return true;
            }
        }
        return false;
    }

    bool isCyclic() {
        std::vector<bool> visited(V, false);
        std::vector<int> parent(V, -1);

        for (int i = 0; i < V; ++i) {
            if (!visited[i] && isCyclicUtil(i, visited, parent))
                return true;
        }
        return false;
    }
};




int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    int vertex1, vertex2;

    for (int i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2;
        graph.addEdge(vertex1, vertex2);
    }
    if (graph.isCyclic()){
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}
