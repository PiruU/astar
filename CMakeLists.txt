cmake_minimum_required(VERSION 3.18)
project(Astar VERSION 1.0.0 LANGUAGES CXX)

# Options de build
option(ASTAR_BUILD_TESTS   "Build unit tests" ON)
option(ASTAR_BUILD_PYTHON  "Build Python extension (nanobind)" ON)
option(BUILD_SHARED_LIBS   "Build shared libraries" OFF)

# Politique d'export/visibilité (utile si lib partagée)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# Dossiers standard
include(GNUInstallDirs)

# Pour la génération des fichiers de package (Config/Version)
include(CMakePackageConfigHelpers)

# Cible principale définie dans src/
add_subdirectory(src)

# En-têtes publics
target_include_directories(astar
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(astar PUBLIC cxx_std_17)

# ========= Installation / Export de la bibliothèque =========
# Installe la lib et publie un export AstarTargets sous le namespace Astar::
install(TARGETS astar
    EXPORT AstarTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Installe les headers publics
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/astar
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Exporte les cibles (targets) pour import ultérieur via find_package
install(EXPORT AstarTargets
    FILE AstarTargets.cmake
    NAMESPACE Astar::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Astar
)

# Fichiers de configuration du package (AstarConfig.cmake / AstarConfigVersion.cmake)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/AstarConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/AstarConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Astar
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/AstarConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/AstarConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/AstarConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Astar
)

# ========= Tests =========
include(CTest) # définit l'option BUILD_TESTING
if(ASTAR_BUILD_TESTS AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

# ========= Module Python (nanobind) =========
if(ASTAR_BUILD_PYTHON)
  add_subdirectory(python_package)
endif()
