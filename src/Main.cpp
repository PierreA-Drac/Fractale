/**
 * @file Main.cpp
 * @brief Programme principale.
 *
 * Lance le programme.
 */

#include <QtGui/QApplication>        // For Qt4
// #include <QtWidgets/QApplication> // For Qt5

#include "MainWindow.hpp"

/**
 * @brief Main
 * @param argc Nombre d'argument.
 * @param argv Tableau des arguments.
 * @return 0 si le programme s'est déroulé sans erreur, 1 sinon.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow wgtMainWin("Fractale (Claire BASKEVITCH & Pierre AYOUB)");
    wgtMainWin.show();
    
    return app.exec();
}
