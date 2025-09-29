#include "connectivity_map.h"
#include "edge_map.h"

namespace astar {

namespace ConnectivityMapFactory {

ConnectivityMap make_node_to_node(const Vertices& vertices, const Faces& faces) {

    const auto edges = EdgeMapFactory::make(vertices, faces);
    auto connectivity = ConnectivityMap{ };
    std::for_each(edges.begin(), edges.end(), [&connectivity](const auto& edge) {
        connectivity[edge.first.v[0]].insert(edge.first.v[1]);
        connectivity[edge.first.v[1]].insert(edge.first.v[0]);
    });
    return connectivity;

}

} // namespace astar::ConnectivityMapFactory

} // namespace astar