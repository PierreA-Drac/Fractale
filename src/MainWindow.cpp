/**
 * @file MainWindow.cpp
 * @brief Fenêtre principale.
 *
 * Implémentation de la classe de la fenêtre principale.
 */

#include <QtCore/QSignalMapper>
#include <QtGui/QtGui>

#include "FractalWindow.hpp"
#include "FractalWindowOGL.hpp"
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
    tabsFrac[FractalWindow::MANDELBROT] = tabsMan;
    tabsFrac[FractalWindow::JULIA] = tabsJul;

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
    connect(butQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(tabsMan, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tabsJul, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    /* Utilisation de "QSignalMapper" pour pouvoir envoyer un argument
     * avec le signal "clicked()". */
    sigOGL = new QSignalMapper(this);
    sigCAI = new QSignalMapper(this);
    connect(butManOGL, SIGNAL(clicked()), sigOGL, SLOT(map()));
    connect(butJulOGL, SIGNAL(clicked()), sigOGL, SLOT(map()));
    connect(butManCAI, SIGNAL(clicked()), sigCAI, SLOT(map()));
    connect(butJulCAI, SIGNAL(clicked()), sigCAI, SLOT(map()));
    sigOGL->setMapping(butManOGL, FractalWindow::MANDELBROT);
    sigOGL->setMapping(butJulOGL, FractalWindow::JULIA);
    sigCAI->setMapping(butManCAI, FractalWindow::MANDELBROT);
    sigCAI->setMapping(butJulCAI, FractalWindow::JULIA);
    connect(sigOGL, SIGNAL(mapped(int)), this, SLOT(displayFrac(int)));
    connect(sigCAI, SIGNAL(mapped(int)), this, SLOT(displayFrac(int)));
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

void MainWindow::toggleFullWindow()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void MainWindow::toggleFullWindowFrac()
{
    /* Si on ne défini pas cette fonction ici, alors on ne va pas dans la
     * fonction "toggleFullWindow" de la fractale car elle n'a pas le focus. */
    if (FractalWindow* ptr = getFracActive())
        ptr->toggleFullWindow();
}

void MainWindow::detachWindowFrac()
{
    if (FractalWindow* ptr = getFracActive()) {
        /* Détache la fenêtre en supprimant son lien avec son parent.
         * Déplacement minime requis pour ne pas apparaître sous la barre des
         * tâches. Affiche en mode normal (pas minimisé, pas maximisé, pas
         * plein écran). */
        ptr->setParent(nullptr);
        ptr->move(0, 60);
        ptr->showNormal();
    }
}

void MainWindow::displayFrac(int fType)
{
    FractalWindow *wgtWinFrac = nullptr;
    /* Si l'émetteur du signal est un bouton concernant OpenGL. */
    if (sender() == sigOGL)
        wgtWinFrac = new FractalWindowOGL(
                static_cast<FractalWindow::type>(fType), COLOR);
    /* Si l'émetteur du signal est un bouton concernant Cairo. */
    else if (sender() == sigCAI) {
        QMessageBox::information(this, "Information",
                QString::fromUtf8("Bibliothèque Cairo bientôt disponible."));
        return;
    }
    tabsFrac[fType]->addTab(wgtWinFrac, wgtWinFrac->getRenderStr());
    /* Pour que Qt supprime le widget si on le ferme
     * alors qu'il était détaché. */
    wgtWinFrac->setAttribute(Qt::WA_DeleteOnClose);
}

    //~ if(coulAllMan->isChecked()){
        //~ FractaleWindow *WinFracManCol = new FractaleWindow(MANDELBROT, COLOR);
        //~ tabsMan->addTab(WinFracManCol, "OpenGL");
        //~ /* Pour que Qt supprime le widget si on le ferme
         //~ * alors qu'il était détaché. */
        //~ WinFracManCol->setAttribute(Qt::WA_DeleteOnClose);
    //~ }
    //~ else if(coulBWMan->isChecked()){
        //~ FractaleWindow *WinFracManBW = new FractaleWindow(MANDELBROT, BLACK_WHITE);
        //~ tabsMan->addTab(WinFracManBW, "OpenGL");
        //~ /* Pour que Qt supprime le widget si on le ferme
         //~ * alors qu'il était détaché. */
        //~ WinFracManBW->setAttribute(Qt::WA_DeleteOnClose);
    //~ }
    //~ else
        //~ QMessageBox::information(this, "Information",
            //~ QString::fromUtf8("Choisissez les paramètres."));
    
//~ }

//~ void MainWindow::displayMandelCairo()
//~ {
    //~ QMessageBox::information(this, "Information",
            //~ QString::fromUtf8("Fonctionnalité non-implémentée."));
//~ }

//~ void MainWindow::displayJulOpenGL()
//~ {
    //~ if(coulAllJul->isChecked()){
        //~ FractaleWindow *WinFracJulCol = new FractaleWindow(JULIA, COLOR);
        //~ tabsJul->addTab(WinFracJulCol, "OpenGL");
        //~ /* Pour que Qt supprime le widget si on le ferme
         //~ * alors qu'il était détaché. */
        //~ WinFracJulCol->setAttribute(Qt::WA_DeleteOnClose);
    //~ }
    //~ else if(coulBWJul->isChecked()){
        //~ FractaleWindow *WinFracJulBW = new FractaleWindow(JULIA, BLACK_WHITE);
        //~ tabsJul->addTab(WinFracJulBW, "OpenGL");
        //~ /* Pour que Qt supprime le widget si on le ferme
         //~ * alors qu'il était détaché. */
        //~ WinFracJulBW->setAttribute(Qt::WA_DeleteOnClose);
    //~ }
    //~ else
        //~ QMessageBox::information(this, "Information",
            //~ QString::fromUtf8("Choisissez les paramètres."));
//~ }

//~ void MainWindow::displayJulCairo()
//~ {
    //~ QMessageBox::information(this, "Information",
            //~ QString::fromUtf8("Fonctionnalité non-implémentée."));
//~ }

//~ void MainWindow::closeManTab(int index)
//~ {
    //~ /* Index == 0 -> Onglet paramètre. */
    //~ if (index != 0)
        //~ tabsMan->removeTab(index);
//~ }

//~ void MainWindow::closeJulTab(int index)
//~ >>>>>>> dev-opengl
void MainWindow::closeTab(int index)
{
    /* Index == 0 => Onglet paramètre. */
    if (index != 0)
        ((QTabWidget *)sender())->removeTab(index);
}

FractalWindow* MainWindow::getFracActive()
{
    /* "Dynamic_cast" renvoie "null" si le pointeur n'est pas un
     * "FractaleWindow". "isVisible" renvoie "false" si le widget n'est pas
     * visible sur l'écran (même s'il à le focus ou qu'il est actif en arrière
     * plan.) */
    FractalWindow *ptr = nullptr;
    if (!(ptr = dynamic_cast<FractalWindow *>(tabsMan->currentWidget()))
            || !(ptr->isVisible())) {
        if (!(ptr = dynamic_cast<FractalWindow *>(tabsJul->currentWidget()))
                || !(ptr->isVisible())) {
            return nullptr;
        }
    }
    return ptr;
}
