#include "astar/norms.h"
#include "astar/vertex.h"
#include "astar/face.h"

#include "astar/edge_map.h"

namespace astar {

namespace detail {

struct AccumulateEdge {

    EdgeMap& edge_map;
    const std::vector<Vertex>& vertices;

    void operator()(const Edge& edge) const {
        edge_map[edge] = euclidian_norm(vertices[edge.v[0]], vertices[edge.v[1]]);
    }

};

struct InsertFaceEdges {

    EdgeMap& edge_map;
    const std::vector<Vertex>& vertices;

    void operator()(const Face& face) {
        const auto edges = face_edges(face);
        std::for_each(edges.begin(), edges.end(), AccumulateEdge{ edge_map, vertices });
    }

};

} // namespace astar::detail

std::array<Edge, 3> face_edges(const Face& face) {

    return {
        Edge{ { face[0], face[1] } },
        Edge{ { face[1], face[2] } },
        Edge{ { face[2], face[0] } }
    };
    
}

bool EdgeEqual::operator()(const Edge& one, const Edge& other) const {

    return ((one.v[0] == other.v[0]) && (one.v[1] == other.v[1])) || ((one.v[0] == other.v[1]) && (one.v[1] == other.v[0]));

}

std::size_t EdgeHash::operator()(const Edge& edge) const noexcept {

    const std::size_t a = std::min(edge.v[0], edge.v[1]);
    const std::size_t b = std::max(edge.v[0], edge.v[1]);
    std::size_t h1 = std::hash<std::size_t>{}(a);
    std::size_t h2 = std::hash<std::size_t>{}(b);
    return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));

}

namespace EdgeMapFactory {

EdgeMap make(const Vertices& vertices, const Faces& faces) {

    auto edge_map = EdgeMap{ };
    std::for_each(faces.begin(), faces.end(), detail::InsertFaceEdges{ edge_map, vertices });
    return edge_map;

}

} // namespace astar::EdgeMapFactory

} // namespace astar