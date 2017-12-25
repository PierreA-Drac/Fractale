#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QtGui>

#include "FractaleWindow.hpp"

/** Nombre maximum d'onglets ouverts pour un type de fractale. */
#define TAB_MAX 5

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow(const char *title = "Fenêtre");

        public slots:
        void displayMandelOpenGL();
        void displayMandelCairo();
        void displayJulOpenGL();
        void displayJulCairo();
        void closeManTab(int index);
        void closeJulTab(int index);

    private:
        /* Mandelbrot. */
        QPushButton *butManOGL;
        QPushButton *butManCAI;
        QGridLayout *layPrmMan;
        QWidget *wgtPrmMan;
        QVBoxLayout *layTabsMan;
        QWidget *wgtTabsMan;

        /* Julia et Fatou. */
        QPushButton *butJulOGL;
        QPushButton *butJulCAI;
        QGridLayout *layPrmJul;
        QWidget *wgtPrmJul;
        QVBoxLayout *layTabsJul;
        QWidget *wgtTabsJul;

        /* Conteneur des onglets secondaires. */
        QTabWidget *tabsMan;
        QTabWidget *tabsJul;

        /* Conteneur des onglets principaux. */
        QTabWidget *tabsMainWin;

        /* Fenêtre principale. */
        QVBoxLayout *layMainWin;
        QPushButton *butQuit;
};

#endif /* ifndef MAINWINDOW_H */
