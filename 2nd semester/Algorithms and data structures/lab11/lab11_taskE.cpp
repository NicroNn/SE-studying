#include <iostream>
#include <vector>
#include <queue>


struct BipartiteMatching {
    std::vector<std::vector<int>> adj;
    std::vector<int> matchingL, matchingR;

    BipartiteMatching(int left_size, int right_size) : adj(left_size), matchingL(left_size, -1), matchingR(right_size, -1) {}

    bool isKun(int u, std::vector<bool>& used) {
        if (used[u])
            return false;
        used[u] = true;

        for (int v : adj[u]) {
            if (matchingR[v] == -1 || isKun(matchingR[v], used)) {
                matchingR[v] = u;
                matchingL[u] = v;
                return true;
            }
        }
        return false;
    }

    int findMaxMatching() {
        int max_matching = 0;
        bool found = true;
        std::vector<bool> visited(adj.size(), false);

        while (found) {
            fill(visited.begin(), visited.end(), false);
            found = false;
            for (int i = 0; i < adj.size(); ++i) {
                if (matchingL[i] == -1 && isKun(i, visited)) {
                    found = true;
                    max_matching++;
                }
            }
        }
        return max_matching;
    }

    void findMinVertexCover(std::vector<int>& left_cover, std::vector<int>& right_cover) {
        std::queue<int> q;
        std::vector<bool> visitedL(adj.size(), false), visitedR(matchingR.size(), false);

        for (int i = 0; i < adj.size(); ++i) {
            if (matchingL[i] == -1) {
                q.push(i);
                visitedL[i] = true;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!visitedR[v] && matchingR[v] != -1) {
                    visitedR[v] = true;
                    q.push(matchingR[v]);
                    visitedL[matchingR[v]] = true;
                }
            }
        }

        for (int i = 0; i < adj.size(); ++i){
            if (!visitedL[i]){
                left_cover.push_back(i);
            }
        }

        for (int i = 0; i < matchingR.size(); ++i){
            if (visitedR[i]){
                right_cover.push_back(i);
            }
        }
    }
};

int main() {
    int n, k, m;
    std::cin >> n >> k >> m;

    BipartiteMatching bm(n, k);

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        u--, v--;
        bm.adj[u].push_back(v);
    }
    bm.findMaxMatching();

    std::vector<int> coverL, coverR;
    bm.findMinVertexCover(coverL, coverR);

    std::cout << coverL.size() << '\n';
    for (auto i : coverL) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    std::cout << coverR.size() << '\n';
    for (auto i : coverR) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';
}
