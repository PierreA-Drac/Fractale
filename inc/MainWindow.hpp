/**
 * @file MainWindow.hpp
 * @brief Fenêtre principale.
 *
 * Header de la classe de la fenêtre principale.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QtGui>

#include "FractaleWindow.hpp"

/** Nombre maximum d'onglets ouverts pour un type de fractale. */
#define TAB_MAX 5

/**
 * @brief Fenêtre principale.
 *
 * La fenêtre principale contient l'ensemble du programme. Elle gère
 * l'interaction avec l'utilisateur par les boutons, la souris et le clavier. De
 * plus, elle gère l'affichage pendant tout le long du programme.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        /**
         * @brief Constructeur
         * @param title Titre de la fenêtre. Si non spécifié, "Fenêtre" sera le
         * titre par défaut.
         *
         * Constructeur de la fenêtre principale. Une fois construite, il ne
         * reste qu'à l'afficher avec "show()".
         */
        MainWindow(const char *title = "Fenêtre");

    public slots:
        /**
         * @brief Affiche Mandelbrot avec OpenGL
         *
         * Affiche la fractale de Mandelbrot en ouvrant un nouvel onglet,
         * en utilisant la bibliothèque de rendu OpenGL.
         */
        void displayMandelOpenGL();
        /**
         * @brief Affiche Mandelbrot avec Cairo
         *
         * Affiche la fractale de Mandelbrot en ouvrant un nouvel onglet,
         * en utilisant la bibliothèque de rendu Cairo.
         */
        void displayMandelCairo();
        /**
         * @brief Affiche Julia et Fatou avec OpenGL
         *
         * Affiche la fractale de Julia et Fatou en ouvrant un nouvel onglet,
         * en utilisant la bibliothèque de rendu OpenGL.
         */
        void displayJulOpenGL();
        /**
         * @brief Affiche Julia et Fatou avec Cairo
         *
         * Affiche la fractale de Julia et Fatou en ouvrant un nouvel onglet,
         * en utilisant la bibliothèque de rendu Cairo.
         */
        void displayJulCairo();
        /**
         * @brief Supprime un onglet
         * @param index Numéro de l'onglet à fermer.
         *
         * Ferme et supprimme un onglet contenu dans le conteneur d'onglet
         * "tabsMan" de Mandelbrot.
         */
        void closeManTab(int index);
        /**
         * @brief Supprime un onglet
         * @param index Numéro de l'onglet à fermer.
         *
         * Ferme et supprimme un onglet contenu dans le conteneur d'onglet
         * "tabsJul" de Julia et Fatou.
         */
        void closeJulTab(int index);

    private:
        /**
         * Bouton pour lancer l'affichage d'une fractale de Mandelbrot avec
         * OpenGL.
         */
        QPushButton *butManOGL;
        /**
         * Bouton pour lancer l'affichage d'une fractale de Mandelbrot avec
         * Cairo.
         */
        QPushButton *butManCAI;
        /**
         * Layout contenant les widgets des paramètres de la fractale de
         * Mandelbrot.
         */
        QGridLayout *layPrmMan;
        /**
         * Widget contenant le layout des paramètres de la fractale de
         * Mandelbrot.
         */
        QWidget *wgtPrmMan;

        /**
         * Bouton pour lancer l'affichage d'une fractale de Julia et Fatou avec
         * OpenGL.
         */
        QPushButton *butJulOGL;
        /**
         * Bouton pour lancer l'affichage d'une fractale de Julia et Fatou avec
         * Cairo.
         */
        QPushButton *butJulCAI;
        /**
         * Layout contenant les widgets des paramètres de la fractale de
         * Julia et Fatou.
         */
        QGridLayout *layPrmJul;
        /**
         * Widget contenant le layout des paramètres de la fractale de
         * Julia et Fatou.
         */
        QWidget *wgtPrmJul;

        /**
         * Conteneur des onglets des fractales de Mandelbrot.
         */
        QTabWidget *tabsMan;
        /**
         * Layout contenant le conteneur des onglets des fractales de
         * Mandelbrot.
         */
        QVBoxLayout *layTabsMan;
        /**
         * Widget qui contient le layout pour l'affichage des onglets des
         * fractales de Mandelbrot.
         */
        QWidget *wgtTabsMan;
        /**
         * Conteneur des onglets des fractales de Julia et Fatou.
         */
        QTabWidget *tabsJul;
        /**
         * Layout contenant le conteneur des onglets des fractales de
         * Julia et Fatou.
         */
        QVBoxLayout *layTabsJul;
        /**
         * Widget qui contient le layout pour l'affichage des onglets des
         * fractales de Julia et Fatou.
         */
        QWidget *wgtTabsJul;

        /** Conteneur des onglets de la fenêtre principale. */
        QTabWidget *tabsMainWin;

        /** Layout de la fenêtre principale. */
        QVBoxLayout *layMainWin;
        /** Bouton pour quitter l'application dans la fenêtre principale. */
        QPushButton *butQuit;
};

#endif /* ifndef MAINWINDOW_H */
