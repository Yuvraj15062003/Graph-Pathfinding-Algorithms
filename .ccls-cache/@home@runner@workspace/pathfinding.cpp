#include "pathfinding.h"

// Add a node to the graph
void Graph::addNode(int node) {
    if (adjacencyList.find(node) == adjacencyList.end()) {
        adjacencyList[node] = {};
    }
}

// Add an edge to the graph
void Graph::addEdge(int source, int target, double weight) {
    adjacencyList[source].push_back({ target, weight });
}

// Get the adjacency list of the graph
const std::unordered_map<int, std::vector<Edge>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}

// Dijkstra Algorithm
std::pair<std::vector<int>, double> dijkstra(const Graph& graph, int start, int goal) {
    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> previous;
    auto comp = [&](int left, int right) { return distances[left] > distances[right]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> queue(comp);

    for (const auto& pair : graph.getAdjacencyList()) {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.top();
        queue.pop();

        if (current == goal) break;

        for (const Edge& edge : graph.getAdjacencyList().at(current)) {
            double newDist = distances[current] + edge.weight;
            if (newDist < distances[edge.target]) {
                distances[edge.target] = newDist;
                previous[edge.target] = current;
                queue.push(edge.target);
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int at = goal; previous.find(at) != previous.end(); at = previous[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return {path, distances[goal]};
}

// Heuristic for A* (Euclidean distance)
double heuristic(int node, int goal, const std::unordered_map<int, std::pair<int, int>>& positions) {
    auto [x1, y1] = positions.at(node);
    auto [x2, y2] = positions.at(goal);
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

// A* Algorithm
std::pair<std::vector<int>, double> aStar(const Graph& graph, int start, int goal, const std::unordered_map<int, std::pair<int, int>>& positions) {
    std::unordered_map<int, double> gScore;
    std::unordered_map<int, double> fScore;
    std::unordered_map<int, int> previous;
    auto comp = [&](int left, int right) { return fScore[left] > fScore[right]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> queue(comp);

    for (const auto& pair : graph.getAdjacencyList()) {
        gScore[pair.first] = std::numeric_limits<double>::infinity();
        fScore[pair.first] = std::numeric_limits<double>::infinity();
    }
    gScore[start] = 0;
    fScore[start] = heuristic(start, goal, positions);
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.top();
        queue.pop();

        if (current == goal) break;

        for (const Edge& edge : graph.getAdjacencyList().at(current)) {
            double tentativeGScore = gScore[current] + edge.weight;
            if (tentativeGScore < gScore[edge.target]) {
                gScore[edge.target] = tentativeGScore;
                fScore[edge.target] = gScore[edge.target] + heuristic(edge.target, goal, positions);
                previous[edge.target] = current;
                queue.push(edge.target);
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int at = goal; previous.find(at) != previous.end(); at = previous[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return {path, gScore[goal]};
}
