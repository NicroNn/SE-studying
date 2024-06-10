#include <iostream>
#include <vector>
#include <algorithm>


struct Edge {
    int from, to, weight;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

struct DSU {
    std::vector<int> parent;

    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

std::pair<int, std::vector<Edge>> kruskalMST(std::vector<Edge>& edges, int V) {
    std::sort(edges.begin(), edges.end(), compareEdges);
    DSU dsu(V);
    std::vector<Edge> mst;
    int mstWeight = 0;

    for (const Edge& edge : edges) {
        if (dsu.find(edge.from) != dsu.find(edge.to)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            dsu.unite(edge.from, edge.to);
        }
    }

    return {mstWeight, mst};
}

int main() {
    int V, E;
    std::cin >> V >> E;

    std::vector<Edge> edges(E);
    for (int i = 0; i < E; ++i) {
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
        edges[i].from--;
        edges[i].to--;
    }

    auto [mstWeight1, mst1] = kruskalMST(edges, V);
    std::cout << mstWeight1 << ' ';

    int secondMSTWeight = INT_MAX;

    for (const Edge& edge : mst1) {
        std::vector<Edge> modifiedEdges = edges;
        modifiedEdges.erase(std::remove_if(modifiedEdges.begin(), modifiedEdges.end(), [&](const Edge& e) {
            return (e.from == edge.from && e.to == edge.to) || (e.from == edge.to && e.to == edge.from);
        }), modifiedEdges.end());

        auto [mstWeight, _] = kruskalMST(modifiedEdges, V);
        if (mstWeight < secondMSTWeight)
            secondMSTWeight = mstWeight;
    }

    std::cout << secondMSTWeight;
}
