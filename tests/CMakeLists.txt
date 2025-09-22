add_executable(astar_tests
  astar_test.cpp
  connectivity_map_test.cpp
  edge_map_test.cpp
  heuristics_test.cpp
  norms_test.cpp
)

target_link_libraries(astar_tests
  PRIVATE
    astar_lib
    GTest::gtest_main
)

target_include_directories(astar_tests
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

include(GoogleTest)
gtest_discover_tests(astar_tests
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  DISCOVERY_TIMEOUT 60
)