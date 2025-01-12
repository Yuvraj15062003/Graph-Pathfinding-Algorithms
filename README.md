# Pathfinding Algorithms in C++

This project implements two popular graph pathfinding algorithms, **Dijkstra's Algorithm** and **A\* (A-star) Algorithm**, in C++. 



## Features

- **Graph Loading**: The graph is loaded from a text file (`graph.txt`), where the nodes, edges, weights of the input graph are defined. Further,
  embeddings of the graph nodes into the Euclidean plane are also specified, enabling heuristics based pathfinding.
- **Pathfinding**: The code implements Djikstra's algorithm to find the path with the least weighted cost between two given nodes in the graph.
- **Heuristics enhanced Pathfinding**: The A* algotithm employing the Euclidean distance as the heuristic function is also implemented. 
