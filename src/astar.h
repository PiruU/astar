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

Path find_best_path(const Mesh& mesh, const Heuristics& heuristics, const Ends& ends);

} // namespace astar