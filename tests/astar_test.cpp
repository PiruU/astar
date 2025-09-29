#include <gtest/gtest.h>

#include "astar/astar.h"
#include "astar/heuristics.h"

#include "helpers.h"

namespace astar {

namespace tests {

namespace {

} // namespace astar::tests::Anonymous

TEST(SimpleAStarTest, FindsDirectShortestPathOnSimpleSquareMesh) {

    const auto mesh = MeshFactory::make_simple();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto ends = std::pair<std::size_t, std::size_t>{ 0, 3 };
    const auto p = FindBestPath{ mesh, h, false }(ends);

    ASSERT_EQ(p.steps.size() , 2u);
    EXPECT_EQ(p.steps.front(), 0u);
    EXPECT_EQ(p.steps.back() , 3u);

}

TEST(ComplexAStarTest, FindsStraightShortestPathOnComplexGridMesh) {

    const auto mesh = MeshFactory::make_complex();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto ends = std::pair<std::size_t, std::size_t>{ 0, 8 };
    const auto p = FindBestPath{ mesh, h, false }(ends);

    ASSERT_EQ(p.steps.size() , 3u);
    EXPECT_EQ(p.steps.at(0), 0u);
    EXPECT_EQ(p.steps.at(1), 4u);
    EXPECT_EQ(p.steps.at(2) , 8u);

}

TEST(ComplexAStarTest, FindsTwistedShortestPathOnComplexGridMesh) {

    const auto mesh = MeshFactory::make_complex();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto ends = std::pair<std::size_t, std::size_t>{ 6, 2 };
    const auto p = FindBestPath{ mesh, h, false }(ends);


    ASSERT_EQ(p.steps.size() , 4u);
    EXPECT_EQ(p.steps.at(0), 6u);
    EXPECT_EQ(p.steps.at(1), 4u);
    EXPECT_EQ(p.steps.at(2), 1u);
    EXPECT_EQ(p.steps.at(3), 2u);

}

TEST(PondDualAStarTest, FindShortPathOnPondMesh) {

    const auto mesh = MeshFactory::make_pond();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto ends = std::pair<Barycenter, Barycenter>{
        { 17, { 1.f, 1.f, 1.f } },
        { 26, { 1.f, 1.f, 1.f } } 
    };
    const auto p = FindBestPath{ mesh, h, false }(ends);

    ASSERT_EQ(p.steps.size() , 4u);
    EXPECT_EQ(p.steps.at(0), 17u);
    EXPECT_EQ(p.steps.at(1), 18u);
    EXPECT_EQ(p.steps.at(2), 25u);
    EXPECT_EQ(p.steps.at(3), 26u);

}

TEST(PondDualAStarTest, FindLongUndeterminedPathOnPondMesh) {

    const auto mesh = MeshFactory::make_pond();
    const auto h = HeuristicsFactory::make_euclidian();
    const auto ends = std::pair<Barycenter, Barycenter>{
        {  0, { 1.f, 1.f, 1.f } },
        { 26, { 1.f, 1.f, 1.f } } 
    };
    const auto p = FindBestPath{ mesh, h, false }(ends);

    ASSERT_EQ(p.steps.size() , 14u);
    EXPECT_EQ(p.steps.at( 0),  0u);
    EXPECT_EQ(p.steps.at( 1),  1u);
    EXPECT_EQ(p.steps.at( 2),  9u);
    EXPECT_EQ(p.steps.at( 3), 10u);
    EXPECT_EQ(p.steps.at( 4),  3u);
    EXPECT_EQ(p.steps.at( 5),  4u);
    EXPECT_EQ(p.steps.at( 6),  5u);
    EXPECT_EQ(p.steps.at( 7), 11u);
    EXPECT_EQ(p.steps.at( 8), 12u);
    EXPECT_EQ(p.steps.at( 9), 13u);
    EXPECT_EQ(p.steps.at(10), 17u);
    EXPECT_EQ(p.steps.at(11), 18u);
    EXPECT_EQ(p.steps.at(12), 25u);
    EXPECT_EQ(p.steps.at(13), 26u);

}

} // namespace astar::tests

} // namespace astar