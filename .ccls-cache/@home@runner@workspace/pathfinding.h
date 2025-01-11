#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>

// Graph Node Structure
struct Edge {
    int target;
    double weight;
};

// Graph Class
class Graph {
public:
    void addNode(int node);
    void addEdge(int source, int target, double weight);
    const std::unordered_map<int, std::vector<Edge>>& getAdjacencyList() const;

private:
    std::unordered_map<int, std::vector<Edge>> adjacencyList;
};

// Pathfinding Algorithms
std::pair<std::vector<int>, double> dijkstra(const Graph& graph, int start, int goal);
std::pair<std::vector<int>, double> aStar(const Graph& graph, int start, int goal, const std::unordered_map<int, std::pair<int, int>>& positions);

#endif
