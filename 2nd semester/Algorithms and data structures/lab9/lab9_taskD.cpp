#include <iostream>
#include <vector>
#include <cinttypes>

int floyd(int n, std::vector<std::vector<uint64_t>>& graph) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][k] + graph[k][j] < graph[i][j] && graph[i][k] != UINT64_MAX && graph[k][j] != UINT64_MAX)
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }

    uint64_t mini = UINT64_MAX;
    int ans = 0;
    for (int j = 0; j < n; ++j) {
        uint64_t sum = 0;
        for (int i = 0; i < n; ++i) {
            if (graph[i][j] == UINT64_MAX) {
                sum = UINT64_MAX;
                break;
            }
            sum += graph[i][j];
        }
        if (sum < mini) {
            mini = sum;
            ans = j + 1;
        }
    }
    return ans;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<uint64_t>> graph;
    int n, m;
    std::cin >> n >> m;
    graph.resize(n, std::vector<uint64_t>(n, UINT64_MAX));
    int x, y;
    uint64_t l;

    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y >> l;
        --x;
        --y;
        graph[x][y] = std::min(l, graph[x][y]);
        graph[y][x] = std::min(l, graph[y][x]);
    }
    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }

    std::cout << floyd(n, graph);
}
