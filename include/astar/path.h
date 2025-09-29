#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include "vertex.h"

namespace astar {

struct Path {

    std::vector<std::size_t> steps;
    std::optional<Vertices> vertices;

};

} // namespace astar