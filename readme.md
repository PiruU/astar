# Astar Library

A lightweight C++17 library implementing an **A*** pathfinding algorithm on 3D meshes.  
It provides simple primitives (`Vertex`, `Face`, `Edge`), utilities (`EdgeMap`, `ConnectivityMap`), and the `find_best_path` function.

---

## Table of Contents

1. [Overview](#overview)  
2. [Features](#features)  
3. [Project Structure](#project-structure)  
4. [Installation](#installation)  
5. [Build Instructions](#build-instructions)  
6. [API Documentation](#api-documentation)  
   - [Types](#types)  
   - [Functions](#functions)  
7. [Example Usage](#example-usage)  
8. [Unit Tests](#unit-tests)  
9. [License](#license)  

---

## Overview

This library lets you compute shortest paths on meshes using the **A*** algorithm.  
Given a set of vertices and triangular faces, it finds the optimal path between two vertices.

---

## Features

- Simple mesh primitives: **Vertex**, **Face**, **Edge**  
- **Norms**: Euclidean distance  
- **Heuristics**: Euclidean heuristic generator  
- **EdgeMap**: edges and their lengths derived from faces  
- **ConnectivityMap**: adjacency relationships between vertices  
- **A*** algorithm: `find_best_path` function  

---

## Project Structure

```
src/
├── astar.h / .cpp             # A* algorithm (find_best_path)
├── connectivity_map.h / .cpp  # Connectivity map from edges
├── edge_map.h / .cpp          # Edge map from faces
├── heuristics.h / .cpp        # Heuristic factories
├── norms.h / .cpp             # Norms (Euclidean)
├── face.h                     # Face definition
├── path.h                     # Path definition
└── vertex.h                   # Vertex definition

tests/
├── astar_test.cpp
├── connectivity_map_test.cpp
├── edge_map_test.cpp
├── heuristics_test.cpp
└── norms_test.cpp
```

---

## Installation

Clone the repository:

```bash
git clone https://github.com/PiruU/astar
cd astar
```

Make sure you have:  
- A **C++17** capable compiler  
- **CMake ≥ 3.20**  
- **GoogleTest** (downloaded automatically with `FetchContent`)  

---

## Build Instructions

```bash
# Configure
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build the library and tests
cmake --build build --parallel

# Run tests (without CTest: launch test binaries directly)
./build/tests/astar_test
./build/tests/connectivity_map_test
./build/tests/edge_map_test
./build/tests/heuristics_test
./build/tests/norms_test
```

---

## API Documentation

### Types

- **`Vertex`** – point in 3D space  
  ```cpp
  Vertex v{1.0f, 2.0f, 0.0f};
  ```

- **`Vertices`** – collection of vertices (`std::vector<Vertex>`)

- **`Face`** – triangle defined by three indices  
  ```cpp
  Face f{ {0, 1, 2} };
  ```

- **`Faces`** – collection of faces

- **`Edge`** – undirected edge between two vertices

- **`EdgeMap`** – map from `Edge` to length

- **`ConnectivityMap`** – adjacency list (`vertex → neighbors`)

- **`Heuristics`** – callable object estimating distance to target

- **`Path`** – ordered sequence of vertex indices

---

### Functions

#### `float euclidian_norm(const Vertex&, const Vertex&)`
Compute the Euclidean distance between two vertices.

#### `Heuristics HeuristicsFactory::make_euclidian(const Vertex& target)`
Return a heuristic function based on Euclidean distance to `target`.

#### `EdgeMap EdgeMapFactory::make(const Vertices&, const Faces&)`
Construct all edges and lengths from a mesh.

#### `ConnectivityMap ConnectivityMapFactory::make(const EdgeMap&)`
Build adjacency from edges.

#### `Path find_best_path(const Vertices&, const Faces&, const Heuristics&, const EndVertices&)`
Compute the optimal path between a start and a goal vertex using A*.

---

## Example Usage

The following program builds a square mesh, splits it into two triangles, and finds a path between opposite corners:

```cpp
#include "astar.h"
#include "vertex.h"
#include "face.h"
#include "heuristics.h"
#include <vector>
#include <iostream>

using namespace astar;

int main() {
    // Vertices: square in XY plane
    Vertices vertices{
        Vertex{0.0f, 0.0f, 0.0f}, // 0
        Vertex{1.0f, 0.0f, 0.0f}, // 1
        Vertex{1.0f, 1.0f, 0.0f}, // 2
        Vertex{0.0f, 1.0f, 0.0f}  // 3
    };

    // Faces: two triangles forming the square
    Faces faces{
        Face{ {0, 1, 2} },
        Face{ {0, 2, 3} }
    };

    // Euclidean heuristic toward target (vertex 3)
    Heuristics h = HeuristicsFactory::make_euclidian(vertices[3]);

    // Run A*
    EndVertices startTarget{0, 3};
    Path p = find_best_path(vertices, faces, h, startTarget);

    // Print path
    std::cout << "Path found: ";
    for (auto v : p) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}
```

Expected output:

```
Path found: 0 3
```

---

## Unit Tests

Unit tests are written with **GoogleTest**.  
Each module (`astar`, `connectivity_map`, `edge_map`, `heuristics`, `norms`) has a corresponding test file in `tests/`.

Run all tests after building:

```bash
./build/tests/astar_test
./build/tests/connectivity_map_test
./build/tests/edge_map_test
./build/tests/heuristics_test
./build/tests/norms_test
```

## Python binding

rm -rf build_py
cmake -S python_package -B build_py \
  -DPython_EXECUTABLE="$(python -c 'import sys; print(sys.executable)')" \
  -Dnanobind_DIR="$(python -m nanobind --cmake_dir)"
cmake --build build_py -j
