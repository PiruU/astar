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

} // namespace squaremind::detail

//Path _find_path(const Path& path, const Vertices& vertices, const ConnectivityMap& connectivity, const Heuristics& heuristics, const std::size_t last) {
//    const auto back = path.back();
//    if(back == last) {
//        return path;
//    } else {
//        const auto step = std::min(connectivity.at(back).begin(), connectivity.at(back).end(), NeighborLess{  });
//
////        path += [ min(filter(lambda n: n != path[-2], [n for n in connectivity[path[-1]]]), key=lambda n: heuristics(vertices[path[-1]], vertices[n]) + heuristics(vertices[n], vertices[last])) ]
////        return _find_path(path, vertices, connectivity, last, heuristics)        
//    }
//}

//def _find_path(path: typing.List[int], vertices: typing.List[Vertex], connectivity: typing.DefaultDict[int, typing.Set[int]], last: int, heuristics: typing.Callable[[Vertex, Vertex], float]) -> typing.List[int]:
//    if path[-1] == last:
//        return path
//    else:
//        path += [ min(filter(lambda n: n != path[-2], [n for n in connectivity[path[-1]]]), key=lambda n: heuristics(vertices[path[-1]], vertices[n]) + heuristics(vertices[n], vertices[last])) ]
//        return _find_path(path, vertices, connectivity, last, heuristics)
//
//class FindPath:
//    def __init__(self, ends: typing.Tuple[int, int], heuristics: typing.Callable[[Vertex, Vertex], float]=euclidian):
//        (self.first, self.last), self.heuristics = ends, heuristics
//
//    def visit(self, mesh: Mesh) -> Path:
//        connectivity, path = mesh(MakeNodeConnectivity()), [self.first] * 2
//        return Path([ v for v in _find_path(path, mesh.vertices, connectivity, self.last, self.heuristics) ][1:])
//
//class FindDualPath:
//    def __init__(self, ends: typing.Tuple[int, int], connectivity: typing.DefaultDict[int, typing.Set[int]], heuristics: typing.Callable[[Vertex, Vertex], float]=euclidian):
//        (self.first, self.last), self.connectivity, self.heuristics = ends, connectivity, heuristics
//
//    def visit(self, mesh: Mesh) -> Path:
//        path = [self.first] * 2
//        return Path([ v for v in _find_path(path, mesh.vertices, self.connectivity, self.last, self.heuristics) ][1:])



Path find_best_path(const Vertices& vertices, const Faces& faces, const Heuristics& heuristics, const EndVertices& startAndTarget) {

    const auto edges = EdgeMapFactory::make(vertices, faces);
    const auto connectivity = ConnectivityMapFactory::make(edges);
    auto path = Path{ startAndTarget.first };
    while(path.back() != startAndTarget.second) {
        const auto neighbors = connectivity.at(path.back());
        path.push_back(
            *std::min_element(neighbors.begin(), neighbors.end(), detail::NeighborLess{ vertices, heuristics, path.back()})
        );
    }
    return path;

}

} // namespace astar