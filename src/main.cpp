#include <QtGui/QApplication>
#include <QtGui/QPushButton>

#include "FractaleWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton button("Hello World !");
    button.show();
    FractaleWindow Frac;
    Frac.show();
    return app.exec();
}
