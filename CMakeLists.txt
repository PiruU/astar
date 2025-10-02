cmake_minimum_required(VERSION 3.18)
project(Astar VERSION 1.0.0 LANGUAGES CXX)

option(ASTAR_BUILD_TESTS   "Build unit tests" ON)
option(ASTAR_BUILD_PYTHON  "Build Python extension (nanobind)" ON)
option(BUILD_SHARED_LIBS   "Build shared libraries" OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

include(GNUInstallDirs)

include(CMakePackageConfigHelpers)

add_subdirectory(src)

target_include_directories(astar
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(astar PUBLIC cxx_std_17)

install(TARGETS astar
    EXPORT AstarTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/astar
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT AstarTargets
    FILE AstarTargets.cmake
    NAMESPACE Astar::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Astar
)

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

include(CTest) # définit l'option BUILD_TESTING
if(ASTAR_BUILD_TESTS AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

if(ASTAR_BUILD_PYTHON)
  add_subdirectory(python_package)
endif()
