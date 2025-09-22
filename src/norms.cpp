#include <cmath>

#include "vertex.h"
#include "norms.h"

namespace astar {

float euclidian_norm(const Vertex& one, const Vertex& other) {
    const auto dx = one[0] - other[0];
    const auto dy = one[1] - other[1];
    const auto dz = one[2] - other[2];
    return sqrt(dx * dx + dy * dy + dz * dz);
}

} // namespace astar