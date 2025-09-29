#include <gtest/gtest.h>

#include "edge_map.h"
#include "vertex.h"
#include "face.h"
#include "norms.h"

namespace astar {

namespace tests {

TEST(EdgeMapTest, TriangleProducesThreeEdgesWithCorrectLengths) {

    const auto vertices = Vertices{
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f } 
    };
    const auto faces = Faces{
        { {0, 1, 2} }
    };
    const auto edges = EdgeMapFactory::make(vertices, faces);

    ASSERT_EQ(edges.size(), 3u);

    const float d01 = euclidian_norm(vertices[0], vertices[1]);
    const float d12 = euclidian_norm(vertices[1], vertices[2]);
    const float d20 = euclidian_norm(vertices[2], vertices[0]);

    EXPECT_NEAR(edges.at({ { 0, 1 } }), d01, 1e-5f);
    EXPECT_NEAR(edges.at({ { 1, 0 } }), d01, 1e-5f);

    EXPECT_NEAR(edges.at({ { 1, 2 } }), d12, 1e-5f);
    EXPECT_NEAR(edges.at({ { 2, 1 } }), d12, 1e-5f);
    
    EXPECT_NEAR(edges.at({ { 2, 0 } }), d20, 1e-5f);
    EXPECT_NEAR(edges.at({ { 0, 2 } }), d20, 1e-5f);
    
}

} // namespace astar::tests

} // namespace astar