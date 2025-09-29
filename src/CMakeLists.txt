if(TARGET astar)
  message(FATAL_ERROR "La cible 'astar' existe déjà. 'src' est ajouté deux fois.")
endif()

add_library(astar
  astar.cpp
  connectivity_map.cpp
  edge_map.cpp
  heuristics.cpp
  norms.cpp
)

target_include_directories(astar PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(astar PUBLIC cxx_std_17)