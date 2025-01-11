#include "visualizer.h"
#include <cairo.h>
#include <unordered_map>
#include <iostream>

// Visualizes the graph and saves it as an image (PNG file)
void visualizeGraphToImage(const Graph& graph, const std::unordered_map<int, std::pair<int, int>>& positions, const std::string& filename) {
    // Create an image surface to draw on (800x600 image, RGB format)
    int width = 800;
    int height = 600;
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
    cairo_t* cr = cairo_create(surface);

    // Set background color to white
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);  // RGB values for white
    cairo_paint(cr);

    // Set up the drawing color for edges and nodes
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);  // Black color

    // Draw edges (lines between nodes)
    for (const auto& pair : graph.getAdjacencyList()) {
        int source = pair.first;
        for (const auto& edge : pair.second) {
            int target = edge.target;

            if (source < target) {
                // Get positions of nodes
                auto [x1, y1] = positions.at(source);
                auto [x2, y2] = positions.at(target);

                // Scale positions for the image
                x1 *= 30;
                y1 *= 30;
                x2 *= 30;
                y2 *= 30;

                // Draw edge (line) between nodes
                cairo_move_to(cr, x1, y1);
                cairo_line_to(cr, x2, y2);
                cairo_stroke(cr);
            }
        }
    }

    // Draw nodes (circles)
    for (const auto& pair : positions) {
        int node = pair.first;
        auto [x, y] = pair.second;

        // Scale positions for the image
        x *= 30;
        y *= 30;

        // Draw node as a circle
        cairo_arc(cr, x, y, 10, 0, 2 * M_PI);  // Node radius of 10
        cairo_fill(cr);  // Fill the circle with the current color (black)
    }

    // Save the image to a file (graph.png)
    cairo_surface_write_to_png(surface, filename);

    // Clean up Cairo objects
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    std::cout << "Graph visualized and saved as " << filename << std::endl;
}
