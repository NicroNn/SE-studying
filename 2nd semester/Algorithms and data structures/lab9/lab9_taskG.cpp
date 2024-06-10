#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

struct PathParams {
    long num;
    int cost;
};

bool operator==(const PathParams &a, const PathParams &b) {
    return std::tie(a.num, a.cost) == std::tie(b.num, b.cost);
}

bool operator!=(const PathParams &a, const PathParams &b) {
    return !(a == b);
}

struct State {
    PathParams params;
    int v;
    int best;
};

bool operator<(const PathParams &a, const PathParams &b) {
    if (a.num != b.num) return a.num < b.num;
    return a.cost > b.cost;
}

bool operator<(const State &a, const State &b) {
    return std::tie(a.params, a.v, a.best) < std::tie(b.params, b.v, b.best);
}

bool operator>(const State &a, const State &b) {
    return !(a < b);
}

int main() {
    int n, m, p;
    std::cin >> n >> m >> p;
    std::vector<std::vector<PathParams>> dp(n, std::vector<PathParams>(n, {static_cast<long>(1e18), 0}));
    std::vector<std::vector<std::pair<int, int>>> g(n);
    std::vector<int> w(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> w[i];
    }

    for (int i = 0; i < m; ++i) {
        int a, b, s;
        std::cin >> a >> b >> s;
        a--;
        b--;
        g[a].emplace_back(b, s);
    }

    dp[0][0] = {0, p};
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    pq.push({{0, p}, 0, 0});

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        int v = current.v;
        int best = current.best;

        if (dp[v][best] != current.params) continue;

        for (auto &[u, s]: g[v]) {
            auto state2 = current;
            PathParams &path = state2.params;

            if (path.cost < s) {
                long need = (s - path.cost + w[best] - 1) / w[best];
                path.num += need;
                path.cost += need * w[best];
            }

            path.cost -= s;
            state2.v = u;

            if (w[u] > w[state2.best]) state2.best = u;

            if (path < dp[u][state2.best]) {
                dp[u][state2.best] = path;
                pq.push(state2);
            }
        }
    }

    long ans = 1e18;

    for (int i = 0; i < n; ++i) {
        ans = std::min(ans, dp[n - 1][i].num);
    }

    std::cout << (ans == 1e18 ? -1 : ans);
}
