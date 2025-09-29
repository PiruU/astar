#include <gtest/gtest.h>

#include "astar/heuristics.h"
#include "astar/norms.h"
#include "astar/vertex.h"

namespace astar {

namespace tests {

TEST(HeuristicsTest, EuclidianHeuristicEqualsDistanceToTarget) {

    const auto target = Vertex{ 1.0f, 2.0f, 3.0f };
    const auto h = HeuristicsFactory::make_euclidian();

    const auto p = Vertex{ 4.0f, -2.0f, 7.5f };
    float expected = euclidian_norm(p, target);
    EXPECT_NEAR(h.distance(p, target), expected, 1e-5f);

}

} // namespace astar::tests

} // namespace astar