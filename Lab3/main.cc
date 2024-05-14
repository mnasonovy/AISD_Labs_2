#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
    };

    template<typename Vertex, typename Distance>
    bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
        return adjacency_list.find(v) != adjacency_list.end();
    }

    template<typename Vertex, typename Distance>
    void Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            adjacency_list[v] = std::vector<Edge>();
        }
    }

    template<typename Vertex, typename Distance>
    bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
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

    template<typename Vertex, typename Distance>
    std::vector<Vertex> Graph<Vertex, Distance>::vertices() const {
        std::vector<Vertex> result;
        for (const auto& pair : adjacency_list) {
            result.push_back(pair.first);
        }
        return result;
    }

    template<typename Vertex, typename Distance>
    void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        add_vertex(from);
        add_vertex(to);
        adjacency_list[from].push_back({ from, to, d });
    }

    template<typename Vertex, typename Distance>
    bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
        auto it = std::find_if(adjacency_list[from].begin(), adjacency_list[from].end(),
            [&](const Edge& e) { return e.to == to; });

        if (it != adjacency_list[from].end()) {
            adjacency_list[from].erase(it);
            return true;
        }

        return false;
    }

    template<typename Vertex, typename Distance>
    bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
        if (!has_vertex(e.from) || !has_vertex(e.to)) {
            return false;
        }

        auto& edges = adjacency_list[e.from];
        auto it = std::find(edges.begin(), edges.end(), e);
        if (it != edges.end()) {
            edges.erase(it);
            return true;
        }

        return false;
    }

    template<typename Vertex, typename Distance>
    bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
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

    template<typename Vertex, typename Distance>
    bool Graph<Vertex, Distance>::has_edge(const Edge& e) const {
        if (!has_vertex(e.from) || !has_vertex(e.to)) {
            return false;
        }

        const auto& edges = adjacency_list.at(e.from);
        return std::find(edges.begin(), edges.end(), e) != edges.end();
    }

    template<typename Vertex, typename Distance>
    std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) const {
        if (!has_vertex(vertex)) {
            return std::vector<Edge>();
        }
        return adjacency_list.at(vertex);
    }

    template<typename Vertex, typename Distance>
    size_t Graph<Vertex, Distance>::order() const {
        return adjacency_list.size();
    }

    template<typename Vertex, typename Distance>
    size_t Graph<Vertex, Distance>::degree(const Vertex& v) const {
        if (!has_vertex(v)) {
            return 0;
        }
        return adjacency_list.at(v).size();
    }

    template<typename Vertex, typename Distance>
    std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> distances;
        std::unordered_map<Vertex, Vertex> previous;
        std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<>> pq;
        for (const auto& pair : adjacency_list) {
            Vertex v = pair.first;
            distances[v] = std::numeric_limits<Distance>::max();
            previous[v] = Vertex();
        }
        distances[from] = Distance();
        pq.push({ Distance(), from });

        while (!pq.empty()) {
            Vertex u = pq.top().second;
            pq.pop();

            if (u == to) {
                break;
            }

            for (const auto& edge : adjacency_list.at(u)) {
                Vertex v = edge.to;
                Distance alt = distances[u] + edge.distance;
                if (alt < distances[v]) {
                    distances[v] = alt;
                    previous[v] = u;
                    pq.push({ alt, v });
                }
            }
        }

        std::vector<Edge> path;
        for (Vertex v = to; previous[v] != Vertex(); v = previous[v]) {
            Vertex u = previous[v];
            for (const auto& edge : adjacency_list.at(u)) {
                if (edge.to == v) {
                    path.push_back(edge);
                    break;
                }
            }
        }
        std::reverse(path.begin(), path.end());

        return path;
    }

    template<typename Vertex, typename Distance>
    std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const {
        std::unordered_set<Vertex> visited;
        std::function<void(const Vertex&)> dfs = [&](const Vertex& current_vertex) {
            visited.insert(current_vertex);
            for (const auto& edge : adjacency_list.at(current_vertex)) {
                const Vertex& next_vertex = edge.to;
                if (visited.find(next_vertex) == visited.end()) { 
                    dfs(next_vertex); 
                }
            }
        };
        dfs(start_vertex);
        std::vector<Vertex> result(visited.begin(), visited.end());
        return result;
    }


private:
    std::unordered_map<Vertex, std::vector<Edge>> adjacency_list;
};
