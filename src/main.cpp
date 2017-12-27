#include "testglwidget.hpp"
#include <QtGui/QtGui>
#include <QtOpenGL/QGLFormat>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow wgtMainWin("Fractale (Claire BASKEVITCH & Pierre AYOUB)");
    wgtMainWin.show();
    
    return app.exec();
}
