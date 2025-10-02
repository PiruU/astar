import sys, pathlib, matplotlib.pyplot, typing, dataclasses, itertools

build = pathlib.Path(__file__).resolve().parents[1] / "build_py"
if build.exists():
    sys.path.insert(0, str(build))

from astar_py import Path

class Visitable:
    def __call__(self, visitor: typing.Any) -> typing.Any:
        return visitor.visit(self)

@dataclasses.dataclass
class PathDisplay(Visitable):
    path: Path

@dataclasses.dataclass
class _DisplayPath:
    def visit(self, display: PathDisplay) -> None:
        vertices = display.path.vertices
        xs, ys, _ = zip(*itertools.islice(itertools.cycle(vertices), len(vertices)))
        matplotlib.pyplot.plot(xs, ys, '-', color='r', lw=3)

def display_path(display: PathDisplay) -> None:
    display(_DisplayPath())

PathDisplay.display = display_path