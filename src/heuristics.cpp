#include "norms.h"

#include "heuristics.h"

namespace astar {

namespace HeuristicsFactory {

Heuristics make_euclidian() {

    return Heuristics{ { euclidian_norm } };

}

} // namespace astar::HeuristicsFactory

} // namespace astar