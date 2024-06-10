#include <iostream>
#include <vector>
#include <stack>

bool isPathExists(const std::vector<std::vector<int>>& adj, int start, int end) {
    std::vector<bool> visited(adj.size(), false);

    std::stack<int> toVisit;
    toVisit.push(start);

    while (!toVisit.empty()) {
        int current = toVisit.top();
        toVisit.pop();

        if (visited[current]) {
            continue;
        }

        visited[current] = true;

        if (current == end) {
            return true;
        }

        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                toVisit.push(neighbor);
            }
        }
    }

    return false;
}

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < q; ++i) {
        char type;
        int a, b;
        std::cin >> type >> a >> b;

        if (type == '?') {
            bool connected = false;

            for (int neighbor : adj[a]) {
                if (neighbor == b || a == b) {
                    connected = true;
                    break;
                }
            }
            if (!connected) {
                connected = isPathExists(adj, a, b);
            }

            std::cout << (connected ? "YES" : "NO") << '\n';
        } else {
            for (int j = 0; j < adj[a].size(); ++j) {
                if (adj[a][j] == b) {
                    adj[a].erase(adj[a].begin() + j);
                    break;
                }
            }
            for (int j = 0; j < adj[b].size(); ++j) {
                if (adj[b][j] == a) {
                    adj[b].erase(adj[b].begin() + j);
                    break;
                }
            }
        }
    }
}
