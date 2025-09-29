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
    const Heuristics &heuristics;
    const std::size_t current;

    bool operator()(const std::size_t one, const std::size_t other) const {
        const auto one_cost   = heuristics.distance(vertices[current], vertices[one]  ) + heuristics.distance(vertices[one]  , heuristics.target);
        const auto other_cost = heuristics.distance(vertices[current], vertices[other]) + heuristics.distance(vertices[other], heuristics.target);
        return one_cost < other_cost;
    }

};

Path find_path(const Path& path, const Vertices& vertices, const ConnectivityMap& connectivity, const Heuristics& heuristics, const std::size_t last) {

    const auto back = path.back();
    if(back == last) {
        return path;
    } else {
        const auto step = *std::min_element(connectivity.at(back).begin(), connectivity.at(back).end(), detail::NeighborLess{ vertices, heuristics, back });
        auto new_path = Path{ path };
        new_path.emplace_back(step);
        return find_path(new_path, vertices, connectivity, heuristics, last);     
    }

}

} // namespace squaremind::detail

Path find_best_path(const Vertices& vertices, const Faces& faces, const Heuristics& heuristics, const EndVertices& startAndTarget) {

    const auto edges = EdgeMapFactory::make(vertices, faces);
    const auto connectivity = ConnectivityMapFactory::make(edges);
    return detail::find_path({ startAndTarget.first }, vertices, connectivity, heuristics, startAndTarget.second);

}

} // namespace astar