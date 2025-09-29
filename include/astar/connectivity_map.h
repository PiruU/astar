#pragma once

#include <unordered_map>
#include <unordered_set>

#include "vertex.h"
#include "face.h"

namespace astar {

using ConnectivityMap = std::unordered_map<std::size_t, std::unordered_set<std::size_t>>;

namespace ConnectivityMapFactory {

ConnectivityMap make_vertex_to_vertex(const Vertices& vertices, const Faces& faces);

ConnectivityMap make_face_to_face(const Faces& faces);

} // // namespace astar::ConnectivityMapFactory

} // namespace astar
