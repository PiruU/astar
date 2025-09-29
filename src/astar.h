#pragma once

#include <variant>

#include "mesh.h"
#include "path.h"
#include "heuristics.h"

namespace astar {

struct Barycenter {

    std::size_t face;
    std::array<float, 3> weights;

};

using Ends = std::variant<
    std::pair<std::size_t, std::size_t>, std::pair<Barycenter, Barycenter>
>;

class FindBestPath {

private:

    const Mesh& mesh;
    const Heuristics& heuristics;
    bool retrieve_vertices;

public:

    FindBestPath(const Mesh& m, const Heuristics& h, const bool retrieve_vertices);
    Path operator()(const std::pair<std::size_t, std::size_t>& ends) const;
    Path operator()(const std::pair<Barycenter, Barycenter>& ends) const;

};

Path find_best_path(const Mesh& mesh, const Heuristics& heuristics, const Ends& ends, const bool retrive_vertices=false);

} // namespace astar