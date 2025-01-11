#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#include "pathfinding.h"
#include <unordered_map>
#include <string>

// Function to load a graph and node positions from a file
bool loadGraphFromFile(const std::string& filename, Graph& graph, std::unordered_map<int, std::pair<int, int>>& positions);

#endif
