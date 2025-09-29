import math, sys, pathlib, matplotlib.pyplot

build = pathlib.Path(__file__).resolve().parents[1] / "build/python_package"
if build.exists():
    sys.path.insert(0, str(build))

from astar_py import Mesh, Heuristics, Barycenter, barycentric_ends, vertex_ends, find_best_path

from mesh_display import MeshDisplay
from path_display import PathDisplay

def make_pond_mesh() -> Mesh:
    mesh = Mesh()
    mesh.vertices = [
    (0., 0., 0.), (1., 0., 0.), (2., 0., 0.), (3., 0., 0.), (4., 0., 0.),
    (0., 1., 0.), (1., 1., 0.), (2., 1., 0.), (3., 1., 0.), (4., 1., 0.),
    (0., 2., 0.), (1., 2., 0.), (2., 2., 0.), (3., 2., 0.), (4., 2., 0.),
    (0., 3., 0.), (1., 3., 0.), (2., 3., 0.), (3., 3., 0.), (4., 3., 0.),
    (0., 4., 0.), (1., 4., 0.), (2., 4., 0.), (3., 4., 0.), (4., 4., 0.)
    ]
    mesh.faces = [
    ( 0,  1,  5), ( 1,  5,  6), ( 1,  2,  6), ( 2,  6,  7), ( 2,  3,  7),
    ( 3,  7,  8), ( 3,  4,  8), ( 4,  8,  9), ( 5, 11, 10), ( 5,  6, 11),
    ( 6,  7, 11), ( 7,  8, 13), ( 8, 13,  9), ( 9, 14, 13), (10, 15, 16),
    (10, 11, 16), (11, 17, 16), (13, 14, 19), (13, 19, 18), (15, 21, 20),
    (15, 16, 21), (16, 22, 21), (16, 17, 22), (17, 22, 18), (18, 23, 22),
    (18, 19, 24), (18, 24, 23)
    ]
    return mesh

def make_barycentric_ends(a: int, b: int):
    first, last = Barycenter(), Barycenter()
    first.face, last.face = a, b
    return barycentric_ends(first, last)

def make_euclidian_euristics() -> Heuristics:
    h = Heuristics()
    h.distance = lambda a, b: math.dist(a, b)
    return h

if __name__ == "__main__":
    mesh = make_pond_mesh()
    path = find_best_path(
        mesh,
        make_euclidian_euristics(),
        make_barycentric_ends(0, 26),
        retrieve_vertices=True
    )
    MeshDisplay(mesh).display()
    PathDisplay(path).display()
    matplotlib.pyplot.show()