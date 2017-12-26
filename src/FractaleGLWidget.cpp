#include "MainWindow.hpp"

#include "FractaleGLWidget.hpp"

FractaleGLWidget::FractaleGLWidget(int framesPerSecond, QWidget *parent, const
        char *name) : QGLWidget(parent)
{
    /* Titre de la fenêtre. */
    setWindowTitle(QString::fromUtf8(name));

    /* Calcul du temps entre deux images à afficher. */
    if (framesPerSecond == 0)
        t_Timer = NULL;
    else {
        int seconde = 1000; // 1000 ms
        int timerInterval = seconde / framesPerSecond;
        /* Création du timer, connexion entre le signal "timeout()" et le slot
         * personnalisé "timeOutSlot()", démarrage du timer. */
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start(timerInterval);
    }
}

void FractaleGLWidget::keyPressEvent(QKeyEvent *keyEvent)
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

void FractaleGLWidget::toggleFullWindow()
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

void FractaleGLWidget::timeOutSlot() {
    updateGL();
}
