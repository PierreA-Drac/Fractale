/**
 * @file FractalWindow.cpp
 * @brief Fenêtre d'une fractale.
 *
 * Implémentation de la classe de la fenêtre d'une fractale.
 */

#include "FractalWindow.hpp"

#include <cstdio>

#include "MainWindow.hpp"

/** Taille maximum de titre de la fenêtre. */
#define TITLE_LENGHT 60

/** Initialisation des variables statiques. */
const int FractalWindow::nMax = 325;
const float FractalWindow::z0 = 0;
const float FractalWindow::xMin = -2.0;
const float FractalWindow::xMax = 1.0;
const float FractalWindow::yMin = -1.0;
const float FractalWindow::yMax = 1.0;

FractalWindow::FractalWindow(type t_fracType, render t_fracRender, float t_zMax,
        float t_cReal, float t_cImg, bool t_coul, QWidget *parent,
        int framesPerSecond) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    n(-(2 * framesPerSecond)), c(QVector2D(t_cReal, t_cImg)), zMax(t_zMax),
    coul(t_coul), fracType(t_fracType), fracRender(t_fracRender)
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
        case Qt::Key_Plus:
            zoomUp();
            break;
        case Qt::Key_Minus:
            zoomDown();
            break;
        case Qt::Key_Up:
            moveUp();
            break;
        case Qt::Key_Down:
            moveDown();
            break;
        case Qt::Key_Right:
            moveRight();
            break;
        case Qt::Key_Left:
            moveLeft();
            break;
        /* Passe le relais au parent pour gérer le clavier. */
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
    /* Si le widget possède un parent, il faut changer les flags de du widget
     * pour pouvoir le passer temporairement en tant que fenêtre et l'afficher
     * en plein écran. */
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
