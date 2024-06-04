#include "Graph.cpp"
#include <iostream>
#include <vector>

int main() {
    Graph<int, int> g;
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 3, 1);
    g.add_edge(2, 4, 3);
    g.add_edge(3, 4, 2);
    g.add_edge(3, 5, 1);
    g.add_edge(4, 5, 2);
    g.add_edge(5, 1, 1);

    std::cout << "Depth-First Search (DFS) traversal: ";
    g.walk(1, [](const int& vertex) {
        std::cout << vertex << " ";
        });
    std::cout << std::endl;

    std::vector<int> visited_vertices;
    g.walk(1, [&visited_vertices](const int& vertex) {
        visited_vertices.push_back(vertex);
        });

    std::cout << "Visited vertices: ";
    for (const auto& vertex : visited_vertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::cout << "Shortest distance from 1 to 5: " << g.shortest_distance(1, 5) << std::endl;
    std::cout << "Center of the graph: " << g.find_center() << std::endl;
    return 0;
}
