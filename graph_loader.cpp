#include "graph_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Function to load a graph from a file
bool loadGraphFromFile(const std::string& filename, Graph& graph, std::unordered_map<int, std::pair<int, int>>& positions) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return false;
    }

    std::string line;
    int numNodes;

    // Read the number of nodes
    if (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        iss >> numNodes;
    } else {
        std::cerr << "Error: Invalid file format (missing number of nodes).\n";
        return false;
    }

    // Add nodes to the graph
    for (int i = 0; i < numNodes; ++i) {
        graph.addNode(i);
    }

    // Read edges
    while (std::getline(inputFile, line)) {
        if (line == "POSITIONS") break;  // Stop if we reach the positions section
        std::istringstream iss(line);
        int source, target;
        double weight;
        if (!(iss >> source >> target >> weight)) {
            std::cerr << "Error: Invalid edge format in line: " << line << "\n";
            return false;
        }
        graph.addEdge(source, target, weight);
    }

    // Read positions (if available)
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int node, x, y;
        if (!(iss >> node >> x >> y)) {
            std::cerr << "Error: Invalid position format in line: " << line << "\n";
            return false;
        }
        positions[node] = {x, y};
    }

    inputFile.close();
    return true;
}
