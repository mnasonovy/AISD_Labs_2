#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
    };

    bool has_vertex(const Vertex& v) const {
        return adjacency_list.find(v) != adjacency_list.end();
    }

    void add_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            adjacency_list[v] = std::vector<Edge>();
        }
    }

    bool remove_vertex(const Vertex& v) {3
        if (!has_vertex(v)) {
            return false;
        }
        adjacency_list.erase(v);

        for (auto& pair : adjacency_list) {
            auto& edges = pair.second;
            edges.erase(std::remove_if(edges.begin(), edges.end(),
                [&](const Edge& e) { return e.to == v; }),
                edges.end());
        }

        return true;
    }

    std::vector<Vertex> vertices() const {
        std::vector<Vertex> result;
        for (const auto& pair : adjacency_list) {
            result.push_back(pair.first);
        }
        return result;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        add_vertex(from);
        add_vertex(to);
        adjacency_list[from].push_back({ from, to, d });
    }


    bool remove_edge(const Vertex& from, const Vertex& to) {
        auto it = std::find_if(adjacency_list[from].begin(), adjacency_list[from].end(),
            [&](const Edge& e) { return e.to == to; });

        if (it != adjacency_list[from].end()) {
            adjacency_list[from].erase(it);
            return true;
        }

        return false;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to)) {
            return false;
        }

        for (const auto& edge : adjacency_list.at(from)) {
            if (edge.to == to) {
                return true;
            }
        }

        return false;
    }

    std::vector<Edge> edges(const Vertex& vertex) const {
        if (!has_vertex(vertex)) {
            return std::vector<Edge>();
        }
        return adjacency_list.at(vertex);
    }

    size_t order() const {
        return adjacency_list.size();
    }

    size_t degree(const Vertex& v) const {
        if (!has_vertex(v)) {
            return 0;
        }
        return adjacency_list.at(v).size();
    }



    Distance shortest_distance(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> distances;
        std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<>> pq;

        for (const auto& pair : adjacency_list) {
            Vertex v = pair.first;
            distances[v] = std::numeric_limits<Distance>::max();
        }
        distances[from] = Distance();
        pq.push({ Distance(), from });

        while (!pq.empty()) {
            Vertex u = pq.top().second;
            Distance dist_u = pq.top().first;
            pq.pop();
            if (dist_u > distances[u]) {
                continue;
            }

            if (u == to) {
                return distances[to];
            }

            for (const auto& edge : adjacency_list.at(u)) {
                Vertex v = edge.to;
                Distance alt = distances[u] + edge.distance;
                if (alt < distances[v]) {
                    distances[v] = alt;
                    pq.push({ alt, v });
                }
            }
        }

        return std::numeric_limits<Distance>::max();
    }



    Vertex find_center() const {
        std::vector<Vertex> verts = vertices();
        Vertex center;
        Distance min_max_distance = std::numeric_limits<Distance>::max();

        for (const auto& v : verts) {
            Distance max_distance = 0;
            for (const auto& u : verts) {
                if (v != u) {
                    Distance dist = shortest_distance(v, u);
                    if (dist > max_distance) {
                        max_distance = dist;
                    }
                }
            }
            if (max_distance < min_max_distance) {
                min_max_distance = max_distance;
                center = v;
            }
        }

        return center;
    }

    void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) {
        std::unordered_set<Vertex> visited;
        std::stack<Vertex> stack;

        stack.push(start_vertex);
        visited.insert(start_vertex);
        action(start_vertex);

        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();

            for (const auto& edge : adjacency_list.at(current)) {
                Vertex neighbor = edge.to;
                if (visited.count(neighbor) == 0) {
                    visited.insert(neighbor);
                    stack.push(current); 
                    stack.push(neighbor);
                    action(neighbor);
                    break; 
                }
            }
        }
    }

private:
    std::unordered_map<Vertex, std::vector<Edge>> adjacency_list;
};

#endif // GRAPH_H
