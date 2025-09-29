#include <unordered_map>
#include <unordered_set>

#include "astar/connectivity_map.h"
#include "astar/edge_map.h"

namespace astar {

namespace detail {

using EdgeBasedConnectivityMap = std::unordered_map<Edge, std::unordered_set<std::size_t>, EdgeHash, EdgeEqual>;

EdgeBasedConnectivityMap make_edge_to_face(const Faces& faces) {
    auto connectivity = EdgeBasedConnectivityMap{ };
    for(std::size_t face=0; face < faces.size(); ++face) {
        const auto edges = face_edges(faces[face]);
        connectivity[edges[0]].insert(face);
        connectivity[edges[1]].insert(face);
        connectivity[edges[2]].insert(face);
    }
    return connectivity;

}

struct ConnectNodes {

    ConnectivityMap vertices;

    void operator()(const std::pair<Edge, float>& edge) {
        vertices[edge.first.v[0]].insert(edge.first.v[1]);
        vertices[edge.first.v[1]].insert(edge.first.v[0]);
    }

};

struct ConnectFaces {

    ConnectivityMap faces;

    void operator()(const std::pair<Edge, std::unordered_set<std::size_t>>& edge_face) {
        if (edge_face.second.size() == 2) {
            const auto first  = edge_face.second.begin();
            const auto second = std::next(first);
                faces[*first].insert(*second);
                faces[*second].insert(*first);
        }
    }

};

} // namespace astar::detail

namespace ConnectivityMapFactory {

ConnectivityMap make_vertex_to_vertex(const Vertices& vertices, const Faces& faces) {

    const auto edges = EdgeMapFactory::make(vertices, faces);
    auto connected = detail::ConnectNodes{ };
    std::for_each(edges.begin(), edges.end(), std::ref(connected));
    return std::move(connected.vertices);

}

ConnectivityMap make_face_to_face(const Faces &faces) {

    const auto edge_faces = detail::make_edge_to_face(faces);
    auto connected = detail::ConnectFaces{ };
    std::for_each(edge_faces.begin(), edge_faces.end(), std::ref(connected));
    return std::move(connected.faces);

}

} // namespace astar::ConnectivityMapFactory

} // namespace astar