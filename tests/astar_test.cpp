#include <gtest/gtest.h>

#include "astar.h"
#include "heuristics.h"
#include "helpers.h"

namespace astar {

namespace tests {

namespace {

} // namespace astar::tests::Anonymous

TEST(SimpleAStarTest, FindsDirectShortestPathOnSimpleSquareMesh) {

    const auto mesh = MeshFactory::make_simple();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto p = find_best_path(mesh, h, std::pair<std::size_t, std::size_t>{ 0, 3 });

    ASSERT_EQ(p.size() , 2u);
    EXPECT_EQ(p.front(), 0u);
    EXPECT_EQ(p.back() , 3u);

}

TEST(ComplexAStarTest, FindsStraightShortestPathOnComplexGridMesh) {

    const auto mesh = MeshFactory::make_complex();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto p = find_best_path(mesh, h, std::pair<std::size_t, std::size_t>{ 0, 8 });

    ASSERT_EQ(p.size() , 3u);
    EXPECT_EQ(p.at(0), 0u);
    EXPECT_EQ(p.at(1), 4u);
    EXPECT_EQ(p.at(2) , 8u);

}

TEST(ComplexAStarTest, FindsTwistedShortestPathOnComplexGridMesh) {

    const auto mesh = MeshFactory::make_complex();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto p = find_best_path(mesh, h, std::pair<std::size_t, std::size_t>{ 6, 2 });

    ASSERT_EQ(p.size() , 4u);
    EXPECT_EQ(p.at(0), 6u);
    EXPECT_EQ(p.at(1), 4u);
    EXPECT_EQ(p.at(2), 1u);
    EXPECT_EQ(p.at(3), 2u);

}

TEST(PondDualAStarTest, FindShortPathOnPondMesh) {

    const auto mesh = MeshFactory::make_pond();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto p = find_best_path(mesh, h, std::pair<Barycenter, Barycenter>{ {17, { 1.f, 1.f, 1.f } }, { 26, { 1.f, 1.f, 1.f } } });

    ASSERT_EQ(p.size() , 4u);
    EXPECT_EQ(p.at(0), 17u);
    EXPECT_EQ(p.at(1), 18u);
    EXPECT_EQ(p.at(2), 25u);
    EXPECT_EQ(p.at(3), 26u);

}



} // namespace astar::tests

} // namespace astar