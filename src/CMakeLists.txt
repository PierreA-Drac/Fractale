# Macros =======================================================================

# Crée une liste de tout les dossiers contenant un header.
macro (HEADER_DIRECTORIES return_list)
    file (GLOB_RECURSE new_list *${INC_EXT})
    set (dir_list "")
    foreach (file_path ${new_list})
        get_filename_component (dir_path ${file_path} PATH)
        set (dir_list ${dir_list} ${dir_path})
    endforeach ()
    list (REMOVE_DUPLICATES dir_list)
    set (${return_list} ${dir_list})
endmacro ()

# Bibliothèques ================================================================

# OpenGL
include (FindOpenGL)

# Qt4
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
find_package (Qt4 REQUIRED QtCore QtGui QtOpenGL)

# Sources ======================================================================

# Extension des fichiers sources et des headers.
set (SRC_EXT .cpp)
set (INC_EXT .hpp)

# Dossiers
set (SHADER_DIR Shaders)

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})
file (GLOB_RECURSE SHADER ${SHADER_DIR}/*)

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de l'exécutable.
set (EXE fractal)

# Dépendances de l'exécutable.
add_executable (${EXE} ${SRC} ${INC} ${SHADER_DIR})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
include_directories (${INC_DIRS} ${OPENGL_INCLUDE_DIR})

# Dossiers des bibliothèques à inclure pour le linker.
link_directories (${OPENGL_gl_LIBRARY})

# Bibliothèques liées à l'exécutable.
target_link_libraries (${EXE} GL Qt4::QtCore Qt4::QtGui Qt4::QtOpenGL)

# Flags
#
# Debug
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options (${EXE} PUBLIC -g3 -Wall)
endif()
# Communs
target_compile_options (${EXE} PUBLIC -fPIC -std=c++0x)

# Commandes ====================================================================

# Copie les shaders avec l'exécutable.
add_custom_command (OUTPUT ${SHADER_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_DIR}/
        ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR}/
    DEPENDS ${SHADER}
    )

# End message
add_custom_command (TARGET ${EXE}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "[100%] Compilation done in ${CMAKE_BUILD_TYPE} mode"
    )

# Installation =================================================================

install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${EXE} DESTINATION bin)
