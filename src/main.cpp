#include "testglwidget.hpp"
#include <QtGui/QtGui>
#include <QtOpenGL/QGLFormat>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow wgtMainWin("Fractale (Claire BASKEVITCH & Pierre AYOUB)");
    wgtMainWin.show();
    
    
// Specify an OpenGL 3.3 format using the Core profile.
 // That is, no old-school fixed pipeline functionality
 QGLFormat glFormat;
 glFormat.setVersion( 3, 3 );
 glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
 glFormat.setSampleBuffers( true );

// Create a GLWidget requesting our format
 GLWidget w( glFormat );
 w.show();

    return app.exec();
}
