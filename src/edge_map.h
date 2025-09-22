#pragma once

#include <array>
#include <unordered_map>

#include "vertex.h"
#include "face.h"

namespace astar {

struct Edge {

    std::array<std::size_t, 2> v;

};

struct EdgeEqual {

    bool operator()(const Edge& one, const Edge& other) const;

};

struct EdgeHash {

    std::size_t operator()(const Edge& edge) const noexcept;

};

using EdgeMap = std::unordered_map<Edge, float, EdgeHash, EdgeEqual>;

namespace EdgeMapFactory {

EdgeMap make(const Vertices& vertices, const Faces& faces);

} // namespace astar::EdgeMapFactory

} // namespace astar