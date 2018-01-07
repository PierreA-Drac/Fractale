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

# Extensions de fichier
set (SRC_EXT .cpp)
set (INC_EXT .hpp)

# Listes de fichier
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Listes de répertoire
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Répertoire
set (EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})

# Cible
add_executable (fractal ${SRC} ${INC})

# Compilation ==================================================================

# Include
include_directories (${INC_DIRS} ${OPENGL_INCLUDE_DIR})

# Link
link_directories (${OPENGL_gl_LIBRARY})
target_link_libraries (fractal GL Qt4::QtCore Qt4::QtGui Qt4::QtOpenGL)
