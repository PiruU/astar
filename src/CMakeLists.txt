add_library(astar_lib
  astar.cpp
  connectivity_map.cpp
  edge_map.cpp
  heuristics.cpp
  norms.cpp
)

target_include_directories(astar_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_features(astar_lib PUBLIC cxx_std_17)