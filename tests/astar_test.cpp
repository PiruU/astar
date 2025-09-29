#include <gtest/gtest.h>

#include "astar.h"
#include "connectivity_map.h"
#include "vertex.h"
#include "face.h"
#include "heuristics.h"

namespace astar {

namespace tests {

namespace {

struct Mesh {

    Vertices vertices;
    Faces faces;

};

Mesh make_simple_square() {

    const auto vertices = Vertices{
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f } 
    };

    const auto faces = Faces{
        { { 0, 1, 2 } },
        { { 0, 2, 3 } }
    };

    return { vertices, faces };

}

Mesh make_complex_grid() {

    const auto vertices = Vertices{
        { 0.0f, 0.0f, 0.0f },
        { 1.5f, 0.0f, 0.0f }, // small x-offset here
        { 2.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { 2.0f, 1.0f, 0.0f },
        { 0.0f, 2.0f, 0.0f },
        { 1.0f, 2.0f, 0.0f },
        { 2.0f, 2.0f, 0.0f },
    };

    const auto faces = Faces{
        { { 0, 1, 4 } },
        { { 0, 4, 3 } },
        { { 1, 5, 4 } },
        { { 1, 2, 5 } },
        { { 3, 4, 6 } },
        { { 4, 7, 6 } },
        { { 4, 8, 7 } },
        { { 4, 5, 8 } },
    };

    return { vertices, faces };

}

} // namespace astar::tests::Anonymous

TEST(SimpleAStarTest, FindsDirectShortestPathOnSimpleSquareMesh) {

    const auto mesh = make_simple_square();

    const auto h = HeuristicsFactory::make_euclidian(mesh.vertices[3]);

    const auto startTarget = EndVertices{0, 3};
    const auto connectivity = ConnectivityMapFactory::make_node_to_node(mesh.vertices, mesh.faces);
    const auto p = find_best_path(mesh.vertices, connectivity, h, startTarget);

    ASSERT_EQ(p.size() , 2u);
    EXPECT_EQ(p.front(), 0u);
    EXPECT_EQ(p.back() , 3u);

}

TEST(ComplexAStarTest, FindsStraightShortestPathOnComplexGridMesh) {

    const auto mesh = make_complex_grid();

    const auto h = HeuristicsFactory::make_euclidian(mesh.vertices[8]);

    const auto startTarget = EndVertices{0, 8};
    const auto connectivity = ConnectivityMapFactory::make_node_to_node(mesh.vertices, mesh.faces);
    const auto p = find_best_path(mesh.vertices, connectivity, h, startTarget);

    ASSERT_EQ(p.size() , 3u);
    EXPECT_EQ(p.at(0), 0u);
    EXPECT_EQ(p.at(1), 4u);
    EXPECT_EQ(p.at(2) , 8u);

}

TEST(ComplexAStarTest, FindsTwistedShortestPathOnComplexGridMesh) {

    const auto mesh = make_complex_grid();

    const auto h = HeuristicsFactory::make_euclidian(mesh.vertices[2]);

    const auto startTarget = EndVertices{6, 2};
    const auto connectivity = ConnectivityMapFactory::make_node_to_node(mesh.vertices, mesh.faces);
    const auto p = find_best_path(mesh.vertices, connectivity, h, startTarget);

    ASSERT_EQ(p.size() , 4u);
    EXPECT_EQ(p.at(0), 6u);
    EXPECT_EQ(p.at(1), 4u);
    EXPECT_EQ(p.at(2), 1u);
    EXPECT_EQ(p.at(3), 2u);

}

} // namespace astar::tests

} // namespace astar