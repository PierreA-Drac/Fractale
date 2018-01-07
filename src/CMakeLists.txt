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

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de l'exécutable.
set (EXE fractal)

# Dépendances de l'exécutable.
add_executable (${EXE} ${SRC} ${INC})

# set (EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
include_directories (${INC_DIRS} ${OPENGL_INCLUDE_DIR})

# Dossiers des bibliothèques à inclure pour le linker.
link_directories (${OPENGL_gl_LIBRARY})

# Bibliothèques liées à l'exécutable.
target_link_libraries (${EXE} GL Qt4::QtCore Qt4::QtGui Qt4::QtOpenGL)

# Installation =================================================================

install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${EXE} DESTINATION bin)
