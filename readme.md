# Astar — Pathfinding on 3D Meshes (C++17 + nanobind)

Lightweight C++17 library implementing a **pathfinding (A\*)** algorithm on 3D triangular meshes, with an optional Python binding via **nanobind**. The core exposes primitives (`Vertex`, `Face`, `Mesh`, …) and the **`find_best_path`** function.

---

## Table of Contents

1. [Overview](#overview)  
2. [Main Structures & API](#main-structures--api)  
3. [Repository Layout](#repository-layout)  
4. [Prerequisites](#prerequisites)  
5. [Build (C++ library)](#build-c-library)  
6. [Unit Tests (GoogleTest)](#unit-tests-googletest)  
7. [Python Binding (nanobind)](#python-binding-nanobind)   
8. [Usage Examples](#usage-examples)  
   - [C++](#c)  
   - [Python](#python)

---

## Overview

The project provides:

- **Basic types**: `Vertex = std::array<float,3>`, `Face = std::array<std::size_t,3>`, `Mesh`, `Path`,
- **Graph utilities** (connectivity/edges) to build adjacency,
- A configurable **heuristic** (`std::function<float(const Vertex&, const Vertex&)>`),
- And **`find_best_path`** (A\*) to return an optimal path on the mesh.

---

## Main Structures & API

### Types

```cpp
using Vertex   = std::array<float, 3>;
using Face     = std::array<std::size_t, 3>;
using Vertices = std::vector<Vertex>;
using Faces    = std::vector<Face>;

struct Path {
    std::vector<std::size_t> steps;       // indices of visited vertices
    std::optional<Vertices>  vertices;    // path vertices (optional)
};

struct Mesh {
    Vertices vertices;
    Faces    faces;
};

struct Heuristics {
    // distance(a, b) -> float estimate
    std::function<float(const Vertex&, const Vertex&)> distance;
};

struct Barycenter {
    std::size_t face;
    std::array<float, 3> weights;         // barycentric weights (sum = 1)
};

// Path endpoints: either two vertex indices OR two barycenters
using Ends = std::variant<
    std::pair<std::size_t, std::size_t>,
    std::pair<Barycenter, Barycenter>
>;
```

### Function

```cpp
Path find_best_path(const Mesh& mesh,
                    const Heuristics& heuristics,
                    const Ends& ends,
                    const bool retrieve_vertices = false);
```

- `retrieve_vertices=true` fills `Path::vertices` with the coordinates of the path vertices.
- `Ends` lets you specify endpoints **on vertices** or **inside faces** (barycenters).

---

## Repository Layout

```
src/
├── astar.cpp / astar.h                  # A* / find_best_path (+ Barycenter, Ends)
├── connectivity_map.cpp / .h            # connectivity construction
├── edge_map.cpp / .h                    # edge construction
├── heuristics.cpp / .h                  # heuristics (distance)
├── norms.cpp / .h                       # norms (Euclidean…)
├── face.h  mesh.h  path.h  vertex.h     # basic types
└── CMakeLists.txt                       # builds the C++ lib (e.g. target astar_lib)

python_package/
├── bindings.cpp                         # nanobind module
└── CMakeLists.txt                       # builds the Python module (target astar_py)
```

> The Python bindings are isolated under `python_package/` and link against the C++ library built from `src/`.

---

## Prerequisites

- **C++17** (recent Clang, GCC, or MSVC)  
- **CMake ≥ 3.16**  
- (For the Python module) **Python ≥ 3.8**, **nanobind** (`pip install nanobind`)

---

## Build (C++ library)

From the repository root:

```bash
cmake -S src -B build_core -DCMAKE_BUILD_TYPE=Release
cmake --build build_core -j
```

The static/shared library will be generated (for example: target `astar_lib` → `build_core/libastar_lib.a`).

---

## Unit Tests (GoogleTest)

From the repository root:

```bash
cmake -S tests -B build_tests -DCMAKE_BUILD_TYPE=Release
cmake --build build_tests -j
```

---

## Python Binding (nanobind)

```bash
python -m pip install -U nanobind

rm -rf build_py
cmake -S python_package -B build_py   -DPython_EXECUTABLE="$(python -c 'import sys; print(sys.executable)')"   -Dnanobind_DIR="$(python -m nanobind --cmake_dir)"

cmake --build build_py -j
```

The produced module will typically be `astar_py.cpython-<ver>-<plat>.so` under `build_py/`.

---

## Usage Examples

### C++

```cpp
#include "astar.h"
#include "mesh.h"
#include "heuristics.h"
#include <cmath>

int main() {
    Mesh mesh;
    mesh.vertices = {
        Vertex{0.f,0.f,0.f}, Vertex{1.f,0.f,0.f}, Vertex{0.f,1.f,0.f}
    };
    mesh.faces = { Face{ {0,1,2} } };

    Heuristics h;
    h.distance = [](const Vertex& a, const Vertex& b) -> float {
        const float dx=a[0]-b[0], dy=a[1]-b[1], dz=a[2]-b[2];
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    };

    Ends ends = std::pair<std::size_t,std::size_t>{0, 2};
    Path p = find_best_path(mesh, h, ends, /*retrieve_vertices=*/true);
    // p.steps -> indices; p.vertices -> positions (if requested)
}
```

### Python

```python
import math, astar_py as ap

m = ap.Mesh()
m.vertices = [(0.0,0.0,0.0),(1.0,0.0,0.0),(0.0,1.0,0.0)]
m.faces    = [(0,1,2)]

h = ap.Heuristics()
h.distance = lambda a,b: math.dist(a,b)

# Two vertex indices
ends = ap.ends_vertex_vertex(0, 2)

# Or two barycenters:
# A = ap.Barycenter(); A.face=0; A.weights=(1/3,1/3,1/3)
# B = ap.Barycenter(); B.face=0; B.weights=(0.2,0.3,0.5)
# ends = ap.ends_bary_bary(A, B)

p = ap.find_best_path(m, h, ends, retrieve_vertices=True)
print(p.steps, p.vertices)
```