#pragma once

#include <functional>

#include "vertex.h"

namespace astar {

struct Heuristics {

    std::function<float(const Vertex&, const Vertex&)> distance;

};

namespace HeuristicsFactory {

Heuristics make_euclidian();

} // namespace astar::HeuristicsFactory

} // namespace astar