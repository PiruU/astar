#pragma once

#include <functional>

#include "vertex.h"

namespace astar {

struct Heuristics {

    Vertex target;
    std::function<float(const Vertex&, const Vertex&)> distance;

};

namespace HeuristicsFactory {

Heuristics make_euclidian(const Vertex& target);

} // namespace astar::HeuristicsFactory

} // namespace astar