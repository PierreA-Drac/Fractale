#include "FractaleGLWidget.hpp"

FractaleGLWidget::FractaleGLWidget(int framesPerSecond, QWidget *parent, char
        *name) : QGLWidget(parent)
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

    /* Initialiation en mode fenêtré. */
    b_Fullscreen = false;
}

void FractaleGLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F1:
            toggleFullWindow();
            break;
    }
}

void FractaleGLWidget::toggleFullWindow()
{
    if(b_Fullscreen)
    {
        showNormal();
        b_Fullscreen = false;
    }
    else
    {
        showFullScreen();
        b_Fullscreen = true;
    }
}

void FractaleGLWidget::timeOutSlot() {
    updateGL();
}
