# Recherche de Latex.
find_package (LATEX COMPONENTS PDFLATEX)

# Si Latex est trouvé, on génère le rapport, sinon, on affiche un message
# d'erreur.
if (NOT LATEX_FOUND)
    message ("-- Report will NOT be generated")
else ()
    # Variables
    set (REPORT_NAME Report)
    set (LATEX_INTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${REPORT_NAME}.tex)
    set (LATEX_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${REPORT_NAME}.pdf)

    # Si compilation en mode Release, alors le rapport sera généré
    # automatiquement lorsque l'on fait make.
    # Si on est en mode debug, alors les détails seront affichés.
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set (MODE ALL)
        if (WIN32)
            set (OUTPUT > nul)
        elseif (UNIX)
            set (OUTPUT > /dev/null)
        endif()
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND UNIX)
        set (OUTPUT | less -RmN)
    endif()

    # Cible de génération du rapport.
    add_custom_target (report ${MODE}
        COMMAND ${CMAKE_COMMAND} -E echo "[ 50%] Building report"
        COMMAND ${PDFLATEX_COMPILER} ${LATEX_INTPUT} ${OUTPUT}
        )

    # Installation du rapport.
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${REPORT_NAME}.pdf
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${EXE}/${REPORT_PATH}
        OPTIONAL)
endif()
