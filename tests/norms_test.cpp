#include <gtest/gtest.h>

#include "norms.h"
#include "vertex.h"

namespace astar {

namespace tests {

TEST(NormsTest, EuclidianNormBasic) {

    const auto a = Vertex{ 0.0f, 0.0f,  0.0f };
    const auto b = Vertex{ 3.0f, 4.0f, 12.0f };
    float d = euclidian_norm(a, b);
    // sqrt(3^2 + 4^2 + 12^2) = sqrt(9 + 16 + 144) = sqrt(169) = 13
    EXPECT_NEAR(d, 13.0f, 1e-5f);

}

TEST(NormsTest, EuclidianNormSymmetry) {

    const auto a = Vertex{ 1.0f, -2.0f,  5.0f };
    const auto b = Vertex{ -4.0f, 3.0f, -1.0f };
    EXPECT_NEAR(euclidian_norm(a, b), euclidian_norm(b, a), 1e-5f);
    
}

} // namespace astar::tests

} // namespace astar