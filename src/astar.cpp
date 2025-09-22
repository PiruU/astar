#include "vertex.h"
#include "face.h"
#include "heuristics.h"
#include "edge_map.h"
#include "connectivity_map.h"

#include "astar.h"

namespace astar {

namespace detail {

struct NeighborLess {

    const std::vector<Vertex>& vertices;
    const EdgeMap& edges;
    const Heuristics &heuristics;
    const std::size_t current;

    bool operator()(const std::size_t one, const std::size_t other) const {
        const auto one_cost = edges.at({ one, current }) + heuristics(vertices[one]);
        const auto other_cost = edges.at({ other, current }) + heuristics(vertices[other]);
        return one_cost < other_cost;
    }

};

} // namespace squaremind::detail

Path find_best_path(const Vertices& vertices, const Faces& faces, const Heuristics& heuristics, const EndVertices& startAndTarget) {

    const auto edges = EdgeMapFactory::make(vertices, faces);
    const auto connectivity = ConnectivityMapFactory::make(edges);
    auto path = Path{ startAndTarget.first };
    while(path.back() != startAndTarget.second) {
        const auto neighbors = connectivity.at(path.back());
        path.push_back(
            *std::min_element(neighbors.begin(), neighbors.end(), detail::NeighborLess{ vertices, edges, heuristics, path.back()})
        );
    }
    return path;

}

} // namespace astar