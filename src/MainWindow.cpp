/**
 * @file MainWindow.cpp
 * @brief Fenêtre principale.
 *
 * Implémentation de la classe de la fenêtre principale.
 */
#include <QtGui/QtGui>

#include "FractaleWindow.hpp"

#include "MainWindow.hpp"

MainWindow::MainWindow(const char *title) : QWidget()
{
    /* Mandelbrot (paramètres). */
    butManOGL  = new QPushButton("Afficher avec OpenGL");
    butManCAI  = new QPushButton("Afficher avec Cairo");
    layPrmMan  = new QGridLayout();
    layPrmMan->addWidget(butManCAI, 0, 0);
    layPrmMan->addWidget(butManOGL, 0, 1);
    wgtPrmMan  = new QWidget();
    wgtPrmMan->setLayout(layPrmMan);

    /* Julia et Fatou (paramètres). */
    butJulOGL  = new QPushButton("Afficher avec OpenGL");
    butJulCAI  = new QPushButton("Afficher avec Cairo");
    layPrmJul  = new QGridLayout();
    layPrmJul->addWidget(butJulCAI, 0, 0);
    layPrmJul->addWidget(butJulOGL, 0, 1);
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
    QObject::connect(butManCAI, SIGNAL(clicked()), this,
            SLOT(displayMandelCairo()));
    QObject::connect(butJulCAI, SIGNAL(clicked()), this,
            SLOT(displayJulCairo()));
    QObject::connect(butManOGL, SIGNAL(clicked()), this,
            SLOT(displayMandelOpenGL()));
    QObject::connect(butJulOGL, SIGNAL(clicked()), this,
            SLOT(displayJulOpenGL()));
    QObject::connect(tabsMan, SIGNAL(tabCloseRequested(int)), this,
            SLOT(closeManTab(int)));
    QObject::connect(tabsJul, SIGNAL(tabCloseRequested(int)), this,
            SLOT(closeJulTab(int)));
}

void MainWindow::displayMandelOpenGL()
{
    FractaleWindow *wgtWinFrac = new FractaleWindow();
    tabsMan->addTab(wgtWinFrac, "OpenGL");
}

void MainWindow::displayMandelCairo()
{
    QMessageBox::information(this, "Information",
            QString::fromUtf8("Fonctionnalité non-implémentée."));
}

void MainWindow::displayJulOpenGL()
{
    QMessageBox::information(this, "Information",
            QString::fromUtf8("Fonctionnalité non-implémentée."));
}

void MainWindow::displayJulCairo()
{
    QMessageBox::information(this, "Information",
            QString::fromUtf8("Fonctionnalité non-implémentée."));
}

void MainWindow::closeManTab(int index)
{
    if (index != 0)
        tabsMan->removeTab(index);
}

void MainWindow::closeJulTab(int index)
{
    if (index != 0)
        tabsMan->removeTab(index);
}
