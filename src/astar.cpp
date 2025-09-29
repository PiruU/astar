#include <algorithm>
#include <iterator>
#include <optional>
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

struct CopyEligibleNeighbors {

    const std::vector<std::size_t>& steps;

    bool operator()(const std::size_t neighbor) const {

        return steps.size() > 1 ? neighbor != *(std::prev(steps.end(), 2)) : true;

    }

};

bool extend_steps(std::vector<std::size_t>& steps, const Vertices& vertices, const ConnectivityMap& connectivity, const Heuristics& heuristics, const std::size_t last) {

    const auto back = steps.back();
    if(back == last) {
        return true;
    } else {
        auto neighbors = std::vector<std::size_t>{ };
        std::copy_if(
            connectivity.at(back).begin(), connectivity.at(back).end(), std::back_inserter(neighbors), CopyEligibleNeighbors{ steps }
        );
        steps.emplace_back(*std::min_element(
            neighbors.begin(), neighbors.end(), detail::NeighborLess{ vertices, heuristics, back, last })
        );
        extend_steps(steps, vertices, connectivity, heuristics, last);     
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

Vertices get_vertices(const Path& path, const Vertices& vertices) {

    auto retrieved = Vertices{ };
    retrieved.reserve(path.steps.size());
    std::for_each(path.steps.begin(), path.steps.end(), [&retrieved, &vertices](const auto step) {
        retrieved.push_back(vertices[step]);
    });
    return retrieved;
}

} // namespace squaremind::detail


FindBestPath::FindBestPath(const Mesh& m, const Heuristics& h, const bool r) :
    mesh{ m }, heuristics{ h }, retrieve_vertices{ r } {

};

Path FindBestPath::operator()(const std::pair<std::size_t, std::size_t>& ends) const {

    auto path = Path{ { ends.first }, std::nullopt };
    const auto connectivity = ConnectivityMapFactory::make_vertex_to_vertex(mesh.vertices, mesh.faces);
    detail::extend_steps(path.steps, mesh.vertices, connectivity, heuristics, ends.second);
    if(retrieve_vertices) path.vertices = detail::get_vertices(path, mesh.vertices);
    return path;

}

Path FindBestPath::operator()(const std::pair<Barycenter, Barycenter>& ends) const {

    auto path = Path{ { ends.first.face }, std::nullopt };
    const auto centroids = detail::build_centroids(mesh);
    const auto connectivity = ConnectivityMapFactory::make_face_to_face(mesh.faces);
    detail::extend_steps(path.steps, centroids, connectivity, heuristics, ends.second.face);
    if(retrieve_vertices) path.vertices = detail::get_vertices(path, centroids);
    return path;
    
}

Path find_best_path(const Mesh& mesh, const Heuristics& heuristics, const Ends& ends, const bool retrieve_vertices) {

    return std::visit(FindBestPath{ mesh, heuristics, retrieve_vertices }, ends);

}

} // namespace astar