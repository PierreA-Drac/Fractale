# Projet =======================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.0)

# Nom du projet et description.
project (Fractal)
set (PROJ_DESC "Fractal project for UVSQ")

# Mode de compilation.
set (CMAKE_BUILD_TYPE Release)

# Paramètres ===================================================================

# Tag generation
if (NOT TAG_GENERATOR)
    find_program (TAG_GENERATOR ctags)
    if (${TAG_GENERATOR} STREQUAL "TAG_GENERATOR-NOTFOUND")
        message ("-- Could NOT find Ctags")
        message ("-- Tags will NOT be generated")
        set (TAG_GEN false)
    else ()
        message ("-- Found Ctags: ${TAG_GENERATOR}")
        set (TAG_GEN true)
    endif()
endif()

# Dosser d'installation
if (UNIX AND ${CMAKE_INSTALL_PREFIX} STREQUAL "/usr/local")
    set (CMAKE_INSTALL_PREFIX /opt)
endif()

# Structure ====================================================================

# Sources
set (SRC_PATH src)
add_subdirectory (${SRC_PATH})

# Documentation
set (DOC_PATH doc)
add_subdirectory (${DOC_PATH})

# Rapport
set (REPORT_PATH report)
add_subdirectory (${REPORT_PATH})
