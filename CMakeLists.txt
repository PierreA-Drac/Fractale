# Projet =======================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.0)

# Nom du projet et description.
project (Fractal)
set(PROJ_DESC "Fractal project for UVSQ")

# Mode de compilation.
set(CMAKE_BUILD_TYPE Debug)

# Structure ====================================================================

# Sources
set (SRC_PATH src/)
add_subdirectory (${SRC_PATH})

# Documentation
set (DOC_PATH doc/)
add_subdirectory (${DOC_PATH})
