#include <gtest/gtest.h>

#include "astar/connectivity_map.h"
#include "astar/vertex.h"
#include "astar/face.h"

namespace astar {

namespace tests {

TEST(VertexConnectivityMapTest, TriangleAdjacencyIsBidirectional) {

    const auto vertices = Vertices{
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f } 
    };
    const auto faces = Faces{
        { {0, 1, 2} }
    };

    const auto connectivity = ConnectivityMapFactory::make_vertex_to_vertex(vertices, faces);

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

TEST(FaceConnectivityMapTest, SPlitSquareAdjacencyIsBidirectional) {

    const auto vertices = Vertices{
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f }
    };
    const auto faces = Faces{
        { {0, 1, 2} },
        { {0, 2, 3} }
    };

    const auto connectivity = ConnectivityMapFactory::make_face_to_face(faces);

    ASSERT_EQ(connectivity.size(), 2u);

    EXPECT_EQ(connectivity.at(0).size(), 1u);
    EXPECT_EQ(connectivity.at(1).size(), 1u);

    EXPECT_TRUE(connectivity.at(0).count(1));
    EXPECT_FALSE(connectivity.at(0).count(0));

    EXPECT_TRUE(connectivity.at(1).count(0));
    EXPECT_FALSE(connectivity.at(1).count(1));
    
}

} // namespace astar::tests

} // namespace astar