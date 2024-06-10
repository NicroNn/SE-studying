#include <iostream>
#include <vector>
#include <queue>
#include <memory>

const int INF = INT_MAX;

struct Edge {
    int from, to, capacity, cost, flow;
    std::shared_ptr<Edge> reverse;

    Edge(int from, int to, int capacity, int cost) :
        from(from), to(to), capacity(capacity), cost(cost), flow(0), reverse(nullptr) {}
};

class FlowNetwork {
  private:
    int numNodes;
    std::vector<std::vector<std::shared_ptr<Edge>>> adjacencyList;
    std::vector<int> potential;
    std::vector<std::shared_ptr<Edge>> parentEdges;

  public:
    FlowNetwork(int nodes) : numNodes(nodes), adjacencyList(nodes), potential(nodes, 0), parentEdges(nodes) {}

    void addEdge(int from, int to, int capacity, int cost) {
        auto edge = std::make_shared<Edge>(from, to, capacity, cost);
        auto revEdge = std::make_shared<Edge>(to, from, 0, -cost);

        edge->reverse = revEdge;
        revEdge->reverse = edge;

        adjacencyList[from].push_back(edge);
        adjacencyList[to].push_back(revEdge);
    }

    bool dijkstra(int source, int sink) {
        std::vector<int> distance(numNodes, INF);
        distance[source] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.emplace(0, source);

        std::vector<bool> visited(numNodes, false);
        parentEdges.assign(numNodes, nullptr);

        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();

            if (dist != distance[u])
                continue;

            for (const auto& edge : adjacencyList[u]) {
                if (edge->capacity > edge->flow) {
                    int cost = edge->cost + potential[u] - potential[edge->to];

                    if (distance[edge->to] > distance[u] + cost) {
                        distance[edge->to] = distance[u] + cost;
                        parentEdges[edge->to] = edge;
                        pq.emplace(distance[edge->to], edge->to);
                    }
                }
            }
        }

        for (int i = 0; i < numNodes; ++i) {
            if (distance[i] < INF)
                potential[i] += distance[i];
        }

        return distance[sink] < INF;
    }

    void maxFlowMinCost(int source, int sink) {
        int maxFlow = 0;
        int minCost = 0;

        while (dijkstra(source, sink)) {
            int pathFlow = INF;
            for (auto pEdge = parentEdges[sink]; pEdge != nullptr; pEdge = parentEdges[pEdge->from]) {
                pathFlow = std::min(pathFlow, pEdge->capacity - pEdge->flow);
            }

            for (auto pEdge = parentEdges[sink]; pEdge != nullptr; pEdge = parentEdges[pEdge->from]) {
                pEdge->flow += pathFlow;
                pEdge->reverse->flow -= pathFlow;
                minCost += pEdge->cost * pathFlow;
            }
            maxFlow += pathFlow;
        }
        std::cout << maxFlow << ' ' << minCost;
    }
};

int main() {
    int numNodes, numEdges, source, sink;
    std::cin >> numNodes >> numEdges >> source >> sink;
    --source;
    --sink;

    FlowNetwork flowNetwork(numNodes);

    int u, v, capacity, cost;
    for (int i = 0; i < numEdges; ++i) {
        std::cin >> u >> v >> capacity >> cost;
        --u;
        --v;
        flowNetwork.addEdge(u, v, capacity, cost);
    }

    flowNetwork.maxFlowMinCost(source, sink);
}
