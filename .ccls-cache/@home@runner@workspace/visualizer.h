#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "pathfinding.h"
#include <unordered_map>
#include <string>

// Function to visualize the graph and save it as an image (PNG file)
void visualizeGraphToImage(const Graph& graph, const std::unordered_map<int, std::pair<int, int>>& positions, const std::string& filename);

#endif

