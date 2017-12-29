#include <cstdio>

#include "MainWindow.hpp"

#include "FractalWindow.hpp"

#define TITLE_LENGHT 60

FractalWindow::FractalWindow(type t_fracType, render t_fracRender, QWidget
        *parent, int framesPerSecond) :
    QGLWidget(parent), fracType(t_fracType), fracRender(t_fracRender)
{
    /* Titre de la fenêtre. */
    char title[TITLE_LENGHT] = {0};
    snprintf(title, TITLE_LENGHT, "Fractale de %s rendu avec %s",
            typeStr[fracType], renderStr[fracRender]);
    setWindowTitle(QString::fromUtf8(title));

    /* Gestion du nombre d'image par seconde. */
    if (framesPerSecond == 0)
        timer = NULL;
    else {
        int seconde = 1000; /* 1000 ms. */
        int timerInterval = seconde / framesPerSecond;
        /* Création du timer, connexion entre le signal "timeout()" et le slot
         * "updateWin()", démarrage du timer. */
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateWin()));
        timer->start(timerInterval);
    }
}

FractalWindow::~FractalWindow()
{
    delete timer;
}

void FractalWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F2:
            toggleFullWindow();
            break;
        default:
            {
                if (MainWindow *ptr = (MainWindow *)parentWidget())
                    ptr->keyPressEvent(keyEvent);
                break;
            }
    }
}

void FractalWindow::toggleFullWindow()
{
    if (isFullScreen()) {
        if (parentWidget())
            setWindowFlags(windowFlags() & ~Qt::Window);
        showNormal();
    }
    else {
        if (parentWidget())
            setWindowFlags(windowFlags() | Qt::Window);
        showFullScreen();
    }
}

const char* FractalWindow::getRenderStr() const
{
    return renderStr[fracRender];
}
