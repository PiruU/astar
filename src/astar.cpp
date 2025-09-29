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

    bool operator()(const std::size_t one, const std::size_t other) const {
        const auto one_cost   = heuristics.distance(vertices[current], vertices[one]  ) + heuristics.distance(vertices[one]  , heuristics.target);
        const auto other_cost = heuristics.distance(vertices[current], vertices[other]) + heuristics.distance(vertices[other], heuristics.target);
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
            detail::NeighborLess{ vertices, heuristics, back })
        );
        extend_path(path, vertices, connectivity, heuristics, last);     
        return false;
    }

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

        return { };
    
    }

};

} // namespace squaremind::detail

Path find_best_path(const Mesh& mesh, const Heuristics& heuristics, const Ends& ends) {

    return std::visit(detail::FindBestPath{ mesh, heuristics }, ends);

}

} // namespace astar