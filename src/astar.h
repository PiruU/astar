#pragma once

#include "connectivity_map.h"
#include "vertex.h"
#include "heuristics.h"
#include "path.h"

namespace astar {

Path find_best_path(
    const Vertices& vertices, const ConnectivityMap& connectivity, const Heuristics& heuristics, const EndVertices& startAndTarget
);

} // namespace astar