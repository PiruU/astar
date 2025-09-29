#include <gtest/gtest.h>

#include "connectivity_map.h"
#include "vertex.h"
#include "face.h"

namespace astar {

namespace tests {

TEST(ConnectivityMapTest, TriangleAdjacencyIsBidirectional) {

    const auto vertices = Vertices{
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f } 
    };
    const auto faces = Faces{
        { {0, 1, 2} }
    };

    const auto connectivity = ConnectivityMapFactory::make_node_to_node(vertices, faces);

    ASSERT_EQ(connectivity.size(), 3u);

    EXPECT_EQ(connectivity.at(0).size(), 2u);
    EXPECT_EQ(connectivity.at(1).size(), 2u);
    EXPECT_EQ(connectivity.at(2).size(), 2u);

    EXPECT_TRUE(connectivity.at(0).count(1));
    EXPECT_TRUE(connectivity.at(0).count(2));
    EXPECT_FALSE(connectivity.at(0).count(0));

    EXPECT_TRUE(connectivity.at(1).count(0));
    EXPECT_TRUE(connectivity.at(1).count(2));
    EXPECT_FALSE(connectivity.at(1).count(1));

    EXPECT_TRUE(connectivity.at(2).count(0));
    EXPECT_TRUE(connectivity.at(2).count(1));
    EXPECT_FALSE(connectivity.at(2).count(2));
    
}

} // namespace astar::tests

} // namespace astar