#include "norms.h"
#include "vertex.h"

#include "heuristics.h"

namespace astar {

namespace HeuristicsFactory {

Heuristics make_euclidian(const Vertex& target) {

    return Heuristics{ target, { euclidian_norm } };

}

} // namespace astar::HeuristicsFactory

} // namespace astar