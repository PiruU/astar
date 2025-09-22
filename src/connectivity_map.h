#pragma once

#include <unordered_map>
#include <unordered_set>

#include "edge_map.h"

namespace astar {

using ConnectivityMap = std::unordered_map<std::size_t, std::unordered_set<std::size_t>>;

namespace ConnectivityMapFactory {

ConnectivityMap make(const EdgeMap& edges);

} // // namespace astar::ConnectivityMapFactory

} // namespace astar
