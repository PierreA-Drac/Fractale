/**
 * @file MainWindow.cpp
 * @brief Fenêtre principale.
 *
 * Implémentation de la classe de la fenêtre principale.
 */

#include <QtGui/QtGui>

//#include "FractaleWindow.hpp"
#include "testglwidget.hpp"
#include "MainWindow.hpp"

MainWindow::MainWindow(const char *title) : QWidget()
{
    /* Mandelbrot (paramètres). */
    butManOGL  = new QPushButton("Afficher avec OpenGL");
    butManCAI  = new QPushButton("Afficher avec Cairo");
    coulBWMan = new QRadioButton("Afficher en noir et blanc");
    coulAllMan = new QRadioButton("Afficher en couleur");
    layPrmMan  = new QGridLayout();
    layPrmMan->addWidget(coulAllMan, 0, 0);
    layPrmMan->addWidget(coulBWMan, 0, 1);
    layPrmMan->addWidget(butManCAI, 1, 0);
    layPrmMan->addWidget(butManOGL, 1, 1);
    wgtPrmMan  = new QWidget();
    wgtPrmMan->setLayout(layPrmMan);

    /* Julia et Fatou (paramètres). */
    butJulOGL  = new QPushButton("Afficher avec OpenGL");
    butJulCAI  = new QPushButton("Afficher avec Cairo");
    coulBWJul = new QRadioButton("Afficher en noir et blanc");
    coulAllJul = new QRadioButton("Afficher en couleur");
    layPrmJul  = new QGridLayout();
    layPrmJul->addWidget(coulAllJul, 0, 0);
    layPrmJul->addWidget(coulBWJul, 0, 1);
    layPrmJul->addWidget(butJulCAI, 1, 0);
    layPrmJul->addWidget(butJulOGL, 1, 1);
    wgtPrmJul  = new QWidget();
    wgtPrmJul->setLayout(layPrmJul);

    /* Conteneur des onglets secondaires. */
    /* Mandelbrot. */
    tabsMan    = new QTabWidget();
    tabsMan->addTab(wgtPrmMan, QString::fromUtf8("Paramètres"));
    tabsMan->setTabsClosable(true);
    layTabsMan = new QVBoxLayout();
    layTabsMan->addWidget(tabsMan);
    wgtTabsMan = new QWidget();
    wgtTabsMan->setLayout(layTabsMan);
    /* Julia et Fatou. */
    tabsJul    = new QTabWidget();
    tabsJul->addTab(wgtPrmJul, QString::fromUtf8("Paramètres"));
    tabsJul->setTabsClosable(true);
    layTabsJul = new QVBoxLayout();
    layTabsJul->addWidget(tabsJul);
    wgtTabsJul = new QWidget();
    wgtTabsJul->setLayout(layTabsJul);

    /* Conteneur des onglets principaux. */
    tabsMainWin = new QTabWidget();
    tabsMainWin->addTab(wgtTabsMan, "Mandelbrot");
    tabsMainWin->addTab(wgtTabsJul, "Julia et Fatou");

    /* Fenêtre principale. */
    butQuit    = new QPushButton("Quitter");
    layMainWin = new QVBoxLayout();
    layMainWin->addWidget(tabsMainWin);
    layMainWin->addWidget(butQuit);
    this->setLayout(layMainWin);
    this->setWindowTitle(QString::fromUtf8(title));
    this->setMinimumSize(this->sizeHint());

    /* Signaux. */
    QObject::connect(butQuit,   SIGNAL(clicked()), qApp,
            SLOT(quit()));
    QObject::connect(butManOGL, SIGNAL(clicked()), this,
            SLOT(displayMandelOpenGL()));
    QObject::connect(butJulOGL, SIGNAL(clicked()), this,
            SLOT(displayJulOpenGL()));
    QObject::connect(butManCAI, SIGNAL(clicked()), this,
            SLOT(displayMandelCairo()));
    QObject::connect(butJulCAI, SIGNAL(clicked()), this,
            SLOT(displayJulCairo()));
    QObject::connect(tabsMan, SIGNAL(tabCloseRequested(int)), this,
            SLOT(closeManTab(int)));
    QObject::connect(tabsJul, SIGNAL(tabCloseRequested(int)), this,
            SLOT(closeJulTab(int)));
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F1:
            toggleFullWindow();
            break;
        case Qt::Key_F2:
            toggleFullWindowFrac();
            break;
        case Qt::Key_F3:
            detachWindowFrac();
            break;
    }
}

