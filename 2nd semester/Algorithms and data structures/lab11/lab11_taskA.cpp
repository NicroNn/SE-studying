#include <iostream>
#include <vector>


int dfs(int v, std::vector<int>& matching, std::vector<int>& visited, std::vector<int>& pair, std::vector<std::vector<int>>& graph) {
    if (visited[v])
        return 0;

    visited[v] = 1;
    for (int to : graph[v]) {
        if (matching[to] == -1 || dfs(matching[to], matching, visited, pair, graph)) {
            matching[to] = v;
            pair[v] = to;
            return 1;
        }
    }
    return 0;
}

std::vector<int> AugmentingPath(int n, int m, std::vector<std::vector<int>>& graph) {
    std::vector<int> matching(n * m, -1);
    std::vector<int> pair(n * m, -1);

    bool done = false;
    while (!done) {
        done = true;
        std::vector<int> visited(n * m, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) % 2)
                    continue;

                if ((pair[i * m + j] == -1) && dfs(i * m + j, matching, visited, pair, graph))
                    done = false;

            }
        }
    }
    return matching;
}


int main() {
    int n, m, q;
    int x, y;
    std::cin >> n >> m >> q;
    std::vector<std::vector<bool>> board(n, std::vector<bool>(m, true));
    for (int i = 0; i < q; ++i) {
        std::cin >> x >> y;
        --x, --y;
        board[x][y] = false;
    }

    std::vector<std::vector<int>> graph(n * m);
    int empty = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!board[i][j])
                continue;
            ++empty;

            if ((i + j) % 2)
                continue;
            int u = i * m + j;

            if ((j > 0) && (board[i][j - 1]))
                graph[u].push_back(u - 1);

            if ((j < m - 1) && (board[i][j + 1]))
                graph[u].push_back(u + 1);

            if ((i > 0) && (board[i - 1][j]))
                graph[u].push_back(u - m);

            if ((i < n - 1) && (board[i + 1][j]))
                graph[u].push_back(u + m);
        }
    }

    std::vector<int> matching = AugmentingPath(n, m, graph);

    int maxMatching = 0;
    for (int i = 0; i < n * m; ++i) {
        if (matching[i] != -1)
            maxMatching++;
    }
    std::cout << maxMatching * 2;
}
