import sys, pathlib, matplotlib.pyplot, typing, dataclasses, itertools

build = pathlib.Path(__file__).resolve().parents[1] / "build_py"
if build.exists():
    sys.path.insert(0, str(build))

from astar_py import Mesh

class Visitable:
    def __call__(self, visitor: typing.Any) -> typing.Any:
        return visitor.visit(self)

@dataclasses.dataclass
class MeshDisplay(Visitable):
    mesh: Mesh

@dataclasses.dataclass
class _DisplayVertices:
    def visit(self, display: MeshDisplay) -> None:
        for x, y, _ in display.mesh.vertices:
            matplotlib.pyplot.plot(x, y, 'o', color='b')

@dataclasses.dataclass
class _DisplayFace:
    face : typing.Any
    ls   : str
    color: str

    def visit(self, display: MeshDisplay) -> None:
        vertices = [ display.mesh.vertices[v] for v in self.face ]
        xs, ys, _ = zip(*itertools.islice(itertools.cycle(vertices), len(vertices) + 1))
        matplotlib.pyplot.plot(xs, ys, ls=self.ls, color=self.color)

@dataclasses.dataclass
class _DisplayFaces:
    def visit(self, display: MeshDisplay) -> None:
        for f in display.mesh.faces:
            display(_DisplayFace(f, ls='-', color='k'))

def _display_mesh(display: MeshDisplay) -> None:
    display(_DisplayVertices())
    display(_DisplayFaces())

MeshDisplay.display = _display_mesh