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
include (FindOpenGL REQUIRED)

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
set (EXE fractal PARENT_SCOPE)
set (EXE fractal)

# Dépendances de l'exécutable.
add_executable (${EXE} ${SRC} ${INC} ${SHADER_DIR})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
include_directories (${INC_DIRS})

# Dossiers des bibliothèques à inclure pour le linker.
link_directories ()

# Bibliothèques liées à l'exécutable.
# N.B. : Pour OpenGL et Qt, la notation Qt::* et OpenGL::* automatise
# l'importation des headers et des bibliothèques.
target_link_libraries (${EXE} OpenGL::GL Qt4::QtCore Qt4::QtGui Qt4::QtOpenGL)

# Flags
#
# Debug
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options (${EXE} PUBLIC -Wall)
    if (UNIX)
        target_compile_options (${EXE} PUBLIC -g3)
    endif()
endif()
# Communs
if (UNIX)
    target_compile_options (${EXE} PUBLIC -fPIC -std=c++0x)
endif()

# Commandes ====================================================================

# Copie les shaders avec l'exécutable.
add_custom_command (OUTPUT ${SHADER_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_DIR}/
        ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR}/
    DEPENDS ${SHADER}
    )

# Génération des tags.
if (${TAG_GEN} STREQUAL true)
    target_sources (${EXE} PUBLIC tags)
    add_custom_command (OUTPUT tags
        COMMAND ${TAG_GENERATOR} ${SRC} ${INC}
        COMMAND ${CMAKE_COMMAND} -E copy tags ${CMAKE_SOURCE_DIR}
        DEPENDS ${SRC} ${INC}
        )
endif()

# End message
add_custom_command (TARGET ${EXE}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "[100%] Compilation done in ${CMAKE_BUILD_TYPE} mode"
    )

# Installation =================================================================

# Paramètres la cible d'installation.
install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${EXE} DESTINATION ${EXE})
install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR} DESTINATION ${EXE})
if (UNIX)
    install (CODE "execute_process ( \
    COMMAND ${CMAKE_COMMAND} -E create_symlink \
    ${CMAKE_INSTALL_PREFIX}/${EXE}/${EXE} \
    /usr/local/bin/${EXE})
    message (\"-- Creating symlink: /usr/loca/bin/${EXE} -> ${CMAKE_INSTALL_PREFIX}/${EXE}/${EXE}\")"
    )
endif()

# Crée une cible de désinstallation.
if (UNIX)
    set (UNIX_REMOVE_LINK
            COMMAND ${CMAKE_COMMAND} -E echo "-- Removing: /usr/local/bin/${EXE}"
            COMMAND ${CMAKE_COMMAND} -E remove /usr/local/bin/${EXE}
        )
endif()
add_custom_target (uninstall
    COMMAND ${CMAKE_COMMAND} -E echo "Remove ${PROJECT_NAME} project..."
    COMMAND ${CMAKE_COMMAND} -E echo "-- Removing: ${CMAKE_INSTALL_PREFIX}/${EXE}"
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_INSTALL_PREFIX}/${EXE}
    ${UNIX_REMOVE_LINK}
    )
