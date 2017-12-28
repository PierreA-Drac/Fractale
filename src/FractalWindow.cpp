#include "MainWindow.hpp"

#include "FractalWindow.hpp"

FractalWindow::FractalWindow(QWidget *parent, const char *name,
        int framesPerSecond) : QWidget(parent)
{
    /* Titre de la fenêtre. */
    setWindowTitle(QString::fromUtf8(name));

    /* Gestion du nombre d'image par seconde. */
    if (framesPerSecond == 0)
        t_Timer = NULL;
    else {
        int seconde = 1000; /* 1000 ms. */
        int timerInterval = seconde / framesPerSecond;
        /* Création du timer, connexion entre le signal "timeout()" et le slot
         * "updateWin()", démarrage du timer. */
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(updateWin()));
        t_Timer->start(timerInterval);
    }
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
