cmake_minimum_required(VERSION 3.14)

include(FetchContent)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(astar_tests
  astar_test.cpp
  connectivity_map_test.cpp
  edge_map_test.cpp
  heuristics_test.cpp
  norms_test.cpp
  helpers.cpp
)

target_link_libraries(astar_tests
  PRIVATE
    astar
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(astar_tests)
