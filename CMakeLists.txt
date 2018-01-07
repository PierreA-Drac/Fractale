# Projet =======================================================================

cmake_minimum_required (VERSION 3.0)
project (Fractal)

# Compilation ==================================================================

# Bibliothèques tierces
#
# OpenGL
include (FindOpenGL)
# Qt4
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
find_package (Qt4 REQUIRED QtCore QtGui QtOpenGL)

# Fichiers sources
set (SRC_PATH src/)
set (INC_PATH inc/)
file (GLOB_RECURSE SRC ${SRC_PATH}*)
file (GLOB_RECURSE INC ${INC_PATH}*)

# Fichiers binaires
set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
add_executable (fractal ${SRC} ${INC})

# Include
include_directories (${INC_PATH} ${OPENGL_INCLUDE_DIR})

# Link
link_directories (${OPENGL_gl_LIBRARY})
target_link_libraries (fractal GL Qt4::QtCore Qt4::QtGui Qt4::QtOpenGL)
