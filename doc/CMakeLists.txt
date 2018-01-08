# Recherche de Doxygen.
find_package (Doxygen)

# Si Doxygen est trouvé, on génère la documentation, sinon, on affiche un
# message d'erreur.
if (NOT DOXYGEN_FOUND)
    message ("Doxygen not found, documentation will not be generate !")
else ()
    # Crée le fichier Doxyfile à partir de Doxyfile.in avec les variables CMake
    # remplacés par leur valeur respective.
    configure_file (Doxyfile.in Doxyfile)

    # Variables
    set (DOXYGEN_INTPUT ${CMAKE_BINARY_DIR}/${DOC_PATH}Doxyfile)
    set (DOXYGEN_OUTPUT ${APIDOC_DIR}/html/index.html)

    # Si compilation en mode Release, alors la documentation sera générée
    # automatiquement lorsque l'on fait make.
    # Si on est en mode debug, alors les warnings seront affichés s'il y en a.
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set (MODE ALL)
        if (WIN32)
            set (OUTPUT > nul)
        elseif (UNIX)
            set (OUTPUT > /dev/null)
        endif()
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND UNIX)
        set (OUTPUT | grep \"warning\" | less -RmN)
    endif()

    # Cible de génération de la documentation.
    add_custom_target (doc ${MODE}
        COMMAND ${CMAKE_COMMAND} -E echo "[ 50%] Building API documentation"
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INTPUT} ${OUTPUT}
        )

    # Installation de la documentation.
    install (DIRECTORY ${CMAKE_BINARY_DIR}/${DOC_PATH}html
        DESTINATION share/doc/${CMAKE_CURRENT_PROJECT_NAME})
endif()
