#include <iostream>
#include <vector>
#include <algorithm>


struct Edge {
    int from, to, weight;
};

class Graph {
  private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<Edge> edges;
    std::vector<int> pairs;
    std::vector<int> rev;
    std::vector<std::vector<std::pair<int, int>>> mst;
    std::vector<std::pair<int, int>> dp;
    std::vector<bool> visited;

    int root(int x) {
        if (pairs[x] == x)
            return x;
        return pairs[x] = root(pairs[x]);
    }

    void unite(int a, int b) {
        a = root(a), b = root(b);
        if (a == b){
            return;
        }
        if (rev[a] > rev[b]) {
            std::swap(a, b);
        }
        pairs[a] = b;
        if (rev[a] == rev[b]){
            rev[a]++;
        }
    }

    bool connected(int a, int b) {
        return root(a) == root(b);
    }

    void dfs(int v, int parent) {
        int skip = 0;
        int take = 0;

        for (auto& p : mst[v]) {
            int to = p.first;
            if (to == parent){
                continue;
            }
            dfs(to, v);

            skip += std::max(dp[to].first, dp[to].second);
            take += dp[to].first;
        }

        dp[v].second = skip;
        dp[v].first = take;

        for (auto& p : mst[v]) {
            int to = p.first;
            if (to == parent)
                continue;
            dp[v].first = std::max(dp[v].first, dp[to].second + skip - std::max(dp[to].first, dp[to].second) + p.second);
        }
    }

  public:
    explicit Graph(int n) : n(n), adj(n), pairs(n), rev(n), mst(n), dp(n), visited(n) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({ u, v, w });
    }

    int maxMatching() {
        int root = -1;
        std::sort(edges.begin(), edges.end(), [&](Edge& a, Edge& b) {
            return a.weight < b.weight;
        });

        for (int i = 0; i < n; ++i)
            pairs[i] = i;

        for (auto& edge : edges) {
            if (!connected(edge.from, edge.to)) {
                if (root == -1)
                    root = edge.from;
                unite(edge.from, edge.to);
                mst[edge.from].emplace_back(edge.to, edge.weight );
                mst[edge.to].emplace_back(edge.from, edge.weight );
            }
        }

        dfs(root, -1);
        return std::max(dp[root].first, dp[root].second);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    int u, v, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> w;
        u--, v--;
        graph.addEdge(u, v, w);
    }

    std::cout << graph.maxMatching();
}
