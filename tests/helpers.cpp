#include "astar/face.h"
#include "astar/vertex.h"
#include "astar/mesh.h"

#include "helpers.h"

namespace astar {

namespace tests {

namespace MeshFactory {

Mesh make_simple() {

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

Mesh make_complex() {

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

Mesh make_pond() {

    const auto vertices = Vertices{
    { 0.f, 0.f, 0.f }, { 1.f, 0.f, 0.f }, { 2.f, 0.f, 0.f }, { 3.f, 0.f, 0.f }, { 4.f, 0.f, 0.f },
    { 0.f, 1.f, 0.f }, { 1.f, 1.f, 0.f }, { 2.f, 1.f, 0.f }, { 3.f, 1.f, 0.f }, { 4.f, 1.f, 0.f },
    { 0.f, 2.f, 0.f }, { 1.f, 2.f, 0.f }, { 2.f, 2.f, 0.f }, { 3.f, 2.f, 0.f }, { 4.f, 2.f, 0.f },
    { 0.f, 3.f, 0.f }, { 1.f, 3.f, 0.f }, { 2.f, 3.f, 0.f }, { 3.f, 3.f, 0.f }, { 4.f, 3.f, 0.f },
    { 0.f, 4.f, 0.f }, { 1.f, 4.f, 0.f }, { 2.f, 4.f, 0.f }, { 3.f, 4.f, 0.f }, { 4.f, 4.f, 0.f }
    };

    const auto faces = Faces{
    {  0,  1,  5 }, {  1,  5,  6 }, {  1,  2,  6 }, {  2,  6,  7 }, {  2,  3,  7 },
    {  3,  7,  8 }, {  3,  4,  8 }, {  4,  8,  9 }, {  5, 11, 10 }, {  5,  6, 11 },
    {  6,  7, 11 }, {  7,  8, 13 }, {  8, 13,  9 }, {  9, 14, 13 }, { 10, 15, 16 },
    { 10, 11, 16 }, { 11, 17, 16 }, { 13, 14, 19 }, { 13, 19, 18 }, { 15, 21, 20 },
    { 15, 16, 21 }, { 16, 22, 21 }, { 16, 17, 22 }, { 17, 22, 18 }, { 18, 23, 22 },
    { 18, 19, 24 }, { 18, 24, 23 }
    };

    return { vertices, faces };

}

} // namespace astar::tests::MeshFactory

} // namespace astar::tests

} // namespace astar