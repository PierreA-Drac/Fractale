#include <QtGui/QtGui>
#include <QtOpenGL/QGLFormat>
#include <QtGui/QApplication>        // For Qt4
// #include <QtWidgets/QApplication> // For Qt5

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow wgtMainWin("Fractale (Claire BASKEVITCH & Pierre AYOUB)");
    wgtMainWin.show();
    
    return app.exec();
}
