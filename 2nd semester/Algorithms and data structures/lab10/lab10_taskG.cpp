#include <iostream>
#include <vector>
#include <algorithm>


long canCollect = 0;

struct Edge {
    int type, weight, from, to;
};

bool cmp(Edge& a, Edge& b) {
    return abs(a.weight) < abs(b.weight);
}

int find(int i, std::vector<int>& par) {
    if (i == par[i])
        return i;
    return par[i] = find(par[i], par);
}

void unit(int u, int v, std::vector<int>& par, std::vector<int>& r) {
    u = find(u, par);
    v = find(v, par);
    if (u != v) {
        if (r[u] < r[v]) {
            par[u] = v;
        }
        else if (r[u] > r[v]) {
            par[v] = u;
        }
        else {
            par[v] = u;
            r[u]++;
        }
    }
}

auto mst(int n, std::vector<Edge>& edges, std::vector<int>& par, std::vector<int>& r) {
    sort(edges.begin(), edges.end(), cmp);

    for (int i = 0; i < n; ++i)
        par[i] = i;

    long total_cost = 0, coins = 0;

    for (auto& edge : edges) {
        int weight, u, v;
        weight = edge.weight;
        u = edge.from;
        v = edge.to;

        int comp_u = find(u, par);
        int comp_v = find(v, par);

        if (comp_u != comp_v) {
            if (edge.type == 0) {
                total_cost += weight;
            }
            else {
                coins += weight;
            }
            unit(comp_u, comp_v, par, r);
        }
        else if (edge.type == 1 && weight < 0) {
            total_cost -= weight;
        }
    }

    return total_cost - (canCollect - coins);
}



int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<Edge> edges;
    std::vector<int> par (n), r (n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        edges.push_back({ 1, w, u, v });
        canCollect += w;
    }

    for (int i = 0; i < k; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        edges.push_back({ 0, w, u, v });
    }

    std::cout << (mst(n, edges, par, r) < 0 ? 0 : mst(n, edges, par, r));
}
