#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/variant.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/function.h>

#include "astar/vertex.h"
#include "astar/face.h"
#include "astar/path.h"
#include "astar/mesh.h"
#include "astar/heuristics.h"
#include "astar/astar.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(astar_py, m) {
    m.doc() = "Bindings nanobind pour find_best_path";

    nb::class_<astar::Barycenter>(m, "Barycenter")
        .def(nb::init<>())
        .def_rw("face",    &astar::Barycenter::face)
        .def_rw("weights", &astar::Barycenter::weights);

    nb::class_<astar::Mesh>(m, "Mesh")
        .def(nb::init<>())
        .def_rw("vertices", &astar::Mesh::vertices)
        .def_rw("faces",    &astar::Mesh::faces);

    nb::class_<astar::Heuristics>(m, "Heuristics")
        .def(nb::init<>())
        .def_rw("distance", &astar::Heuristics::distance);

    // astar::Path (résultat)
    nb::class_<astar::Path>(m, "Path")
        .def(nb::init<>())
        .def_rw("steps",    &astar::Path::steps)     // vector<size_t>
        .def_rw("vertices", &astar::Path::vertices); // optional<Vertices>

    // Aides pour construire un astar::Ends côté Python (facultatif mais pratique)
    m.def("vertex_ends",
          [](std::size_t a, std::size_t b) -> astar::Ends {
              return astar::Ends{ std::pair<std::size_t,std::size_t>{a, b} };
          },
          "a"_a, "b"_a,
          "Crée un Ends défini par deux indices de sommets");

    m.def("barycentric_ends",
          [](const astar::Barycenter& A, const astar::Barycenter& B) -> astar::Ends {
              return astar::Ends{ std::pair<astar::Barycenter,astar::Barycenter>{A, B} };
          },
          "A"_a, "B"_a,
          "Crée un Ends défini par deux barycentres");

    // La fonction à exposer
    m.def("find_best_path",
          &astar::find_best_path,
          "mesh"_a,
          "heuristics"_a,
          "ends"_a,
          nb::arg("retrieve_vertices") = false,  // nom Python lisible
          R"doc(
              Trouve le meilleur chemin selon les heuristiques fournies.

              Args:
                  mesh (Mesh): sommets & faces.
                  heuristics (Heuristics): callables Python acceptés pour `distance(a, b) -> float`.
                  ends (tuple[int,int] | tuple[Barycenter,Barycenter]): extrémités.
                  retrieve_vertices (bool): si True, remplit `Path.vertices`.

              Returns:
                  Path
          )doc");
}
