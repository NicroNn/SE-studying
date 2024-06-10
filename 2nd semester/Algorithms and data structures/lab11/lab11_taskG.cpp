#include <iostream>
#include <vector>
#include <queue>


std::vector<int> findHamiltonianCycle(std::vector<std::vector<int>>& graph, std::queue<int>& q, std::vector<bool>& visited) {
    std::vector<int> hamiltonianCycle;

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        hamiltonianCycle.push_back(currentVertex);
        for (int nextVertex : graph[currentVertex]) {
            if (!visited[nextVertex]) {
                q.push(nextVertex);
                visited[nextVertex] = true;
            }
        }
    }

    return hamiltonianCycle;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::queue<int> readQueue;
    std::vector<bool> visited(n, false);
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int ai, bi;
        std::cin >> ai >> bi;
        if (!visited[ai]){
            readQueue.push(ai);
            visited[ai] = true;
        }
        if (!visited[bi]){
            readQueue.push(bi);
            visited[bi] = true;
        }
        graph[ai].push_back(bi);
    }

    std::vector<int> cycle = findHamiltonianCycle(graph, readQueue, visited);

    for (int v : cycle) {
        std::cout << v << ' ';
    }
}
