#pragma once

#include <utility>
#include <vector>

#include "vertex.h"
#include "face.h"
#include "heuristics.h"
#include "path.h"

namespace astar {

Path find_best_path(
    const Vertices& vertices, const Faces& faces, const Heuristics& heuristics, const EndVertices& startAndTarget
);

} // namespace astar