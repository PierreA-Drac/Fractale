#include <QtGui/QtGui>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow *wgtMainWin = new MainWindow("Fractale "
            "(Claire BASKEVITCH & Pierre AYOUB)");
    wgtMainWin->show();

    return app.exec();
}
