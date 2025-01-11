#include <iostream>
#include "pathfinding.h"
#include "graph_loader.h"

int main() {
    Graph graph;
    std::unordered_map<int, std::pair<int, int>> positions;

    // Load the graph from a file
    std::string filename = "graph.txt";
    if (!loadGraphFromFile(filename, graph, positions)) {
        return 1;  // Exit if loading fails
    }

    // Test Dijkstra
    std::cout << "Enter start and goal nodes for Dijkstra: ";
    int start, goal;
    std::cin >> start >> goal;

    auto [pathDijkstra, weightDijkstra] = dijkstra(graph, start, goal);
    std::cout << "Dijkstra Path: ";
    for (int node : pathDijkstra) {
        std::cout << node << " ";
    }
    std::cout << "\n";
    std::cout << "Dijkstra Path Weight: " << weightDijkstra << "\n";

    // Test A*
    std::cout << "Enter start and goal nodes for A*: ";
    std::cin >> start >> goal;

    auto [pathAStar, weightAStar] = aStar(graph, start, goal, positions);
    std::cout << "A* Path: ";
    for (int node : pathAStar) {
        std::cout << node << " ";
    }
    std::cout << "\n";
    std::cout << "A* Path Weight: " << weightAStar << "\n";

    return 0;
}
