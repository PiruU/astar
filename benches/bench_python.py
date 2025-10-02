import math, sys, pathlib, matplotlib.pyplot

build = pathlib.Path(__file__).resolve().parents[1] / "build/python_package"
if build.exists():
    sys.path.insert(0, str(build))

from astar_py import Mesh, Heuristics, Barycenter, barycentric_ends, vertex_ends, find_best_path

from mesh_display import MeshDisplay
from path_display import PathDisplay
from pond_mesh import make_pond_mesh

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
        make_barycentric_ends(1360, 1232),
        retrieve_vertices=True
    )
    MeshDisplay(mesh).display()
    PathDisplay(path).display()
    matplotlib.pyplot.show()