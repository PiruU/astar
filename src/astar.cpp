#include <variant>

#include "vertex.h"
#include "heuristics.h"
#include "connectivity_map.h"

#include "astar.h"

namespace astar {

namespace detail {

struct NeighborLess {

    const std::vector<Vertex>& vertices;
    const Heuristics &heuristics;
    const std::size_t current;
    const std::size_t target;

    bool operator()(const std::size_t one, const std::size_t other) const {
        const auto one_cost   = heuristics.distance(vertices[current], vertices[one]  ) + heuristics.distance(vertices[one]  , vertices[target]);
        const auto other_cost = heuristics.distance(vertices[current], vertices[other]) + heuristics.distance(vertices[other], vertices[target]);
        return one_cost < other_cost;
    }

};

bool extend_path(Path& path, const Vertices& vertices, const ConnectivityMap& connectivity, const Heuristics& heuristics, const std::size_t last) {

    const auto back = path.back();
    if(back == last) {
        return true;
    } else {
        path.emplace_back(*std::min_element(
            connectivity.at(back).begin(),
            connectivity.at(back).end(),
            detail::NeighborLess{ vertices, heuristics, back, last })
        );
        extend_path(path, vertices, connectivity, heuristics, last);     
        return false;
    }

}

Vertex face_center(const Mesh& mesh, const std::size_t i_face) {
    const auto& face = mesh.faces[i_face];
    const auto& a = mesh.vertices[face[0]];
    const auto& b = mesh.vertices[face[1]];
    const auto& c = mesh.vertices[face[2]];
    return { (a[0] + b[0] + c[0]) / 3.f, (a[1] + b[1] + c[1]) / 3.f, (a[2] + b[2] + c[2]) / 3.f };
}

Vertices build_centroids(const Mesh &mesh) {
    auto centroids = Vertices{ };
    centroids.reserve(mesh.faces.size());
    for(std::size_t face=0; face < mesh.faces.size(); ++face) {
        centroids.push_back(face_center(mesh, face));
    }
    return centroids;
}

class FindBestPath {

private:

    const Mesh& mesh;
    const Heuristics& heuristics;

public:

    FindBestPath(const Mesh& m, const Heuristics& h) : mesh{ m }, heuristics{ h } {  };

    Path operator()(const std::pair<std::size_t, std::size_t>& ends) const {

        auto path = Path{ ends.first };
        const auto connectivity = ConnectivityMapFactory::make_vertex_to_vertex(mesh.vertices, mesh.faces);
        detail::extend_path(path, mesh.vertices, connectivity, heuristics, ends.second);
        return path;

    }

    Path operator()(const std::pair<Barycenter, Barycenter>& ends) const {

        auto path = Path{ ends.first.face };
        const auto centroids = build_centroids(mesh);
        const auto connectivity = ConnectivityMapFactory::make_face_to_face(mesh.faces);
        detail::extend_path(path, centroids, connectivity, heuristics, ends.second.face);
        return path;
    
    }

};

} // namespace squaremind::detail

Path find_best_path(const Mesh& mesh, const Heuristics& heuristics, const Ends& ends) {

    return std::visit(detail::FindBestPath{ mesh, heuristics }, ends);

}

} // namespace astar