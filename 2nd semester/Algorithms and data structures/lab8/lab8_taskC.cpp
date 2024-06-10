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

    void dfsUtil(int v, std::vector<bool>& visited) {
        visited[v] = true;
        for (int i : adj[v]) {
            if (!visited[i]) {
                dfsUtil(i, visited);
            }
        }
    }

    int countConnectedComponents() {
        int count = 0;
        std::vector<bool> visited(V, false);

        for (int v = 0; v < V; ++v) {
            if (!visited[v]) {
                dfsUtil(v, visited);
                ++count;
            }
        }
        return count;
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
    std::cout << graph.countConnectedComponents();
}
