cmake_minimum_required(VERSION 3.16)
project(astar_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Amener ta lib core (rebâtie dans un sous-dossier du build)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../src
                 ${CMAKE_CURRENT_BINARY_DIR}/_astar_core_build)

# --- GoogleTest via FetchContent ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# (Windows) aligne la CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Exécutable de tests ---
add_executable(astar_tests
  helpers.cpp
  astar_test.cpp
  connectivity_map_test.cpp
  edge_map_test.cpp
  heuristics_test.cpp
  norms_test.cpp
)

target_link_libraries(astar_tests PRIVATE
  astar_lib
  GTest::gtest_main   # fournit le main(); inutile d’ajouter aussi GTest::gtest
)

target_include_directories(astar_tests PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../src
)

# --- Intégration CTest ---
include(GoogleTest)
gtest_discover_tests(astar_tests)
enable_testing()
