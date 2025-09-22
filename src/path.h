#pragma once

#include <cstddef>
#include <vector>
#include <utility>

namespace astar {

using Path = std::vector<std::size_t>;

using EndVertices = std::pair<std::size_t, std::size_t>;

} // namespace astar