#pragma once

#include <unordered_map>
#include <unordered_set>

#include "vertex.h"
#include "face.h"

namespace astar {

using ConnectivityMap = std::unordered_map<std::size_t, std::unordered_set<std::size_t>>;

namespace ConnectivityMapFactory {

ConnectivityMap make_node_to_node(const Vertices& vertices, const Faces& faces);

} // // namespace astar::ConnectivityMapFactory

} // namespace astar
