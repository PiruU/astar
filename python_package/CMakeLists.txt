find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(astar_py MODULE bindings.cpp)

if (TARGET astar_lib)
  set(CORE_TARGET astar_lib)
elseif (TARGET astar)
  set(CORE_TARGET astar)   # au cas où tu aurais renommé/aliassé
else()
  message(FATAL_ERROR "Cible core introuvable (ni 'astar_lib' ni 'astar').")
endif()

target_link_libraries(astar_py PRIVATE ${CORE_TARGET})
target_include_directories(astar_py PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
