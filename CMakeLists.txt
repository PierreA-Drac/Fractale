# Projet =======================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.0)

# Nom du projet.
project (Fractal)

# Mode de compilation.
set(CMAKE_BUILD_TYPE Debug)

# Structure ====================================================================

# Sources
set (SRC_PATH src/)
add_subdirectory (${SRC_PATH})