void MainWindow::toggleFullWindow() {
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void MainWindow::toggleFullWindowFrac() {
    /* Si on ne défini pas cette fonction ici, alors on ne va pas dans la
     * fonction "toggleFullWindow" de la fractale car elle n'a pas le focus. */
    if (FractaleWindow* ptr = getFracActive())
        ptr->toggleFullWindow();
}

void MainWindow::detachWindowFrac() {
    if (FractaleWindow* ptr = getFracActive()) {
        /* Détache la fenêtre en supprimant son lien avec son parent.
         * Déplacement minime requis pour ne pas apparaître sous la barre des
         * tâches. Affiche en mode normal (pas minimisé, pas maximisé, pas
         * plein écran). */
        ptr->setParent(nullptr);
        ptr->move(0, 60);
        ptr->showNormal();
    }
}

void MainWindow::displayMandelOpenGL()
{
    if(coulAllMan->isChecked()){
        FractaleWindow *WinFracManCol = new FractaleWindow(MANDELBROT, COLOR);
        tabsMan->addTab(WinFracManCol, "OpenGL");
        /* Pour que Qt supprime le widget si on le ferme
         * alors qu'il était détaché. */
        WinFracManCol->setAttribute(Qt::WA_DeleteOnClose);
    }
    else if(coulBWMan->isChecked()){
        FractaleWindow *WinFracManBW = new FractaleWindow(MANDELBROT, BLACK_WHITE);
        tabsMan->addTab(WinFracManBW, "OpenGL");
        /* Pour que Qt supprime le widget si on le ferme
         * alors qu'il était détaché. */
        WinFracManBW->setAttribute(Qt::WA_DeleteOnClose);
    }
    else
        QMessageBox::information(this, "Information",
            QString::fromUtf8("Choisissez les paramètres."));
    
}

void MainWindow::displayMandelCairo()
{
    QMessageBox::information(this, "Information",
            QString::fromUtf8("Fonctionnalité non-implémentée."));
}

void MainWindow::displayJulOpenGL()
{
    if(coulAllJul->isChecked()){
        FractaleWindow *WinFracJulCol = new FractaleWindow(JULIA, COLOR);
        tabsJul->addTab(WinFracJulCol, "OpenGL");
        /* Pour que Qt supprime le widget si on le ferme
         * alors qu'il était détaché. */
        WinFracJulCol->setAttribute(Qt::WA_DeleteOnClose);
    }
    else if(coulBWJul->isChecked()){
        FractaleWindow *WinFracJulBW = new FractaleWindow(JULIA, BLACK_WHITE);
        tabsJul->addTab(WinFracJulBW, "OpenGL");
        /* Pour que Qt supprime le widget si on le ferme
         * alors qu'il était détaché. */
        WinFracJulBW->setAttribute(Qt::WA_DeleteOnClose);
    }
    else
        QMessageBox::information(this, "Information",
            QString::fromUtf8("Choisissez les paramètres."));
}

void MainWindow::displayJulCairo()
{
    QMessageBox::information(this, "Information",
            QString::fromUtf8("Fonctionnalité non-implémentée."));
}

void MainWindow::closeManTab(int index)
{
    /* Index == 0 -> Onglet paramètre. */
    if (index != 0)
        tabsMan->removeTab(index);
}

void MainWindow::closeJulTab(int index)
{
    /* Index == 0 -> Onglet paramètre. */
    if (index != 0)
        tabsJul->removeTab(index);
}

FractaleWindow* MainWindow::getFracActive()
{
    /* "Dynamic_cast" renvoie "null" si le pointeur n'est pas un
     * "FractaleWindow". "isVisible" renvoie "false" si le widget n'est pas
     * visible sur l'écran (même s'il à le focus ou qu'il est actif en arrière
     * plan.) */
    FractaleWindow *ptr = nullptr;
    if (!(ptr = dynamic_cast<FractaleWindow *>(tabsMan->currentWidget()))
            || !(ptr->isVisible())) {
        if (!(ptr = dynamic_cast<FractaleWindow *>(tabsJul->currentWidget()))
                || !(ptr->isVisible())) {
            return nullptr;
        }
    }
    return ptr;
}
